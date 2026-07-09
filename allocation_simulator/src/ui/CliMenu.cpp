/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 08/07/2026
   Version: 1.0
   Licencia: Uso academico, Universidad del Valle
   Descripcion: Implementacion de CliMenu
*/
#include "../../include/ui/CliMenu.h"
#include "../../include/exceptions/SimulatorException.h"
#include "../../include/algorithms/FirstFit.h"
#include "../../include/algorithms/BestFit.h"
#include "../../include/algorithms/WorstFit.h"
#include <iostream> //Libreria para leer y escribir por consola
#include <fstream> //Libreria para escribir el archivo de salida

CliMenu::CliMenu()
{
    this->manager = nullptr;
}

CliMenu::CliMenu(MemoryManager* manager)
{
    this->manager = manager;
}

CliMenu::~CliMenu()
{
    //No hago delete de manager porque este menu no es dueno de ese objeto
}

void CliMenu::showMenu() const
{
    std::cout << "\n===== SIMULADOR DE ASIGNACION DE MEMORIA =====" << std::endl;
    std::cout << "1. Crear proceso manualmente" << std::endl;
    std::cout << "2. Liberar proceso manualmente" << std::endl;
    std::cout << "3. Cargar y ejecutar archivo de entrada" << std::endl;
    std::cout << "4. Ver estado de la memoria" << std::endl;
    std::cout << "5. Cambiar estrategia de asignacion" << std::endl;
    std::cout << "6. Salir" << std::endl;
    std::cout << "Seleccione una opcion: ";
}

void CliMenu::requestProcessCreation()
{
    int id = 0;
    std::string name;
    int requestedSize = 0;

    std::cout << "Ingrese el id del proceso: ";
    std::cin >> id;
    std::cout << "Ingrese el nombre del proceso: ";
    std::cin >> name;
    std::cout << "Ingrese el tamano solicitado: ";
    std::cin >> requestedSize;

    if (!Process::isValidData(requestedSize))
    {
        std::cout << "Tamano invalido, debe ser mayor que cero. Se cancela la creacion." << std::endl;
        return;
    }

    Process newProcess(id, name, requestedSize);
    try
    {
        this->manager->allocateProcess(newProcess);
        std::cout << "Proceso creado y asignado correctamente." << std::endl;
    }
    catch (const SimulatorException& exceptionCaught)
    {
        std::cout << "Error al asignar el proceso: " << exceptionCaught.what() << std::endl;
    }
}

void CliMenu::requestProcessRelease()
{
    int id = 0;
    std::cout << "Ingrese el id del proceso a liberar: ";
    std::cin >> id;

    try
    {
        this->manager->releaseProcess(id);
        std::cout << "Proceso liberado correctamente." << std::endl;
    }
    catch (const SimulatorException& exceptionCaught)
    {
        std::cout << "Error al liberar el proceso: " << exceptionCaught.what() << std::endl;
    }
}

void CliMenu::showMemoryState() const
{
    const std::vector<MemoryBlock>& blocks = this->manager->getBlocks();
    std::cout << "\n----- ESTADO DE LA MEMORIA -----" << std::endl;
    for (size_t i = 0; i < blocks.size(); i++)
    {
        const MemoryBlock& currentBlock = blocks.at(i);
        std::cout << "Bloque " << i << " | Inicio: " << currentBlock.getStartAddress();
        std::cout << " | Tamano: " << currentBlock.getSize();
        std::cout << " | Estado: " << (currentBlock.isFree() ? "Libre" : "Ocupado") << std::endl;
    }
    std::cout << "Fragmentacion externa: " << this->manager->calculateExternalFragmentation() << std::endl;
    std::cout << "Fragmentacion interna: " << this->manager->calculateInternalFragmentation() << std::endl;
}

