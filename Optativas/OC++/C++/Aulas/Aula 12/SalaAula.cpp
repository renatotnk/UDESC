#include<iostream>
#include "Disciplina.hpp"

void SalaAula::adicionarDisciplina(Disciplina* disciplina){
    disciplinasMinistradas.push_back(disciplina);
}

void SalaAula::removerDisciplina(Disciplina* disciplina){
    disciplinasMinistradas.remove(disciplina);
}

std::list<Disciplina*>& SalaAula::getDisciplinas(){
    return disciplinasMinistradas;
}