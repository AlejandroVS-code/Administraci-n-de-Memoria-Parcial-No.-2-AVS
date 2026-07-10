/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 08/07/2026
   Version: 1.0
   Descripcion: Declaracion de CliMenu, la interfaz de consola
   del simulador. Ahora tambien permite cargar y ejecutar un
   archivo de entrada y cambiar de estrategia en caliente
*/
#ifndef CLI_MENU_H
#define CLI_MENU_H

#include "../core/MemoryManager.h"
#include "../io/SimulationFileReader.h"
#include <map> //Libreria para usar map, para el label->id dentro de loadAndRunFile

class CliMenu
{
private:
    //Atributos
    MemoryManager* manager; //No es dueno del manager, solo lo referencia (agregacion)
    SimulationFileReader fileReader; //Se guarda por valor, no necesita punteros

    void showMenu() const;
    void requestProcessCreation();
    void requestProcessRelease();
    void showMemoryState() const;
    void loadAndRunFile();
    void changeAllocationStrategy();
    void writeOutputFile(const std::string& outputPath) const;

public:
    //Metodos
    CliMenu(); //Constructor por defecto
    explicit CliMenu(MemoryManager* manager); //Constructor con parametros
    ~CliMenu(); //Destructor explicito, no borra el manager porque no es dueno

    void run();
};

#endif
