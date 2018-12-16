#ifndef ALUMNO_H
#define ALUMNO_H

class Alumno : public Persona
{
    private:
        std::string correo_;
        std::string fecha_nacimiento_;
        std::string domicilio_;
        std::string telefono_;
        int curso_mas_alto_;
        int grupo_;
        bool rol_;

    public:
        Alumno(const Alumno& rhs)
        {
            this->setDNI(rhs.getDNI());
            this->setNombre(rhs.getNombre());
            this->setApellidos(rhs.getApellidos());
            this->setCorreo_electronico(rhs.getCorreo_electronico());
            this->setFecha_de_nacimiento(rhs.getFecha_de_nacimiento());
            this->setDomicilio(rhs.getDomicilio());
            this->setTelefono(rhs.getTelefono());
            this->setCurso_mas_alto_matriculado(rhs.getCurso_mas_alto_matriculado());
            this->setGrupo(rhs.getGrupo());
            this->setRol(rhs.getRol());
        }
        Alumno(){};
        
        //Getters
        inline std::string getCorreo_electronico() const {return correo_;}
        inline std::string getFecha_de_nacimiento() const {return fecha_nacimiento_;}
        inline std::string getDomicilio() const {return domicilio_;}
        inline std::string getTelefono() const {return telefono_;}
        inline int getCurso_mas_alto_matriculado() const {return curso_mas_alto_;}
        inline int getGrupo() const {return grupo_;}
        inline bool getRol() const {return rol_;}

        //Setters
        inline void setCorreo_electronico(std::string new_correo) {correo_ = new_correo;}
        inline void setFecha_de_nacimiento(std::string new_fecha_nacimiento) {fecha_nacimiento_ = new_fecha_nacimiento;}
        inline void setDomicilio(std::string new_domicilio) {domicilio_ = new_domicilio;}
        inline void setTelefono(std::string new_telefono) {telefono_ = new_telefono;}
        inline void setCurso_mas_alto_matriculado(int new_curso_mas_alto) {curso_mas_alto_ = new_curso_mas_alto;}
        inline void setGrupo(int new_grupo) {grupo_ = new_grupo;}
        inline void setRol(bool new_rol) {rol_ = new_rol;}

        //Aux
        bool operator==(const Alumno& rhs)
        {
            return (this->getDNI()==rhs.getDNI());
        }        
        
        void operator =(const Alumno& rhs)
        {
            this->setDNI(rhs.getDNI());
            this->setNombre(rhs.getNombre());
            this->setApellidos(rhs.getApellidos());
            this->setCorreo_electronico(rhs.getCorreo_electronico());
            this->setFecha_de_nacimiento(rhs.getFecha_de_nacimiento());
            this->setDomicilio(rhs.getDomicilio());
            this->setTelefono(rhs.getTelefono());
            this->setCurso_mas_alto_matriculado(rhs.getCurso_mas_alto_matriculado());
            this->setGrupo(rhs.getGrupo());
            this->setRol(rhs.getRol());
        }

        void reset()
        {
            Alumno empty;
            this->setDNI(empty.getDNI());
            this->setNombre(empty.getNombre());
            this->setApellidos(empty.getApellidos());
            this->setCorreo_electronico(empty.getCorreo_electronico());
            this->setFecha_de_nacimiento(empty.getFecha_de_nacimiento());
            this->setDomicilio(empty.getDomicilio());
            this->setTelefono(empty.getTelefono());
            this->setCurso_mas_alto_matriculado(empty.getCurso_mas_alto_matriculado());
            this->setGrupo(empty.getGrupo());
            this->setRol(empty.getRol());
        }
};

#endif