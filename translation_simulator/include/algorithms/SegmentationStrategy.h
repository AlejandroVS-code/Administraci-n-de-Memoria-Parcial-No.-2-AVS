/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Declaracion de SegmentationStrategy, traduce
   direcciones usando segmentacion de un nivel (segmento =
   rawValue / maxSegmentSize)
*/
#ifndef SEGMENTATION_STRATEGY_H
#define SEGMENTATION_STRATEGY_H

#include "TranslationStrategy.h"

class SegmentationStrategy : public TranslationStrategy
{
private:
    //Atributos
    int maxSegmentSize; //Ancho de direccionamiento usado para decodificar segmento+desplazamiento

public:
    explicit SegmentationStrategy(int maxSegmentSize); //Constructor con parametros
    ~SegmentationStrategy(); //Destructor explicito

    PhysicalAddress translate(const VirtualAddress& virtualAddress, const PageTable& pageTable, const SegmentTable& segmentTable) const override;
    std::string getName() const override;

    int getMaxSegmentSize() const;
};

#endif