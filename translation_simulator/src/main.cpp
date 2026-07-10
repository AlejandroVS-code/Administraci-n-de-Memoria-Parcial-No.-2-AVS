/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 10/07/2026
   Version: 1.1
   Descripcion: Punto de entrada de Implementacion 2, el simulador
   de traduccion de direcciones virtuales a fisicas. Corre el menu
   de consola de siempre, y ademas levanta un servidor web en un
   hilo aparte como interfaz grafica adicional
*/
#include "core/MemoryTranslator.h"
#include "ui/CliMenu.h"
#include "ui/WebServer.h"
#include "algorithms/PagingStrategy.h"
#include <thread>
#include <iostream>

int main()
{
    //Tamano de memoria fisica y de marco
    int physicalMemorySize = 1024;
    int frameSize = 64;

    //Arranca con Paginacion, el usuario puede cambiar a Segmentacion desde el menu
    MemoryTranslator translator(physicalMemorySize, frameSize, new PagingStrategy(frameSize));

    //El servidor web corre en su propio hilo, como un plus sobre el menu de consola
    //Uso detach() porque cuando el usuario sale del menu y el programa termina,
    //el proceso completo se cierra y el hilo del servidor se cierra con el
    WebServer webServer(&translator, 8081);
    std::thread webServerThread(&WebServer::start, &webServer);
    webServerThread.detach();

    std::cout << "Interfaz web disponible en http://localhost:8081 (ademas del menu de consola)" << std::endl;

    CliMenu menu(&translator);
    menu.run();

    return 0;
}