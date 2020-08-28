#include "Disciplina.hpp"

Disciplina::Disciplina(std::string nomeDisciplina)
	:nome{nomeDisciplina} {
}

Pessoa** Disciplina::getAlunos(){
	return alunos;
}

unsigned int Disciplina::getNumAlunos(){
	return numAlunos;
}

bool Disciplina::adicionarAluno(Pessoa* aluno){
	if(numAlunos >=49)
		return false;
	alunos[numAlunos] = aluno;
	numAlunos++;
	return true;
}

std::string Disciplina::getNome(){
	return nome;
}

void Disciplina::setNome(std::string novoNome){
	nome = novoNome;
}

int Disciplina::getCargaHoraria(){
	return cargaHoraria;
}

void Disciplina::setCargaHoraria(unsigned int novaCarga){
	cargaHoraria = novaCarga;
}

Pessoa* Disciplina::getProfessor(){
	return professor;
}

void Disciplina::setProfessor(Pessoa* novoProfessor){
	professor = novoProfessor;
}
