#include <iostream>
#include <string>

#include "Pessoa.hpp"

int main(){
	Pessoa *p{nullptr};
	std::string nome;
	unsigned long cpf;

	std::cout << "Digite o nome: ";
	std::cin >> nome;
	std::cout << "Digite o cpf: ";
	std::cin >> cpf;

	while(p == nullptr){
		try{
			p = new Pessoa{nome, cpf};
			std::cout << p->getNome() << " " << p->getCpf() << std::endl;
		}catch(int& ex){
			if(ex == 1){
				std::cout << "CPF invalido! Digite outro: " << std::endl;
				std::cin >> cpf;
			}else{
				std::cout << "Erro desconhecido!" << std::endl;
			}
		}
	}

	delete p;
	return 0;
}

