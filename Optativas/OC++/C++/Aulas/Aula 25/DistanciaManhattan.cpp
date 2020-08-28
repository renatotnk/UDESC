#include <cmath>
#include "DistanciaManhattan.hpp"

double DistanciaManhattan::calcularDistanciaPontos(const Ponto* const p1, const Ponto* const p2) const{
    return abs(p1->getCoordX() - p2->getCoordX()) + abs(p1->getCoordY() - p2->getCoordY());
}