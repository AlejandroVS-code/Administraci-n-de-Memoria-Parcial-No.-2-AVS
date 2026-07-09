/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 08/07/2026
   Version: 1.0
   Licencia: Uso academico, Universidad del Valle
   Descripcion: Implementacion de SimulationFileReader
*/
#include "io/SimulationFileReader.h"
#include "exceptions/SimulatorException.h"
#include "exceptions/InvalidCommandException.h"
#include <fstream> //Libreria para leer el archivo con ifstream
#include <sstream> //Libreria para separar los campos con stringstream

SimulationFileReader::SimulationFileReader()
{
    //Constructor vacio, esta clase no tiene atributos propios
}

SimulationFileReader::~SimulationFileReader()
{
    //Destructor vacio
}

bool SimulationFileReader::isCommentOrEmptyLine(const std::string& line) const
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

std::string SimulationFileReader::trim(const std::string& text) const
{
    //Quito espacios al inicio y al final del texto, paso a paso, sin nada compacto
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

Command SimulationFileReader::parseLine(const std::string& line) const
{
    //Separo la linea por ';' y guardo cada campo en un vector
    std::vector<std::string> fields;
    std::stringstream lineStream(line);
    std::string field;

    while (std::getline(lineStream, field, ';'))
    {
        fields.push_back(this->trim(field));
    }

    //Debe tener exactamente 3 campos: label, size, action
    if (fields.size() != 3)
    {
        throw InvalidCommandException(line);
    }

    std::string label = fields.at(0);
    std::string sizeText = fields.at(1);
    std::string actionText = fields.at(2);

    if (actionText.size() != 1)
    {
        throw InvalidCommandException(line);
    }

    char action = actionText.at(0);
    if (action != 'C' && action != 'R')
    {
        throw InvalidCommandException(line);
    }

    int size = 0;
    try
    {
        size = std::stoi(sizeText);
    }
    catch (const std::exception&)
    {
        //Si el campo de tamano no es un numero valido, tambien es un comando invalido
        throw InvalidCommandException(line);
    }

    CommandType type;
    if (action == 'C')
    {
        type = CommandType::CREATE;
    }
    else
    {
        type = CommandType::RELEASE;
    }

    return Command(type, label, size);
}

std::vector<Command> SimulationFileReader::readCommands(const std::string& filePath) const
{
    std::ifstream inputFile(filePath);
    if (!inputFile.is_open())
    {
        throw SimulatorException("No se pudo abrir el archivo: " + filePath);
    }

    std::vector<Command> commands;
    std::string line;

    while (std::getline(inputFile, line))
    {
        //Windows guarda los saltos de linea como \r\n, pero std::getline en Linux
        //solo corta en el \n y deja el \r pegado al final de la linea
        //Lo quito aqui para que no se cuele como parte del ultimo campo (la accion C/R)
        if (!line.empty() && line.at(line.size() - 1) == '\r')
        {
            line = line.substr(0, line.size() - 1);
        }

        if (this->isCommentOrEmptyLine(line))
        {
            continue;
        }
        Command parsedCommand = this->parseLine(line);
        commands.push_back(parsedCommand);
    }

    inputFile.close();
    return commands;
}