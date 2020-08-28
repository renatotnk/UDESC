//Aluno: Renato Tanaka
#include "Triangulo.hpp"

Triangulo::Triangulo(float base, float altura)
    :base{base}, altura{altura}{
}

float Triangulo::getArea() const{
    return ((this->base * this->altura) / 2);
}