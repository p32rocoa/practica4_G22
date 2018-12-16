#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <list>
#include <string>
#include <fstream>
#include "profesor.hpp"
#include "agenda.hpp"
#include "persona.hpp"
#include "alumno.hpp"



void Agenda::insertarAlumno()
{
  std::string foo;

  if(_alumnos.size() >= 150)
  {
    system("clear");
    std::cout << "No se pueden insertar más alumnos, la lista está llena." << std::endl;
    std::cout << "\nPulsa ENTER para continuar..." << std::endl;
    std::getline(std::cin, foo);
    return;
  }

  Alumno trash, alumno;
  alumno = generateAlumno(trash, 0);
  trash = buscarAlumno(alumno.getDNI());
  if(trash.getDNI() == "")
  {
    int repeated_email = 0;
    for (Alumno i : _alumnos)
    {
      if(i.getCorreo_electronico() == alumno.getCorreo_electronico())
        repeated_email = 1;
    }
    if(!repeated_email)
      _alumnos.push_back(alumno);
    else
    {
      std::cout << "Ya existe un alumno con ese email\nPulsa ENTER para continuar..." << std::endl;
      std::getline(std::cin, foo);
    }
  }
  else
  {
    std::cout << "Ya existe un alumno con ese DNI\nPulsa ENTER para continuar..." << std::endl;
    std::getline(std::cin, foo);
  }
}


void Agenda::modificarAlumno(Alumno &alumno)
{
  std::string key = "1";
  std::string buffer, foo;
  int repeated_email = 0;

  if(alumno.getDNI() == "")
  {
    system("clear");
    do {
      std::cout << "Introduce 1 si quieres buscar al alumno por DNI, y 0 si es por apellidos." << std::endl;
      std::cin >> key;
      getchar();
    } while(key!="1" and key!="0");

    system("clear");
    if(key=="1")
      std::cout << "Introduzca DNI: ";
    else
      std::cout << "Introduzca Apellidos: ";

    std::getline(std::cin, buffer);

    if(key=="1")
      alumno = this->buscarAlumno(buffer, 1);
    else
      alumno = this->buscarAlumno(buffer, 0);
  }

  if(alumno.getDNI() != "")
  {
    Alumno new_alumno, trash;
    new_alumno = generateAlumno(alumno, 1);
    if(alumno.getDNI() != new_alumno.getDNI())
    {
      trash = buscarAlumno(new_alumno.getDNI());
    }
    if(alumno.getCorreo_electronico() != new_alumno.getCorreo_electronico())
    {
      repeated_email = 0;
      for (Alumno i : _alumnos)
      {
        if(i.getCorreo_electronico() == new_alumno.getCorreo_electronico())
          repeated_email = 1;
      }
    }
    if(trash.getDNI() != "")
    {
      std::cout << "Ya existe un alumno con ese DNI\nPulsa ENTER para continuar..." << std::endl;
      std::getline(std::cin, foo);
    }
    else if(repeated_email)
    {
      std::cout << "Ya existe un alumno con ese email\nPulsa ENTER para continuar..." << std::endl;
      std::getline(std::cin, foo);
    }
    else
    {
      borrarAlumno(alumno);
      alumno = new_alumno;
      _alumnos.push_back(new_alumno);
    }
  }
  else
  {
    system("clear");
    std::cout << "No existe el alumno." << std::endl;
    std::cout << "\nPulsa ENTER para continuar..." << std::endl;
    std::getline(std::cin, foo);
  }
}


void Agenda::borrarAlumno(Alumno &alumno)
{
  Alumno search;
  std::string dni, foo;

  if (alumno.getDNI() != "")
    search = buscarAlumno(alumno.getDNI());
  else
  {
    system("clear");
    std::cout << "Introduce el dni del alumno a borrar: ";
    std::getline(std::cin, dni);
    search = buscarAlumno(dni);
  }

  if(search.getDNI() != "")
  {
    system("clear");
    std::cout << "Alumno no encontrado." << std::endl;
    std::cout << "\nPulsa ENTER para continuar..." << std::endl;
    std::getline(std::cin, foo);
  }
  else
  {
    _alumnos.remove(search);

    system("clear");
    std::cout << "Se ha borrado al alumno indicado de la lista." << std::endl;
    std::cout << "\nPulsa ENTER para continuar..." << std::endl;
    std::getline(std::cin, foo);
  }
}


void Agenda::reiniciarAlumnos()
{
  std::string option;

  do {
    system("clear");
    std::cout << "¿Estás seguro de borrar toda la lista de alumnos actual? (S/N)" << std::endl;
    std::cin >> option;
    getchar();
  } while(option!="S" and option!="s" and option!="N" and option!="n");

  if(option=="S" or option=="s")  // Se limpia la lista
  {
    _alumnos.clear();
  }

}


