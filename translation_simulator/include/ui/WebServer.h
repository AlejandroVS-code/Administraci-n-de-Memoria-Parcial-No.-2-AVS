/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Declaracion de CliMenu para Implementacion 2
*/
#ifndef WEB_SERVER_H
#define WEB_SERVER_H
#include "../core/MemoryTranslator.h"
#include "../io/TranslationFileReader.h"
#include <string>

class WebServer
{
private:
    MemoryTranslator* translator;
    TranslationFileReader fileReader;
    int port;

    std::string buildStateJson() const;
    std::string buildErrorJson(const std::string& message) const;
    std::string escapeJson(const std::string& text) const;

public:
    WebServer();
    WebServer(MemoryTranslator* translator, int port);
    ~WebServer();

    void start();
};
#endif