/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 08/07/2026
   Version: 1.0
   Descripcion: Implementacion de CliMenu
*/
#include "ui/CliMenu.h"
#include "exceptions/SimulatorException.h"
#include "algorithms/FirstFit.h"
#include "algorithms/BestFit.h"
#include "algorithms/WorstFit.h"
#include <iostream> //Libreria para leer y escribir por consola
#include <fstream> //Libreria para escribir el archivo de salida
#include <sstream>

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
    std::string fileName;
    std::cout << "Ingrese el nombre del archivo (debe estar en data/allocation/): ";
    std::cin >> fileName;

    //Arma la ruta completa, el usuario ya no necesita escribir la carpeta
    std::string fullPath = "data/allocation/" + fileName;

    std::vector<Command> commands;
    try
    {
        commands = this->fileReader.readCommands(fullPath);
    }
    catch (const SimulatorException& exceptionCaught)
    {
        std::cout << "Error al leer el archivo: " << exceptionCaught.what() << std::endl;
        return;
    }

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

    this->writeOutputFile(fileName);
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

void CliMenu::writeOutputFile(const std::string& inputFileName) const
{
    
    std::string baseName = inputFileName;
    size_t extensionPosition = baseName.rfind(".txt");
    if (extensionPosition != std::string::npos && extensionPosition == baseName.size() - 4)
    {
        baseName = baseName.substr(0, extensionPosition);
    }

    
    std::string outputPath = "allocation_simulator/tests/" + baseName + "_output.txt";

    std::ofstream outputFile(outputPath);
    if (!outputFile.is_open())
    {
        std::cout << "No se pudo crear el archivo de salida: " << outputPath << std::endl;
        return;
    }

    const std::vector<MemoryBlock>& blocks = this->manager->getBlocks();

   
    std::stringstream outputContent;
    outputContent << "ESTADO FINAL DE LA MEMORIA" << std::endl;
    for (size_t i = 0; i < blocks.size(); i++)
    {
        const MemoryBlock& currentBlock = blocks.at(i);
        outputContent << "Bloque " << i << " | Inicio: " << currentBlock.getStartAddress();
        outputContent << " | Tamano: " << currentBlock.getSize();
        outputContent << " | Estado: " << (currentBlock.isFree() ? "Libre" : "Ocupado") << std::endl;
    }
    outputContent << "Fragmentacion externa: " << this->manager->calculateExternalFragmentation() << std::endl;
    outputContent << "Fragmentacion interna: " << this->manager->calculateInternalFragmentation() << std::endl;

    outputFile << outputContent.str();
    outputFile.close();

    std::cout << "\n----- RESULTADO GUARDADO EN: " << outputPath << " -----" << std::endl;
    std::cout << outputContent.str();
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