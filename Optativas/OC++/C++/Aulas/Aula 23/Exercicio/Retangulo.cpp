//Aluno: Renato Tanaka
#include "Retangulo.hpp"

Retangulo::Retangulo(float base, float altura)
    :base{base}, altura{altura}{
}

float Retangulo::getArea() const{
    return this->base * this->altura;
}