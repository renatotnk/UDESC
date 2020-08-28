#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#include <string>
#include <list>

#include "Pessoa.hpp"
#include "Professor.hpp"
#include "ConteudoMinistrado.hpp"
class SalaAula;//forward declaration

class Disciplina{
	public:
		Disciplina(std::string nome);
		virtual ~Disciplina();

		std::string getNome();
		void setNome(std::string nome);
		
		int getCargaHoraria();
		void setCargaHoraria(unsigned int cargaHoraria);
		
		const Professor* getProfessor() const;
		void setProfessor(Professor* professor);

		void adicionarAluno(Pessoa* aluno);
		void removerAluno(Pessoa* aluno);
		void removerAluno(unsigned long cpf);
		const std::list<Pessoa*>& getAlunos() const;

		void setSalaAula(SalaAula* salaAula);
		void setSalaAulaSemAtualizarSala(SalaAula* salaAula);

		SalaAula* getSalaAula();

		void adicionarConteudoMinistrado(std::string conteudo, unsigned short cargaHorariaConteudo);
		std::list<ConteudoMinistrado*>& getConteudos();
	private:
		std::string nome;
		unsigned short int cargaHoraria;
		SalaAula* salaAula;

		Professor* professor;
		std::list<Pessoa*> alunos;
		std::list<ConteudoMinistrado*> conteudos;
};
#endif
