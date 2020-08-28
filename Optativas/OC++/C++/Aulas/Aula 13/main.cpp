//Aluno: Renato Tanaka

#include <iostream>
#include <string>
#include <list>

#include "Pessoa.hpp"
#include "Disciplina.hpp"
#include "SalaAula.hpp"

int main(){
	Pessoa prof1{"João", 40};
	Disciplina dis1{"C++", 72};
	dis1.setProfessor(&prof1);

	Pessoa prof2{"Maria", 30};	
	Disciplina dis2{"Java",72};
	dis2.setProfessor(&prof2);

	SalaAula sala{"F204", 20};
	
	dis1.setSalaAula(&sala);
	dis2.setSalaAula(&sala);

	std::cout << sala.getNome() << std::endl;
	std::list<Disciplina*>& disciplinas{sala.getDisciplinas()};
	std::list<Disciplina*>::iterator it;
	for(it=disciplinas.begin(); it != disciplinas.end(); it++)
		std::cout << (*it)->getNome() << std::endl;

	std::cout << dis1.getSalaAula()->getNome() << std::endl;

	return 0;
}
