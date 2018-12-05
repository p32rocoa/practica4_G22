#include <list>
#include <string>
#include "Alumno.hpp"


class Agenda
{
  private:

    // Lista de alumnos
    std::list<Alumno> _alumnos;

    // Funciones internas de búsqueda
    Alumno buscarAlumno(std::string dato);
    std::list<Alumno> buscarGrupo(int numGrupo);

  public:

    // Modificadores de datos de alumnos
    void insertarAlumno();
    void modificarAlumno(Alumno alumno);
    void borrarAlumno(Alumno alumno);
    void reiniciarAlumnos();

    // Observadores de datos de alumnos
    void listarAlumnos();
    void mostrarAlumno(Alumno alumno);
    void mostrarGrupo(std::list<Alumno> grupo);
    
};
