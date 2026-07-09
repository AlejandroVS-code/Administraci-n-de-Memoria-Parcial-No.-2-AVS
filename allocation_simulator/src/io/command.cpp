/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 08/07/2026
   Version: 1.0
   Licencia: Uso academico, Universidad del Valle
   Descripcion: Implementacion de Command
*/
#include "io/Command.h"

Command::Command()
{
    //Constructor por defecto, un CREATE vacio como valor neutro
    this->type = CommandType::CREATE;
    this->label = "";
    this->size = 0;
}

Command::Command(CommandType type, const std::string& label, int size)
{
    this->type = type;
    this->label = label;
    this->size = size;
}

Command::~Command()
{
    //Destructor vacio, no maneja punteros
}

CommandType Command::getType() const
{
    return this->type;
}

std::string Command::getLabel() const
{
    return this->label;
}

int Command::getSize() const
{
    return this->size;
}