#include <stdio.h>
typedef struct {
	char *valor;
	char *naipe;
}Carta;

int main(void){
	Carta c1;
	Carta c2;
	c1.valor = "sete";
	c1.naipe = "ouro";
	c2.valor = "seis";
	c2.naipe = "espadas";
	Carta *pc1;
	pc1 = &c1;
	printf("%s de %s\n",c1.valor,c1.naipe);
	printf("%s de %s\n",pc1->valor,pc1->naipe);
	return 0;
}
