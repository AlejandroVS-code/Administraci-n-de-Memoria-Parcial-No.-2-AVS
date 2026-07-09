/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Declaracion de InvalidCommandException para
   translation_simulator
*/
#ifndef INVALID_COMMAND_EXCEPTION_H
#define INVALID_COMMAND_EXCEPTION_H

#include "TranslatorException.h"

// Se lanza cuando una linea del archivo de entrada no tiene el formato esperado
class InvalidCommandException : public TranslatorException
{
public:
    explicit InvalidCommandException(const std::string& line);
    ~InvalidCommandException();
};

#endif