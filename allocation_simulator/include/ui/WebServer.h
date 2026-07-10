/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 10/07/2026
   Ultima modificacion: 10/07/2026
   Version: 1.0
   Descripcion: Declaracion de WebServer, expone una API HTTP sobre
   MemoryManager como un plus grafico ademas del menu de consola
*/
#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include "../core/MemoryManager.h"
#include "../io/SimulationFileReader.h"
#include <string>

class WebServer
{
private:
    MemoryManager* manager; 
    SimulationFileReader fileReader;
    int port;

    std::string buildStateJson() const;
    std::string buildErrorJson(const std::string& message) const;
    std::string escapeJson(const std::string& text) const;

public:
    WebServer(); //Constructor por defecto
    WebServer(MemoryManager* manager, int port); //Constructor con parametros
    ~WebServer(); //Destructor explicito, 

    void start(); //Bloqueante, se corre en un hilo aparte desde main.cpp
};

#endif