/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Declaracion de VirtualAddress, representa una
   direccion virtual sin interpretar, la interpretacion (pagina+
   desplazamiento o segmento+desplazamiento) la hace la estrategia
*/
#ifndef VIRTUAL_ADDRESS_H
#define VIRTUAL_ADDRESS_H

class VirtualAddress
{
private:
   
    int rawValue;

public:

    VirtualAddress(); //Constructor por defecto
    explicit VirtualAddress(int rawValue); //Constructor con parametros
    ~VirtualAddress(); //Destructor explicito

    //Valida los datos ANTES de construir el objeto
    static bool isValidData(int rawValue);

    int getValue() const;
};

#endif