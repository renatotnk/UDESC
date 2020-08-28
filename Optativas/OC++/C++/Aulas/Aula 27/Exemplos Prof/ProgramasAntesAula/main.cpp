#include <iostream>

#include "ProfessorAdjunto.hpp"
#include "Professor.hpp"
#include "Engenheiro.hpp"
#include "ProfessorEngenheiro.hpp"

int main(){
	ProfessorEngenheiro pe{"Maria", 11111111111,85, 40, 1234};

	std::cout << pe.getNome() << " " << pe.getSalario() << std::endl;

	return 0;
}

