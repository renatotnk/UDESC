//Aluno: Renato Tanaka
#include <iostream>
#include"Pessoa.hpp"


int main(){
	Pessoa p1;
	for(long i =0; i < 400000000; i++){
		p1.setIdade(i%100);
		p1.getIdade();
		i = i + p1.getIdade();
		i = i - p1.getIdade();
	}
	std::cout << (unsigned short int)p1.getIdade() << std::endl;

	return 0;

	return 0;
}
