// Aluno: Renato Tanaka
#ifndef RETANGULO_H
#define RETANGULO_H

class Retangulo{
    public:
        Retangulo();
        Retangulo(float novaAltura, float novoComprimento = 5.0);

        float getAltura();
        void setAltura(float novaAltura);

        float getComprimento();
        void setComprimento(float novoComprimento);

        float getPerimetro();
        float getArea();

        unsigned int getNoRetangulos();
    private:
        static unsigned int noRetangulos;
        
        float altura;
        float comprimento;
        unsigned int retangulos;
};

#endif