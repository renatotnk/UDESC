#include <iostream>
#include <string>
#include <list>

#include "Pessoa.hpp"
#include "Disciplina.hpp"
#include "SalaAula.hpp"
#include "ConteudoMinistrado.hpp"


int main(){
	const Pessoa p{"Joao", 22, 11111111111};
	const int valor{1};


	std::cout << p.getNome() << std::endl;
	return 0;
}
