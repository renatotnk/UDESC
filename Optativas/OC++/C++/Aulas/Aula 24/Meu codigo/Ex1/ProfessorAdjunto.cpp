#include<iostream>
#include "ProfessorAdjunto.hpp"


ProfessorAdjunto::~ProfessorAdjunto(){
	std::cerr << "Destruindo objeto professor adjunto" << std::endl;
}

unsigned int ProfessorAdjunto::getSalario() const{
	return Professor::getSalario() * 1.1;
}
