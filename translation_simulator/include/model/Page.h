/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Declaracion de Page, representa una entrada de la
   tabla de paginas: que pagina virtual esta mapeada a que marco
*/
#ifndef PAGE_H
#define PAGE_H

class Page
{
private:

    int pageNumber;
    int frameNumber;
    bool valid; 

public:
    
    Page(); //Constructor por defecto
    Page(int pageNumber, int frameNumber); //Constructor con parametros, valido
    ~Page(); //Destructor explicito

    int getPageNumber() const;
    int getFrameNumber() const;
    bool isValid() const;

    void invalidate();
};

#endif