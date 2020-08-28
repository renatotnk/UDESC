#ifndef PESSOA_H
#define PESSOA_H

#include<string>

class Pessoa{
	public:
		//Pessoa();

		Pessoa(const std::string& nome);

		Pessoa(const std::string& nome, const unsigned long cpf);

		virtual ~Pessoa();

		unsigned short int getIdade() const;
		void setIdade(const unsigned short int idade);

		std::string getNome() const;
		void setNome(const std::string& nome);

		unsigned long getCpf() const;
		void setCpf(const unsigned long cpf);
	private:
		bool validarCPF(unsigned long cpfTeste) const;
	
		std::string nome;
		unsigned long cpf;
		unsigned char idade;
};

#endif
