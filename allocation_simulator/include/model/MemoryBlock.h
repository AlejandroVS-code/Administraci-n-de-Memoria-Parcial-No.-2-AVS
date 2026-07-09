/* Autor: [Tu Nombre Completo]
   Correo: [tu.correo]@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 08/07/2026
   Version: 1.0
   Licencia: Uso academico, Universidad del Valle
   Descripcion: Declaracion de la clase MemoryBlock, representa un
   bloque de memoria que puede estar libre u ocupado por un proceso
*/
#ifndef MEMORY_BLOCK_H
#define MEMORY_BLOCK_H

class Process; //Forward declaration para evitar include circular con Process.h

// Representa un bloque de memoria, puede estar libre u ocupado por un proceso
class MemoryBlock
{
private:
    //Atributos
    int startAddress;
    int size;
    bool free;
    Process* process; //No es dueno del proceso, solo lo referencia (agregacion)

public:
    //Metodos
    MemoryBlock(); //Constructor por defecto
    MemoryBlock(int startAddress, int size); //Constructor con parametros
    ~MemoryBlock(); //Destructor explicito, no borra process porque no es dueno

    bool isFree() const;
    int getStartAddress() const;
    int getSize() const;
    Process* getProcess() const;

    void allocate(Process* process);
    void release();
    void setSize(int newSize);
    void setStartAddress(int newStartAddress);
};

#endif
