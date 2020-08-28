#include "ProfessorAdjunto.hpp"


unsigned int ProfessorAdjunto::getSalario() const{
	return Professor::getSalario() * 1.1;
}
