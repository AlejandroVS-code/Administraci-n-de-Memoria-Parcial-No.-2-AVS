/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 08/07/2026
   Version: 1.0
   Descripcion: Declaracion de SimulationFileReader, lee el archivo
   de entrada y lo convierte en una lista de Command. No conoce
   MemoryManager ni Allocation, solo se encarga de parsear texto
*/
#ifndef SIMULATION_FILE_READER_H
#define SIMULATION_FILE_READER_H

#include <vector> //Libreria para usar vector
#include <string> //Libreria para usar string
#include "Command.h"

class SimulationFileReader
{
private:
    //Metodos auxiliares privados
    bool isCommentOrEmptyLine(const std::string& line) const;
    std::string trim(const std::string& text) const;
    Command parseLine(const std::string& line) const;

public:
    //Metodos
    SimulationFileReader(); //Constructor por defecto
    ~SimulationFileReader(); //Destructor explicito

    //Lee el archivo completo y devuelve todos los comandos parseados
    std::vector<Command> readCommands(const std::string& filePath) const;
};

#endif