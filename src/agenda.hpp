#ifndef AGENDA_HPP
#define AGENDA_HPP

#include <list>
#include <string>
#include "alumno.hpp"
#include "profesor.hpp"


class Agenda
{
  private:

    // Lista de alumnos
    std::list<Alumno> _alumnos;

    // Funciones internas de búsqueda
    Alumno buscarAlumno(std::string dato);
    std::list<Alumno> buscarGrupo(int numGrupo);

  public:

    // Constructor
    Agenda(){};

    // Observador de la lista de alumnos
    std::list<Alumno> * getLista() {return &_alumnos;}

    // Modificadores de datos de alumnos
    void insertarAlumno();
    void modificarAlumno(Alumno alumno);
    void borrarAlumno(Alumno alumno);
    void reiniciarAlumnos();

    // Observadores de datos de alumnos
    void listarAlumnos();
    void mostrarAlumno();
    void mostrarGrupo();

};

#endif
