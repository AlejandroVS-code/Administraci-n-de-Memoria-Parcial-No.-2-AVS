/* Autor: [Tu Nombre Completo]
   Correo: [tu.correo]@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 08/07/2026
   Version: 1.0
   Licencia: Uso academico, Universidad del Valle
   Descripcion: Implementacion de CliMenu
*/
#include "../../include/ui/CliMenu.h"
#include "../../include/exceptions/SimulatorException.h"
#include <iostream> //Libreria para leer y escribir por consola

CliMenu::CliMenu()
{
    //Constructor por defecto, deja el menu sin manager asignado
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
    std::cout << "1. Crear proceso" << std::endl;
    std::cout << "2. Liberar proceso" << std::endl;
    std::cout << "3. Ver estado de la memoria" << std::endl;
    std::cout << "4. Salir" << std::endl;
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

    //Valido antes de crear el objeto, en vez de lanzar excepcion desde el constructor
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

void CliMenu::run()
{
    int option = 0;
    while (option != 4)
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
            this->showMemoryState();
        }
        else if (option != 4)
        {
            std::cout << "Opcion invalida." << std::endl;
        }
    }
    std::cout << "Saliendo del simulador..." << std::endl;
}
