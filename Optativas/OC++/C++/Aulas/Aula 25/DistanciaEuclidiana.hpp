#ifndef DISTANCIA_E_HPP
#define DISTANCIA_E_HPP

#include "Trajeto.hpp"

class DistanciaEuclidiana : public Trajeto{
    public:
        using Trajeto::Trajeto;
        virtual ~DistanciaEuclidiana() = default;
        virtual double calcularDistanciaPontos(const Ponto* const p1, const Ponto* const p2) const;
};
#endif