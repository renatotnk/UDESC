#include <iostream>
#include <string>

#include "Pessoa.hpp"
#include "Disciplina.hpp"

int main(){
	Pessoa* p1{new Pessoa{"Maria", 30}};
	Pessoa* p2{new Pessoa{"Joao", 20}};
	Disciplina* d1{new Disciplina{"C++"}};
	d1->adicionarAluno(p1);
	d1->adicionarAluno(p2);

	
	std::cout << d1->getVetorAlunos() << std::endl;

	delete p1;
	delete p2;
	delete d1;
	

	return 0;
}
