//Aluno: Renato Tanaka

#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#include<list>
#include <string>

#include "Pessoa.hpp"

class SalaAula;

class Disciplina{
	public:
		Disciplina(std::string nome, unsigned short cargaHoraria);

		std::string getNome();
		void setNome(std::string nome);
		
		int getCargaHoraria();
		void setCargaHoraria(unsigned int cargaHoraria);

		Pessoa* getProfessor();
		void setProfessor(Pessoa* professor);

		std::string getNomeProfessor();

		void adicionarAluno(Pessoa* aluno);
		void removerAluno(Pessoa* aluno);
		void removerAluno(unsigned long cpf);
		std::list<Pessoa*>& getAlunos();

		SalaAula* getSalaAula();
		void setSalaAula(SalaAula* salaAula);

		void imprimeDados(std::string& cabecalho, unsigned int cargaTotalCurso);
	private:
		std::string nome;
		unsigned short int cargaHoraria;
		SalaAula* salaAula;

		Pessoa* professor;
		std::list<Pessoa*> alunos;
};

class Curso{
	public:
		Curso(std::string nomeCurso, unsigned short anoCriacao, unsigned short cargaHorariaMinima);

		std::string getNome();
		void setNome(std::string nome);
		
		int getCargaHoraria();
		void setCargaHoraria(unsigned short cargaHorariaMinima);

		int getAnoCriacao();
		void setAnoCriacao(unsigned short anoCriacao);

		void imprimeDados();

		void adicionarDisciplina(Disciplina* disciplina);
		bool removerDisciplina(Disciplina* disciplina);

	private:
		std::string nomeCurso;
		unsigned short anoCriacao;
		unsigned short cargaHorariaMinima;
		std::list<Disciplina *> disciplinas;
		std::list<Disciplina *>::iterator itDis;
};


#endif
