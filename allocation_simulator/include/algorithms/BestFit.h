/* Autor: [Tu Nombre Completo]
   Correo: [tu.correo]@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 08/07/2026
   Version: 1.0
   Licencia: Uso academico, Universidad del Valle
   Descripcion: Declaracion de la estrategia Best Fit
*/
#ifndef BEST_FIT_H
#define BEST_FIT_H

#include "Allocation.h" //Clase base de la que hereda esta estrategia

// Estrategia Best Fit: elige el bloque libre mas pequeno que alcance para el proceso
class BestFit : public Allocation
{
public:
    BestFit(); //Constructor por defecto
    ~BestFit(); //Destructor explicito

    int findBlock(const std::vector<MemoryBlock>& blocks, int requestedSize) const override;
    std::string getName() const override;
};

#endif
