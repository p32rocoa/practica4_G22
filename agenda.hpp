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
    std::list<Alumno> buscarGrupo(int numGrupo);

  public:

    //;
    Agenda() {};

    // Modificadores de datos de alumnos
    void insertarAlumno()
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
    void borrarAlumno(Alumno alumno)
    {
      Alumno search;
      search = buscarAlumno(alumno.getDNI());
      _alumnos.remove(search);
    }
    void modificarAlumno(Alumno alumno)
    {
      Alumno new_alumno;
      std::string buffer;
      std::cout << "Para omitir el campo a editar pulse enter dejando el campo vacío";
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
    void reiniciarAlumnos();

    // Observadores de datos de alumnos
    void listarAlumnos()
    {
      int count = 0;
      for(Alumno i : _alumnos)
      {
        ++count;
        std::cout << "/// Alumno nº " << count << " ///" << std::endl;
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
    }
    void mostrarAlumno(Alumno i)
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
    void mostrarGrupo(std::list<Alumno> grupo);

    //Aux
    Alumno buscarAlumno(std::string dni)
    {
      Alumno alumno;
      for (Alumno i : _alumnos)
      {
        if(i.getDNI() == dni)
          return i;
      }
      return alumno;
    }


};

#endif
