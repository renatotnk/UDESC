//Aluno: Renato Tanaka

#ifndef DISCIPLINA_H
#define DISCIPLINA_H

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
		unsigned int getNumAlunos();
		Pessoa** getVetorAlunos();
		void imprimeDados(std::string& cabecalho, unsigned int cargaTotalCurso);

	private:
		std::string nome;
		Pessoa* professor;
		Pessoa* alunos[50];
		Curso& cursoAssociado;
		unsigned int numAlunos = 0;
		unsigned short int cargaHoraria;
};

#endif
