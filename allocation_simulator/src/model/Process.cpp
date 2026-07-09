/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 08/07/2026
   Version: 1.0
   Licencia: Uso academico, Universidad del Valle
   Descripcion: Implementacion de la clase Process
*/
#include "model/Process.h"

Process::Process()
{
    //Constructor por defecto, deja el proceso en un estado neutro
    this->id = 0;
    this->name = "";
    this->requestedSize = 0;
    this->allocatedSize = 0;
}

Process::Process(int id, const std::string& name, int requestedSize)
{
    //Asigno los valores recibidos dentro del cuerpo del constructor
    this->id = id;
    this->name = name;
    this->requestedSize = requestedSize;
    this->allocatedSize = 0; //Todavia no se le ha asignado memoria
}

Process::~Process()
{
    //Destructor vacio, el proceso no es dueno de ningun puntero
}

bool Process::isValidData(int requestedSize)
{
    //Un tamano solicitado debe ser mayor que cero para ser valido
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
    //La fragmentacion interna es lo que sobra del bloque que no se uso
    return this->allocatedSize - this->requestedSize;
}