void Agenda::listarAlumnos()
{
  std::string option, mode, type, fileName, foo;
  std::list<Alumno>::iterator it, it2;
  int aux_it=1;

  if(_alumnos.empty())  // Se comprueba que la lista no esté vacía
  {
    system("clear");
    std::cout << "La lista de alumnos está vacía." << std::endl;
    std::cout << "\nPulsa ENTER para continuar..." << std::endl;
    std::getline(std::cin, foo);
  }
  else
  {
    do {
      system("clear");
      std::cout << "¿En qué formato se va a mostrar la lista?" << std::endl;
      std::cout << "\t1. Markdown." << std::endl;
      std::cout << "\t2. HTML." << std::endl;
      std::cin >> type;
      getchar();
    } while(type!="1" and type!="2");

    do {
      system("clear");
      std::cout << "¿Con qué dato quieres ordenar la lista?" << std::endl;
      std::cout << "\t1. Ordenar por apellidos." << std::endl;
      std::cout << "\t2. Ordenar por DNI." << std::endl;
      std::cout << "\t3. Ordenar por curso más alto matriculado." << std::endl;
      std::cin >> option;
      getchar();
    } while(option!="1" and option!="2" and option!="3");

    do {
      system("clear");
      std::cout << "¿En qué sentido se ordenará?" << std::endl;
      std::cout << "\t1. Ascendente." << std::endl;
      std::cout << "\t2. Descendente." << std::endl;
      std::cin >> mode;
      getchar();
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
      getchar();

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
      std::cout << "Error al abrir el fichero." << std::endl;
      std::cout << "\n\nPulsa ENTER para continuar." << std::endl;
      std::getline(std::cin, foo);
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
          fichero << "**Sí**|\n";
        else
          fichero << "No|\n";
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

    system("clear");
    std::cout << "El archivo ha sido creado.\n";
    std::cout << "\n\nPulsa ENTER para continuar." << std::endl;
    std::getline(std::cin, foo);
  }
}


void Agenda::mostrarAlumno()
{
  std::string foo, type, tipoBusqueda, dato, fileName;
  Alumno alum;

  if(_alumnos.empty())  // Se comprueba que la lista no esté vacía
  {
    system("clear");
    std::cout << "La lista de alumnos está vacía." << std::endl;
    std::cout << "\nPulsa ENTER para continuar..." << std::endl;
    std::getline(std::cin, foo);
    return;
  }

  do {
    system("clear");
    std::cout << "¿En qué formato se va a mostrar?" << std::endl;
    std::cout << "\t1. Markdown." << std::endl;
    std::cout << "\t2. HTML." << std::endl;
    std::cin >> type;
    getchar();
  } while(type!="1" and type!="2");

  do {
    system("clear");
    std::cout << "¿Cómo se va a buscar al alumno?" << std::endl;
    std::cout << "\t1. Por DNI." << std::endl;
    std::cout << "\t2. Por Apellidos." << std::endl;
    std::cin >> tipoBusqueda;
    getchar();
  } while(type!="1" and type!="2");

  system("clear");
  std::cout << "Introduce el dato del alumno:" << std::endl;
  std::getline(std::cin, dato);
  // getchar();

  alum = buscarAlumno(dato, atoi(tipoBusqueda.c_str()));

  if(alum.getDNI()=="")
  {
    system("clear");
    std::cout << "Ese alumno no está en la lista." << std::endl;
    std::cout << "\nPulsa ENTER para continuar..." << std::endl;
    std::getline(std::cin, foo);
    return;
  }

  // Markdown o HTML
  std::ifstream checkFile(fileName);
  system("clear");
  do {
    std::cout << "\nIntroduce el nombre que tendrá el fichero (sin extensión):" << std::endl;
    std::cin >> fileName;
    getchar();

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
    std::cout << "Error al abrir el fichero." << std::endl;
    std::cout << "\n\nPulsa ENTER para continuar." << std::endl;
    std::getline(std::cin, foo);
    return;
  }

  if(type=="1") // Markdown
  {
    fichero << "## Ficha de alumno\n\n---\n\n\n";
    fichero << "- **DNI:** " << alum.getDNI() << "\n";
    fichero << "- **Nombre completo:** *" << alum.getNombre() << " " << alum.getApellidos() << "*\n";
    fichero << "- **Fecha de nacimiento:** " << alum.getFecha_de_nacimiento() << "\n";
    fichero << "- **Curso más alto matriculado:** " << alum.getCurso_mas_alto_matriculado() << "\n\n\n\n";
    fichero << "+ **Grupo:** " << alum.getGrupo() << "\n";

    if(alum.getRol())
      fichero << "+ **Rol dentro del grupo** Líder \n\n\n\n";
    else
      fichero << "+ **Rol dentro del grupo** Miembro \n\n\n\n";

    fichero << "- **Correo electrónico:** *" << alum.getCorreo_electronico() << "*\n";
    fichero << "- **Teléfono:** " << alum.getTelefono() << "\n";
    fichero << "- **Domicilio:** *" << alum.getDomicilio() << "*\n";
  }
  else  // HTML
  {
    fichero << "<!DOCTYPE html>\n";
    fichero << "<html>\n<head>\n<meta charset=\"utf-8\">\n<title>Ficha alumno</title>\n";
    fichero << "</head>\n<body>\n<h2>Ficha de alumno</h2>\n<hr>\n<br>\n\n";
    fichero << "<ul>\n<li> <b>DNI:</b> "<< alum.getDNI() << " </li>\n";
    fichero << "<li> <b>Nombre completo:</b> <i> " << alum.getNombre() << " " << alum.getApellidos() << " </i> </li>\n";
    fichero << "<li> <b>Fecha de nacimiento:</b> " << alum.getFecha_de_nacimiento() << " </li>\n";
    fichero << "<li> <b>Curso más alto matriculado:</b> " << alum.getCurso_mas_alto_matriculado() << " </li>\n";
    fichero << "<br>\n<li> <b>Grupo:</b> " << alum.getGrupo() << " </li>\n";

    if(alum.getRol())
      fichero << "<li> <b>Rol dentro del grupo:</b> Líder </li>\n";
    else
      fichero << "<li> <b>Rol dentro del grupo:</b> Miembro </li>\n";

    fichero << "<br>\n<li> <b>Correo electrónico:</b> <i>" << alum.getCorreo_electronico() << "</i> </li>\n";
    fichero << "<li> <b>Teléfono:</b> " << alum.getTelefono() << " </li>\n";
    fichero << "<li> <b>Domicilio:</b> <i> " << alum.getDomicilio() << " </i> </li>\n";
    fichero << "</ul>\n</body>\n</html>";
  }
  fichero.close();

  system("clear");
  std::cout << "El archivo ha sido creado.\n";
  std::cout << "\n\nPulsa ENTER para continuar." << std::endl;
  std::getline(std::cin, foo);
}


void Agenda::mostrarGrupo()
{
  std::string foo, type, fileName;
  std::list<Alumno> grupo;
  int dato;


  if(_alumnos.empty())  // Se comprueba que la lista no esté vacía
  {
    system("clear");
    std::cout << "La lista de alumnos está vacía." << std::endl;
    std::cout << "\nPulsa ENTER para continuar..." << std::endl;
    std::getline(std::cin, foo);
    return;
  }

  do {
    system("clear");
    std::cout << "¿En qué formato se va a mostrar?" << std::endl;
    std::cout << "\t1. Markdown." << std::endl;
    std::cout << "\t2. HTML." << std::endl;
    std::cin >> type;
    getchar();
  } while(type!="1" and type!="2");

  system("clear");
  std::cout << "Introduce el grupo a mostrar:" << std::endl;
  std::cin >> dato;
  getchar();

  grupo = buscarGrupo(dato);

  if(grupo.size()==0)
  {
    system("clear");
    std::cout << "Este grupo no existe en la lista." << std::endl;
    std::cout << "\nPulsa ENTER para continuar..." << std::endl;
    std::getline(std::cin, foo);
    return;
  }

  // Markdown o HTML
  std::ifstream checkFile(fileName);
  system("clear");
  do {
    std::cout << "\nIntroduce el nombre que tendrá el fichero (sin extensión):" << std::endl;
    std::cin >> fileName;
    getchar();

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
    std::cout << "Error al abrir el fichero." << std::endl;
    std::cout << "\n\nPulsa ENTER para continuar." << std::endl;
    std::getline(std::cin, foo);
    return;
  }

  std::list<Alumno>::iterator it;
  it=grupo.begin();

  if(type=="1") // Markdown
  {
    fichero << "## Grupo: " << dato << "\n\n---\n\n\n";
    fichero << "- **Líder del grupo:** ***" << it->getNombre() << " " << it->getApellidos() << "*** ---- **" << it->getDNI() << "**\n\n";
    it++;
    fichero << "- **Resto de miembros:**\n";

    while(it!=grupo.end())
    {
      fichero << "\t-  *" << it->getNombre() << " " << it->getApellidos() << "* ---- " << it->getDNI() << "\n";
      it++;
    }

  }
  else  // HTML
  {
    fichero << "<!DOCTYPE html>\n";
    fichero << "<html>\n<head>\n<meta charset=\"utf-8\">\n<title>Ficha grupo</title>\n";
    fichero << "</head>\n<body>\n<h2>Grupo: " << dato << "</h2>\n<hr>\n<br>\n\n";
    fichero << "<ul>\n<li> <b>Líder del grupo:</b> <b><i> " << it->getNombre() << " " << it->getApellidos() << " </i></b> ---- <b>" << it->getDNI() <<"</b> </li>\n";
    it++;
    fichero << "<br>\n<li> <b>Resto de miembros:</b> </li>\n<ul>\n";

    while(it!=grupo.end())
    {
      fichero << "<li> " << it->getNombre() << " " << it->getApellidos() << " ---- " << it->getDNI() << " </li>\n";
      it++;
    }

    fichero << "</ul>\n</ul>\n</body>\n</html>";
  }
  fichero.close();

  system("clear");
  std::cout << "El archivo ha sido creado.\n";
  std::cout << "\n\nPulsa ENTER para continuar." << std::endl;
  std::getline(std::cin, foo);

}

Alumno Agenda::generateAlumno(Alumno alumno, int mod)
{
  Alumno new_alumno(alumno);
  std::string buffer;

  std::cout << "\nIntroduce el DNI del alumno";

  if (mod)
    std::cout << " (" << alumno.getDNI() << ")";

  std::cout << ": ";
  std::getline(std::cin, buffer);
  if(buffer!="")
    new_alumno.setDNI(buffer);

  std::cout << "Introduce el nombre del alumno";
  if (mod)
    std::cout << " (" << alumno.getNombre() << ")";

  std::cout << ": ";
  std::getline(std::cin, buffer);
  if(buffer!="")
    new_alumno.setNombre(buffer);

  std::cout << "Introduce los apellidos del alumno";
  if (mod)
    std::cout << " (" << alumno.getApellidos() << ")";

  std::cout << ": ";
  std::getline(std::cin, buffer);
  if(buffer!="")
    new_alumno.setApellidos(buffer);

  std::cout << "Introduce el correo del alumno";
  if (mod)
    std::cout << " (" << alumno.getCorreo_electronico() << ")";

  std::cout << ": ";
  std::getline(std::cin, buffer);
  if(buffer!="")
    new_alumno.setCorreo_electronico(buffer);

  std::cout << "Introduce la fecha de nacimiento del alumno";
  if (mod)
    std::cout << " (" << alumno.getFecha_de_nacimiento() << ")";

  std::cout << ": ";
  std::getline(std::cin, buffer);
  if(buffer!="")
    new_alumno.setFecha_de_nacimiento(buffer);

  std::cout << "Introduce el domicilio del alumno";
  if (mod)
    std::cout << " (" << alumno.getDomicilio() << ")";

  std::cout << ": ";
  std::getline(std::cin, buffer);
  if(buffer!="")
    new_alumno.setDomicilio(buffer);

  std::cout << "Introduce el telefono del alumno";
  if (mod)
    std::cout << " (" << alumno.getTelefono() << ")";

  std::cout << ": ";
  std::getline(std::cin, buffer);
  if(buffer!="")
    new_alumno.setTelefono(buffer);

  std::cout << "Introduce el curso mas alto matriculado del alumno";
  if (mod)
    std::cout << " (" << alumno.getCurso_mas_alto_matriculado() << ")";

  std::cout << ": ";
  std::getline(std::cin, buffer);
  if(buffer!="")
    new_alumno.setCurso_mas_alto_matriculado(atoi(buffer.c_str()));

  std::cout << "Introduce el grupo del alumno (0 si no pertenece a ninguno)";
  if (mod)
    std::cout << " (" << alumno.getGrupo() << ")";

  std::cout << ": ";
  std::getline(std::cin, buffer);
  if(buffer!="")
    new_alumno.setGrupo(atoi(buffer.c_str()));

  if(atoi(buffer.c_str()) > 0)
  {
    std::cout << "Introduce si el alumno es lider (1 Si, 0 no) ";
    if (mod)
      std::cout << " (" << alumno.getRol() << ")";
    std::cout << ": ";
    std::getline(std::cin, buffer);
    if(buffer!="")
    {
      if(atoi(buffer.c_str()) == 1)
      {
        for(Alumno i : _alumnos)
        {
          if(i.getGrupo() == new_alumno.getGrupo() and i.getRol() == 1)
            i.setRol(0);
        }
      }
      new_alumno.setRol(atoi(buffer.c_str()));
    }
  }
  else
    new_alumno.setRol(0);

  return new_alumno;
}
