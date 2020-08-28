//Aluno: Renato Tanaka
#include<iostream>

#include "Forma.hpp"
#include "Circulo.hpp"
#include "Retangulo.hpp"
#include "Triangulo.hpp"

int main(){
    Circulo r{1};
    Retangulo s{2,3};
    Triangulo t{2,3};

    std::cout << "Area circulo: " << r.getArea() << std::endl;
    std::cout << "Area retangulo: " << s.getArea() << std::endl;
    std::cout << "Area triangulo: " << t.getArea() << std::endl;

    return 0;
}