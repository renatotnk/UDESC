// Aluno: Renato Tanaka
#include<iostream>
#include"Retangulo.hpp"

int main(){
	Retangulo r0();
	Retangulo r1(10.0);

	float novaAltura = 0.0;
    float novoComprimento = 0.0;

	std::cout << "Digite a altura do retangulo r2:" << std::endl;
	std::cin >> novaAltura;
	
	std::cout << "Digite o comprimento do retangulo r2:" << std::endl;
    std::cin >> novoComprimento;
	
	Retangulo r2(novaAltura, novoComprimento);

	std::cout << "Perimetro r1:" << r1.getPerimetro() << std::endl;
	std::cout << "Area r1:" << r1.getArea() << std::endl;

	std::cout << "Perimetro r2:" << r2.getPerimetro() << std::endl;
	std::cout << "Area r2:" << r2.getArea() << std::endl;

	std::cout << r1.getNoRetangulos() << std::endl;


	return 0;
}

