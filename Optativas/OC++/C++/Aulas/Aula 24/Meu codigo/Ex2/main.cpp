#include <iostream>

#include "Trajeto.hpp"
#include "DistanciaManhattan.hpp"
#include "DistanciaEuclidiana.hpp"

int main(){
	DistanciaEuclidiana* e{new DistanciaEuclidiana};
	DistanciaManhattan* m{new DistanciaManhattan};

	Ponto* p1{new Ponto(1.0, 1.0)};
	Ponto* p2{new Ponto(2.0, 2.0)};
	
	e->adicionarPonto(1.0, 1.0);
	m->adicionarPonto(2.0, 2.0);

	e->imprimirTrajeto();
	m->imprimirTrajeto();

	double d1 = e->calcularDistanciaPontos(p1, p2);
	double d2 = m->calcularDistanciaPontos(p1, p2);

	std::cout << "Distancia Euclidiana: " << d1 << std::endl;
	std::cout << "Distancia Manhattan: " << d2 << std::endl;	

	return 0;
}
