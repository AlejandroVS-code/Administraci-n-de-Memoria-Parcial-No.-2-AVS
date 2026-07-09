/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 08/07/2026
   Version: 1.0
   Licencia: Uso academico, Universidad del Valle
   Descripcion: Punto de entrada de Implementacion 1, el simulador
   de asignacion de memoria
*/
#include "core/MemoryManager.h"
#include "ui/CliMenu.h"
#include "algorithms/FirstFit.h"

int main()
{
    //Tamano total de la memoria simulada, coincide con los archivos de prueba en data/allocation/
    int totalMemorySize = 1000;

    //La memoria arranca con First Fit, el usuario puede cambiar de estrategia desde el menu
    MemoryManager manager(totalMemorySize, new FirstFit());

    CliMenu menu(&manager);
    menu.run();

    return 0;
}