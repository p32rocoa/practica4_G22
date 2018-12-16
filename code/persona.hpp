#ifndef PERSONA_H
#define PERSONA_H

#include <string>

class Persona
{
    private:
        std::string dni_;
        std::string nombre_;
        std::string apellidos_;

    public:
        Persona(){};

        //Getters
        inline std::string getDNI() const {return dni_;}
        inline std::string getNombre() const {return nombre_;}
        inline std::string getApellidos() const {return apellidos_;}

        //Setters
        inline void setDNI(std::string new_dni) {dni_ = new_dni;}
        inline void setNombre(std::string new_nombre) {nombre_ = new_nombre;}
        inline void setApellidos(std::string new_apellidos) {apellidos_ = new_apellidos;}
};

#endif
