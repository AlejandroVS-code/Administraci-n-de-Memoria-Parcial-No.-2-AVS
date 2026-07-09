/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 08/07/2026
   Version: 1.0
   Licencia: Uso academico, Universidad del Valle
   Descripcion: Implementacion de ProcessNotFoundException
*/
#include "exceptions/ProcessNotFoundException.h"
#include <sstream>

static std::string buildMessage(int processId)
{
    std::stringstream messageStream;
    messageStream << "No se encontro ningun proceso con id " << processId;
    return messageStream.str();
}

ProcessNotFoundException::ProcessNotFoundException(int processId) : SimulatorException(buildMessage(processId))
{
}

ProcessNotFoundException::~ProcessNotFoundException()
{
}