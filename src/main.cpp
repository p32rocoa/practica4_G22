#include <iostream>
#include "persona.hpp"
#include "profesor.hpp"
#include "agenda.hpp"

int main ()
{
    std::cout << "IS" << std::endl;
    Agenda a;
    Alumno search;
    std::string buffer;
    a.insertarAlumno();
    std::cout << "Introduzca el DNI del alumno a buscar: ";
    std::getline(std::cin, buffer);
    search = a.buscarAlumno(buffer);
    a.mostrarAlumno(search);
    a.modificarAlumno(search);
    search = a.buscarAlumno(buffer);
    a.mostrarAlumno(search);
    a.borrarAlumno(search);
    a.listarAlumnos();
    return 0;
}