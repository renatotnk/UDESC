#ifndef PESSOA_H
#define PESSOA_H

#include<string>

class Pessoa{
	public:
		Pessoa();

		Pessoa(const std::string& nome);

		Pessoa(const std::string& nome, const unsigned long cpf);

		unsigned short int getIdade() const;
		void setIdade(const unsigned short int idade);

		std::string getNome() const;
		void setNome(const std::string& nome);

		unsigned long getCpf() const;
		void setCpf(const unsigned long cpf);
	protected:
		std::string nome;
		unsigned long cpf;
		unsigned char idade;

	private:
		bool validarCPF(unsigned long cpfTeste) const;
};

#endif
