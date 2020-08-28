#include <iostream>
#include <string>

#include "Pessoa.hpp"
#include "Disciplina.hpp"

int main(){
	Pessoa* prof{new Pessoa{"Joao"}};
	Pessoa* al1{new Pessoa{"Maria"}};
	Pessoa* al2{new Pessoa{"Pedro"}};

	Disciplina dis{"C++"};
	dis.setProfessor(prof);
	dis.adicionarAluno(al1);
	dis.adicionarAluno(al2);

	Pessoa** vetorAlunos = dis.getAlunos();
	for(unsigned int i=0; i < dis.getNumAlunos(); i++){
		std::cout << "Aluno " << i << ": " << vetorAlunos[i]->getNome() << std::endl;
	}

	delete al1;
	delete al2;

	return 0;
}
