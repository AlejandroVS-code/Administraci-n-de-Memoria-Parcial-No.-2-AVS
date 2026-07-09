/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Licencia: Uso academico, Universidad del Valle
   Descripcion: Implementacion de InvalidCommandException
*/
#include "../../include/exceptions/InvalidCommandException.h"

static std::string buildMessage(const std::string& line)
{
    return "Linea con formato invalido en el archivo de entrada: " + line;
}

InvalidCommandException::InvalidCommandException(const std::string& line) : TranslatorException(buildMessage(line))
{
}

InvalidCommandException::~InvalidCommandException()
{
}