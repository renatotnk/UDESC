#include<stdio.h>
extern void intToString(int i, char *c);

int main(){
    int input;
    char* string;

    printf("Digite um inteiro:\n");
    scanf("%d\n", &input);
    intToString(input, string);
    puts(string);

    return 0;
}