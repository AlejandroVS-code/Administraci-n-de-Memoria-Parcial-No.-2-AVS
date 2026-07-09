/* Autor: [Tu Nombre Completo]
   Correo: [tu.correo]@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 08/07/2026
   Version: 1.0
   Licencia: Uso academico, Universidad del Valle
   Descripcion: Declaracion de la estrategia Worst Fit
*/
#ifndef WORST_FIT_H
#define WORST_FIT_H

#include "Allocation.h" //Clase base de la que hereda esta estrategia

// Estrategia Worst Fit: elige el bloque libre mas grande disponible
class WorstFit : public Allocation
{
public:
    WorstFit(); //Constructor por defecto
    ~WorstFit(); //Destructor explicito

    int findBlock(const std::vector<MemoryBlock>& blocks, int requestedSize) const override;
    std::string getName() const override;
};

#endif