/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 08/07/2026
   Version: 1.0
   Licencia: Uso academico, Universidad del Valle
   Descripcion: Implementacion de la estrategia Best Fit
*/
#include "algorithms/BestFit.h"
#include "model/MemoryBlock.h"

BestFit::BestFit()
{
}

BestFit::~BestFit()
{
}

int BestFit::findBlock(const std::vector<MemoryBlock>& blocks, int requestedSize) const
{
    int bestIndex = -1;
    int bestSize = -1;

    for (size_t i = 0; i < blocks.size(); i++)
    {
        const MemoryBlock& currentBlock = blocks.at(i);
        if (currentBlock.isFree() && currentBlock.getSize() >= requestedSize)
        {
            if (bestIndex == -1 || currentBlock.getSize() < bestSize)
            {
                bestIndex = static_cast<int>(i);
                bestSize = currentBlock.getSize();
            }
        }
    }
    return bestIndex;
}

std::string BestFit::getName() const
{
    return "Best Fit";
}