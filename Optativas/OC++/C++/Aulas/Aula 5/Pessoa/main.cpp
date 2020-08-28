//Aluno: Renato Tanaka
#include <iostream>
#include"Pessoa.hpp"


int main(){
	Pessoa p1{"Joao",11111111111, 22};
	Pessoa p2();
	Pessoa p3("Maria", 75);
	
	std::cout << p1.getNome() << " " << p1.getCpf() << std::endl;

	return 0;

	return 0;
}
