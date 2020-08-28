//Aluno: Renato Tanaka

#include <iostream>
#include <string>

#include "Pessoa.hpp"
#include "Disciplina.hpp"

int main(){
	Pessoa* p1{new Pessoa{"Joao", 20}};
	Curso c1 = {"BCC", 1985, 36};
	Disciplina disciplina{"C++", c1};
	disciplina.setProfessor(p1);
	disciplina.setCargaHoraria(72);

	std::string cabecalho = "Dados da disciplina";
	unsigned int cargaHorariaTotal = 3000;
	disciplina.imprimeDados(cabecalho,
	cargaHorariaTotal);

	delete p1;

	return 0;
}
