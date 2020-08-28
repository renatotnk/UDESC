#ifndef DISTANCIA_M_HPP
#define DISTANCIA_M_HPP

#include "Trajeto.hpp"

class DistanciaManhattan : public Trajeto{
    public:
        using Trajeto::Trajeto;
        virtual ~DistanciaManhattan() = default;
        virtual double calcularDistanciaPontos(const Ponto* const p1, const Ponto* const p2) const;
};
#endif