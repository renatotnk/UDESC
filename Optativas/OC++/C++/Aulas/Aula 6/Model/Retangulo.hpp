/**
 * Project Untitled
 */


#ifndef _RETANGULO_H
#define _RETANGULO_H

class Retangulo {
    public:     
        void Retangulo();

        /**
         * @param novaAltura
         * @param novoComprimento
         */
        void Retangulo(float novaAltura, float novoComprimento);
        
        float getAltura();
        
        /**
         * @param novaAltura
         */
        void setAltura(float novaAltura);
            
        float getComprimento();
            
        /**
         * @param novoComprimento
         */
        void setComprimento(float novoComprimento);
            
        float getPerimetro();
            
        float getArea();
    private: 
        float altura;
        float comprimento;
};

#endif //_RETANGULO_H