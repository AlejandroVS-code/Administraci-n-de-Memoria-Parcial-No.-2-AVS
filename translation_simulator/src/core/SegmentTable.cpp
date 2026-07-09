/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Implementacion de SegmentTable, tabla de
   segmentos de un solo nivel
*/
#include "../../include/core/SegmentTable.h"
#include "../../include/exceptions/SegmentationFaultException.h"

SegmentTable::SegmentTable()
{
    //Constructor vacio, entries arranca vacio por defecto
}

SegmentTable::~SegmentTable()
{
    //Destructor vacio, no maneja punteros
}

void SegmentTable::addSegment(int segmentNumber, int baseAddress, int limit)
{
    //Si el segmento ya existia, se reemplaza en vez de duplicar la entrada
    for (size_t i = 0; i < this->entries.size(); i++)
    {
        if (this->entries.at(i).getSegmentNumber() == segmentNumber)
        {
            this->entries.at(i) = Segment(segmentNumber, baseAddress, limit);
            return;
        }
    }
    this->entries.push_back(Segment(segmentNumber, baseAddress, limit));
}

bool SegmentTable::exists(int segmentNumber) const
{
    for (size_t i = 0; i < this->entries.size(); i++)
    {
        if (this->entries.at(i).getSegmentNumber() == segmentNumber)
        {
            return true;
        }
    }
    return false;
}

const Segment& SegmentTable::getSegment(int segmentNumber) const
{
    for (size_t i = 0; i < this->entries.size(); i++)
    {
        if (this->entries.at(i).getSegmentNumber() == segmentNumber)
        {
            return this->entries.at(i);
        }
    }
    //En condiciones normales SegmentationStrategy ya llamo exists() antes de llegar aqui,
    //este throw es una segunda capa de defensa por si se llama este metodo directo
    throw SegmentationFaultException(segmentNumber, 0);
}

const std::vector<Segment>& SegmentTable::getEntries() const
{
    return this->entries;
}