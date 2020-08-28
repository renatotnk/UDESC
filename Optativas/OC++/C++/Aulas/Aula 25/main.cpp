#include <iostream>

#include "Trajeto.hpp"
#include "DistanciaManhattan.hpp"
#include "DistanciaEuclidiana.hpp"

int main(){
	Trajeto *t{new Trajeto};
	DistanciaEuclidiana* e{new DistanciaEuclidiana};
	DistanciaManhattan* m{new DistanciaManhattan};

	Ponto* p1{new Ponto(1.0, 1.0)};
	Ponto* p2{new Ponto(2.0, 2.0)};
	
	e->adicionarPonto(1.0, 1.0);
	m->adicionarPonto(2.0, 2.0);

	e->imprimirTrajeto();
	m->imprimirTrajeto();

	delete e;
	delete m;
	delete t;

	return 0;
}
