//Aluno: Renato Tanaka

#include<iostream>
#include "Professor.hpp"

Professor::Professor(const std::string& nome, const unsigned long cpf,
const unsigned int salario, const unsigned short cargaHoraria)
    :Pessoa(nome, cpf), salario(salario), cargaHoraria(cargaHoraria){
        std::cout << "Professor criado!" << std::endl;
        idade = (char)15;
}

Professor::~Professor(){
}

void Professor::setSalario(const unsigned int salario){
    this->salario = salario;
}

unsigned int Professor::getSalario() const{
    return this->salario;
}

void Professor::setCargaHoraria(const unsigned short cargaHoraria){
    this->cargaHoraria = cargaHoraria;
}

unsigned short Professor::getCargaHoraria() const{
    return this->cargaHoraria;
}