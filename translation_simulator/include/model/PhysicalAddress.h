/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Declaracion de PhysicalAddress, representa una
   direccion fisica ya traducida, lista para mostrar al usuario
*/
#ifndef PHYSICAL_ADDRESS_H
#define PHYSICAL_ADDRESS_H

class PhysicalAddress
{
private:

    int rawValue;

public:

    PhysicalAddress(); //Constructor por defecto
    explicit PhysicalAddress(int rawValue); //Constructor con parametros
    ~PhysicalAddress(); //Destructor explicito

    static bool isValidData(int rawValue);

    int getValue() const;
};

#endif