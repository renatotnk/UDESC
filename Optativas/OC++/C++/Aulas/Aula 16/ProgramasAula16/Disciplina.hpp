#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#include <string>
#include <list>

#include "Pessoa.hpp"
#include "ConteudoMinistrado.hpp"
class SalaAula;//forward declaration

class Disciplina{
	public:
		Disciplina(std::string nome);
		~Disciplina();

		std::string getNome();
		void setNome(std::string nome);
		
		int getCargaHoraria();
		void setCargaHoraria(unsigned int cargaHoraria);
		
		Pessoa* getProfessor();
		void setProfessor(Pessoa* professor);

		void adicionarAluno(Pessoa* aluno);
		void removerAluno(Pessoa* aluno);
		void removerAluno(unsigned long cpf);
		std::list<Pessoa*>& getAlunos();

		void setSalaAula(SalaAula* salaAula);
		void setSalaAulaSemAtualizarSala(SalaAula* salaAula);

		SalaAula* getSalaAula();

		void adicionarConteudoMinistrado(std::string conteudo, unsigned short cargaHorariaConteudo);
		std::list<ConteudoMinistrado*>& getConteudos();
	private:
		std::string nome;
		unsigned short int cargaHoraria;
		SalaAula* salaAula;

		Pessoa* professor;
		std::list<Pessoa*> alunos;
		std::list<ConteudoMinistrado*> conteudos;
};
#endif
