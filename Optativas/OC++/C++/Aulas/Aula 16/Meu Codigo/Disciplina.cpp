//Aluno: Renato Tanaka

#include<iostream>
#include "Disciplina.hpp"
#include "SalaAula.hpp"

Disciplina::Disciplina(std::string nome, unsigned short cargaHoraria)
	:nome{nome}, cargaHoraria{cargaHoraria}, salaAula{nullptr}, professor{nullptr} {
}

Disciplina::~Disciplina(){
	std::cerr << "Destruindo a disciplina " << this->nome << std::endl;
	this->setSalaAula(nullptr);
	std::list<ConteudoMinistrado*>::iterator it;
	for(it=conteudos.begin(); it!=conteudos.end(); it++){
		delete *it;
	}
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

void Disciplina::adicionarAluno(Pessoa* novoAluno){
	this->alunos.push_back(novoAluno);
}

void Disciplina::removerAluno(Pessoa* aluno){
	std::cout << "Removendo o aluno " << aluno->getNome() << std::endl;
	this->alunos.remove(aluno);
	
}

void Disciplina::removerAluno(unsigned long cpf){
	std::cout << "Removendo o aluno com CPF" << cpf << std::endl;
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
	if(this->salaAula != nullptr){//se já existia uma sala, remover a disciplina dessa sala
		this->salaAula->removerDisciplina(this); 
	}
	this->salaAula = salaAula;
	if(this->salaAula != nullptr){
		this->salaAula->adicionarDisciplina(this);//adicionar a disciplina na nova sala
	}
}

void Disciplina::setSalaAulaSemAtualizarSala(SalaAula* salaAula){
	this->salaAula = salaAula;
}


void Disciplina::adicionarConteudoMinistrado(std::string conteudo, unsigned short cargaHorariaConteudo){
	this->conteudos.push_back(new ConteudoMinistrado{conteudo, cargaHorariaConteudo});
}

void Disciplina::removerConteudoMinistrado(unsigned long int id){
	std::list<ConteudoMinistrado*>::iterator it;
	for(it = conteudos.begin(); it!=conteudos.end(); it++){
		if((*it)->getId() == id){
			break;
		}
	}
	if(it != this->conteudos.end())
		conteudos.erase(it);
}

void Disciplina::imprimirConteudosMinistrados(){
	std::list<ConteudoMinistrado*>::iterator it;
	for(it = conteudos.begin(); it!=conteudos.end(); it++){
		std::cout << "Id: " << (*it)->getId() << std::endl
		<< "Conteudo: " << (*it)->getDescricao() << std::endl
		<< "Carga: " << (*it)->getCargaHorariaConteudo() << std::endl << std::endl;
	}
}

std::list<ConteudoMinistrado*>& Disciplina::getConteudos(){
	return conteudos;
}
void Disciplina::limparConteudos(){
	std::list<ConteudoMinistrado*>::iterator it;
	for(it = conteudos.begin(); it != conteudos.end(); it++){
		delete *it;
	}

	conteudos.clear();
}



/////////////////////////// Curso //////////////////////////////////

Curso::Curso(std::string nome, unsigned short anoCriacao = 0, unsigned short cargaHorariaMinima = 0)
	:nomeCurso{nome}, anoCriacao{anoCriacao}, cargaHorariaMinima{cargaHorariaMinima}{
}

Curso::~Curso(){
	std::cerr << "Destruindo o curso " << this->nomeCurso << std::endl;
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
