#include <iostream>

#include "Disciplina.hpp"
#include "ProfessorAdjunto.hpp"
#include "Professor.hpp"
#include "Pessoa.hpp"

int main(){
	ProfessorAdjunto p{"Joao", 11111111111, 8500, 40};
	Professor p2{"Pedro", 11111111111, 8500, 40};

	Professor* ptr{&p};

	std::cout << p.getNome() << " " << p.getSalario() << std::endl;
	std::cout << ptr->getNome() << " " << ptr->getSalario() << std::endl;


	return 0;
}
