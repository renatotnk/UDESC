//Aluno: Renato Tanaka
#ifndef CIRCULO_H
#define CIRCULO_H

#include "Forma.hpp"

class Circulo : public Forma{
    public:
        Circulo(float r);
        virtual ~Circulo() = default;
        float getArea() const;
    private:
        float r;
};

#endif