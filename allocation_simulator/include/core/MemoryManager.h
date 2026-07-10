/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 08/07/2026
   Version: 1.0
   Licencia: Uso academico, Universidad del Valle
   Descripcion: Declaracion de MemoryManager, el orquestador central
   que administra los bloques, los procesos y la estrategia activa
*/
#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <vector> //Libreria para usar vector
#include <map> //Libreria para usar map, asocio el id del proceso con el objeto Process
#include "../model/MemoryBlock.h"
#include "../model/Process.h"
#include "../algorithms/Allocation.h"

// Orquestador principal: administra los bloques, los procesos
// y delega la busqueda de espacio a la estrategia activa
class MemoryManager
{
private:
    //Atributos
    int nextProcessId;
    int totalSize;
    std::vector<MemoryBlock> blocks; //Composicion fuerte, el manager es dueno de los bloques (se guardan por valor)
    std::map<int, Process> processes; //Los Process se guardan por valor, el map garantiza que sus direcciones no cambien
    Allocation* allocation; //Composicion, el manager es dueno de la estrategia activa

    //Une bloques libres contiguos para reducir la fragmentacion externa
    void mergeFreeBlocks();

public:
    //Metodos
    MemoryManager(); //Constructor por defecto
    MemoryManager(int totalSize, Allocation* initialAllocation); //Constructor con parametros
    int generateProcessId();
    

    //Prohibido copiar: allocation es un puntero dueno (delete en el destructor).
    //Si se permitiera copiar por defecto, dos manager apuntarian al mismo Allocation
    //y ambos destructores harian delete sobre el mismo puntero (double free)
    MemoryManager(const MemoryManager&) = delete;
    MemoryManager& operator=(const MemoryManager&) = delete;

    ~MemoryManager(); //Destructor explicito, libera la estrategia activa con delete

    bool allocateProcess(const Process& process);
    bool releaseProcess(int processId);

    void reset();
    void setAllocation(Allocation* newAllocation); //Libera la estrategia vieja con delete y guarda la nueva

    int calculateExternalFragmentation() const;
    int calculateInternalFragmentation() const;

    const std::vector<MemoryBlock>& getBlocks() const;
};

#endif