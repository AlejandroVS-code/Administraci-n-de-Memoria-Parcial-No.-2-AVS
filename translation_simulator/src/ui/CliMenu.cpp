/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Implementacion de CliMenu para Implementacion 2
*/
#include "ui/CliMenu.h"
#include "exceptions/TranslatorException.h"
#include "algorithms/PagingStrategy.h"
#include "algorithms/SegmentationStrategy.h"
#include <iostream> //Libreria para leer y escribir por consola
#include <fstream> //Libreria para escribir el archivo de salida
#include <sstream> //Libreria para construir el contenido antes de guardarlo y mostrarlo

CliMenu::CliMenu()
{
    this->translator = nullptr;
}

CliMenu::CliMenu(MemoryTranslator* translator)
{
    this->translator = translator;
}

CliMenu::~CliMenu()
{
    
}

void CliMenu::showMenu() const
{
    std::cout << "\n===== SIMULADOR DE TRADUCCION DE DIRECCIONES =====" << std::endl;
    std::cout << "1. Cargar mapeo de pagina manualmente" << std::endl;
    std::cout << "2. Cargar segmento manualmente" << std::endl;
    std::cout << "3. Traducir una direccion manualmente" << std::endl;
    std::cout << "4. Cargar y ejecutar archivo de entrada" << std::endl;
    std::cout << "5. Ver estado (marcos, tabla de paginas, tabla de segmentos)" << std::endl;
    std::cout << "6. Cambiar estrategia de traduccion" << std::endl;
    std::cout << "7. Salir" << std::endl;
    std::cout << "Seleccione una opcion: ";
}

void CliMenu::requestPageMapping()
{
    int pageNumber = 0;
    int frameNumber = 0;
    std::cout << "Ingrese el numero de pagina: ";
    std::cin >> pageNumber;
    std::cout << "Ingrese el numero de marco: ";
    std::cin >> frameNumber;

    try
    {
        this->translator->loadPageMapping(pageNumber, frameNumber);
        std::cout << "Mapeo de pagina creado correctamente." << std::endl;
    }
    catch (const TranslatorException& exceptionCaught)
    {
        std::cout << "Error al mapear la pagina: " << exceptionCaught.what() << std::endl;
    }
}

void CliMenu::requestSegmentMapping()
{
    int segmentNumber = 0;
    int baseAddress = 0;
    int limit = 0;
    std::cout << "Ingrese el numero de segmento: ";
    std::cin >> segmentNumber;
    std::cout << "Ingrese la direccion base: ";
    std::cin >> baseAddress;
    std::cout << "Ingrese el limite: ";
    std::cin >> limit;

    try
    {
        this->translator->loadSegment(segmentNumber, baseAddress, limit);
        std::cout << "Segmento cargado correctamente." << std::endl;
    }
    catch (const TranslatorException& exceptionCaught)
    {
        std::cout << "Error al cargar el segmento: " << exceptionCaught.what() << std::endl;
    }
}

void CliMenu::requestAddressTranslation()
{
    int rawValue = 0;
    std::cout << "Ingrese la direccion virtual a traducir: ";
    std::cin >> rawValue;

    if (!VirtualAddress::isValidData(rawValue))
    {
        std::cout << "Direccion invalida, debe ser mayor o igual a cero." << std::endl;
        return;
    }

    VirtualAddress virtualAddress(rawValue);
    try
    {
        PhysicalAddress physicalAddress = this->translator->translateAddress(virtualAddress);
        std::cout << "Direccion fisica resultante: " << physicalAddress.getValue() << std::endl;
    }
    catch (const TranslatorException& exceptionCaught)
    {
        std::cout << "Error al traducir la direccion: " << exceptionCaught.what() << std::endl;
    }
}

void CliMenu::loadAndRunFile()
{
    std::string fileName;
    std::cout << "Ingrese el nombre del archivo (debe estar en data/translation/): ";
    std::cin >> fileName;

    std::string fullPath = "data/translation/" + fileName;

    std::vector<TranslationCommand> commands;
    try
    {
        commands = this->fileReader.readCommands(fullPath);
    }
    catch (const TranslatorException& exceptionCaught)
    {
        std::cout << "Error al leer el archivo: " << exceptionCaught.what() << std::endl;
        return;
    }

    std::stringstream sessionLog;
    sessionLog << "RESULTADOS DE LA EJECUCION: " << fileName << std::endl;

    for (size_t i = 0; i < commands.size(); i++)
    {
        const TranslationCommand& currentCommand = commands.at(i);

        if (currentCommand.getType() == TranslationCommandType::MAP_PAGE)
        {
            try
            {
                this->translator->loadPageMapping(currentCommand.getFirstValue(), currentCommand.getSecondValue());
                sessionLog << "Mapeo cargado: pagina " << currentCommand.getFirstValue() << " -> marco " << currentCommand.getSecondValue() << std::endl;
            }
            catch (const TranslatorException& exceptionCaught)
            {
                sessionLog << "Error al mapear pagina " << currentCommand.getFirstValue() << ": " << exceptionCaught.what() << std::endl;
            }
        }
        else if (currentCommand.getType() == TranslationCommandType::MAP_SEGMENT)
        {
            try
            {
                this->translator->loadSegment(currentCommand.getFirstValue(), currentCommand.getSecondValue(), currentCommand.getThirdValue());
                sessionLog << "Segmento cargado: " << currentCommand.getFirstValue() << " base=" << currentCommand.getSecondValue() << " limite=" << currentCommand.getThirdValue() << std::endl;
            }
            catch (const TranslatorException& exceptionCaught)
            {
                sessionLog << "Error al cargar segmento " << currentCommand.getFirstValue() << ": " << exceptionCaught.what() << std::endl;
            }
        }
        else
        {
            VirtualAddress virtualAddress(currentCommand.getFirstValue());
            try
            {
                PhysicalAddress physicalAddress = this->translator->translateAddress(virtualAddress);
                sessionLog << "Traduccion: VA=" << virtualAddress.getValue() << " -> PA=" << physicalAddress.getValue() << std::endl;
            }
            catch (const TranslatorException& exceptionCaught)
            {
                sessionLog << "Error al traducir VA=" << virtualAddress.getValue() << ": " << exceptionCaught.what() << std::endl;
            }
        }
    }

    std::cout << "Ejecucion del archivo terminada." << std::endl;
    this->writeOutputFile(fileName, sessionLog.str());
}

