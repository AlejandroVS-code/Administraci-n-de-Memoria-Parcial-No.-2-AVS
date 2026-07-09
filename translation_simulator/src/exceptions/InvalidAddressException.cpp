/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Implementacion de InvalidAddressException
*/
#include "../../include/exceptions/InvalidAddressException.h"
#include <sstream> 

//Funcion auxiliar para armar el mensaje antes de pasarselo al constructor de la clase base
static std::string buildMessage(int rawValue)
{
    std::stringstream messageStream;
    messageStream << "Direccion virtual invalida: " << rawValue << " (no puede ser negativa)";
    return messageStream.str();
}

InvalidAddressException::InvalidAddressException(int rawValue) : TranslatorException(buildMessage(rawValue))
{
}

InvalidAddressException::~InvalidAddressException()
{
}