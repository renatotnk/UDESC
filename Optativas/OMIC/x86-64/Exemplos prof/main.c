#include<stdio.h>
extern int divisao(int dividendo, int divisor, int* resto);

int main(){
    int dividendo, divisor, resultado, resto;
    scanf("%i %i", &dividendo, &divisor);
    resultado = divisao(dividendo, divisor, &resto);
    printf("%d / %d = %d Resto %d\n", dividendo, divisor, resultado, resto);
    return 0;
}