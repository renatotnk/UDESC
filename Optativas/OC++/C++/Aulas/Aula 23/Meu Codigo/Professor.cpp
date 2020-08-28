#include "Professor.hpp"

//#include<iostream>

Professor::Professor(const std::string& nome, const unsigned long cpf,
	       	const unsigned int valorHora, const unsigned short cargaHoraria)
		:Pessoa(nome, cpf), valorHora(valorHora), cargaHoraria(cargaHoraria) {
//	std::cout << "Construtindo professor " << nome << std::endl;
}

Professor::~Professor(){
}

unsigned int Professor::getValorHora() const{
	return valorHora;
}

void Professor::setValorHora(const int valorHora){
	this->valorHora = valorHora;
}


unsigned int Professor::getSalario() const{
	return this->valorHora * this->cargaHoraria * 4.5;//considerando que um mes tem 4,5 semanas
}

void Professor::setCargaHoraria(const unsigned short cargaHoraria){
	this->cargaHoraria = cargaHoraria;
}

unsigned short Professor::getCargaHoraria() const{
	return this->cargaHoraria;
}
