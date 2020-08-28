//Aluno: Renato Tanaka

#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#include <string>
#include "Pessoa.hpp"

class Curso{
	public:
		Curso(std::string novoNome, unsigned short novaCriacao, unsigned short novaMinima);

		std::string getNome();
		void setNome(std::string novoNome);
		
		int getCargaHoraria();
		void setCargaHoraria(unsigned short novaCarga);

		int getAnoCriacao();
		void setAnoCriacao(unsigned short novoAno);

		void imprimeDados();

	private:
		std::string nomeCurso;
		unsigned short anoCriacao;
		unsigned short cargaHorariaMinima;
};

class Disciplina{
	public:
		Disciplina(std::string nomeDisciplina, Curso& associado);

		std::string getNome();
		void setNome(std::string novoNome);
		
		int getCargaHoraria();
		void setCargaHoraria(unsigned int novaCarga);

		Pessoa* getProfessor();
		void setProfessor(Pessoa* novoProfessor);

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
