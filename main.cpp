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
    a.mostrarAlumno(search);
    std::cout << "a.modificarAlumno(search);" << std::endl;
    a.modificarAlumno(search);
    std::cout << "a.mostrarAlumno(search);" << std::endl;
    a.mostrarAlumno(search);
    std::cout << "a.borrarAlumno(search);" << std::endl;
    a.borrarAlumno(search);
    std::cout << "a.listarAlumnos();" << std::endl;
    a.listarAlumnos();
    return 0;
}