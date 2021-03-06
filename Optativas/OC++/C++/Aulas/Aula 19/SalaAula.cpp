#include<iostream>
#include "SalaAula.hpp"

SalaAula::SalaAula(std::string nome, unsigned int capacidade)
	:nome{nome}, capacidade{capacidade}{
}

SalaAula::~SalaAula(){
	std::cerr << "Destruind a sala de aula " << this->nome << std::endl;
	std::list<Disciplina*>::iterator it;
	for(it = disciplinasMinistradas.begin(); it != disciplinasMinistradas.end(); it++){
			(*it)->setSalaAulaSemAtualizarSala(nullptr);
	}
}
    
std::string SalaAula::getNome() const{
	return nome;
}

void SalaAula::setNome(std::string nome){
	this->nome = nome;
}

unsigned int SalaAula::getCapacidade() const{
	return capacidade;
}

void SalaAula::setCapacidade(unsigned int capacidade){
	this->capacidade = capacidade;
}

void SalaAula::adicionarDisciplina(Disciplina* disciplina){
    disciplinasMinistradas.push_back(disciplina);
}

void SalaAula::removerDisciplina(Disciplina* disciplina){
    disciplinasMinistradas.remove(disciplina);
}

std::list<Disciplina*>& SalaAula::getDisciplinas(){
    return disciplinasMinistradas;
}