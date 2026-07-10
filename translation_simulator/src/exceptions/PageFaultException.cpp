/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Implementacion de PageFaultException
*/
#include "exceptions/PageFaultException.h"
#include <sstream> //Libreria para construir el mensaje con stringstream

//Funcion auxiliar para armar el mensaje antes de pasarselo al constructor de la clase base
static std::string buildMessage(int pageNumber)
{
    std::stringstream messageStream;
    messageStream << "Fallo de pagina: la pagina " << pageNumber << " no esta mapeada en la tabla de paginas";
    return messageStream.str();
}

PageFaultException::PageFaultException(int pageNumber) : TranslatorException(buildMessage(pageNumber))
{
}

PageFaultException::~PageFaultException()
{
}