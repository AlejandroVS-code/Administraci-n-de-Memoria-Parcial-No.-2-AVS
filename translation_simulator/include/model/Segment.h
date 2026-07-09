/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Declaracion de Segment, representa una entrada de
   la tabla de segmentos: base fisica y limite de un segmento
*/
#ifndef SEGMENT_H
#define SEGMENT_H

class Segment
{
private:

    int segmentNumber;
    int baseAddress;
    int limit; 

public:
   
    Segment(); //Constructor por defecto
    Segment(int segmentNumber, int baseAddress, int limit); //Constructor con parametros
    ~Segment(); //Destructor explicito

    int getSegmentNumber() const;
    int getBaseAddress() const;
    int getLimit() const;
};

#endif