/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Declaracion de Frame, representa un marco de
   memoria fisica, usado por el esquema de paginacion
*/
#ifndef FRAME_H
#define FRAME_H

class Frame
{
private:
    int frameNumber;
    bool free;

public:
    //Metodos
    Frame(); //Constructor por defecto
    explicit Frame(int frameNumber); //Constructor con parametros, nace libre
    ~Frame(); //Destructor explicito

    int getFrameNumber() const;
    bool isFree() const;

    void occupy();
    void release();
};

#endif