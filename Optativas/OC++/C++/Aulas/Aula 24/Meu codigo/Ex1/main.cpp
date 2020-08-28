#include <iostream>

#include "Disciplina.hpp"
#include "ProfessorAdjunto.hpp"
#include "Professor.hpp"
#include "Pessoa.hpp"

int main(){
	Pessoa* p{new ProfessorAdjunto{"Maria", 11111111111, 100, 40}};
	std::cout << p->getNome() << std::endl;
	delete p;

	return 0;
}
