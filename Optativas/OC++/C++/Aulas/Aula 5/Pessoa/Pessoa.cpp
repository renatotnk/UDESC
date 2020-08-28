//Aluno: Renato Tanaka
#include<iostream>
#include"Pessoa.hpp"

Pessoa::Pessoa()
    :nome{""}, cpf{0}, idade{(unsigned char)0}{
    std::cout << "Construtor 1" << std::endl;       // Porque nao printa?
}

Pessoa::Pessoa(std::string nomePessoa, unsigned short int idadePessoa)
        :nome{nomePessoa}, idade{(unsigned char)idadePessoa}{
    std::cout << "Construtor 2" << std::endl;
}

Pessoa::Pessoa(std::string nomePessoa, unsigned long cpfPessoa, unsigned short int idadePessoa)
    :Pessoa(nomePessoa, idadePessoa){

    if(validarCPF(cpfPessoa)){
        cpf = cpfPessoa;
    }else{
        cpf = 0;
    }
    std::cout << "Construtor 3" << std::endl;
}

std::string Pessoa::getNome(){
    return nome;
}

void Pessoa::setNome(std::string novoNome){
    nome = novoNome;
}


bool Pessoa::setCpf(unsigned long novoCpf){
	if(validarCPF(novoCpf)){
		cpf = novoCpf;
		return true;
	}
	return false;
}

unsigned long Pessoa::getCpf(){
	return cpf;
}

bool Pessoa::validarCPF(unsigned long cpfTeste){
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