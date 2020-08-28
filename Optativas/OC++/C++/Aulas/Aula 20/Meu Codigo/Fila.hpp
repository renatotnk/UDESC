#ifndef FILA_HPP
#define FILA_HPP
#include<iostream>
#include<list>

template <typename T>
class Fila{
    public:
        Fila():tamanho{0}{
            std::cout << "Fila criada com sucesso!" << std::endl;
        }

        ~Fila(){
        }

        bool push(const T valor){
            this->fila.push_back(valor);
            this->tamanho++;
            return true;
        }

        bool pop(T* const retorno){
            if(!this->filaVazia()){
                *retorno = this->fila.front();
                this->fila.pop_front();
                this->tamanho--;
                return true;
            }
            return false;
        }

        bool filaVazia(){
            if(this->tamanho == 0){
                return true;
            }
            return false;
        }

    private:
        std::list<T> fila;
        unsigned int tamanho;
};
#endif