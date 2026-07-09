/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Implementacion de VirtualAddress
*/
#include "../../include/model/VirtualAddress.h"

VirtualAddress::VirtualAddress()
{
    this->rawValue = 0;
}

VirtualAddress::VirtualAddress(int rawValue)
{
    this->rawValue = rawValue;
}

VirtualAddress::~VirtualAddress()
{
    //Destructor vacio, no maneja punteros
}

bool VirtualAddress::isValidData(int rawValue)
{
    if (rawValue < 0)
    {
        return false;
    }
    return true;
}

int VirtualAddress::getValue() const
{
    return this->rawValue;
}