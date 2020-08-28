#ifndef BANCO_H
#define BANCO_H

int menu(void);

void relatorio(FILE *arquivo,int (*f) (double));

int devedor(double saldo);
int credor(double saldo);
int zerado(double saldo);

#endif