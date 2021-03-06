//Aluno: Renato Tanaka

#include <iostream>
#include <string>
#include <list>
#include "Pessoa.hpp"
#include "Disciplina.hpp"

int main(){
	Curso c1{"BCC", 1978, 72};
	Curso& cref{c1};
	Disciplina* cpp = new Disciplina{"C++", cref};
	Pessoa* p1 = new Pessoa{"Joao", 20, 11111111111};
	Pessoa* p2 = new Pessoa{"Maria", 21, 24121285700};
	Pessoa* p3 = new Pessoa{"Jose", 24, 19269938450};
	Pessoa* p4 = new Pessoa{"Pedro", 25, 99327365461};
	Pessoa* p5 = new Pessoa{"Marcos", 26, 51592119930};

	cpp->adicionarAluno(p1);
	cpp->adicionarAluno(p2);
	cpp->adicionarAluno(p3);
	cpp->adicionarAluno(p4);
	cpp->adicionarAluno(p5);

	cpp->removerAluno(p1);
	cpp->removerAluno(p2);
	cpp->removerAluno(p3);
	cpp->removerAluno(p4);
	cpp->removerAluno(p5);

	return 0;
}
