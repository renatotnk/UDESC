//Aluno: Renato Tanaka

#include <iostream>
#include <string>

#include "Pessoa.hpp"
#include "Disciplina.hpp"

int main(){
	Pessoa* prof{new Pessoa{"Maria", 30}};
	Pessoa* p1{new Pessoa{"Joao", 20}};
	Pessoa* p2{new Pessoa{"Jose", 23}};
	bool add1 = true;
	bool add2 = true;

	Disciplina d1{"C++"};
	d1.setProfessor(prof);
	add1 = d1.adicionarAluno(p1);
	add2 = d1.adicionarAluno(p2);

	if(!add1 && !add2){
		std::cout << "Falha na inclusao de um dos alunos" << std::endl;
	}
	
	Pessoa ** vetorAlunos = d1.getVetorAlunos();
	for(unsigned int i=0; i < d1.getNumAlunos(); i++){
		std::cout << "Aluno " << i << ": " << vetorAlunos[i]->getNome() << std::endl;
	}
	

	delete p1;
	delete p2;
	delete prof;
	

	return 0;
}
