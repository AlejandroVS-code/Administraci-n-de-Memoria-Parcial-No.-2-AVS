/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 08/07/2026
   Version: 1.0
   Licencia: Uso academico, Universidad del Valle
   Descripcion: Implementacion de la estrategia Worst Fit
*/
#include "algorithms/WorstFit.h"
#include "model/MemoryBlock.h"

WorstFit::WorstFit()
{
}

WorstFit::~WorstFit()
{
}

int WorstFit::findBlock(const std::vector<MemoryBlock>& blocks, int requestedSize) const
{
    int worstIndex = -1;
    int worstSize = -1;

    for (size_t i = 0; i < blocks.size(); i++)
    {
        const MemoryBlock& currentBlock = blocks.at(i);
        if (currentBlock.isFree() && currentBlock.getSize() >= requestedSize)
        {
            if (worstIndex == -1 || currentBlock.getSize() > worstSize)
            {
                worstIndex = static_cast<int>(i);
                worstSize = currentBlock.getSize();
            }
        }
    }
    return worstIndex;
}

std::string WorstFit::getName() const
{
    return "Worst Fit";
}