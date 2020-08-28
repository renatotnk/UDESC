#ifndef ENGENHEIRO_HPP
#define ENGENHEIRO_HPP

#include "Pessoa.hpp"

class Engenheiro : virtual public Pessoa{
	public:
		Engenheiro(const std::string& nome, const unsigned long cpf, const unsigned int numeroCrea);
		virtual ~Engenheiro();

		unsigned int getNumeroCrea() const;
		void setNumeroCrea(const unsigned int numeroCrea);

	 	virtual unsigned int getSalario() const;

	private:
                const static unsigned int SALARIO_PADRAO;

		unsigned int numeroCrea;
};
#endif
