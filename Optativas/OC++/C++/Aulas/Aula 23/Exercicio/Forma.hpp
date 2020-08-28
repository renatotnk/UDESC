//Aluno: Renato Tanaka
#ifndef FORMA_H
#define FORMA_H

class Forma{
    public:
        Forma();
        virtual ~Forma() = default;
        virtual unsigned int getArea() = 0;
};
#endif