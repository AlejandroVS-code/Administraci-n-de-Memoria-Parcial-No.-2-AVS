/* Autor: [Tu Nombre Completo]
   Correo: [tu.correo]@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Licencia: Uso academico, Universidad del Valle
   Descripcion: Punto de entrada de Implementacion 2, el simulador
   de traduccion de direcciones virtuales a fisicas
*/
#include "core/MemoryTranslator.h"
#include "ui/CliMenu.h"
#include "algorithms/PagingStrategy.h"

int main()
{
    //Tamano de memoria fisica y de marco, coinciden con los archivos de prueba en data/translation/
    int physicalMemorySize = 1024;
    int frameSize = 64;

    //Arranca con Paginacion, el usuario puede cambiar a Segmentacion desde el menu
    MemoryTranslator translator(physicalMemorySize, frameSize, new PagingStrategy(frameSize));

    CliMenu menu(&translator);
    menu.run();

    return 0;
}