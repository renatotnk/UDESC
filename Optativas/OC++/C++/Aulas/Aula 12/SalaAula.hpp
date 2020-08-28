//Aluno: Renato Tanaka

#ifndef SALAAULA_H
#define SALAAULA_H

#include "Disciplina.hpp"

class SalaAula{
    public:
        void adicionarDisciplina(Disciplina* disciplina);
        void removerDisciplina(Disciplina* disciplina);
        std::list<Disciplina*>& getDisciplinas();

    private:
        std::string nome;
        unsigned int capacidade;
        std::list<Disciplina*> disciplinasMinistradas;
};

#endif