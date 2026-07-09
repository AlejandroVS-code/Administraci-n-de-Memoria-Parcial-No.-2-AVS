/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Implementacion de PhysicalAddress
*/
#include "../../include/model/PhysicalAddress.h"

PhysicalAddress::PhysicalAddress()
{
    this->rawValue = 0;
}

PhysicalAddress::PhysicalAddress(int rawValue)
{
    this->rawValue = rawValue;
}

PhysicalAddress::~PhysicalAddress()
{
    //Destructor vacio, no maneja punteros
}

bool PhysicalAddress::isValidData(int rawValue)
{
    
    if (rawValue < 0)
    {
        return false;
    }
    return true;
}

int PhysicalAddress::getValue() const
{
    return this->rawValue;
}