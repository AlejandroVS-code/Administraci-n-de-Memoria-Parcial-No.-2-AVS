/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 08/07/2026
   Version: 1.0
   Descripcion: Declaracion de Command, representa una linea ya
   interpretada del archivo de entrada (label; size; action)
*/
#ifndef COMMAND_H
#define COMMAND_H

#include <string> //Libreria para usar string

enum class CommandType
{
    CREATE,
    RELEASE
};

// Representa una instruccion parseada del archivo de entrada
class Command
{
private:
    //Atributos
    CommandType type;
    std::string label;
    int size;

public:
    //Metodos
    Command(); //Constructor por defecto
    Command(CommandType type, const std::string& label, int size); //Constructor con parametros
    ~Command(); //Destructor explicito

    CommandType getType() const;
    std::string getLabel() const;
    int getSize() const;
};

#endif