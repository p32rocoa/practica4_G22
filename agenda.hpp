#ifndef AGENDA_HPP
#define AGENDA_HPP

#include <list>
#include <string>
#include "alumno.hpp"

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
      if (search != "" and key)
      {
        for (Alumno i : _alumnos)
        {
          if(i.getDNI() == search)
            return i;
        }
      }
      else if (search != "" and !key)
      {
        for (Alumno i : _alumnos)
        {
          if(i.getApellidos() == search)
            alumnos.push_back(i);
        }
      }
      if (alumnos.size() == 1)
        return alumnos.front();
      else
      {
        std::cout << "Hay varios alumnos con los mismos apellidos, introduzca el DNI" << std::endl;
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
        return alumno;
      }
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

    //;
    Agenda() {};

    // Modificadores de datos de alumnos
    void insertarAlumno()
    {
      Alumno trash;
      _alumnos.push_back(generateAlumno(trash, 0));
    }
    void borrarAlumno(Alumno &alumno)
    {
      Alumno search;
      std::string dni;
      if (alumno.getDNI() != "")
        search = buscarAlumno(alumno.getDNI());
      else
      {
        std::cout << "Introduce el dni del alumno a borrar: ";
        std::getline(std::cin, dni);
        search = buscarAlumno(dni);
      }
      if(search.getDNI() != "")
        std::cout << "Alumno no encontrado" << std::endl;
      else 
        _alumnos.remove(search);
    }
    void modificarAlumno(Alumno &alumno)
    {
      std::string key = "1";
      std::string buffer;
      if(alumno.getDNI() == "")
      {
        std::cout << "Introduzca 1 si quiere buscar al alumno por DNI, y 0 si es por apellidos" << std::endl;
        std::getline(std::cin, key);
        if(atoi(key.c_str()))
          std::cout << "Introduzca DNI: ";
        else
          std::cout << "Introduzca Apellidos: ";
        std::getline(std::cin, buffer);
        alumno = this->buscarAlumno(buffer);
      }
      if(alumno.getDNI() != "")
      {
        Alumno new_alumno;
        new_alumno = generateAlumno(alumno, 1);
        borrarAlumno(alumno);
        alumno = new_alumno;
        _alumnos.push_back(new_alumno);
      }
      else
        std::cout << "No existe el alumno" << std::endl;
    }
    void reiniciarAlumnos();

    // Observadores de datos de alumnos
    void listarAlumnos()
    {
      int count = 0;
      for(Alumno i : _alumnos)
      {
        ++count;
        std::cout << "/// Alumno nº " << count << " ///" << std::endl;
        mostrarAlumno(i);
      }
    }
    void mostrarAlumno(Alumno &i)
    {
      std::string key = "1";
      std::string buffer;
      if(i.getDNI() == "")
      {
        std::cout << "Introduzca 1 si quiere buscar al alumno por DNI, y 0 si es por apellidos" << std::endl;
        std::getline(std::cin, key);
        if(atoi(key.c_str()))
          std::cout << "Introduzca DNI: ";
        else
          std::cout << "Introduzca Apellidos: ";
        std::getline(std::cin, buffer);
        i = this->buscarAlumno(buffer);
      }
      if(i.getDNI() != "")
      {
        std::cout << "DNI: " << std::endl;
        std::cout << i.getDNI() << std::endl;
        std::cout << "Nombre: " << std::endl;
        std::cout << i.getNombre() << std::endl;
        std::cout << "Apellidos: " << std::endl;
        std::cout << i.getApellidos() << std::endl;
        std::cout << "Correo: " << std::endl;
        std::cout << i.getCorreo_electronico() << std::endl;
        std::cout << "Fecha de nacimiento: " << std::endl;
        std::cout << i.getFecha_de_nacimiento() << std::endl;
        std::cout << "Domicilio: " << std::endl;
        std::cout << i.getDomicilio() << std::endl;
        std::cout << "Telefono: " << std::endl;
        std::cout << i.getTelefono() << std::endl;
        std::cout << "Curso: " << std::endl;
        std::cout << i.getCurso_mas_alto_matriculado() << std::endl;
        std::cout << "Grupo: " << std::endl;
        std::cout << i.getGrupo() << std::endl;
        std::cout << "Lider: " << std::endl;
        if(i.getRol())
          std::cout << "Si" << std::endl;
        else
          std::cout << "No" << std::endl;
      }
      else
        std::cout << "No existe el alumno" << std::endl;
    }
    void mostrarGrupo(std::list<Alumno> grupo)
    {
      
    }

    //Aux
    Alumno generateAlumno(Alumno alumno, int mod)
    {
      Alumno new_alumno(alumno);
      std::string buffer;
      std::cout << "Introduce el DNI del alumno";
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
      std::cout << "Introduce el curso del alumno";
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


};

#endif
