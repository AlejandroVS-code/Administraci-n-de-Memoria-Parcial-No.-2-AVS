/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 09/07/2026
   Ultima modificacion: 09/07/2026
   Version: 1.0
   Descripcion: Declaracion de SegmentationFaultException
*/
#ifndef SEGMENTATION_FAULT_EXCEPTION_H
#define SEGMENTATION_FAULT_EXCEPTION_H

#include "TranslatorException.h"

// Se lanza cuando el segmento no existe o el desplazamiento
// solicitado excede el limite del segmento
class SegmentationFaultException : public TranslatorException
{
public:
    SegmentationFaultException(int segmentNumber, int offset);
    ~SegmentationFaultException();
};

#endif