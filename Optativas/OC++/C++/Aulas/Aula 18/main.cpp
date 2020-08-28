#include <iostream>
#include <list>

#include "Disciplina.hpp"
#include "Pessoa.hpp"

int main(){
	Disciplina d{"C++", 72};
	Pessoa p1{"Joao"};

	d.adicionarAluno(&p1);
	const std::list<Pessoa*>& alunos{d.getAlunos()};//acessamos a lista original
	Pessoa p2{"Maria"};
	//alunos.push_back(&p2);  //modificamos o objeto interno de Disciplina

	std::list<Pessoa*>::const_iterator it = d.getAlunos().begin();
	for( ;it != d.getAlunos().end(); it++){
		std::cout << (*it)->getNome() << std::endl;
	}

return 0;
}