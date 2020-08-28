//Aluno: Renato Tanaka
#define _USE_MATH_DEFINES
#include <cmath>

#include "Circulo.hpp"


Circulo::Circulo(float r)
    :r{r}{
}

float Circulo::getArea() const{
    return M_PI * pow(this->r, 2);
}