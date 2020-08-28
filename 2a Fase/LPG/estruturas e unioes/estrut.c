#include <stdio.h>
#include <math.h>
typedef struct ponto {
	int x;
	int y;
}Ponto;

double distancia (Ponto a,Ponto b);

int main(void){
	int d = 0;
	Ponto p1;
	Ponto p2;
	printf("coordenadas para p1\n");
	scanf("%d %d ",&p1.x,&p1.y);
	printf("coordenadas para p2\n");
	scanf("%d %d",&p2.x,&p2.y);
	d = distancia(p1,p2);
	printf("distancia = %d\n",d);
	return 0;
}

double distancia(Ponto a,Ponto b){
	int x = 0;
	x = sqrt(pow(a.x-b.x,2) + pow(a.y-b.y,2));
	return x;
}