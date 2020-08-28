// Aluno: Renato Tanaka
#include<iostream>
#include"Retangulo.hpp"

Retangulo::Retangulo()
    :altura{0.0}, comprimento{0.0}{
    std::cout << "Retangulo vazio inicializado com sucesso" << std::endl;
}

Retangulo::Retangulo(float novaAltura, float novoComprimento)
    :altura{novaAltura}, comprimento{novoComprimento}{
    std::cout << "Retangulo inicializado com sucesso" << std::endl;
}

float Retangulo::getAltura(){
    return altura;
}

float Retangulo::getComprimento(){
    return comprimento;
}

void Retangulo::setAltura(float novaAltura){
    altura = novaAltura;
}

void Retangulo::setComprimento(float novoComprimento){
    comprimento = novoComprimento;
}

float Retangulo::getArea(){
    float area = 0.0;
    area = altura * comprimento;
    return area;
}

float Retangulo::getPerimetro(){
    float perimetro = 0.0;
    perimetro = (2 * altura) + (2 * comprimento);
    return perimetro;
}