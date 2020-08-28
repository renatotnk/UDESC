//Aluno: Renato Tanaka
#ifndef PESSOA_H
#define PESSOA_H
#include<string>

class Pessoa{
	public:
		inline unsigned char getIdade(){
			return idade;
		}
		inline void setIdade(const unsigned char novaIdade){
			idade = novaIdade;
		}

		std::string getNome();
		void setNome(std::string novoNome);

		bool setCpf(unsigned long novoCpf);
		unsigned long getCpf();
	private:
		std::string nome;
		unsigned long cpf;
		unsigned char idade;

		bool validarCPF(unsigned long cpfTeste);
};

#endif