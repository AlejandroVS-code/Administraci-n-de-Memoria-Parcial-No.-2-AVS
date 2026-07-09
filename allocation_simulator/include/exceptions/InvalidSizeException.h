/* Autor: [Tu Nombre Completo]
   Correo: [tu.correo]@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 08/07/2026
   Version: 1.0
   Licencia: Uso academico, Universidad del Valle
   Descripcion: Declaracion de InvalidSizeException
*/
#ifndef INVALID_SIZE_EXCEPTION_H
#define INVALID_SIZE_EXCEPTION_H

#include "SimulatorException.h"

// Se lanza cuando el tamano solicitado por un proceso es invalido (<= 0)
class InvalidSizeException : public SimulatorException
{
public:
    explicit InvalidSizeException(int size);
    ~InvalidSizeException();
};

#endif