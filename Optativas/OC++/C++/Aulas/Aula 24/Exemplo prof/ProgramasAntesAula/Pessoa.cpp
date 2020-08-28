#include "Pessoa.hpp"

//#include<iostream>

Pessoa::Pessoa(){
}

Pessoa::Pessoa(const std::string& nome)
		:nome{nome} {
//	std::cout << "Construindo Pessoa " << nome << std::endl;
}

Pessoa:: Pessoa(const std::string& nome, const unsigned long cpf)
		: Pessoa(nome) {
	if(validarCPF(cpf))
		this->cpf = cpf;
	else
		this->cpf = 0;
}

std::string Pessoa::getNome() const{
	return this->nome;
}

void Pessoa::setNome(const std::string& nome) {
	this->nome = nome;
}

unsigned long Pessoa::getCpf() const{
	return this->cpf;
}

void Pessoa::setCpf(const unsigned long cpf){
	if(validarCPF(cpf))
		this->cpf = cpf;
}

unsigned short int Pessoa::getIdade() const{
	return this->idade;
}

void Pessoa::setIdade(const unsigned short int idade){
	this->idade =  idade;
}

bool Pessoa::validarCPF(unsigned long cpfTeste) const{
	int somatorioValidaUltimo;
	int modulo;
	int somatorioValidaPenultimo = 0;
	int ultimo = cpfTeste%10;
	cpfTeste = cpfTeste/10;
	int penultimo = cpfTeste%10;
	cpfTeste = cpfTeste/10;
	
	somatorioValidaUltimo = penultimo*2;
	for(int i=2; i <= 11; i++){
		modulo = cpfTeste%10;
		cpfTeste = cpfTeste/10;
		somatorioValidaPenultimo += modulo*i;
		somatorioValidaUltimo += modulo*(i+1);
	}
	modulo = somatorioValidaPenultimo%11;
	if(modulo < 2){
		if(!penultimo)
			return false;//cpf invalido
	}else{
		if(penultimo != 11 - modulo)
			return false;//cpf invalido
	}
	modulo = somatorioValidaUltimo%11;
	if(modulo < 2){
		if(!ultimo)
			return false;//cpf invalido
	}else{
		if(ultimo != 11-modulo)
			return false;//cpf invalido
	}
	return true;//cpf valido
}
