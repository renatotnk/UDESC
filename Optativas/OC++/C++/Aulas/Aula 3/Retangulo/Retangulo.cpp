// Aluno: Renato Tanaka
#include"Retangulo.hpp"

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