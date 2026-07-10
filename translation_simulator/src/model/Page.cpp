/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Licencia: Uso academico, Universidad del Valle
   Descripcion: Implementacion de Page
*/
#include "model/Page.h"

Page::Page()
{
    this->pageNumber = 0;
    this->frameNumber = 0;
    this->valid = false;
}

Page::Page(int pageNumber, int frameNumber)
{
    this->pageNumber = pageNumber;
    this->frameNumber = frameNumber;
    this->valid = true; 
}

Page::~Page()
{
    //Destructor vacio, no maneja punteros
}

int Page::getPageNumber() const
{
    return this->pageNumber;
}

int Page::getFrameNumber() const
{
    return this->frameNumber;
}

bool Page::isValid() const
{
    return this->valid;
}

void Page::invalidate()
{
    this->valid = false;
}