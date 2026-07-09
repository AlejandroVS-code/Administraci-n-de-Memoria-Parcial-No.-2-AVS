/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 08/07/2026
   Version: 1.0
   Licencia: Uso academico, Universidad del Valle
   Descripcion: Declaracion de la estrategia First Fit
*/
#ifndef FIRST_FIT_H
#define FIRST_FIT_H

#include "Allocation.h" //Clase base de la que hereda esta estrategia

// Estrategia First Fit: elige el primer bloque libre que alcance para el proceso
class FirstFit : public Allocation
{
public:
    FirstFit(); //Constructor por defecto
    ~FirstFit(); //Destructor explicito

    int findBlock(const std::vector<MemoryBlock>& blocks, int requestedSize) const override;
    std::string getName() const override;
};

#endif
