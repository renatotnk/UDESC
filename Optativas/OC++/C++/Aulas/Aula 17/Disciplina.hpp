//Aluno: Renato Tanaka

#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#include<list>
#include <string>

#include "Pessoa.hpp"
#include "ConteudoMinistrado.hpp"

class SalaAula;

class Disciplina{
	public:
		Disciplina(std::string nome, unsigned short cargaHoraria);
		~Disciplina();

		std::string getNome() const;
		void setNome(std::string nome);
		
		int getCargaHoraria() const;
		void setCargaHoraria(unsigned int cargaHoraria);

		Pessoa* getProfessor();
		void setProfessor(Pessoa* professor);

		std::string getNomeProfessor() const;

		void adicionarAluno(Pessoa* aluno);
		void removerAluno(Pessoa* aluno);
		void removerAluno(unsigned long cpf);
		std::list<Pessoa*>& getAlunos();

		SalaAula* getSalaAula();
		void setSalaAula(SalaAula* salaAula);
		void setSalaAulaSemAtualizarSala(SalaAula* salaAula);

		void adicionarConteudoMinistrado(std::string conteudo, unsigned short cargaHorariaConteudo);
		void removerConteudoMinistrado(unsigned long int id);
		std::list<ConteudoMinistrado*>&  getConteudos();
		void limparConteudos();
		void imprimirConteudosMinistrados();

		void imprimeDados(std::string& cabecalho, unsigned int cargaTotalCurso);
	private:
		std::string nome;
		unsigned short int cargaHoraria;
		SalaAula* salaAula;

		Pessoa* professor;
		std::list<Pessoa*> alunos;
		std::list<ConteudoMinistrado*> conteudos;		
};

class Curso{
	public:
		Curso(std::string nomeCurso, unsigned short anoCriacao, unsigned short cargaHorariaMinima);
		~Curso();

		std::string getNome() const;
		void setNome(std::string nome);
		
		int getCargaHoraria() const;
		void setCargaHoraria(unsigned short cargaHorariaMinima);

		int getAnoCriacao() const;
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
