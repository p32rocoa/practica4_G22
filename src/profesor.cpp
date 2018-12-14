#include <fstream>
#include <list>
#include <iostream>
#include <cstdlib>
#include "profesor.hpp"
#include "alumno.hpp"
#include "agenda.hpp"
#include "persona.hpp"


void Profesor::buscarProfesor()
{
  // toDo
}


void borrarProfesor()
{
  // toDo
}


void Profesor::iniciarSesion()
{
  // toDo
}


void Profesor::cerrarSesion()
{
  // toDo
}


void Profesor::guardarBD()
{
  std::ofstream fichero("DataBase.bin", std::ofstream::binary);
  std::list<Alumno>::iterator it;

  if(fichero.is_open())
  {
    // for(it=agenda_._alumnos.begin(); it!=agenda_._alumnos.end(); it++)
    // {
    //   fichero.write((char *)it->getDNI().c_str(), sizeof(it->getDNI().c_str()));
    //   fichero.write((char *)it->getNombre().c_str(), sizeof(it->getNombre().c_str())));
    //   fichero.write((char *)it->getApellidos().c_str(), sizeof(it->getApellidos().c_str()));
    //   fichero.write((char *)it->getCorreo_electronico().c_str(), sizeof(it->getCorreo_electronico().c_str()));
    //   fichero.write((char *)it->getFecha_de_nacimiento().c_str(), sizeof(it->getFecha_de_nacimiento().c_str()));
    //   fichero.write((char *)it->getDomicilio().c_str(), sizeof(it->getDomicilio().c_str()));
    //   fichero.write((char *)it->getTelefono().c_str(), sizeof(it->getTelefono().c_str()));
    //   fichero.write((char *)it->getCurso_mas_alto_matriculado().c_str(), sizeof(it->getCurso_mas_alto_matriculado().c_str()));
    //   fichero.write((char *)it->getGrupo().c_str(), sizeof(it->getGrupo().c_str()));
    //   fichero.write((char *)it->getRol().c_str(), sizeof(it->getRol().c_str()));
    // }

    fichero.close();
  }
}

void Profesor::cargarBD()
{
  Alumno new_alumno;
  std::ifstream fichero("DataBase.bin", std::ifstream::binary);
  int size=0;
  std::string aux_buffer;

  if(fichero.is_open())
  {
    fichero.seekg(0, std::ifstream::end);
    size = (int) fichero.tellg();
    fichero.seekg(0, std::ifstream::beg);

    // toDo Limpiar lista

    // while(fichero.tellg()<size)
    // {
    //   // toDo read
    // }

    fichero.close();
  }
}

void Profesor::guardarCopia()
{
  if(getTipo())
  {
    // toDo write
  }
  else
  {
    std::string foo;
    system("clear");
    std::cout << "Permiso denegado." << std::endl;
    std::cout << "\nPulsa ENTER para continuar." << std::endl;
    std::cin >> foo;
  }
}

void Profesor::cargarCopia()
{
  if(getTipo())
  {
    // toDo read
  }
  else
  {
    std::string foo;
    system("clear");
    std::cout << "Permiso denegado." << std::endl;
    std::cout << "\nPulsa ENTER para continuar." << std::endl;
    std::cin >> foo;
  }
}
