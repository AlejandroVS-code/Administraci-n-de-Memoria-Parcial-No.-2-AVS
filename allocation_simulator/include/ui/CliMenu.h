/* Autor: [Tu Nombre Completo]
   Correo: [tu.correo]@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 08/07/2026
   Version: 1.0
   Licencia: Uso academico, Universidad del Valle
   Descripcion: Declaracion de CliMenu, la interfaz de consola
   del simulador de asignacion de memoria
*/
#ifndef CLI_MENU_H
#define CLI_MENU_H

#include "../core/MemoryManager.h" 

// Interfaz de consola del simulador, solo depende de MemoryManager
class CliMenu
{
private:
    //Atributos
    MemoryManager* manager; 

    void showMenu() const;
    void requestProcessCreation();
    void requestProcessRelease();
    void showMemoryState() const;

public:
    //Metodos
    CliMenu(); //Constructor por defecto
    explicit CliMenu(MemoryManager* manager); //Constructor con parametros
    ~CliMenu(); //Destructor explicito, no borra el manager porque no es dueno

    void run();
};

#endif
