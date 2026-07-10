/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Declaracion de TranslationFileReader, lee el
   archivo de entrada y lo convierte en una lista de TranslationCommand
*/
#ifndef TRANSLATION_FILE_READER_H
#define TRANSLATION_FILE_READER_H

#include <vector> 
#include <string> 
#include "TranslationCommand.h"

class TranslationFileReader
{
private:
    bool isCommentOrEmptyLine(const std::string& line) const;
    std::string trim(const std::string& text) const;
    TranslationCommand parseLine(const std::string& line) const;

public:
    TranslationFileReader(); //Constructor por defecto
    ~TranslationFileReader(); //Destructor

    std::vector<TranslationCommand> readCommands(const std::string& filePath) const;
};

#endif