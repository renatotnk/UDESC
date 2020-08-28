//Aluno: Renato Tanaka

#include <iostream>
#include <string>
#include <list>
#include "Pessoa.hpp"
#include "Disciplina.hpp"
#include "SalaAula.hpp"

int main(){
	Curso c1{"BCC", 1978, 72};
	Disciplina* cpp = new Disciplina{"C++", 36};
	Disciplina* rby = new Disciplina{"Ruby", 36};
	Disciplina* pyt = new Disciplina{"Python", 36};
	Disciplina* java= new Disciplina{"Java", 36};
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

	c1.adicionarDisciplina(cpp);
	c1.adicionarDisciplina(rby);
	c1.adicionarDisciplina(pyt);
	c1.adicionarDisciplina(java);

	c1.removerDisciplina(rby);
	c1.removerDisciplina(pyt);
	c1.removerDisciplina(java);

	return 0;
}
