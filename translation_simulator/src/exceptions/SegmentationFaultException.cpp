/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Implementacion de SegmentationFaultException
*/
#include "exceptions/SegmentationFaultException.h"
#include <sstream> 

//Funcion auxiliar para armar el mensaje antes de pasarselo al constructor de la clase base
static std::string buildMessage(int segmentNumber, int offset)
{
    std::stringstream messageStream;
    messageStream << "Fallo de segmentacion: el segmento " << segmentNumber << " no existe o el offset " << offset << " excede su limite";
    return messageStream.str();
}

SegmentationFaultException::SegmentationFaultException(int segmentNumber, int offset) : TranslatorException(buildMessage(segmentNumber, offset))
{
}

SegmentationFaultException::~SegmentationFaultException()
{
}