#ifndef BANCO_H
#define BANCO_H
 
typedef struct{
	int conta;
	char nome[20];
	char sobrenome[20];
	double saldo;
} Cliente;

int menu(void);
void cadastrar_cliente(FILE *arquivo);
void remover_cliente(FILE *arquivo);
void atualizar_cliente(FILE *arquivo);
void relatorio(FILE *arquivo);

#endif