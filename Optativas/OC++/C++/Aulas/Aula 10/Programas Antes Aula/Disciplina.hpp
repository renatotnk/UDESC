#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#include <string>

#include "Pessoa.hpp"

class Disciplina{
	public:
		Disciplina(std::string nome);

		std::string getNome();
		void setNome(std::string nome);
		
		int getCargaHoraria();
		void setCargaHoraria(unsigned int cargaHoraria);
		
		Pessoa* getProfessor();
		void setProfessor(Pessoa* professor);

		void imprimeDados(std::string& cabecalho, unsigned int& cargaTotalCurso);
	private:
		std::string nome;
		unsigned short int cargaHoraria;

		Pessoa* professor;
};
#endif
