#include <fstream>
#include <list>
#include "profesor.hpp"
#include "alumno.hpp"


void Profesor::guardarBD()
{
  std::ofstream fichero("DataBase.bin", ios::out | ios::binary);
  std::list<Alumno>::iterator it;

  if(fichero)
  {
    for(it=agenda_._alumnos.begin(); it!=agenda_._alumnos.end(); it++)
    {
      //fichero.write();
    }

    fichero.close();
  }
}

void Profesor::cargarBD()
{
  std::ifstream fichero("DataBase.bin", ios::in | ios::binary);
  std::list<Alumno>::iterator it;

  if(fichero)
  {
    for(it=agenda_._alumnos.begin(); it!=agenda_._alumnos.end(); it++)
    {
      //fichero.read();
    }

    fichero.close();
  }
}
