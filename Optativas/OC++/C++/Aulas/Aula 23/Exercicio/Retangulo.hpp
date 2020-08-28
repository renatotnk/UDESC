//Aluno: Renato Tanaka
#ifndef RETANGULO_H
#define RETANGULO_H

#include "Forma.hpp"

class Retangulo : public Forma{
    public:
        Retangulo(float base, float altura);
        virtual ~Retangulo() = default;
        float getArea() const;
    private:
        float base;
        float altura;
};
#endif