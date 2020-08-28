#ifndef PROFESSOR_HPP
#define PROFESSOR_HPP

#include <string>
#include "Pessoa.hpp"

class Professor : public Pessoa{
	public:
		Professor(const std::string& nome, const unsigned long cpf, const unsigned int valorHora, const unsigned short cargaHoraria);
		~Professor();

		unsigned int getSalario() const;

		unsigned int getValorHora() const;
		void setValorHora(const int valorHora);

		void setCargaHoraria(const unsigned short cargaHoraria);
		unsigned short getCargaHoraria() const;

	private:
		unsigned int valorHora;
		unsigned short cargaHoraria;
};
#endif
