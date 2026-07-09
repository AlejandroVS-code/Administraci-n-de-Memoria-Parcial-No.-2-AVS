/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Declaracion de PagingStrategy, traduce direcciones
   usando paginacion de un nivel (pagina = rawValue / pageSize)
*/
#ifndef PAGING_STRATEGY_H
#define PAGING_STRATEGY_H

#include "TranslationStrategy.h"

class PagingStrategy : public TranslationStrategy
{
private:
    
    int pageSize;

public:
    explicit PagingStrategy(int pageSize); //Constructor con parametros
    ~PagingStrategy(); //Destructor explicito

    PhysicalAddress translate(const VirtualAddress& virtualAddress, const PageTable& pageTable, const SegmentTable& segmentTable) const override;
    std::string getName() const override;

    int getPageSize() const;
};

#endif