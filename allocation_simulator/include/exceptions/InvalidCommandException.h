/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 08/07/2026
   Version: 1.0
   Descripcion: Declaracion de InvalidCommandException
*/
#ifndef INVALID_COMMAND_EXCEPTION_H
#define INVALID_COMMAND_EXCEPTION_H

#include "SimulatorException.h"

// Se lanza cuando una linea del archivo de entrada no tiene el formato esperado
class InvalidCommandException : public SimulatorException
{
public:
    explicit InvalidCommandException(const std::string& line);
    ~InvalidCommandException();
};

#endif