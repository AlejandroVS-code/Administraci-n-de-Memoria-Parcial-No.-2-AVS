/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 10/07/2026
   Version: 1.1
   Licencia: Uso academico, Universidad del Valle
   Descripcion: Punto de entrada de Implementacion 1. Corre el menu
   de consola de siempre, y ademas levanta un servidor web en un
   hilo aparte como interfaz grafica adicional
*/
#include "core/MemoryManager.h"
#include "ui/CliMenu.h"
#include "ui/WebServer.h"
#include "algorithms/FirstFit.h"
#include <thread>
#include <iostream>

int main()
{
    int totalMemorySize = 1000;
    MemoryManager manager(totalMemorySize, new FirstFit());

    //El servidor web corre en su propio hilo, como un plus sobre el menu de consola
    //Uso detach() porque cuando el usuario sale del menu y el programa termina,
    //el proceso completo se cierra y el hilo del servidor se cierra con el
    WebServer webServer(&manager, 8080);
    std::thread webServerThread(&WebServer::start, &webServer);
    webServerThread.detach();

    std::cout << "Interfaz web disponible en http://localhost:8080 (ademas del menu de consola)" << std::endl;

    CliMenu menu(&manager);
    menu.run();

    return 0;
}