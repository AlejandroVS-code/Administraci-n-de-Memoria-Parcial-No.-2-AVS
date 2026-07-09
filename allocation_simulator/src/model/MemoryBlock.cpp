/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 08/07/2026
   Version: 1.0
   Descripcion: Implementacion de la clase MemoryBlock
*/
#include "../../include/model/MemoryBlock.h"
#include "../../include/model/Process.h" 

MemoryBlock::MemoryBlock()
{
    this->startAddress = 0;
    this->size = 0;
    this->free = true;
    this->process = nullptr;
}

MemoryBlock::MemoryBlock(int startAddress, int size)
{
    this->startAddress = startAddress;
    this->size = size;
    this->free = true;
    this->process = nullptr;
}

MemoryBlock::~MemoryBlock()
{
    //No hago delete de process porque este bloque no es dueno de ese objeto
}

bool MemoryBlock::isFree() const
{
    return this->free;
}

int MemoryBlock::getStartAddress() const
{
    return this->startAddress;
}

int MemoryBlock::getSize() const
{
    return this->size;
}

Process* MemoryBlock::getProcess() const
{
    return this->process;
}

void MemoryBlock::allocate(Process* process)
{
    this->process = process;
    this->free = false;
}

void MemoryBlock::release()
{
    this->process = nullptr;
    this->free = true;
}

void MemoryBlock::setSize(int newSize)
{
    this->size = newSize;
}

void MemoryBlock::setStartAddress(int newStartAddress)
{
    this->startAddress = newStartAddress;
}