/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Implementacion de TranslatorException
*/
#include "exceptions/TranslatorException.h"

//constructor por defecto
TranslatorException::TranslatorException(const std::string& message) : std::runtime_error(message)
{
}

TranslatorException::~TranslatorException()
{
}