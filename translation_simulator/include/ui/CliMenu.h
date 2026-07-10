/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Declaracion de CliMenu para Implementacion 2
*/
#ifndef CLI_MENU_H
#define CLI_MENU_H

#include "../core/MemoryTranslator.h"
#include "../io/TranslationFileReader.h"

class CliMenu
{
private:

    MemoryTranslator* translator; //solo referencia (agregacion)
    TranslationFileReader fileReader; //Se guarda por valor, no necesita punteros

    void showMenu() const;
    void requestPageMapping();
    void requestSegmentMapping();
    void requestAddressTranslation();
    void loadAndRunFile();
    void showState() const;
    void changeStrategy();
    void writeOutputFile(const std::string& inputFileName, const std::string& content) const;

public:
    CliMenu(); //Constructor por defecto
    explicit CliMenu(MemoryTranslator* translator); //Constructor con parametros
    ~CliMenu(); //Destructor 

    void run();
};

#endif