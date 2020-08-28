#ifndef PROFESSOR_ADJUNTO_HPP
#define PROFESSOR_ADJUNTO_HPP

#include "Professor.hpp"

class ProfessorAdjunto : public Professor{
	public:
		using Professor::Professor;
		unsigned int getSalario() const;
};
#endif
