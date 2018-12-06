#ifndef PROFESOR_H
#define PROFESOR_H

class Profesor : public Persona
{
    private:
        std::string correo_;
        bool tipo_;
        //Agenda agenda_;

    public:
        Profesor(){};
        
        //Getters
        inline std::string getCorreo_electronico() const {return correo_;}
        inline bool getTipo() const {return tipo_;}
        //inline Agenda getAgenda() {return agenda_;}

        //Setters
        inline void setCorreo_electronico(std::string new_correo) {correo_ = new_correo;}
        inline void setTipo(bool new_tipo) {tipo_ = new_tipo;}
        //inline void setAgenda(Agenda new_agenda) {agenda_ = new_agenda;}

        //Extra
        void buscarProfesor() {};
        void borrarProfesor() {};
        void iniciarSesion() {};
        void cerrarSesion() {};
        void guardarBD() {};
        void cargarBD() {};
        void guardarCopia() {};
        void cargarCopia() {};
};

#endif