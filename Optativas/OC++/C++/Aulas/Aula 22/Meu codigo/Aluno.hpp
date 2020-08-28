//Aluno: Renato Tanaka

#ifndef ALUNO_H
#define ALUNO_H

#include "Pessoa.hpp"

class Aluno: public Pessoa{
    public:
        Aluno(const std::string& nome, const unsigned long cpf,
        const unsigned int matricula, const unsigned short fase);

        ~Aluno();

        unsigned long getMatricula() const;
        void setMatricula(const unsigned long matricula);

        unsigned short getFase() const;
        void setFase(const unsigned short fase);

    private:
        unsigned long matricula;
        unsigned short fase;
};

#endif