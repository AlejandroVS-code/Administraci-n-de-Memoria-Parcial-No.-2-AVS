/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 08/07/2026
   Version: 1.0
   Licencia: Uso academico, Universidad del Valle
   Descripcion: Declaracion de SimulatorException, la excepcion
   base de todo el simulador
*/
#ifndef SIMULATOR_EXCEPTION_H
#define SIMULATOR_EXCEPTION_H

#include <stdexcept> //Libreria para heredar de runtime_error
#include <string> //Libreria para usar string

// Excepcion base de todo el simulador, las demas excepciones heredan de esta
// Nota: no tiene constructor por defecto porque std::runtime_error tampoco lo tiene
class SimulatorException : public std::runtime_error
{
public:
    explicit SimulatorException(const std::string& message); //Constructor con parametros
    virtual ~SimulatorException(); //Destructor explicito
};

#endif
