#include <iostream>
#include <string>
#include <list>

#include "Pessoa.hpp"
#include "Disciplina.hpp"
#include "SalaAula.hpp"
#include "ConteudoMinistrado.hpp"


int main(){
	Pessoa prof1{"João", 40};
	Disciplina dis1{"C++"};
	dis1.setProfessor(&prof1);

	ConteudoMinistrado c1{"Ponteiros", 4};
	std::cout << c1.getId() << " " <<c1.getDescricao() << std::endl;




	return 0;
}
