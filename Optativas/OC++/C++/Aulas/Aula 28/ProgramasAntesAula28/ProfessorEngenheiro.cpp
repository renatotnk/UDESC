#include "ProfessorEngenheiro.hpp"

#include <iostream>

ProfessorEngenheiro::ProfessorEngenheiro(const std::string& nome,
			const unsigned long cpf, const unsigned int valorHora,
			const unsigned short cargaHoraria, const unsigned int numeroCrea)
       			: Pessoa(nome, cpf),
			Professor(nome, cpf, valorHora, cargaHoraria),
			Engenheiro(nome, cpf, numeroCrea) {
	//std::cout << "Construindo Professor Engenheiro" << std::endl;
}

ProfessorEngenheiro::~ProfessorEngenheiro(){}
	
unsigned int ProfessorEngenheiro::getSalario() const{
	return Professor::getSalario() + Engenheiro::getSalario();

}
