/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Implementacion de MemoryTranslator, orquestador
   central de Implementacion 2
*/
#include "../../include/core/MemoryTranslator.h"
#include "../../include/exceptions/InvalidAddressException.h"
#include "../../include/exceptions/TranslatorException.h"

MemoryTranslator::MemoryTranslator()
{
    this->physicalMemorySize = 0;
    this->strategy = nullptr;
}

MemoryTranslator::MemoryTranslator(int physicalMemorySize, int frameSize, TranslationStrategy* initialStrategy)
{
    this->physicalMemorySize = physicalMemorySize;
    this->strategy = initialStrategy;

    //se Divide la memoria fisica total en marcos de tamano fijo
    int frameCount = physicalMemorySize / frameSize;
    for (int i = 0; i < frameCount; i++)
    {
        this->frames.push_back(Frame(i));
    }
}

MemoryTranslator::~MemoryTranslator()
{
    
    delete this->strategy;
}

PhysicalAddress MemoryTranslator::translateAddress(const VirtualAddress& virtualAddress) const
{
    
    if (!VirtualAddress::isValidData(virtualAddress.getValue()))
    {
        throw InvalidAddressException(virtualAddress.getValue());
    }

    //se delego la traduccion a la estrategia activa, se pasa ambas tablas aunque solo use una
    return this->strategy->translate(virtualAddress, this->pageTable, this->segmentTable);
}

void MemoryTranslator::loadPageMapping(int pageNumber, int frameNumber)
{
    //se Valida que el marco exista dentro del rango de memoria fisica configurado
    if (frameNumber < 0 || frameNumber >= static_cast<int>(this->frames.size()))
    {
        throw TranslatorException("El marco solicitado esta fuera de rango");
    }

    this->frames.at(frameNumber).occupy();
    this->pageTable.addMapping(pageNumber, frameNumber);
}

void MemoryTranslator::loadSegment(int segmentNumber, int baseAddress, int limit)
{
    //se Valida que el segmento completo (base + limite) quepa dentro de la memoria fisica configurada
    if (baseAddress < 0 || (baseAddress + limit) > this->physicalMemorySize)
    {
        throw TranslatorException("El segmento solicitado excede el tamano de la memoria fisica");
    }

    this->segmentTable.addSegment(segmentNumber, baseAddress, limit);
}

void MemoryTranslator::setStrategy(TranslationStrategy* newStrategy)
{
    delete this->strategy; 
    this->strategy = newStrategy;
}

const std::vector<Frame>& MemoryTranslator::getFrames() const
{
    return this->frames;
}

const PageTable& MemoryTranslator::getPageTable() const
{
    return this->pageTable;
}

const SegmentTable& MemoryTranslator::getSegmentTable() const
{
    return this->segmentTable;
}