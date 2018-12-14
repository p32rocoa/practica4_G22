#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <list>
#include <string>
#include <fstream>
#include "agenda.hpp"
#include "persona.hpp"
#include "alumno.hpp"
#include "profesor.hpp"


Alumno Agenda::buscarAlumno(std::string dato)
{
  Alumno alumno;
  for (Alumno i : _alumnos)
  {
    if(i.getDNI() == dato)
      alumno = i;
  }
  return alumno;
}


std::list<Alumno> Agenda::buscarGrupo(int numGrupo)
{
  // toDo
}


void Agenda::insertarAlumno()
{
  Alumno new_alumno;
  std::string buffer;

  std::cout << "Introduce el DNI del alumno: ";
  std::getline(std::cin, buffer);
  new_alumno.setDNI(buffer);
  std::cout << "Introduce el nombre del alumno: ";
  std::getline(std::cin, buffer);
  new_alumno.setNombre(buffer);
  std::cout << "Introduce los apellidos del alumno: ";
  std::getline(std::cin, buffer);
  new_alumno.setApellidos(buffer);
  std::cout << "Introduce el correo del alumno: ";
  std::getline(std::cin, buffer);
  new_alumno.setCorreo_electronico(buffer);
  std::cout << "Introduce la fecha de nacimiento del alumno: ";
  std::getline(std::cin, buffer);
  new_alumno.setFecha_de_nacimiento(buffer);
  std::cout << "Introduce el domicilio del alumno: ";
  std::getline(std::cin, buffer);
  new_alumno.setDomicilio(buffer);
  std::cout << "Introduce el telefono del alumno: ";
  std::getline(std::cin, buffer);
  new_alumno.setTelefono(buffer);
  std::cout << "Introduce el curso del alumno: ";
  std::getline(std::cin, buffer);
  new_alumno.setCurso_mas_alto_matriculado(atoi(buffer.c_str()));
  std::cout << "Introduce el grupo del alumno (0 si no pertenece a ninguno): ";
  std::getline(std::cin, buffer);
  new_alumno.setGrupo(atoi(buffer.c_str()));

  if(atoi(buffer.c_str()) > 0)
  {
    std::cout << "Introduce si el alumno es lider (1 Si, 0 no): ";
    std::getline(std::cin, buffer);
    new_alumno.setRol(atoi(buffer.c_str()));
  }
  else
    new_alumno.setRol(0);

  _alumnos.push_back(new_alumno);
}


void Agenda::modificarAlumno(Alumno alumno)
{
  Alumno new_alumno;
  std::string buffer;

  std::cout << "Para omitir el campo a editar pulse enter dejando el campo vacío." << std::endl;
  std::cout << "Introduce el DNI del alumno (" << alumno.getDNI() << "): ";
  std::getline(std::cin, buffer);
  if(buffer!="")
    new_alumno.setDNI(buffer);
  std::cout << "Introduce el nombre del alumno (" << alumno.getNombre() << "): ";
  std::getline(std::cin, buffer);
  if(buffer!="")
    new_alumno.setNombre(buffer);
  std::cout << "Introduce los apellidos del alumno (" << alumno.getApellidos() << "): ";
  std::getline(std::cin, buffer);
  if(buffer!="")
    new_alumno.setApellidos(buffer);
  std::cout << "Introduce el correo del alumno (" << alumno.getCorreo_electronico() << "): ";
  std::getline(std::cin, buffer);
  if(buffer!="")
    new_alumno.setCorreo_electronico(buffer);
  std::cout << "Introduce la fecha de nacimiento del alumno (" << alumno.getFecha_de_nacimiento() << "): ";
  std::getline(std::cin, buffer);
  if(buffer!="")
    new_alumno.setFecha_de_nacimiento(buffer);
  std::cout << "Introduce el domicilio del alumno (" << alumno.getDomicilio() << "): ";
  std::getline(std::cin, buffer);
  if(buffer!="")
    new_alumno.setDomicilio(buffer);
  std::cout << "Introduce el telefono del alumno (" << alumno.getTelefono() << "): ";
  std::getline(std::cin, buffer);
  if(buffer!="")
    new_alumno.setTelefono(buffer);
  std::cout << "Introduce el curso del alumno (" << alumno.getCurso_mas_alto_matriculado() << "): ";
  std::getline(std::cin, buffer);
  if(buffer!="")
    new_alumno.setCurso_mas_alto_matriculado(atoi(buffer.c_str()));
  std::cout << "Introduce el grupo del alumno (0 si no pertenece a ninguno) (" << alumno.getGrupo() << "): ";
  std::getline(std::cin, buffer);
  if(buffer!="")
    new_alumno.setGrupo(atoi(buffer.c_str()));
  if(atoi(buffer.c_str()) > 0)
  {
    std::cout << "Introduce si el alumno es lider (1 Si, 0 no) (" << alumno.getRol() << "): ";
    std::getline(std::cin, buffer);
    if(buffer!="")
      new_alumno.setRol(atoi(buffer.c_str()));
  }
  else
    new_alumno.setRol(0);

  borrarAlumno(alumno);
  _alumnos.push_back(new_alumno);
}


