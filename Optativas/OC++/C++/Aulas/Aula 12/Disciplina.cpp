//Aluno: Renato Tanaka

#include<iostream>
#include "Disciplina.hpp"
#include "SalaAula.hpp"

Disciplina::Disciplina(std::string nome, unsigned short cargaHoraria)
	:nome{nome}, cargaHoraria{cargaHoraria}{
}

std::string Disciplina::getNome(){
	return nome;
}

void Disciplina::setNome(std::string novoNome){
	this->nome = novoNome;
}

Pessoa* Disciplina::getProfessor(){
	return professor;
}

void Disciplina::setProfessor(Pessoa* professor){
	this->professor = professor;
}


int Disciplina::getCargaHoraria(){
	return cargaHoraria;
}

void Disciplina::setCargaHoraria(unsigned int cargaHoraria){
	this->cargaHoraria = cargaHoraria;
}

std::string Disciplina::getNomeProfessor(){
	return professor->getNome();
}

bool Disciplina::adicionarAluno(Pessoa* novoAluno){
	this->alunos.push_back(novoAluno);
	this->numAlunos++;
	return true;
}

bool Disciplina::removerAluno(Pessoa* aluno){
	std::cout << "Removendo o aluno " << aluno->getNome() << std::endl;
	this->itPes = this->alunos.begin();
	while(itPes != this->alunos.end()){
		if((*itPes)->getNome() == aluno->getNome()){
			this->itPes = this->alunos.erase(itPes);
			this->numAlunos--;
			std::cout << "Aluno removido com sucesso." << std::endl;
			return true;
		}else{
			this->itPes++;
		}
	}
	std::cout << "Erro, nao foi possivel encontrar o aluno." << std::endl;
	return false;
}

bool Disciplina::removerAluno(unsigned long cpf){
	std::cout << "Removendo o aluno com CPF" << cpf << std::endl;
	this->itPes = this->alunos.begin();
	while(itPes != this->alunos.end()){
		if((*itPes)->getCpf() == cpf){
			this->itPes = this->alunos.erase(itPes);
			this->numAlunos--;
			std::cout << "Aluno removido com sucesso." << std::endl;
			return true;
		}else{
			this->itPes++;
		}
	}
	std::cout << "Erro, nao foi possivel encontrar o aluno." << std::endl;
	return false;

}


unsigned int Disciplina::getNumAlunos(){
	return numAlunos;
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
}

SalaAula* Disciplina::getSalaAula(){
	return salaAula;
}

void Disciplina::setSalaAula(SalaAula* salaAula){
	this->salaAula = salaAula;
	salaAula->adicionarDisciplina(this);
}



/////////////////////////// Curso //////////////////////////////////

Curso::Curso(std::string nome, unsigned short anoCriacao = 0, unsigned short cargaHorariaMinima = 0)
	:nomeCurso{nome}, anoCriacao{anoCriacao}, cargaHorariaMinima{cargaHorariaMinima}{
}

std::string Curso::getNome(){
	return nomeCurso;
}

void Curso::setNome(std::string nomeCurso){
	this->nomeCurso = nomeCurso;
}

int Curso::getCargaHoraria(){
	return cargaHorariaMinima;
}

void Curso::setCargaHoraria(unsigned short cargaHorariaMinima){
	this->cargaHorariaMinima = cargaHorariaMinima;
}

int Curso::getAnoCriacao(){
	return anoCriacao;
}

void Curso::setAnoCriacao(unsigned short anoCriacao){
	this->anoCriacao = anoCriacao;
}

void Curso::imprimeDados(){
	std::cout << "Nome do curso: " << nomeCurso << std::endl;
	std::cout << "Ano de criacao do curso: " << anoCriacao << std::endl;
	std::cout << "Carga horaria minima: " << cargaHorariaMinima << std::endl;
}

void Curso::adicionarDisciplina(Disciplina* disciplina){
	this->disciplinas.push_back(disciplina);
	std::cout << "Disciplina " << disciplina->getNome() << " inserida com sucesso" << std::endl;
}

bool Curso::removerDisciplina(Disciplina* disciplina){
	std::cout << "Removendo a disciplina " << disciplina->getNome() << std::endl;
	this->itDis = this->disciplinas.begin();
	while(itDis != this->disciplinas.end()){
		if((*itDis)->getNome() == disciplina->getNome()){
			this->itDis = this->disciplinas.erase(itDis);
			std::cout << "Disciplina removida com sucesso." << std::endl;
			return true;
		}else{
			this->itDis++;
		}
	}
	std::cout << "Erro, nao foi possivel encontrar a disciplina." << std::endl;
	return false;
}
