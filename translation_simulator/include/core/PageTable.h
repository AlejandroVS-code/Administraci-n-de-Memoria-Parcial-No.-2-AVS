/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Declaracion de PageTable, tabla de paginas de un
   solo nivel, asocia numero de pagina con numero de marco
*/
#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H

#include <vector> 
#include "../model/Page.h"

class PageTable
{
private:
  
    std::vector<Page> entries;

public:
    PageTable(); //Constructor por defecto
    ~PageTable(); //Destructor explicito

    void addMapping(int pageNumber, int frameNumber);
    bool isMapped(int pageNumber) const;

    //Lanza PageFaultException si la pagina no esta mapeada
    int translatePage(int pageNumber) const;

    const std::vector<Page>& getEntries() const;
};

#endif