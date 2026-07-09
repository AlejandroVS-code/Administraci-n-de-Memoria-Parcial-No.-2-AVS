/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Declaracion de SegmentTable, tabla de segmentos de
   un solo nivel, asocia numero de segmento con base y limite
*/
#ifndef SEGMENT_TABLE_H
#define SEGMENT_TABLE_H

#include <vector> 
#include "../model/Segment.h"

class SegmentTable
{
private:
   
    std::vector<Segment> entries;

public:
    SegmentTable(); //Constructor por defecto
    ~SegmentTable(); //Destructor explicito

    void addSegment(int segmentNumber, int baseAddress, int limit);
    bool exists(int segmentNumber) const;

    //Lanza SegmentationFaultException si el segmento no existe
    const Segment& getSegment(int segmentNumber) const;

    const std::vector<Segment>& getEntries() const;
};

#endif