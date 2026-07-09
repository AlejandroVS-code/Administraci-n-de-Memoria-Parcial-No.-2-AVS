/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 08/07/2026
   Version: 1.0
   Licencia: Uso academico, Universidad del Valle
   Descripcion: Implementacion de SimulatorException
*/
#include "../../include/exceptions/SimulatorException.h"

//Nota: aqui SI uso lista de inicializacion porque runtime_error no tiene
//constructor por defecto, es la unica forma de pasarle el mensaje
SimulatorException::SimulatorException(const std::string& message) : std::runtime_error(message)
{
}

SimulatorException::~SimulatorException()
{
}