/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Declaracion de TranslationCommand, representa una
   linea ya interpretada del archivo de entrada (type;v1;v2;v3)
*/
#ifndef TRANSLATION_COMMAND_H
#define TRANSLATION_COMMAND_H

enum class TranslationCommandType
{
    MAP_PAGE,
    MAP_SEGMENT,
    TRANSLATE
};

// Representa una instruccion parseada del archivo de entrada de Implementacion 2
class TranslationCommand
{
private:
    TranslationCommandType type;
    int firstValue;
    int secondValue;
    int thirdValue;

public:

    TranslationCommand(); //Constructor por defecto
    TranslationCommand(TranslationCommandType type, int firstValue, int secondValue, int thirdValue); //Constructor con parametros
    ~TranslationCommand(); //Destructor 

    TranslationCommandType getType() const;
    int getFirstValue() const;
    int getSecondValue() const;
    int getThirdValue() const;
};

#endif