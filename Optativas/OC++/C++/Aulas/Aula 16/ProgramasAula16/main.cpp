#include <iostream>
#include <string>
#include <list>

#include "Disciplina.hpp"
#include "SalaAula.hpp"
#include "ConteudoMinistrado.hpp"

int main(){
	Disciplina dis1{"C++"};
	Disciplina* dis2{new Disciplina{"Java"}};
	SalaAula sala{"F203", 40};
	
	dis1.setSalaAula(&sala);
	dis2->setSalaAula(&sala);

	std::list<Disciplina*> disSala = sala.getDisciplinas();
	std::list<Disciplina*>::iterator it;
	for(it = disSala.begin(); it != disSala.end(); it++)
		std::cout << (*it)->getNome() << std::endl;

	delete dis2;

	std::cout << "Fim do Programa" << std::endl;


	return 0;
}
