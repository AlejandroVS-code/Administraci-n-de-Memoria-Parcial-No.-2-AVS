/* Autor: [Tu Nombre Completo]
   Correo: [tu.correo]@correounivalle.edu.co
   Fecha de creacion: 08/07/2026
   Ultima modificacion: 08/07/2026
   Version: 1.0
   Licencia: Uso academico, Universidad del Valle
   Descripcion: Declaracion de la clase Process, representa un
   proceso que solicita memoria en el simulador
*/
#ifndef PROCESS_H
#define PROCESS_H

#include <string> //Libreria para usar string

// Representa un proceso que solicita memoria en el simulador
class Process
{
private:
    //Atributos
    int id;
    std::string name;
    int requestedSize;
    int allocatedSize;

public:
    //Metodos
    Process(); //Constructor por defecto
    Process(int id, const std::string& name, int requestedSize); //Constructor con parametros
    ~Process(); //Destructor explicito

    //Valida los datos ANTES de construir el objeto, en vez de lanzar excepcion en el constructor
    static bool isValidData(int requestedSize);

    int getId() const;
    std::string getName() const;
    int getRequestedSize() const;
    int getAllocatedSize() const;

    void setAllocatedSize(int size);

    //Diferencia entre el tamano asignado y el solicitado (fragmentacion interna de este proceso)
    int getInternalFragmentation() const;
};

#endif
