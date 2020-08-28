#include<iostream>
#include<string>
#include"Fila.hpp"

int main(){
    std::string retorno;
    Fila<std::string> f;
    f.push("Primeiro");
    f.push("Segundo");
    f.push("Terceiro");
    f.push("Quarto");
    f.push("Quinto");

    while(!f.filaVazia()){
        f.pop(&retorno);
        std::cout << retorno << std::endl;
    }

    std::cout << "Fim" << std::endl;

    return 0;
}