/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Declaracion de InvalidAddressException
*/
#ifndef INVALID_ADDRESS_EXCEPTION_H
#define INVALID_ADDRESS_EXCEPTION_H

#include "TranslatorException.h"

// Se lanza cuando la direccion virtual solicitada es invalida (negativa
// o fuera del rango de memoria virtual configurado)
class InvalidAddressException : public TranslatorException
{
public:
    explicit InvalidAddressException(int rawValue);
    ~InvalidAddressException();
};

#endif