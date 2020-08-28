#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#include <string>
#include "Pessoa.hpp"

class Disciplina{
	public:
		Disciplina(std::string nomeDisciplina);

		std::string getNome();
		void setNome(std::string novoNome);
		
		int getCargaHoraria();
		void setCargaHoraria(unsigned int novaCarga);

		Pessoa* getProfessor();
		void setProfessor(Pessoa* novoProfessor);

		std::string getNomeProfessor();

		bool adicionarAluno(Pessoa* aluno);
		Pessoa* getVetorAlunos();
	private:
		std::string nome;
		Pessoa* professor;
		Pessoa* alunos{new Pessoa[50]};
		unsigned short int cargaHoraria;
};
#endif
