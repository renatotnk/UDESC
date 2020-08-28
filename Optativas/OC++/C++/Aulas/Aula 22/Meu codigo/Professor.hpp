//Aluno: Renato Tanaka

#ifndef PROFESSOR_HPP
#define PROFESSOR_HPP

#include <string>
#include "Pessoa.hpp"

class Professor: public Pessoa{
    public:
        Professor(const std::string& nome, const unsigned long cpf,
        const unsigned int salario, const unsigned short cargaHoraria);

        ~Professor();

        void setSalario(const unsigned int salario);
        unsigned int getSalario() const;

        unsigned short getCargaHoraria() const;
        void setCargaHoraria(const unsigned short cargaHoraria);

    private:
        unsigned int salario;
        unsigned short cargaHoraria;
};

#endif