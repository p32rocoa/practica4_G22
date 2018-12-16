#include <fstream>
#include <list>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include "profesor.hpp"
#include "alumno.hpp"
#include "agenda.hpp"
#include "persona.hpp"


Profesor * Profesor::buscarProfesor(std::string username, std::string &pass)
{
  Profesor * p = new Profesor;
  DataProfesor dp;
  std::list<DataProfesor> ldp;
  int size=0;

  std::ifstream fichero("registro_profesores.bin", std::ifstream::binary);

  if(fichero.is_open())
  {
    fichero.seekg(0, std::ios::end);
    size = (int) fichero.tellg();
    fichero.seekg(0, std::ios::beg);

    while(fichero.tellg() < size)
    {
      fichero.read((char *)&dp, sizeof(DataProfesor));
      ldp.push_back(dp);
    }

    std::list<DataProfesor>::iterator it;

    for(it=ldp.begin(); it!=ldp.end(); it++)
    {
      if(strcmp(username.c_str(),it->email)==0)
      {
        p->setCorreo_electronico(it->email);
        p->setTipo(it->tipo);
        pass = it->password;
        return p;
      }
    }

  }

  return NULL;
}


void Profesor::borrarProfesor()
{
  DataProfesor dp;
  std::list<DataProfesor> ldp;
  int size=0;
  std::string target, foo, aux;
  std::ifstream fichero("registro_profesores.bin", std::ifstream::binary);

  if(getTipo()) // Coordinador
  {
    if(fichero.is_open())
    {
      fichero.seekg(0, std::ios::end);
      size = (int) fichero.tellg();
      fichero.seekg(0, std::ios::beg);

      while(fichero.tellg() < size) // Lectura del registro
      {
        fichero.read((char *)&dp, sizeof(DataProfesor));
        ldp.push_back(dp);
      }
      fichero.close();
      std::list<DataProfesor>::iterator it;

      system("clear");
      std::cout << "Usuarios Registrados:\n" << std::endl;

      for(it=ldp.begin(); it!=ldp.end(); it++)
      {
        aux = (it->tipo)?"Coordinador":"Ayudante";
        std::cout << it->email << "------" << aux << std::endl;
      }
      std::cout << "\nIntroduce el usuario a eliminar: ";
      std::cin >> target;
      getchar();

      for(it=ldp.begin(); it!=ldp.end(); it++)
      {
        if(strcmp(target.c_str(),it->email)==0)
        {
          if((it->tipo) or (getCorreo_electronico()==it->email))  // Se comprueba que no es un coordinador ni el usuario actual
          {
            system("clear");
            std::cout << "No puedes eliminar a un coordinador." << std::endl;
            std::cout << "\nPulsa ENTER para continuar." << std::endl;
            std::getline(std::cin, foo);
            return;
          }

          ldp.erase(it);  // Borrado del profesor indicado

          std::ofstream fichero2("registro_profesores.bin", std::ofstream::binary);

          for(it=ldp.begin(); it!=ldp.end(); it++)
          {
            fichero2.write((char *)&(*it), sizeof(DataProfesor));
          }
          fichero2.close();
          system("clear");
          std::cout << "El profesor indicado ha sido borrado del registro.\n";
          std::cout << "\n\nPulsa ENTER para continuar." << std::endl;
          std::getline(std::cin, foo);
          return;
        }
      }
      system("clear");
      std::cout << "El dato introducido no es un usuario existente." << std::endl;
      std::cout << "\nPulsa ENTER para continuar." << std::endl;
      std::getline(std::cin, foo);
    }
  }
  else
  {
    system("clear");
    std::cout << "Permiso denegado." << std::endl;
    std::cout << "\nPulsa ENTER para continuar." << std::endl;
    std::getline(std::cin, foo);
  }
}


void Profesor::registrarse()
{
  Profesor * p;
  DataProfesor dp, new_dp;
  std::list<DataProfesor> ldp;
  std::string target, foo, password;
  int size=0, coordinador=0;
  std::list<DataProfesor>::iterator it;

  std::ifstream fichero("registro_profesores.bin", std::ifstream::binary);

  if(fichero.is_open())
  {
    fichero.seekg(0, std::ios::end);
    size = (int) fichero.tellg();
    fichero.seekg(0, std::ios::beg);

    while(fichero.tellg() < size) // Lectura del registro
    {
      fichero.read((char *)&dp, sizeof(DataProfesor));
      ldp.push_back(dp);

      if(dp.tipo)
        coordinador++;
    }
    fichero.close();
  }

  if(coordinador==0)
  {
    system("clear");
    std::cout << "Al no haber un coordinador entre los usuarios, se realizará un registro como profesor coordinador.\n" << std::endl;
    new_dp.tipo = true;
  }
  else
  {
    system("clear");
    std::cout << "Al existir ya un coordinador, se realizará un registro como profesor ayudante.\n" << std::endl;
    new_dp.tipo = false;
  }

  std::cout << "Introduce el e-mail a registrar: ";
  std::cin >> target;
  getchar();

  p = buscarProfesor(target, foo);
  if(p!=NULL)
  {
    system("clear");
    std::cout << "Registro denegado. Este usuario ya existe." << std::endl;
    std::cout << "\nPulsa ENTER para continuar." << std::endl;
    std::getline(std::cin, foo);
    return;
  }
  strcpy(new_dp.email, target.c_str());

  std::cout << "Introduce la contraseña: ";
  std::cin >> password;
  getchar();

  strcpy(new_dp.password, password.c_str());
  ldp.push_back(new_dp);

  std::ofstream fichero2("registro_profesores.bin", std::ofstream::binary);

  for(it=ldp.begin(); it!=ldp.end(); it++)
  {
    fichero2.write((char *)&(*it), sizeof(DataProfesor));
  }
  fichero2.close();
  system("clear");
  std::cout << "El registro ha sido realizado.\n";
  std::cout << "\n\nPulsa ENTER para continuar." << std::endl;
  std::getline(std::cin, foo);
}