void Agenda::borrarAlumno(Alumno alumno)
{
  Alumno search;
  search = buscarAlumno(alumno.getDNI());
  _alumnos.remove(search);
}


void Agenda::reiniciarAlumnos()
{
  std::string option;

  do {
    system("clear");
    std::cout << "¿Estás seguro de borrar toda la lista de alumnos actual? (S/N)" << std::endl;
    std::cin >> option;
  } while(option!="S" and option!="s" and option!="N" and option!="n");

  if(option=="S" or option=="s")  // Se limpia la lista
  {
    _alumnos.clear();
  }

}


void Agenda::listarAlumnos()
{
  std::string option, mode, type, fileName;
  std::list<Alumno>::iterator it, it2;
  int aux_it=1;

  if(_alumnos.empty())  // Se comprueba que la lista no esté vacía
  {
    system("clear");
    std::string foo;
    std::cout << "La lista de alumnos está vacía." << std::endl;
    std::cout << "\nPulsa ENTER para continuar..." << std::endl;
    std::cin >> foo;
  }
  else
  {
    do {
      system("clear");
      std::cout << "¿En qué formato se va a mostrar la lista?" << std::endl;
      std::cout << "\t1. Markdown." << std::endl;
      std::cout << "\t2. HTML." << std::endl;
      std::cin >> type;
    } while(type!="1" and type!="2");

    do {
      system("clear");
      std::cout << "¿Con qué dato quieres ordenar la lista?" << std::endl;
      std::cout << "\t1. Ordenar por apellidos." << std::endl;
      std::cout << "\t2. Ordenar por DNI." << std::endl;
      std::cout << "\t3. Ordenar por curso más alto matriculado." << std::endl;
      std::cin >> option;
    } while(option!="1" and option!="2" and option!="3");

    do {
      system("clear");
      std::cout << "¿En qué sentido se ordenará?" << std::endl;
      std::cout << "\t1. Ascendente." << std::endl;
      std::cout << "\t2. Descendente." << std::endl;
      std::cin >> mode;
    } while(mode!="1" and mode!="2");

    // Se ordena la lista de alumnos ascendentemente
    for(it=_alumnos.begin(); it!=prev(_alumnos.end()); it++) {
      for(it2=_alumnos.begin(); it2!=prev(_alumnos.end(), aux_it); it2++) {
        if((option=="1" and it2->getApellidos().compare(next(it2, 1)->getApellidos())>0) or
           (option=="2" and it2->getDNI().compare(next(it2, 1)->getDNI())>0) or
           (option=="3" and it2->getCurso_mas_alto_matriculado()>next(it2, 1)->getCurso_mas_alto_matriculado()))
        {
          std::swap(*it2, *next(it2, 1));
        }
      }
      aux_it++;
    }

    if(mode=="2") // Cambio a modo descendente
      _alumnos.reverse();

    // Markdown o HTML
    std::ifstream checkFile(fileName);
    system("clear");
    do {
      std::cout << "\nIntroduce el nombre que tendrá el fichero (sin extensión):" << std::endl;
      std::cin >> fileName;

      if(type=="1")
      fileName = fileName + ".md";
      else
      fileName = fileName + ".html";

      if (checkFile) {
        std::cout << "Error. El fichero introducido ya existe." << std::endl;
        checkFile.close();
      }
    } while(checkFile);

    std::ofstream fichero(fileName);
    if (!fichero) {
      std::cout << "Error al abrir el fichero." << '\n';
      return;
    }

    if(type=="1") // Markdown
    {
      fichero << "|DNI|Nombre|Apellidos|Correo electrónico|Fecha de nacimiento|Domicilio|Teléfono|";
      fichero << "Curso más alto matriculado|Grupo|¿Líder de grupo?|\n";
      fichero << "|---|---|---|---|---|---|---|---|---|---|\n";

      for(Alumno i: _alumnos)
      {
        fichero << "|"<<i.getDNI()<<"|"<<i.getNombre()<<"|"<<i.getApellidos()<<"|"<<i.getCorreo_electronico()<<"|";
        fichero << i.getFecha_de_nacimiento()<<"|"<<i.getDomicilio()<<"|"<<i.getTelefono()<<"|";
        fichero << i.getCurso_mas_alto_matriculado()<<"|"<<i.getGrupo()<<"|";
        if(i.getRol())
          fichero << "**Sí**|";
        else
          fichero << "No|";
      }
    }
    else  // HTML
    {
      fichero << "<!DOCTYPE html>\n";
      fichero << "<html>\n<head>\n<meta charset=\"utf-8\">\n<title>Lista alumnos</title>\n";
      fichero << "<style>\nth, td { border: 2px solid grey; }\n</style>\n</head>\n<body>\n";
      fichero << "<h1>Lista de alumnos</h1>\n<hr>\n<br>\n";
      fichero << "\n<table>\n<tr>\n<th>DNI</th>\n<th>Nombre</th>\n<th>Apellidos</th>\n";
      fichero << "<th>E-mail</th>\n<th>Fecha nacimiento</th>\n<th>Domicilio</th>\n";
      fichero << "<th>Teléfono</th>\n<th>Curso más alto</th>\n<th>Grupo</th>\n<th>¿Líder de grupo?</th>\n</tr>\n";

      for(Alumno i : _alumnos)
      {
        fichero << "<tr>\n<td>" << i.getDNI() << "</td>\n";
        fichero << "<td>" << i.getNombre() << "</td>\n";
        fichero << "<td>" << i.getApellidos() << "</td>\n";
        fichero << "<td>" << i.getCorreo_electronico() << "</td>\n";
        fichero << "<td>" << i.getFecha_de_nacimiento() << "</td>\n";
        fichero << "<td>" << i.getDomicilio() << "</td>\n";
        fichero << "<td>" << i.getTelefono() << "</td>\n";
        fichero << "<td>" << i.getCurso_mas_alto_matriculado() << "</td>\n";
        fichero << "<td>" << i.getGrupo() << "</td>\n";
        if(i.getRol())
          fichero << "<td><b>Sí</b></td>\n";
        else
          fichero << "<td>No</td>\n";

        fichero << "</tr>\n";
      }
      fichero << "</table>\n</body>\n</html>";
    }
    fichero.close();
  }
}


