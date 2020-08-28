//Aluno: Renato Tanaka

#ifndef SALAAULA_H
#define SALAAULA_H

#include<string>
#include<list>

#include "Disciplina.hpp"

class SalaAula{
    friend void Disciplina::setSalaAula(SalaAula* salaAula);
    public:
        SalaAula(std::string nome, unsigned int capacidade);
        ~SalaAula();
		
		std::string getNome() const;
		void setNome(std::string nome);

		unsigned int getCapacidade() const;
		void setCapacidade(unsigned int capacidade);

        std::list<Disciplina*>& getDisciplinas();

    private:
        std::string nome;
        unsigned int capacidade;
        std::list<Disciplina*> disciplinasMinistradas;

        void adicionarDisciplina(Disciplina* disciplina);
        void removerDisciplina(Disciplina* disciplina);
};

#endif