#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include "persona.hpp"
#include "alumno.hpp"
#include "profesor.hpp"
#include "agenda.hpp"

int main ()
{
  std::string auxMenu="repetir", foo;
  Profesor p;

  // Menú principal
  while(true){

    // Menú de inicio
    while(auxMenu=="repetir") {
      do {
        system("clear");
        std::cout << "Introduce el número de la opción deseada:\n" << std::endl;
        std::cout << "\t1. Registrarse" << std::endl;
        std::cout << "\t2. Iniciar sesión" << std::endl;
        std::cout << "\t0. Salir" << std::endl;

        // Comprobando menú de inicio
        std::cout << "\n\nOpción: ";
        std::cin >> auxMenu;
        getchar();

        if(auxMenu!="1" and auxMenu!="2" and auxMenu!="0") {
  				std::cout << "Debes introducir un número que esté en el menú de opciones.\n";
          std::cout << "\n\nPulsa ENTER para continuar." << std::endl;
          std::getline(std::cin, foo);
  				auxMenu = "redo";
  			}
      } while(auxMenu=="redo");

      if(auxMenu=="1")
      {
        p.registrarse();
        auxMenu="repetir";
      }
      else if(auxMenu=="2")
      {
        p.iniciarSesion(p);
      }
      else
      {
        std::cout << "\n\nCerrando la aplicación..." << std::endl;
        exit(EXIT_SUCCESS);
      }
    }

    // Interfaz menú principal
    do {
      system("clear");
      std::cout << "Introduce el número de la opción deseada:\n" << std::endl;
      std::cout << "\t1. Gestionar alumnos" << std::endl;
      std::cout << "\t2. Mostrar la lista de alumnos" << std::endl;
      std::cout << "\t3. Mostrar alumno" << std::endl;
      std::cout << "\t4. Mostrar grupo\n" << std::endl;

      if(p.getTipo())
        std::cout << "\t5. Importar lista" << std::endl;
      else
        std::cout << "\t5. Cargar base de datos" << std::endl;

      if(p.getTipo())
        std::cout << "\t6. Exportar lista" << std::endl;
      else
        std::cout << "\t6. Guardar base de datos" << std::endl;

      if(p.getTipo())
        std::cout << "\n\t7. Borrar profesor" << std::endl;

      std::cout << "\n\t0. Cerrar Sesión" << std::endl;

      // Comprobando menú principal
      std::cout << "\n\nOpción: ";
      std::cin >> auxMenu;
      getchar();

      if((!p.getTipo() and auxMenu=="7") or (auxMenu!="1" and auxMenu!="2" and auxMenu!="3" and auxMenu!="4"
      and auxMenu!="5" and auxMenu!="6" and auxMenu!="7" and auxMenu!="0")) {
        std::cout << "Debes introducir un número que esté en el menú de opciones.\n";
        std::cout << "\n\nPulsa ENTER para continuar." << std::endl;
        std::getline(std::cin, foo);
        auxMenu = "redo2";
      }
    } while(auxMenu=="redo2");

    if(auxMenu=="1")
    {
      //Menú de gestión de alumnos
      do {
        system("clear");
        std::cout << "Gestión de alumnos:\n" << std::endl;
        std::cout << "\t1. Insertar alumno" << std::endl;
        std::cout << "\t2. Modificar alumno" << std::endl;
        std::cout << "\t3. Borrar alumno" << std::endl;
        std::cout << "\t4. Borrar lista de alumnos\n" << std::endl;

        std::cout << "\t0. Atrás" << std::endl;

        // Comprobación de menú de gestión de alumnos
        std::cout << "\n\nOpción: ";
        std::cin >> auxMenu;
        getchar();

        if(auxMenu!="1" and auxMenu!="2" and auxMenu!="3" and auxMenu!="4" and auxMenu!="0") {
          std::cout << "Debes introducir un número que esté en el menú de opciones.\n";
          std::cout << "\n\nPulsa ENTER para continuar." << std::endl;
          std::getline(std::cin, foo);
          auxMenu = "redoGestion";
        }
      } while(auxMenu=="redoGestion");

      if(auxMenu=="1")
      {
        p.getAgenda()->insertarAlumno();
      }
      else if(auxMenu=="2")
      {
        // p.getAgenda()->modificarAlumno();
      }
      else if(auxMenu=="3")
      {
        // p.getAgenda()->borrarAlumno();
      }
      else if(auxMenu=="4")
      {
        p.getAgenda()->reiniciarAlumnos();
      }
      else
      {
        // Atrás
      }
    }
    else if(auxMenu=="2")
    {
      p.getAgenda()->listarAlumnos();
    }
    else if(auxMenu=="3")
    {
      p.getAgenda()->mostrarAlumno();
    }
    else if(auxMenu=="4")
    {
      p.getAgenda()->mostrarGrupo();
    }
    else if(auxMenu=="5")
    {
      //Menú Importar
      if(p.getTipo()) // Coordinador
      {
        do {
          system("clear");
          std::cout << "Importar lista:" << std::endl;
          std::cout << "\t1. Cargar base de datos" << std::endl;
          std::cout << "\t2. Cargar copia de seguridad\n" << std::endl;

          std::cout << "\t0. Volver al menú principal" << std::endl;

          // Comprobación de menú de importación
          std::cout << "\n\nOpción: ";
          std::cin >> auxMenu;
          getchar();

          if(auxMenu!="1" and auxMenu!="2" and auxMenu!="0") {
            std::cout << "Debes introducir un número que esté en el menú de opciones.\n";
            std::cout << "\n\nPulsa ENTER para continuar." << std::endl;
            std::getline(std::cin, foo);
            auxMenu = "redoImportar";
          }
        } while(auxMenu=="redoImportar");

        if(auxMenu=="1")
        {
          p.cargarBD();
        }
        else if(auxMenu=="2")
        {
          p.cargarCopia();
        }
        else
        {
          // Menú principal
        }
      }
      else  // Ayudante
      {
        p.cargarBD();
      }
    }
    else if(auxMenu=="6")
    {
      //Menú Exportar
      if(p.getTipo()) // Coordinador
      {
        do {
          system("clear");
          std::cout << "Exportar lista:" << std::endl;
          std::cout << "\t1. Guardar lista en la base de datos" << std::endl;
          std::cout << "\t2. Guardar lista en una copia de seguridad\n" << std::endl;

          std::cout << "\t0. Volver al menú principal" << std::endl;

          // Comprobación de menú de exportación
          std::cout << "\n\nOpción: ";
          std::cin >> auxMenu;
          getchar();

          if(auxMenu!="1" and auxMenu!="2" and auxMenu!="0") {
            std::cout << "Debes introducir un número que esté en el menú de opciones.\n";
            std::cout << "\n\nPulsa ENTER para continuar." << std::endl;
            std::getline(std::cin, foo);
            auxMenu = "redoExportar";
          }
        } while(auxMenu=="redoExportar");

        if(auxMenu=="1")
        {
          p.guardarBD();
        }
        else if(auxMenu=="2")
        {
          p.guardarCopia();
        }
        else
        {
          // Menú principal
        }
      }
      else  // Ayudante
      {
        p.guardarBD();
      }
    }
    else if(auxMenu=="7")
    {
      p.borrarProfesor();
    }
    else
    {
      p.cerrarSesion(p);
      auxMenu="repetir";
    }

  }

    return 0;
}
