// Aluno: Renato Tanaka
#ifndef RETANGULO_H
#define RETANGULO_H

class Retangulo{
    public:
        float getAltura();
        void setAltura(float novaAltura);

        float getComprimento();
        void setComprimento(float novoComprimento);

        float getPerimetro();
        float getArea();
    private:
        float altura;
        float comprimento;
};

#endif