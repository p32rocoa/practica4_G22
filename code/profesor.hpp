#ifndef PROFESOR_H
#define PROFESOR_H

#include <string>
#include "persona.hpp"
#include "agenda.hpp"

typedef struct DataAlumno
{
  char dni[20];
  char nombre[50];
  char apellidos[100];
  char email[50];
  char fecha_nacimiento[50];
  char domicilio[100];
  char telefono[30];
  int curso;
  int grupo;
  bool rol;
} DataAlumno;

typedef struct DataProfesor
{
  char email[50];
  char password[30];
  bool tipo;
} DataProfesor;

class Agenda; // Declaración de clase para "Agenda agenda_;"

class Profesor : public Persona
{
    private:
        std::string correo_;
        bool tipo_;
        Agenda * agenda_;

        Profesor * buscarProfesor(std::string email, std::string &pass);

    public:
        Profesor()
        {
          agenda_ = new class Agenda;
        };

        //Getters
        inline std::string getCorreo_electronico() const {return correo_;}
        inline bool getTipo() const {return tipo_;}
        inline Agenda * getAgenda() {return agenda_;}

        //Setters
        inline void setCorreo_electronico(std::string new_correo) {correo_ = new_correo;}
        inline void setTipo(bool new_tipo) {tipo_ = new_tipo;}
        inline void setAgenda(Agenda * new_agenda) {agenda_ = new_agenda;}

        //Extra
        void borrarProfesor();
        void registrarse();
        void iniciarSesion(Profesor &p);
        void cerrarSesion(Profesor &p);
        void guardarBD();
        void cargarBD();
        void guardarCopia();
        void cargarCopia();
};

#endif
