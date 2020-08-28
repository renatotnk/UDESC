//Aluno: Renato Tanaka
#include"Pessoa.hpp"

/*
unsigned char Pessoa::getIdade(){
    return idade;
}

void Pessoa::setIdade(unsigned char novaIdade){
    idade = novaIdade;
}
*/

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