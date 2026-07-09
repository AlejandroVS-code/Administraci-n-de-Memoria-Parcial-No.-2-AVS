/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Declaracion de TranslatorException, excepcion base
   de todo Implementacion 2
*/
#ifndef TRANSLATOR_EXCEPTION_H
#define TRANSLATOR_EXCEPTION_H

#include <stdexcept> 
#include <string> 

// Excepcion base de Implementacion 2, las demas heredan de esta
// Nota: no tiene constructor por defecto porque std::runtime_error tampoco lo tiene
class TranslatorException : public std::runtime_error
{
public:
    explicit TranslatorException(const std::string& message);
    virtual ~TranslatorException();
};

#endif