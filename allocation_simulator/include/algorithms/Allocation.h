/* Autor: [Tu Nombre Completo]
   Correo: [tu.correo]@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 08/07/2026
   Version: 1.0
   Licencia: Uso academico, Universidad del Valle
   Descripcion: Interfaz abstracta del patron Strategy para las
   estrategias de asignacion de memoria (First Fit, Best Fit, Worst Fit)
*/
#ifndef ALLOCATION_H
#define ALLOCATION_H

#include <vector> //Libreria para usar vector
#include <string> //Libreria para usar string

class MemoryBlock; //Forward declaration para evitar include circular

// Clase abstracta pura, define el contrato que deben cumplir
// todas las estrategias de asignacion de memoria
class Allocation
{
public:
    Allocation(); //Constructor por defecto
    virtual ~Allocation(); //Destructor virtual, se implementa vacio en el cpp

    //Busca el indice del bloque donde se puede alojar requestedSize
    //Retorna -1 si no encuentra ningun bloque valido
    virtual int findBlock(const std::vector<MemoryBlock>& blocks, int requestedSize) const = 0;
    virtual std::string getName() const = 0;
};

#endif
