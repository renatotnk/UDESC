// Aluno: Renato Tanaka
#include<iostream>
#include"Retangulo.hpp"

int main(){
	Retangulo r1;

    float novaAltura = 0.0;
    float novoComprimento = 0.0;

	std::cin >> novaAltura;
	r1.setAltura(novaAltura);
	std::cout << "Altura:" << r1.getAltura() << std::endl;

    std::cin >> novoComprimento;
	r1.setComprimento(novaAltura);
	std::cout << "Comprimento:" <<  r1.getComprimento() << std::endl;

	std::cout << "Perimetro:" << r1.getPerimetro() << std::endl;
	
	std::cout << "Area:" << r1.getArea() << std::endl;


	return 0;
}

