#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <string>
#include <fstream>
#include "agenda.hpp"
#include "persona.hpp"
#include "alumno.hpp"


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
  int count=0;

  if(_alumnos.empty())  // Se comprueba que la lista no esté vacía
  {
    system("clear");
    std::cout << "La lista de alumnos está vacía." << std::endl;
    std::cout << "\nPulsa ENTER para continuar..." << std::endl;
    getchar();
  }
  else
  {
    do {
      system("clear");
      std::cout << "¿En qué formato se va a mostrar la lista?" << std::endl;
      std::cout << "\t1. Markdown." << std::endl;
      std::cout << "\t2. HTML." << std::endl;
      std::cin >> type;
    } while(type!=1 and type!=2);

    do {
      system("clear");
      std::cout << "¿Con qué dato quieres ordenar la lista?" << std::endl;
      std::cout << "\t1. Ordenar por apellidos." << std::endl;
      std::cout << "\t2. Ordenar por DNI." << std::endl;
      std::cout << "\t3. Ordenar por curso más alto matriculado." << std::endl;
      std::cin >> option;
    } while(option!=1 and option!=2 and option!=3);

    do {
      system("clear");
      std::cout << "¿En qué sentido se ordenará?" << std::endl;
      std::cout << "\t1. Ascendente." << std::endl;
      std::cout << "\t2. Descendente." << std::endl;
      std::cin >> mode;
    } while(mode!=1 and mode!=2);

    // Se ordena la lista de alumnos
    for(it=_alumnos.begin(); it!=(_alumnos.end()-1); it++) {
      for(it2=_alumnos.begin(); it2!=(_alumnos.end()-it-1); it2++) {
        if((option==1 and it2->getApellidos().compare((it2+1)->getApellidos())>0) or
           (option==2 and it2->getDNI().compare((it2+1)->getDNI())>0) or
           (option==3 and it2->getCurso_mas_alto_matriculado()>(it2+1)->getCurso_mas_alto_matriculado()))
        {
          std::swap(*it2, *(it2+1));
        }
      }
    }

    if(mode==2) // Cambio a modo descendente
      _alumnos.reverse();

    // Markdown o HTML
    system("clear");
    do {
      std::cout << "\nIntroduce el nombre que tendrá el fichero (sin extensión):" << std::endl;
      std::cin >> fileName;

      if(type=1)
      fileName = fileName + ".md";
      else
      fileName = fileName + ".html";

      std::ifstream checkFile(fileName);
      if (checkFile) {
        std::cout << "Error. El fichero introducido ya existe." << std::endl;
        checkFile.close();
      }
    } while(checkFile);

    std::ofstream fichero(fileName);
    if (!fichero) {
      std::cout << "Error al abrir el fichero." << '\n';
      exit(-1);
    }

    if(type==1) // Markdown
    {
      fichero << "|DNI|Nombre|Apellidos|Correo electrónico|Fecha de nacimiento|Domicilio|Teléfono|";
      fichero << "Curso más alto matriculado|Grupo|¿Líder de grupo?|\n";
      fichero << "|---|---|---|---|---|---|---|---|---|---|\n";
      for(Alumno i: _alumnos)
      {
        ++count;
        fichero << "|"+i.getDNI()+"|"+i.getNombre()+"|"+i.getApellidos()+"|"+i.getCorreo_electronico()+"|";
        fichero << i.getFecha_de_nacimiento()+"|"+i.getDomicilio()+"|"+i.getTelefono()+"|";
        fichero << i.getCurso_mas_alto_matriculado()+"|"+i.getGrupo()+"|";
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
        ++count;
        fichero << "<tr>\n<td>" + i.getDNI() + "</td>\n";
        fichero << "<td>" + i.getNombre() + "</td>\n";
        fichero << "<td>" + i.getApellidos() + "</td>\n";
        fichero << "<td>" + i.getCorreo_electronico() + "</td>\n";
        fichero << "<td>" + i.getFecha_de_nacimiento() + "</td>\n";
        fichero << "<td>" + i.getDomicilio() + "</td>\n";
        fichero << "<td>" + i.getTelefono() + "</td>\n";
        fichero << "<td>" + i.getCurso_mas_alto_matriculado() + "</td>\n";
        fichero << "<td>" + i.getGrupo() + "</td>\n";
        if(i.getRol())
          fichero << "<td><b>Sí</b></td>\n";
        else
          fichero << "<td>No</td>\n";

        fichero << "</tr>\n";
      }
      fichero << "</table>\n</body>\n</html>"
    }
    fichero.close();
  }
}
