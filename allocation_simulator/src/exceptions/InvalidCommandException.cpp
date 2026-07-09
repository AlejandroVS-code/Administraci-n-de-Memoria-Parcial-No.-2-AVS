/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 08/07/2026
   Version: 1.0
   Licencia: Uso academico, Universidad del Valle
   Descripcion: Implementacion de InvalidCommandException
*/
#include "../../include/exceptions/InvalidCommandException.h"

//Funcion auxiliar para armar el mensaje antes de pasarselo al constructor de la clase base
static std::string buildMessage(const std::string& line)
{
    return "Linea con formato invalido en el archivo de entrada: " + line;
}

InvalidCommandException::InvalidCommandException(const std::string& line) : SimulatorException(buildMessage(line))
{
}

InvalidCommandException::~InvalidCommandException()
{
}