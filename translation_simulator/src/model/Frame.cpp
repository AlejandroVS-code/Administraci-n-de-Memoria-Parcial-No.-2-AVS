/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Implementacion de Frame
*/
#include "model/Frame.h"

Frame::Frame()
{
    this->frameNumber = 0;
    this->free = true;
}

Frame::Frame(int frameNumber)
{
    this->frameNumber = frameNumber;
    this->free = true; 
}

Frame::~Frame()
{
    //Destructor vacio, no maneja punteros
}

int Frame::getFrameNumber() const
{
    return this->frameNumber;
}

bool Frame::isFree() const
{
    return this->free;
}

void Frame::occupy()
{
    this->free = false;
}

void Frame::release()
{
    this->free = true;
}