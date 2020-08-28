#include<stdio.h>

extern int divisao(int dividendo, int divisor, int* resto);

int main(){
    int dividendo;
    int divisor;
    int resultado, resto;

    scanf("%d %d", &dividendo, &divisor);
    resultado = divisao(dividendo, divisor, &resto);
    printf("%d %d\n", resultado, resto);
    return 0;
}