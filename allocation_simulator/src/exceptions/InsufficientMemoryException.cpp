/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 08/07/2026
   Version: 1.0
   Descripcion: Implementacion de InsufficientMemoryException
*/
#include "exceptions/InsufficientMemoryException.h"
#include <sstream>

static std::string buildMessage(int requestedSize)
{
    std::stringstream messageStream;
    messageStream << "No hay memoria suficiente para asignar " << requestedSize << " unidades";
    return messageStream.str();
}

InsufficientMemoryException::InsufficientMemoryException(int requestedSize) : SimulatorException(buildMessage(requestedSize))
{
}

InsufficientMemoryException::~InsufficientMemoryException()
{
}