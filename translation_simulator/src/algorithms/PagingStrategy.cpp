/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Implementacion de PagingStrategy, traduce
   direcciones usando paginacion de un nivel
*/
#include "algorithms/PagingStrategy.h"
#include "model/VirtualAddress.h"
#include "model/PhysicalAddress.h"
#include "core/PageTable.h"
#include "core/SegmentTable.h"

PagingStrategy::PagingStrategy(int pageSize)
{
    this->pageSize = pageSize;
}

PagingStrategy::~PagingStrategy()
{
    //Destructor vacio
}

PhysicalAddress PagingStrategy::translate(const VirtualAddress& virtualAddress, const PageTable& pageTable, const SegmentTable& segmentTable) const
{
    (void)segmentTable; //se evita el warning de parametro no usado

    int rawValue = virtualAddress.getValue();
    int pageNumber = rawValue / this->pageSize;
    int offset = rawValue % this->pageSize;

    //pageTable.translatePage ya lanza PageFaultException si la pagina no esta mapeada
    int frameNumber = pageTable.translatePage(pageNumber);

    int physicalValue = (frameNumber * this->pageSize) + offset;
    return PhysicalAddress(physicalValue);
}

std::string PagingStrategy::getName() const
{
    return "Paging";
}

int PagingStrategy::getPageSize() const
{
    return this->pageSize;
}