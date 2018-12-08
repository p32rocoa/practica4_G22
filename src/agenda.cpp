#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <string>
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

  if(option=="S" or option=="s")
  {
    _alumnos.clear();
  }

}


void Agenda::listarAlumnos()
{
  std::string option, mode, type;
  std::list<Alumno>::iterator it, it2;

  if(_alumnos.empty())
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

    // Se ordena la lista
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

    // toDo Pedir nombre del fichero 

    if(type==1)
    {
      // toDo Markdown
    }
    else
    {
      // toDo HTML
    }

  }
}
