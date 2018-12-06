#include <iostream>
#include <cstdlib>
#include "agenda.hpp"





void Agenda::reiniciarAlumnos()
{
  std::string option;

  do {
    system("clear");
    std::cout << "¿Está seguro de borrar toda la lista de alumnos actual? (S/N)" << std::endl;
    std::cin >> option;
  } while(option!="S" and option!="s" and option!="N" and option!="n");

  if(option=="S" or option=="s")
  {
    _alumnos.clear();
  }

  /* Mostrar menú */
  // system("clear");
  //

}

void Agenda::listarAlumnos()
{

}
