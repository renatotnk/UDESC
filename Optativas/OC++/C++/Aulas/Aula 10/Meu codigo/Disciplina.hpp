//Aluno: Renato Tanaka

#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#include<list>
#include <string>
#include "Pessoa.hpp"

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

	private:
		std::string nomeCurso;
		unsigned short anoCriacao;
		unsigned short cargaHorariaMinima;
};

class Disciplina{
	public:
		Disciplina(std::string nome, Curso& associado);

		std::string getNome();
		void setNome(std::string nome);
		
		int getCargaHoraria();
		void setCargaHoraria(unsigned int cargaHoraria);

		Pessoa* getProfessor();
		void setProfessor(Pessoa* professor);

		std::string getNomeProfessor();

		bool adicionarAluno(Pessoa* aluno);
		bool removerAluno(Pessoa* aluno);
		bool removerAluno(unsigned long cpf);

		unsigned int getNumAlunos();
		void imprimeDados(std::string& cabecalho, unsigned int cargaTotalCurso);

	private:
		std::string nome;
		Pessoa* professor;
		std::list<Pessoa*> alunos;
		std::list<Pessoa *>::iterator itPes;
		Curso& cursoAssociado;
		unsigned int numAlunos = 0;
		unsigned short int cargaHoraria;
};

#endif
