/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Declaracion de PageFaultException
*/
#ifndef PAGE_FAULT_EXCEPTION_H
#define PAGE_FAULT_EXCEPTION_H

#include "TranslatorException.h"

// Se lanza cuando la pagina solicitada no tiene mapeo en la tabla de paginas
class PageFaultException : public TranslatorException
{
public:
    explicit PageFaultException(int pageNumber);
    ~PageFaultException();
};

#endif