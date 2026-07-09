/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Interfaz abstracta del patron Strategy para las
   estrategias de traduccion de direcciones (paginacion, segmentacion)
*/
#ifndef TRANSLATION_STRATEGY_H
#define TRANSLATION_STRATEGY_H

#include <string> 

class VirtualAddress; 
class PhysicalAddress; 
class PageTable; 
class SegmentTable; 

// Clase abstracta pura, define el contrato que deben cumplir
// todas las estrategias de traduccion de direcciones
class TranslationStrategy
{
public:
    TranslationStrategy(); //Constructor por defecto
    virtual ~TranslationStrategy(); //Destructor virtual, se implementa vacio en el cpp

    //Recibe ambas tablas aunque cada estrategia solo use la que le corresponde,
    virtual PhysicalAddress translate(const VirtualAddress& virtualAddress, const PageTable& pageTable, const SegmentTable& segmentTable) const = 0;
    virtual std::string getName() const = 0;
};

#endif