//Aluno: Renato Tanaka

#include<iostream>
#include "Disciplina.hpp"

Disciplina::Disciplina(std::string nomeDisciplina, Curso& associado)
	:nome{nomeDisciplina}, cursoAssociado{associado}{
}

std::string Disciplina::getNome(){
	return nome;
}

void Disciplina::setNome(std::string novoNome){
	nome = novoNome;
}

Pessoa* Disciplina::getProfessor(){
	return professor;
}

void Disciplina::setProfessor(Pessoa* novoProfessor){
	professor = novoProfessor;
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

void Disciplina::imprimeDados(std::string& cabecalho,
	unsigned int cargaTotalCurso){
	double pctCurso = (double)cargaHoraria/cargaTotalCurso;
	pctCurso = pctCurso * 100;
	std::cout << cabecalho << std::endl;
	std::cout << "Disciplina: " << nome << std::endl;
	std::cout << "Carga: " << cargaHoraria << std::endl;
	std::cout << "Pct do curso: " << pctCurso << "%" << std::endl;
	std::cout << "Professor: " << professor->getNome() << std::endl;
	cursoAssociado.imprimeDados();
}

Curso::Curso(std::string novoNome, unsigned short novaCriacao = 0, unsigned short novaMinima = 0)
	:nomeCurso{novoNome}, anoCriacao{novaCriacao}, cargaHorariaMinima{novaMinima}{
}

std::string Curso::getNome(){
	return nomeCurso;
}

void Curso::setNome(std::string novoNome){
	nomeCurso = novoNome;
}

int Curso::getCargaHoraria(){
	return cargaHorariaMinima;
}

void Curso::setCargaHoraria(unsigned short novaCarga){
	cargaHorariaMinima = novaCarga;
}

int Curso::getAnoCriacao(){
	return anoCriacao;
}

void Curso::setAnoCriacao(unsigned short novoAno){
	anoCriacao = novoAno;
}

void Curso::imprimeDados(){
	std::cout << "Nome do curso: " << nomeCurso << std::endl;
	std::cout << "Ano de criacao do curso: " << anoCriacao << std::endl;
	std::cout << "Carga horaria minima: " << cargaHorariaMinima << std::endl;
}