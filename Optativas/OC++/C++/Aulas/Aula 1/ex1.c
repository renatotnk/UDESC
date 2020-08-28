// Aluno: Renato tanaka

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    char nome[50];
    unsigned short idade;
    unsigned long cpf;
} Pessoa;

long validaCPF(char cpf[]){
    int j = 0;
    int add1 = 0;
    int add2 = 0;
    int ver1 = 0;
    int ver2 = 0;
    char validacao[11] = "";

    printf("Validando CPF\n");

    if(strlen(cpf) != 11){
        printf("Numero de caracteres invalido.\n");   
    }
    
    sprintf(validacao, "%s", cpf); 

    /* 1o digito */
    for (j=0; j < 9; j++){
        add1 += (validacao[j] - 48) * (10 - j); //(subtraindo -48 por conta da posicao do numer 0 na tabela ASCII)
    }

    add1 %= 11;
    if(add1 < 2){
        ver1 = 0;
    }else{
        ver1 = 11- add1;
    }

    /* 2o digito */
    for (j=0; j<10; j++){
        add2 += (validacao[j] - 48) * (11 - j); //(subtraindo -48 por conta da posicao do numer 0 na tabela ASCII)
    }
    add2 %= 11;
    if(add2 < 2){
        ver2 = 0;
    }else{
        ver2 = 11- add2;
    }


    if ((cpf[9] - 48) == ver1 && (cpf[10] - 48) == ver2){
            printf("CPF validado com sucesso\n");
            return atol(cpf);
    }

    printf("CPF invalido! Por favor, digite um CPF valido.\n");
    return 0;
}




int main(void){

    Pessoa v[5];
    int i =0;
    for(int k = 0; k < 5; k++){
        strcpy(v[k].nome, "NULL");
        v[k].idade = 0;
        v[k].cpf = 0;
    }

    while (i < 5){
        printf("Digite o nome para o membro numero %d do banco:\n", i+1);
        scanf("%s*c", v[i].nome);

        printf("Digite a idade para o membro numero %d do banco:\n", i+1);
        scanf("%hu*c", &v[i].idade);

        unsigned long cpf = 0;
        while(1){
            char validar[11] = "";
            fflush(stdout);
            printf("Digite o CPF para o membro numero %d do banco (sem pontos e hifens):\n", i+1);
            scanf("%s",validar);
            unsigned long validado = (validaCPF(validar));
            if(validado != 0){
                cpf = validado;
                break;
            }
        }

        v[i].cpf = cpf;
        printf("Seu CPF valido eh: %lu\n", v[i].cpf); 
        i += 1;
    }


    return 0;    
}