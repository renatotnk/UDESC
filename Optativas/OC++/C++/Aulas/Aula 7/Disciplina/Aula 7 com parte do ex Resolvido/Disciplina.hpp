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

		Pessoa** getAlunos();
		unsigned int getNumAlunos();
		bool adicionarAluno(Pessoa* aluno);
	private:
		std::string nome;
		unsigned short int cargaHoraria;
		Pessoa* alunos[50];
		unsigned int numAlunos = 0;//somente get para esse dado membro
		Pessoa* professor;
};
#endif
