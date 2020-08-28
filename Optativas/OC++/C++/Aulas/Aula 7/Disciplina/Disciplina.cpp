//Aluno: Renato Tanaka

#include<iostream>
#include "Disciplina.hpp"

Disciplina::Disciplina(std::string nomeDisciplina)
	:nome{nomeDisciplina} {
}

std::string Disciplina::getNome(){
	return nome;
}

Pessoa* Disciplina::getProfessor(){
	return professor;
}

void Disciplina::setProfessor(Pessoa* novoProfessor){
	professor = novoProfessor;
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

std::string Disciplina::getNomeProfessor(){
	return professor->getNome();
}

bool Disciplina::adicionarAluno(Pessoa* novoAluno){
	if(numAlunos >= 49){
		return false;
	}else{
		alunos[numAlunos] = novoAluno;
		numAlunos++;
		return true;
	}
}

unsigned int Disciplina::getNumAlunos(){
	return numAlunos;
}

Pessoa** Disciplina::getVetorAlunos(){
	return alunos;
}