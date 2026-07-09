/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 08/07/2026
   Version: 1.0
   Licencia: Uso academico, Universidad del Valle
   Descripcion: Implementacion de MemoryManager
*/
#include "../../include/core/MemoryManager.h"
#include "../../include/exceptions/InsufficientMemoryException.h"
#include "../../include/exceptions/ProcessNotFoundException.h"
#include "../../include/exceptions/InvalidSizeException.h"

MemoryManager::MemoryManager()
{
    this->totalSize = 0;
    this->allocation = nullptr;
}

MemoryManager::MemoryManager(int totalSize, Allocation* initialAllocation)
{
    this->totalSize = totalSize;
    this->allocation = initialAllocation;

    MemoryBlock initialBlock(0, totalSize);
    this->blocks.push_back(initialBlock);
}

MemoryManager::~MemoryManager()
{
    delete this->allocation;
}

bool MemoryManager::allocateProcess(const Process& process)
{
    if (!Process::isValidData(process.getRequestedSize()))
    {
        throw InvalidSizeException(process.getRequestedSize());
    }

    int blockIndex = this->allocation->findBlock(this->blocks, process.getRequestedSize());
    if (blockIndex == -1)
    {
        throw InsufficientMemoryException(process.getRequestedSize());
    }

    this->processes[process.getId()] = process;
    Process* storedProcess = &this->processes.at(process.getId());
    storedProcess->setAllocatedSize(process.getRequestedSize());

    int remainingSize = this->blocks.at(blockIndex).getSize() - process.getRequestedSize();
    if (remainingSize > 0)
    {
        int originalStart = this->blocks.at(blockIndex).getStartAddress();
        this->blocks.at(blockIndex).setSize(process.getRequestedSize());

        MemoryBlock newFreeBlock(originalStart + process.getRequestedSize(), remainingSize);
        this->blocks.insert(this->blocks.begin() + blockIndex + 1, newFreeBlock);
    }

    this->blocks.at(blockIndex).allocate(storedProcess);
    return true;
}

bool MemoryManager::releaseProcess(int processId)
{
    std::map<int, Process>::iterator processIterator = this->processes.find(processId);
    if (processIterator == this->processes.end())
    {
        throw ProcessNotFoundException(processId);
    }

    for (size_t i = 0; i < this->blocks.size(); i++)
    {
        MemoryBlock& currentBlock = this->blocks.at(i);
        if (!currentBlock.isFree() && currentBlock.getProcess() != nullptr && currentBlock.getProcess()->getId() == processId)
        {
            currentBlock.release();
            break;
        }
    }

    this->processes.erase(processIterator);
    this->mergeFreeBlocks();
    return true;
}

void MemoryManager::setAllocation(Allocation* newAllocation)
{
    delete this->allocation;
    this->allocation = newAllocation;
}

void MemoryManager::mergeFreeBlocks()
{
    for (size_t i = 0; i < this->blocks.size(); i++)
    {
        if (i + 1 < this->blocks.size())
        {
            MemoryBlock& currentBlock = this->blocks.at(i);
            MemoryBlock& nextBlock = this->blocks.at(i + 1);
            if (currentBlock.isFree() && nextBlock.isFree())
            {
                currentBlock.setSize(currentBlock.getSize() + nextBlock.getSize());
                this->blocks.erase(this->blocks.begin() + i + 1);
                i--;
            }
        }
    }
}

int MemoryManager::calculateExternalFragmentation() const
{
    int totalFree = 0;
    for (size_t i = 0; i < this->blocks.size(); i++)
    {
        if (this->blocks.at(i).isFree())
        {
            totalFree = totalFree + this->blocks.at(i).getSize();
        }
    }
    return totalFree;
}

int MemoryManager::calculateInternalFragmentation() const
{
    //Uso iterador aqui porque std::map no permite recorrido con indice como un vector
    int totalFragmentation = 0;
    std::map<int, Process>::const_iterator processIterator;
    for (processIterator = this->processes.begin(); processIterator != this->processes.end(); ++processIterator)
    {
        totalFragmentation = totalFragmentation + processIterator->second.getInternalFragmentation();
    }
    return totalFragmentation;
}

const std::vector<MemoryBlock>& MemoryManager::getBlocks() const
{
    return this->blocks;
}