void CliMenu::showState() const
{
    std::cout << "\n----- ESTADO DE LA MEMORIA FISICA -----" << std::endl;
    const std::vector<Frame>& frames = this->translator->getFrames();
    for (size_t i = 0; i < frames.size(); i++)
    {
        const Frame& currentFrame = frames.at(i);
        std::cout << "Marco " << currentFrame.getFrameNumber() << " | Estado: " << (currentFrame.isFree() ? "Libre" : "Ocupado") << std::endl;
    }

    std::cout << "\n----- TABLA DE PAGINAS -----" << std::endl;
    const std::vector<Page>& pages = this->translator->getPageTable().getEntries();
    for (size_t i = 0; i < pages.size(); i++)
    {
        const Page& currentPage = pages.at(i);
        std::cout << "Pagina " << currentPage.getPageNumber() << " -> Marco " << currentPage.getFrameNumber() << " | Valida: " << (currentPage.isValid() ? "Si" : "No") << std::endl;
    }

    std::cout << "\n----- TABLA DE SEGMENTOS -----" << std::endl;
    const std::vector<Segment>& segments = this->translator->getSegmentTable().getEntries();
    for (size_t i = 0; i < segments.size(); i++)
    {
        const Segment& currentSegment = segments.at(i);
        std::cout << "Segmento " << currentSegment.getSegmentNumber() << " | Base: " << currentSegment.getBaseAddress() << " | Limite: " << currentSegment.getLimit() << std::endl;
    }
}

void CliMenu::changeStrategy()
{
    std::cout << "Seleccione la nueva estrategia:" << std::endl;
    std::cout << "1. Paginacion" << std::endl;
    std::cout << "2. Segmentacion" << std::endl;
    std::cout << "Opcion: ";

    int option = 0;
    std::cin >> option;

    if (option == 1)
    {
        int pageSize = 0;
        std::cout << "Ingrese el tamano de pagina: ";
        std::cin >> pageSize;
        this->translator->setStrategy(new PagingStrategy(pageSize));
        std::cout << "Estrategia cambiada a Paginacion." << std::endl;
    }
    else if (option == 2)
    {
        int maxSegmentSize = 0;
        std::cout << "Ingrese el tamano maximo de direccionamiento de segmento: ";
        std::cin >> maxSegmentSize;
        this->translator->setStrategy(new SegmentationStrategy(maxSegmentSize));
        std::cout << "Estrategia cambiada a Segmentacion." << std::endl;
    }
    else
    {
        std::cout << "Opcion invalida, no se cambio la estrategia." << std::endl;
    }
}

void CliMenu::writeOutputFile(const std::string& inputFileName, const std::string& content) const
{
    std::string baseName = inputFileName;
    size_t extensionPosition = baseName.rfind(".txt");
    if (extensionPosition != std::string::npos && extensionPosition == baseName.size() - 4)
    {
        baseName = baseName.substr(0, extensionPosition);
    }

    std::string outputPath = "translation_simulator/tests/" + baseName + "_output.txt";

    std::ofstream outputFile(outputPath);
    if (!outputFile.is_open())
    {
        std::cout << "No se pudo crear el archivo de salida: " << outputPath << std::endl;
        return;
    }

    outputFile << content;
    outputFile.close();

    std::cout << "\n----- RESULTADO GUARDADO EN: " << outputPath << " -----" << std::endl;
    std::cout << content;
}

void CliMenu::run()
{
    int option = 0;
    while (option != 7)
    {
        this->showMenu();
        std::cin >> option;

        if (option == 1)
        {
            this->requestPageMapping();
        }
        else if (option == 2)
        {
            this->requestSegmentMapping();
        }
        else if (option == 3)
        {
            this->requestAddressTranslation();
        }
        else if (option == 4)
        {
            this->loadAndRunFile();
        }
        else if (option == 5)
        {
            this->showState();
        }
        else if (option == 6)
        {
            this->changeStrategy();
        }
        else if (option != 7)
        {
            std::cout << "Opcion invalida." << std::endl;
        }
    }
    std::cout << "Saliendo del simulador..." << std::endl;
}