void CliMenu::loadAndRunFile()
{
    std::string filePath;
    std::cout << "Ingrese la ruta del archivo de entrada: ";
    std::cin >> filePath;

    std::vector<Command> commands;
    try
    {
        commands = this->fileReader.readCommands(filePath);
    }
    catch (const SimulatorException& exceptionCaught)
    {
        std::cout << "Error al leer el archivo: " << exceptionCaught.what() << std::endl;
        return;
    }

    //Mapa auxiliar para resolver el label legible (A, B, C...) al id numerico interno
    std::map<std::string, int> labelToId;
    int nextId = 1;

    for (size_t i = 0; i < commands.size(); i++)
    {
        const Command& currentCommand = commands.at(i);

        if (currentCommand.getType() == CommandType::CREATE)
        {
            int assignedId = nextId;
            nextId++;
            labelToId[currentCommand.getLabel()] = assignedId;

            Process newProcess(assignedId, currentCommand.getLabel(), currentCommand.getSize());
            try
            {
                this->manager->allocateProcess(newProcess);
                std::cout << "Proceso " << currentCommand.getLabel() << " creado correctamente." << std::endl;
            }
            catch (const SimulatorException& exceptionCaught)
            {
                std::cout << "Error al crear el proceso " << currentCommand.getLabel() << ": " << exceptionCaught.what() << std::endl;
            }
        }
        else
        {
            std::map<std::string, int>::iterator labelIterator = labelToId.find(currentCommand.getLabel());
            if (labelIterator == labelToId.end())
            {
                std::cout << "No se encontro el proceso " << currentCommand.getLabel() << " para liberar." << std::endl;
                continue;
            }

            try
            {
                this->manager->releaseProcess(labelIterator->second);
                std::cout << "Proceso " << currentCommand.getLabel() << " liberado correctamente." << std::endl;
            }
            catch (const SimulatorException& exceptionCaught)
            {
                std::cout << "Error al liberar el proceso " << currentCommand.getLabel() << ": " << exceptionCaught.what() << std::endl;
            }
        }
    }

    std::cout << "Ejecucion del archivo terminada." << std::endl;
    std::cout << "Desea guardar el estado final en un archivo? (S/N): ";
    char answer = 'N';
    std::cin >> answer;
    if (answer == 'S' || answer == 's')
    {
        std::string outputPath;
        std::cout << "Ingrese la ruta del archivo de salida: ";
        std::cin >> outputPath;
        this->writeOutputFile(outputPath);
    }
}

void CliMenu::changeAllocationStrategy()
{
    std::cout << "Seleccione la nueva estrategia:" << std::endl;
    std::cout << "1. First Fit" << std::endl;
    std::cout << "2. Best Fit" << std::endl;
    std::cout << "3. Worst Fit" << std::endl;
    std::cout << "Opcion: ";

    int option = 0;
    std::cin >> option;

    if (option == 1)
    {
        this->manager->setAllocation(new FirstFit());
        std::cout << "Estrategia cambiada a First Fit." << std::endl;
    }
    else if (option == 2)
    {
        this->manager->setAllocation(new BestFit());
        std::cout << "Estrategia cambiada a Best Fit." << std::endl;
    }
    else if (option == 3)
    {
        this->manager->setAllocation(new WorstFit());
        std::cout << "Estrategia cambiada a Worst Fit." << std::endl;
    }
    else
    {
        std::cout << "Opcion invalida, no se cambio la estrategia." << std::endl;
    }
}

void CliMenu::writeOutputFile(const std::string& outputPath) const
{
    std::ofstream outputFile(outputPath);
    if (!outputFile.is_open())
    {
        std::cout << "No se pudo crear el archivo de salida: " << outputPath << std::endl;
        return;
    }

    const std::vector<MemoryBlock>& blocks = this->manager->getBlocks();
    outputFile << "ESTADO FINAL DE LA MEMORIA" << std::endl;
    for (size_t i = 0; i < blocks.size(); i++)
    {
        const MemoryBlock& currentBlock = blocks.at(i);
        outputFile << "Bloque " << i << " | Inicio: " << currentBlock.getStartAddress();
        outputFile << " | Tamano: " << currentBlock.getSize();
        outputFile << " | Estado: " << (currentBlock.isFree() ? "Libre" : "Ocupado") << std::endl;
    }
    outputFile << "Fragmentacion externa: " << this->manager->calculateExternalFragmentation() << std::endl;
    outputFile << "Fragmentacion interna: " << this->manager->calculateInternalFragmentation() << std::endl;

    outputFile.close();
    std::cout << "Archivo de salida guardado correctamente." << std::endl;
}

void CliMenu::run()
{
    int option = 0;
    while (option != 6)
    {
        this->showMenu();
        std::cin >> option;

        if (option == 1)
        {
            this->requestProcessCreation();
        }
        else if (option == 2)
        {
            this->requestProcessRelease();
        }
        else if (option == 3)
        {
            this->loadAndRunFile();
        }
        else if (option == 4)
        {
            this->showMemoryState();
        }
        else if (option == 5)
        {
            this->changeAllocationStrategy();
        }
        else if (option != 6)
        {
            std::cout << "Opcion invalida." << std::endl;
        }
    }
    std::cout << "Saliendo del simulador..." << std::endl;
}