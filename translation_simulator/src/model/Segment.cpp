/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Implementacion de Segment
*/
#include "model/Segment.h"

Segment::Segment()
{
    this->segmentNumber = 0;
    this->baseAddress = 0;
    this->limit = 0;
}

Segment::Segment(int segmentNumber, int baseAddress, int limit)
{
    this->segmentNumber = segmentNumber;
    this->baseAddress = baseAddress;
    this->limit = limit;
}

Segment::~Segment()
{
    //Destructor vacio, no maneja punteros
}

int Segment::getSegmentNumber() const
{
    return this->segmentNumber;
}

int Segment::getBaseAddress() const
{
    return this->baseAddress;
}

int Segment::getLimit() const
{
    return this->limit;
}