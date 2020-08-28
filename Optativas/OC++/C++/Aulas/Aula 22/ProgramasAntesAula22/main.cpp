#include <iostream>

#include "Pessoa.hpp"
#include "Professor.hpp"


int main(){
	Professor p1("João", 11111111111, 6000, 40);

	std::cout << p1.getNome() << " " << p1.getIdade() << std::endl;
	
	return 0;
}
