/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Declaracion de MemoryTranslator, orquestador
   central de Implementacion 2, equivalente a MemoryManager en
   Implementacion 1
*/
#ifndef MEMORY_TRANSLATOR_H
#define MEMORY_TRANSLATOR_H

#include <vector> 
#include "../model/Frame.h"
#include "../model/VirtualAddress.h"
#include "../model/PhysicalAddress.h"
#include "PageTable.h"
#include "SegmentTable.h"
#include "../algorithms/TranslationStrategy.h"

class MemoryTranslator
{
private:
    int physicalMemorySize;
    std::vector<Frame> frames;
    PageTable pageTable; 
    SegmentTable segmentTable; 
    TranslationStrategy* strategy; 
    

public:
    MemoryTranslator(); //Constructor por defecto
    MemoryTranslator(int physicalMemorySize, int frameSize, TranslationStrategy* initialStrategy); //Constructor con parametros
    ~MemoryTranslator(); //Destructor explicito
    //Copia deshabilitada, evitar doble delete de strategy
    MemoryTranslator(const MemoryTranslator& other) = delete;
    MemoryTranslator& operator=(const MemoryTranslator& other) = delete;
    void reset();

    PhysicalAddress translateAddress(const VirtualAddress& virtualAddress) const;

    void loadPageMapping(int pageNumber, int frameNumber);
    void loadSegment(int segmentNumber, int baseAddress, int limit);

    void setStrategy(TranslationStrategy* newStrategy); 

    const std::vector<Frame>& getFrames() const;
    const PageTable& getPageTable() const;
    const SegmentTable& getSegmentTable() const;
};

#endif