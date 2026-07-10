/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Implementacion de TranslationCommand
*/
#include "io/TranslationCommand.h"

TranslationCommand::TranslationCommand()
{
    //Constructor por defecto, un MAP_PAGE vacio como valor neutro
    this->type = TranslationCommandType::MAP_PAGE;
    this->firstValue = 0;
    this->secondValue = 0;
    this->thirdValue = 0;
}

TranslationCommand::TranslationCommand(TranslationCommandType type, int firstValue, int secondValue, int thirdValue)
{
    this->type = type;
    this->firstValue = firstValue;
    this->secondValue = secondValue;
    this->thirdValue = thirdValue;
}

TranslationCommand::~TranslationCommand()
{
    //Destructor vacio, no maneja punteros
}

TranslationCommandType TranslationCommand::getType() const
{
    return this->type;
}

int TranslationCommand::getFirstValue() const
{
    return this->firstValue;
}

int TranslationCommand::getSecondValue() const
{
    return this->secondValue;
}

int TranslationCommand::getThirdValue() const
{
    return this->thirdValue;
}