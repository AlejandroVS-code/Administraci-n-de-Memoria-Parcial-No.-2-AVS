/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Implementacion de SegmentationStrategy, traduce
   direcciones usando segmentacion de un nivel
*/
#include "algorithms/SegmentationStrategy.h"
#include "model/VirtualAddress.h"
#include "model/PhysicalAddress.h"
#include "core/PageTable.h"
#include "core/SegmentTable.h"
#include "exceptions/SegmentationFaultException.h"

SegmentationStrategy::SegmentationStrategy(int maxSegmentSize)
{
    this->maxSegmentSize = maxSegmentSize;
}

SegmentationStrategy::~SegmentationStrategy()
{
    //Destructor vacio
}

PhysicalAddress SegmentationStrategy::translate(const VirtualAddress& virtualAddress, const PageTable& pageTable, const SegmentTable& segmentTable) const
{
    (void)pageTable; //se evita el warning de parametro no usado

    int rawValue = virtualAddress.getValue();
    int segmentNumber = rawValue / this->maxSegmentSize;
    int offset = rawValue % this->maxSegmentSize;

    if (!segmentTable.exists(segmentNumber))
    {
        throw SegmentationFaultException(segmentNumber, offset);
    }

    const Segment& segment = segmentTable.getSegment(segmentNumber);
    if (offset > segment.getLimit())
    {
        throw SegmentationFaultException(segmentNumber, offset);
    }

    int physicalValue = segment.getBaseAddress() + offset;
    return PhysicalAddress(physicalValue);
}

std::string SegmentationStrategy::getName() const
{
    return "Segmentation";
}

int SegmentationStrategy::getMaxSegmentSize() const
{
    return this->maxSegmentSize;
}