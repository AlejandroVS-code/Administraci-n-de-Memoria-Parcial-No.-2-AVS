/* Autor: [Tu Nombre Completo]
   Correo: [tu.correo]@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 08/07/2026
   Version: 1.0
   Licencia: Uso academico, Universidad del Valle
   Descripcion: Implementacion de la clase Process
*/
#include "../../include/model/Process.h"

Process::Process()
{
    this->id = 0;
    this->name = "";
    this->requestedSize = 0;
    this->allocatedSize = 0;
}

Process::Process(int id, const std::string& name, int requestedSize)
{
    this->id = id;
    this->name = name;
    this->requestedSize = requestedSize;
    this->allocatedSize = 0;
}

Process::~Process()
{
    //Destructor vacio, el proceso no es dueno de ningun puntero
}

bool Process::isValidData(int requestedSize)
{
    if (requestedSize <= 0)
    {
        return false;
    }
    return true;
}

int Process::getId() const
{
    return this->id;
}

std::string Process::getName() const
{
    return this->name;
}

int Process::getRequestedSize() const
{
    return this->requestedSize;
}

int Process::getAllocatedSize() const
{
    return this->allocatedSize;
}

void Process::setAllocatedSize(int size)
{
    this->allocatedSize = size;
}

int Process::getInternalFragmentation() const
{
    return this->allocatedSize - this->requestedSize;
}