void Agenda::mostrarAlumno(Alumno alumno)
{
  std::cout << "DNI: " << std::endl;
  std::cout << alumno.getDNI() << std::endl;
  std::cout << "Nombre: " << std::endl;
  std::cout << alumno.getNombre() << std::endl;
  std::cout << "Apellidos: " << std::endl;
  std::cout << alumno.getApellidos() << std::endl;
  std::cout << "Correo: " << std::endl;
  std::cout << alumno.getCorreo_electronico() << std::endl;
  std::cout << "Fecha de nacimiento: " << std::endl;
  std::cout << alumno.getFecha_de_nacimiento() << std::endl;
  std::cout << "Domicilio: " << std::endl;
  std::cout << alumno.getDomicilio() << std::endl;
  std::cout << "Telefono: " << std::endl;
  std::cout << alumno.getTelefono() << std::endl;
  std::cout << "Curso: " << std::endl;
  std::cout << alumno.getCurso_mas_alto_matriculado() << std::endl;
  std::cout << "Grupo: " << std::endl;
  std::cout << alumno.getGrupo() << std::endl;
  std::cout << "Lider: " << std::endl;
  if(alumno.getRol())
    std::cout << "Si" << std::endl;
  else
    std::cout << "No" << std::endl;
}


void Agenda::mostrarGrupo(std::list<Alumno> grupo)
{
  // toDo
}
