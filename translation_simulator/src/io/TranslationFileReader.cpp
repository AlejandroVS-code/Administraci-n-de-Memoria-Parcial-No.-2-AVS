/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Implementacion de TranslationFileReader
*/
#include "../../include/io/TranslationFileReader.h"
#include "../../include/exceptions/TranslatorException.h"
#include "../../include/exceptions/InvalidCommandException.h"
#include <fstream> 
#include <sstream> 

TranslationFileReader::TranslationFileReader()
{
    //Constructor vacio, esta clase no tiene atributos propios
}

TranslationFileReader::~TranslationFileReader()
{
    //Destructor vacio
}

bool TranslationFileReader::isCommentOrEmptyLine(const std::string& line) const
{
    std::string trimmedLine = this->trim(line);
    if (trimmedLine.empty())
    {
        return true;
    }
    if (trimmedLine.at(0) == '#')
    {
        return true;
    }
    return false;
}

std::string TranslationFileReader::trim(const std::string& text) const
{
    size_t start = 0;
    size_t end = text.size();

    while (start < end && text.at(start) == ' ')
    {
        start++;
    }
    while (end > start && text.at(end - 1) == ' ')
    {
        end--;
    }
    return text.substr(start, end - start);
}

TranslationCommand TranslationFileReader::parseLine(const std::string& line) const
{
    
    std::vector<std::string> fields;
    std::stringstream lineStream(line);
    std::string field;

    while (std::getline(lineStream, field, ';'))
    {
        fields.push_back(this->trim(field));
    }

    //Siempre deben ser 4 campos: type, v1, v2, v3 (algunos quedan en 0 sin usar)
    if (fields.size() != 4)
    {
        throw InvalidCommandException(line);
    }

    std::string typeText = fields.at(0);
    if (typeText.size() != 1)
    {
        throw InvalidCommandException(line);
    }

    char typeChar = typeText.at(0);
    if (typeChar != 'P' && typeChar != 'S' && typeChar != 'T')
    {
        throw InvalidCommandException(line);
    }

    int firstValue = 0;
    int secondValue = 0;
    int thirdValue = 0;
    try
    {
        firstValue = std::stoi(fields.at(1));
        secondValue = std::stoi(fields.at(2));
        thirdValue = std::stoi(fields.at(3));
    }
    catch (const std::exception&)
    {
        //Si algun campo numerico no es valido, tambien es un comando invalido
        throw InvalidCommandException(line);
    }

    TranslationCommandType type;
    if (typeChar == 'P')
    {
        type = TranslationCommandType::MAP_PAGE;
    }
    else if (typeChar == 'S')
    {
        type = TranslationCommandType::MAP_SEGMENT;
    }
    else
    {
        type = TranslationCommandType::TRANSLATE;
    }

    return TranslationCommand(type, firstValue, secondValue, thirdValue);
}

std::vector<TranslationCommand> TranslationFileReader::readCommands(const std::string& filePath) const
{
    std::ifstream inputFile(filePath);
    if (!inputFile.is_open())
    {
        throw TranslatorException("No se pudo abrir el archivo: " + filePath);
    }

    std::vector<TranslationCommand> commands;
    std::string line;

    while (std::getline(inputFile, line))
    {
        if (!line.empty() && line.at(line.size() - 1) == '\r')
        {
            line = line.substr(0, line.size() - 1);
        }

        if (this->isCommentOrEmptyLine(line))
        {
            continue;
        }
        TranslationCommand parsedCommand = this->parseLine(line);
        commands.push_back(parsedCommand);
    }

    inputFile.close();
    return commands;
}