void Profesor::iniciarSesion(Profesor &p)
{
  Profesor * pAux;
  std::string username, pass, password, condition;

  system("clear");
  do {
    condition="0";
    std::cout << "Iniciar sesión:\n" << std::endl;
    std::cout << "E-mail de la cuenta: ";
    std::cin >> username;
    getchar();

    pAux = buscarProfesor(username, pass);
    if(pAux==NULL)
      condition = "1";

    std::cout << "Contraseña: ";
    std::cin >> password;
    getchar();

    if(password!=pass and condition!="1")
      condition = "2";

    if(condition=="1")
      std::cout << "\n\n Ese usuario no existe.\n\n" << std::endl;
    else
      std::cout << "\n\n La contraseña no coincide.\n\n" << std::endl;

  } while(condition!="0");

  p.setCorreo_electronico(pAux->getCorreo_electronico());
  p.setTipo(pAux->getTipo());
}


void Profesor::cerrarSesion(Profesor &p)
{
  Profesor pAux;

  p = pAux;
}


void Profesor::guardarBD()
{
  std::list<Alumno>::iterator it;
  DataAlumno da;
  std::string foo;
  std::ofstream fichero("DataBase.bin", std::ofstream::binary);

  if(getAgenda()->getLista()->empty())  // Se comprueba que la lista no esté vacía
  {
    system("clear");
    std::cout << "La lista de alumnos está vacía." << std::endl;
    std::cout << "\nPulsa ENTER para continuar..." << std::endl;
    std::getline(std::cin, foo);
  }
  else if(fichero)
  {
    for(it=getAgenda()->getLista()->begin(); it!=getAgenda()->getLista()->end(); it++)
    {
      strcpy(da.dni, it->getDNI().c_str());
      strcpy(da.nombre, it->getNombre().c_str());
      strcpy(da.apellidos, it->getApellidos().c_str());
      strcpy(da.email, it->getCorreo_electronico().c_str());
      strcpy(da.fecha_nacimiento, it->getFecha_de_nacimiento().c_str());
      strcpy(da.domicilio, it->getDomicilio().c_str());
      strcpy(da.telefono, it->getTelefono().c_str());
      da.curso = it->getCurso_mas_alto_matriculado();
      da.grupo = it->getGrupo();
      da.rol = it->getRol();
      fichero.write((char *)&da, sizeof(DataAlumno));
    }
    fichero.close();
    system("clear");
    std::cout << "La lista ha sido guardada en la base de datos.\n";
    std::cout << "\n\nPulsa ENTER para continuar." << std::endl;
    std::getline(std::cin, foo);
  }
  else
  {
    system("clear");
    std::cout << "No se ha podido acceder al archivo.\n";
    std::cout << "\n\nPulsa ENTER para continuar." << std::endl;
    std::getline(std::cin, foo);
  }
}

void Profesor::cargarBD()
{
  std::ifstream fichero("DataBase.bin", std::ifstream::binary);
  Alumno new_alumno;
  DataAlumno da;
  std::string foo;
  int size=0;

  if(fichero.is_open())
  {
    fichero.seekg(0, std::ios::end);
    size = (int) fichero.tellg();
    fichero.seekg(0, std::ios::beg);

    // Se vacía la lista
    getAgenda()->getLista()->clear();

    while(fichero.tellg() < size)
    {
      fichero.read((char *)&da, sizeof(DataAlumno));
      new_alumno.setDNI(da.dni);
      new_alumno.setNombre(da.nombre);
      new_alumno.setApellidos(da.apellidos);
      new_alumno.setCorreo_electronico(da.email);
      new_alumno.setFecha_de_nacimiento(da.fecha_nacimiento);
      new_alumno.setDomicilio(da.domicilio);
      new_alumno.setTelefono(da.telefono);
      new_alumno.setCurso_mas_alto_matriculado(da.curso);
      new_alumno.setGrupo(da.grupo);
      new_alumno.setRol(da.rol);
      getAgenda()->getLista()->push_back(new_alumno);
    }

    fichero.close();
    system("clear");
    std::cout << "Se ha importado la lista de alumnos desde la base de datos.\n";
    std::cout << "\n\nPulsa ENTER para continuar." << std::endl;
    std::getline(std::cin, foo);
  }
  else
  {
    system("clear");
    std::cout << "No se ha podido acceder al archivo.\n";
    std::cout << "\n\nPulsa ENTER para continuar." << std::endl;
    std::getline(std::cin, foo);
  }
}

