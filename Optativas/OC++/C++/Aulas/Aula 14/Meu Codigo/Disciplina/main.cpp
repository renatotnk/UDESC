#include <iostream>
#include <string>
#include <list>

#include "Pessoa.hpp"
#include "Disciplina.hpp"
#include "SalaAula.hpp"
#include "ConteudoMinistrado.hpp"


int main(){
	ConteudoMinistrado c1{"Ponteiros", 4};
	ConteudoMinistrado c2{"Referencias", 2};

	Disciplina d1{"C++", 72};

	d1.adicionarConteudoMinistrado("Ponteiros", 4);
	d1.adicionarConteudoMinistrado("Referencias", 2);

	d1.imprimirConteudosMinistrados();

	std::cout << c1.getId() << std::endl;
	std::cout << c2.getId() << std::endl;

	return 0;
}
