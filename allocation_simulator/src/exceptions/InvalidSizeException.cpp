/* Autor: [Tu Nombre Completo]
   Correo: [tu.correo]@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 08/07/2026
   Version: 1.0
   Licencia: Uso academico, Universidad del Valle
   Descripcion: Implementacion de InvalidSizeException
*/
#include "../../include/exceptions/InvalidSizeException.h"
#include <sstream>

static std::string buildMessage(int size)
{
    std::stringstream messageStream;
    messageStream << "El tamano " << size << " no es valido, debe ser mayor que cero";
    return messageStream.str();
}

InvalidSizeException::InvalidSizeException(int size) : SimulatorException(buildMessage(size))
{
}

InvalidSizeException::~InvalidSizeException()
{
}