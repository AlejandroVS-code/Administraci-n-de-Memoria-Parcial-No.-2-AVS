/* Autor: [Tu Nombre Completo]
   Correo: [tu.correo]@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 08/07/2026
   Version: 1.0
   Licencia: Uso academico, Universidad del Valle
   Descripcion: Implementacion de InsufficientMemoryException
*/
#include "../../include/exceptions/InsufficientMemoryException.h"
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