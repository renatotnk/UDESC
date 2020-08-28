#include "ProfessorAdjunto.hpp"

#include <iostream>

ProfessorAdjunto::~ProfessorAdjunto(){
}

unsigned int ProfessorAdjunto::getSalario() const{
	return Professor::getSalario() * 1.1;
}
