/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 08/07/2026
   Version: 1.0
   Licencia: Uso academico, Universidad del Valle
   Descripcion: Declaracion de ProcessNotFoundException
*/
#ifndef PROCESS_NOT_FOUND_EXCEPTION_H
#define PROCESS_NOT_FOUND_EXCEPTION_H

#include "SimulatorException.h"

// Se lanza al intentar liberar un proceso que no existe en el gestor
class ProcessNotFoundException : public SimulatorException
{
public:
    explicit ProcessNotFoundException(int processId);
    ~ProcessNotFoundException();
};

#endif
