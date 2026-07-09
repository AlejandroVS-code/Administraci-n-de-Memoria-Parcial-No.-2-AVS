/* Autor: [Tu Nombre Completo]
   Correo: [tu.correo]@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 08/07/2026
   Version: 1.0
   Licencia: Uso academico, Universidad del Valle
   Descripcion: Implementacion de la estrategia First Fit
*/
#include "../../include/algorithms/FirstFit.h"
#include "../../include/model/MemoryBlock.h"

FirstFit::FirstFit()
{
}

FirstFit::~FirstFit()
{
}

int FirstFit::findBlock(const std::vector<MemoryBlock>& blocks, int requestedSize) const
{
    for (size_t i = 0; i < blocks.size(); i++)
    {
        const MemoryBlock& currentBlock = blocks.at(i);
        if (currentBlock.isFree() && currentBlock.getSize() >= requestedSize)
        {
            return static_cast<int>(i);
        }
    }
    return -1;
}

std::string FirstFit::getName() const
{
    return "First Fit";
}