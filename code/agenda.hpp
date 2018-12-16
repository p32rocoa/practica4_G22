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
    Alumno buscarAlumno(std::string search, int key = 1)
    {
      Alumno alumno;
      std::list<Alumno> alumnos;

      if (search != "" and key == 1)
      {
        for (Alumno i : _alumnos)
        {
          if(i.getDNI() == search)
            return i;
        }
      }
      else if (search != "" and key == 2)
      {
        for (Alumno i : _alumnos)
        {
          if(i.getApellidos() == search)
            alumnos.push_back(i);
        }
      }

      if (alumnos.size() == 1)
        return alumnos.front();
      else if (alumnos.size() > 1)
      {
        system("clear");
        std::cout << "Hay varios alumnos con los mismos apellidos, introduzca el DNI:" << std::endl;
        for (Alumno i : alumnos)
          std::cout << i.getNombre() << " " << i.getApellidos() << ", " << i.getDNI() << std::endl;

        std::getline(std::cin, search);
        if (search != "")
        {
          for (Alumno i : alumnos)
          {
            if(i.getDNI() == search)
              return i;
          }
        }
      }
      return alumno;
    }
    std::list<Alumno> buscarGrupo(int numGrupo)
    {
      std::list<Alumno> grupo;

      for (Alumno i : _alumnos)
      {
        if(i.getGrupo() == numGrupo and i.getRol())
          grupo.push_back(i);
      }

      for (Alumno i : _alumnos)
      {
        if(i.getGrupo() == numGrupo and !i.getRol())
          grupo.push_back(i);
      }

      return grupo;
    }

  public:

    // Constructor
    Agenda(){};

    // Observador de la lista de alumnos
    std::list<Alumno> * getLista() {return &_alumnos;}

    // Modificadores de datos de alumnos
    void insertarAlumno();
    void modificarAlumno(Alumno &alumno);
    void borrarAlumno(Alumno &alumno);
    void reiniciarAlumnos();

    // Observadores de datos de alumnos
    void listarAlumnos();
    void mostrarAlumno();
    void mostrarGrupo();

    // Aux
    Alumno generateAlumno(Alumno alumno, int mod);

};

#endif
