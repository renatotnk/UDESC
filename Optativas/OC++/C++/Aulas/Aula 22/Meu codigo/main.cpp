//Aluno: Renato Tanaka

#include <iostream>

#include "Pessoa.hpp"
#include "Professor.hpp"
#include "Disciplina.hpp"
#include "Aluno.hpp"


int main(){
	Aluno p1("João", 11111111111, 253061852, 5);
	Disciplina* d1{new Disciplina("C++")};

	d1->adicionarAluno(&p1);
	
	return 0;
}