void Profesor::guardarCopia()
{
  std::string foo, fileName;
  std::list<Alumno>::iterator it;
  DataAlumno da;

  if(getTipo()) // Coordinador
  {
    std::ifstream checkFile(fileName, std::ifstream::binary);
    system("clear");
    do {
      std::cout << "\nIntroduce el nombre que tendrá el fichero:" << std::endl;
      std::cin >> fileName;
      getchar();

      if (checkFile or fileName=="DataBase.bin" or fileName=="registro_profesores.bin") {
        std::cout << "Error. El fichero introducido ya existe." << std::endl;
        checkFile.close();
      }
    } while(checkFile);

    std::ofstream fichero(fileName, std::ofstream::binary);

    if(getAgenda()->getLista()->empty())  // Se comprueba que la lista no esté vacía
    {
      system("clear");
      std::cout << "La lista de alumnos está vacía." << std::endl;
      std::cout << "\nPulsa ENTER para continuar..." << std::endl;
      std::getline(std::cin, foo);
    }
    else if(fichero)
    {
      for(it=getAgenda()->getLista()->begin(); it!=getAgenda()->getLista()->end(); it++)
      {
        strcpy(da.dni, it->getDNI().c_str());
        strcpy(da.nombre, it->getNombre().c_str());
        strcpy(da.apellidos, it->getApellidos().c_str());
        strcpy(da.email, it->getCorreo_electronico().c_str());
        strcpy(da.fecha_nacimiento, it->getFecha_de_nacimiento().c_str());
        strcpy(da.domicilio, it->getDomicilio().c_str());
        strcpy(da.telefono, it->getTelefono().c_str());
        da.curso = it->getCurso_mas_alto_matriculado();
        da.grupo = it->getGrupo();
        da.rol = it->getRol();
        fichero.write((char *)&da, sizeof(DataAlumno));
      }
      fichero.close();
      system("clear");
      std::cout << "La lista ha sido guardada en el fichero indicado.\n";
      std::cout << "\n\nPulsa ENTER para continuar." << std::endl;
      std::getline(std::cin, foo);
    }
    else
    {
      system("clear");
      std::cout << "No se ha podido acceder al archivo.\n";
      std::cout << "\n\nPulsa ENTER para continuar." << std::endl;
      std::getline(std::cin, foo);
    }
  }
  else
  {
    system("clear");
    std::cout << "Permiso denegado." << std::endl;
    std::cout << "\nPulsa ENTER para continuar." << std::endl;
    std::getline(std::cin, foo);
  }
}

void Profesor::cargarCopia()
{
  Alumno new_alumno;
  DataAlumno da;
  std::string foo, fileName;
  int size=0;

  if(getTipo()) // Coordinador
  {
    system("clear");
    std::cout << "\nIntroduce el nombre del fichero:" << std::endl;
    std::cin >> fileName;
    getchar();

    std::ifstream fichero(fileName, std::ifstream::binary);

    if(fichero.is_open())
    {
      fichero.seekg(0, std::ios::end);
      size = (int) fichero.tellg();
      fichero.seekg(0, std::ios::beg);

      // Se vacía la lista
      getAgenda()->getLista()->clear();

      while(fichero.tellg() < size)
      {
        fichero.read((char *)&da, sizeof(DataAlumno));
        new_alumno.setDNI(da.dni);
        new_alumno.setNombre(da.nombre);
        new_alumno.setApellidos(da.apellidos);
        new_alumno.setCorreo_electronico(da.email);
        new_alumno.setFecha_de_nacimiento(da.fecha_nacimiento);
        new_alumno.setDomicilio(da.domicilio);
        new_alumno.setTelefono(da.telefono);
        new_alumno.setCurso_mas_alto_matriculado(da.curso);
        new_alumno.setGrupo(da.grupo);
        new_alumno.setRol(da.rol);
        getAgenda()->getLista()->push_back(new_alumno);
      }

      fichero.close();
      system("clear");
      std::cout << "Se ha importado la lista de alumnos desde la base de datos.\n";
      std::cout << "\n\nPulsa ENTER para continuar." << std::endl;
      std::getline(std::cin, foo);
    }
    else
    {
      system("clear");
      std::cout << "No se ha podido acceder al archivo.\n";
      std::cout << "\n\nPulsa ENTER para continuar." << std::endl;
      std::getline(std::cin, foo);
    }
  }
  else
  {
    system("clear");
    std::cout << "Permiso denegado." << std::endl;
    std::cout << "\nPulsa ENTER para continuar." << std::endl;
    std::getline(std::cin, foo);
  }
}
