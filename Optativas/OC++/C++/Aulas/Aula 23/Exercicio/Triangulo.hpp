//Aluno: Renato Tanaka
#ifndef TRIANGULO_H
#define TRIANGULO_H

#include "Forma.hpp"

class Triangulo : public Forma{
    public:
        Triangulo(float base, float altura);
        virtual ~Triangulo() = default;
        float getArea() const;
    private:
        float base;
        float altura;
};
#endif