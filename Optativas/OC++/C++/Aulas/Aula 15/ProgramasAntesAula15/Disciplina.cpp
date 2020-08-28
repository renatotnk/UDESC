#include "Disciplina.hpp"

#include<iostream>

#include "SalaAula.hpp"

Disciplina::Disciplina(std::string nome)
	:nome{nome}, cargaHoraria{0}, salaAula{nullptr}, professor{nullptr} {
}

void Disciplina::adicionarAluno(Pessoa* aluno){
	this->alunos.push_back(aluno);
}

void Disciplina::removerAluno(Pessoa* aluno){
	this->alunos.remove(aluno);
}

void Disciplina::removerAluno(unsigned long cpf){
	std::list<Pessoa*>::iterator it;

	for(it = this->alunos.begin(); it != this->alunos.end(); it++)
		if((*it)->getCpf() == cpf)
			break;
	if(it != this->alunos.end())
		alunos.erase(it);
}

std::list<Pessoa*>& Disciplina::getAlunos(){//retornamos uma referência para a lista, o que custa mais barato
	return alunos;
}

std::string Disciplina::getNome(){
	return this->nome;
}

void Disciplina::setNome(std::string nome){
	this->nome = nome;
}

int Disciplina::getCargaHoraria(){
	return this->cargaHoraria;
}

void Disciplina::setCargaHoraria(unsigned int cargaHoraria){
	this->cargaHoraria = cargaHoraria;
}

Pessoa* Disciplina::getProfessor(){
	return this->professor;
}

void Disciplina::setProfessor(Pessoa* professor){
	this->professor = professor;
}

void Disciplina::setSalaAula(SalaAula* salaAula){
	if(this->salaAula != nullptr)//se já existia uma sala, remover a disciplina dessa sala
		this->salaAula->removerDisciplina(this);
	this->salaAula = salaAula;
	if(this->salaAula != nullptr)
		this->salaAula->adicionarDisciplina(this);//adicionar a disciplina na nova sala
}

SalaAula* Disciplina::getSalaAula(){
	return this->salaAula;
}

void Disciplina::adicionarConteudoMinistrado(std::string conteudo, unsigned short cargaHorariaConteudo){
	this->conteudos.push_back(new ConteudoMinistrado{conteudo, cargaHorariaConteudo});
}

std::list<ConteudoMinistrado*>& Disciplina::getConteudos(){
	return conteudos;
}
