/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 08/07/2026
   Version: 1.0
   Licencia: Uso academico, Universidad del Valle
   Descripcion: Declaracion de InsufficientMemoryException
*/
#ifndef INSUFFICIENT_MEMORY_EXCEPTION_H
#define INSUFFICIENT_MEMORY_EXCEPTION_H

#include "SimulatorException.h"

// Se lanza cuando ningun bloque libre puede alojar el tamano solicitado
class InsufficientMemoryException : public SimulatorException
{
public:
    explicit InsufficientMemoryException(int requestedSize);
    ~InsufficientMemoryException();
};

#endif
