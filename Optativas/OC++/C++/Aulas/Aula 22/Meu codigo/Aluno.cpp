//Aluno: Renato Tanaka

#include<iostream>

#include "Aluno.hpp"

Aluno::Aluno(const std::string& nome, const unsigned long cpf,
const unsigned int matricula, const unsigned short fase)
    :Pessoa(nome, cpf), matricula(matricula), fase(fase){
        std::cout << "Aluno criado!" << std::endl;
        idade = (char)18;
}

Aluno::~Aluno(){
}

unsigned long Aluno::getMatricula() const{
    return this->matricula;
}

void Aluno::setMatricula(const unsigned long matricula){
    this->matricula = matricula;
}

unsigned short Aluno::getFase() const{
    return this->fase;
}

void Aluno::setFase(const unsigned short fase){
    this->fase = fase;
}

