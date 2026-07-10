/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Implementacion de PageTable, tabla de paginas de
   un solo nivel
*/
#include "core/PageTable.h"
#include "exceptions/PageFaultException.h"

PageTable::PageTable()
{
    //Constructor vacio, entries arranca vacio por defecto
}

PageTable::~PageTable()
{
    //Destructor vacio, no maneja punteros
}
void PageTable::clear()
{
    this->entries.clear();
}

void PageTable::addMapping(int pageNumber, int frameNumber)
{
    //Si la pagina ya tenia un mapeo, se reemplazo en vez de duplicar la entrada
    for (size_t i = 0; i < this->entries.size(); i++)
    {
        if (this->entries.at(i).getPageNumber() == pageNumber)
        {
            this->entries.at(i) = Page(pageNumber, frameNumber);
            return;
        }
    }
    this->entries.push_back(Page(pageNumber, frameNumber));
}

bool PageTable::isMapped(int pageNumber) const
{
    for (size_t i = 0; i < this->entries.size(); i++)
    {
        const Page& currentPage = this->entries.at(i);
        if (currentPage.getPageNumber() == pageNumber && currentPage.isValid())
        {
            return true;
        }
    }
    return false;
}

int PageTable::translatePage(int pageNumber) const
{
    for (size_t i = 0; i < this->entries.size(); i++)
    {
        const Page& currentPage = this->entries.at(i);
        if (currentPage.getPageNumber() == pageNumber && currentPage.isValid())
        {
            return currentPage.getFrameNumber();
        }
    }
    throw PageFaultException(pageNumber);
}

const std::vector<Page>& PageTable::getEntries() const
{
    return this->entries;
}