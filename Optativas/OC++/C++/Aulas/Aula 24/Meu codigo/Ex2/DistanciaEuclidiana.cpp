#include <cmath>
#include "DistanciaEuclidiana.hpp"

double DistanciaEuclidiana::calcularDistanciaPontos(const Ponto* const p1, const Ponto* const p2) const{
    return hypot((p1->getCoordX() - p2->getCoordX()),(p1->getCoordY() - p2->getCoordY()));
}