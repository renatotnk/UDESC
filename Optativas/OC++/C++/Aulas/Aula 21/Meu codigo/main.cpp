#include <iostream>

#include "Pilha.hpp"

int main(){
	int retorno;
	Pilha<int,5> p;
	p.push(1);
	p.push(2);
	p.push(3);
	p.push(4);

	while(!p.estaVazia()){
		p.pop(&retorno);
		std::cout << retorno << std::endl;
	}
	

	std::cout << "Fim" << std::endl;

	return 0;
}
