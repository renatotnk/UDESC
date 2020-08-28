#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

typedef struct Cliente{
       char nome[100], datacompra[11], datapagamento[11], tlfixo[16], tlmovel[16], endereco[50]; /*define as estruturas para cadastro e 
	   																								e procura do Cliente*/ 
                      } STcliente;

int verificaNumero(char nome[100]){ //fun��o verificadora de numeros no lugar errado
	int i, contador;
	for (i=0; i<strlen(nome); i++){
		if (isdigit(nome[i])){
			printf("\nTente novamente!\n");	
			return 0;
		}	
	}
	return 1;
	system ("cls");
}

int verificaLetra(char data[100]){ //fun��o verificadora de letras no lugar errado
	int i, contador;
	for (i=0; i<strlen(data); i++){
		if (isalpha(data[i])){
			printf("\nTente novamente!\n");	
			return 0;
		}	
	}
	return 1;
	system ("cls");
                                }

int verificaData (char data[100]) {
	int i;
	
	if (strlen(data)>10){
			printf("\n\nFormato Inv�lido! Tente novamente!\n\n");
			return 0;
	                    }
	
	for (i=0; i<11; i++){
		if (data[2] != '/' && data [5] != '/' ) {
			printf("\n\nFormato inv�lido! Tente novamente!\n\n");
			return 0;
		                                        }   
	                    }
	return 1;
                                 }

int verificaTelefone (char numero[100]) {
	int i;

	if (strlen(numero)>15) {			
		printf("\n\nFormato Inv�lido! Tente novamente!\n\n");
		return 0;
	                       }
	
	for (i=0; i<15; i++) {
		printf("%c",numero[i]);
		if (numero[0] != '(' || numero[4] != ')' || numero[10] != '-' ) {
			printf("\n\nFormato inv�lido! Tente novamente!\n\n");
			return 0;
		                                                                }
                       	}
	
	for (i=0; i<15; i++)  {
		if (!isspace(numero[5])){
			("\n\nFormato inv�lido! Tente novamente\n\n");
			return 0;
		                        }	
                        	}
	return 1;
                                        }

int escreveArquivo(FILE *arquivo, STcliente cli) {
    arquivo = fopen("teste.arq","ab");
    int verificatel, i, contador, contador1;
    
    if (arquivo == NULL){ 
       printf("N�o foi poss�vel abrir o arquivo");
       return 0;
                        }
    
	do{
    	contador = 0;
		printf("Digite o nome do cliente: "); 
    	fflush(stdin);//para n�o se ter problema com espa�os no nome, a fun��o fflush limpa o espa�o
		gets(cli.nome);//l� o espa�o corretamente
		for (i=0; i<strlen(cli.nome);i++){ //estrutura de repeti��o para verifica��o de muitos espa�os
			if (isspace(cli.nome[i])){
				contador++;
			                         }
		                                  }	
    } while (verificaNumero(cli.nome) == 0 || strlen(cli.nome) == 0 /* pede de novo se der enter */|| contador == strlen(cli.nome) );

	do{
		contador = 0;
		printf("\nDigite a data da compra do cliente (Formato: DD/MM/AAAA): ");
    	fflush(stdin);//n�o ter problema com espa�os no nome, limpa o espa�o
		gets(cli.datacompra);//l� o espa�o corretamente
		for (i=0; i<strlen(cli.datacompra);i++){//estrutura de repeti��o para verifica��o de muitos espa�os
			if (isspace(cli.datacompra[i])){
				contador++;
			}
		}	
    } while (verificaLetra(cli.datacompra) == 0 || strlen (cli.datacompra) == 0 /* pede de novo se der enter */|| contador == strlen(cli.datacompra) || verificaData(cli.datacompra) == 0);
    
	do{
		contador = 0;
		printf("\nDigite a data de pagamento (Formato: DD/MM/AAAA): ");
    	fflush(stdin); //para n�o se ter problema com espa�os no nome, a fun��o fflush limpa o espa�o
		gets(cli.datapagamento); //l� o espa�o corretamente
		for (i=0; i<strlen(cli.datapagamento);i++){//estrutura de repeti��o para verifica��o de muitos espa�os
			if (isspace(cli.datapagamento[i])){
				contador++;
		                                   	  }
	                                               }	
    } while (verificaLetra(cli.datapagamento) == 0 || strlen(cli.datapagamento) == 0 /* pede de novo se der enter */|| contador == strlen(cli.datapagamento) || verificaData(cli.datapagamento) == 0);
    
    do{
		contador = 0;
		printf("\nDigite um telefone celular para o cliente (Formato: (DDD) XXXX-XXXX): ");
    	fflush(stdin); //para n�o se ter problema com espa�os no nome, a fun��o fflush limpa o espa�o
		gets(cli.tlmovel); //l� o espa�o corretamente
		for (i=0; i<strlen(cli.tlmovel);i++) { //estrutura de repeti��o para verifica��o de muitos espa�os
			if (isspace(cli.tlmovel[i])){
				contador++;
			                             }
		                                      }	
    } while (verificaLetra(cli.tlmovel) == 0 || strlen (cli.tlmovel) == 0 /* pede de novo se der enter */|| contador == strlen(cli.tlmovel) || verificaTelefone(cli.tlmovel) == 0);
    
    do{
		contador = 0;
		printf("\nO cliente possui telefone fixo? (Digite '1' para sim; Digite '2' para n�o): ");
    	scanf("%i", &verificatel);
    } while (strlen (cli.nome) == 0 || contador == strlen(cli.datacompra));
	
	do{
    	if (verificatel == 1){
    		contador = 0;
			printf("\nDigite um telefone fixo para o cliente (Formato: (DDD) XXXX-XXXX): ");
    		fflush(stdin); //para n�o se ter problema com espa�os no nome, a fun��o fflush limpa o espa�o
			gets(cli.tlfixo); //l� o espa�o corretamente
			for (i=0; i<strlen(cli.tlfixo);i++){//estrutura de repeti��o para verifica��o de muitos espa�os
			if (isspace(cli.tlfixo[i])){
				contador++;
			                             }
		                                       }		
    	                       }
    	else   {
    		printf("\nO cliente n�o possui telefone fixo\n");
    		break;
    	       }
    } while (verificaLetra(cli.tlfixo) == 0 || strlen (cli.tlfixo) == 0 /* pede de novo se der enter */|| contador == strlen(cli.tlfixo) || verificaTelefone(cli.tlfixo) == 0);
	
	do{
		contador = 0;
		printf("\nDigite o endere�o do cliente: ");
    	fflush(stdin); //para n�o se ter problema com espa�os no nome, a fun��o fflush limpa o espa�o
		gets(cli.endereco);//l� o espa�o corretamente
    	for (i=0; i<strlen(cli.endereco);i++) { //estrutura de repeti��o para verifica��o de muitos espa�os
			if (isspace(cli.endereco[i])){
				contador++;
			                             }
		                                      }	
    } while (strlen (cli.endereco) == 0 || contador == strlen(cli.endereco));
    
    fwrite(&cli,sizeof(STcliente),1,arquivo);
    system ("cls");
    printf ("\nCadastro do cliente conclu�do com sucesso!\n\nPressione enter para retorar ao menu principal.");
    fclose(arquivo);
                                                         }

int leArquivo(FILE *arquivo, STcliente cli) { //m�dulo para exibi��o dos cadastros
    arquivo = fopen("teste.arq","rb");

    if (arquivo == NULL){ 
       printf("N�o h� registros neste programa.");
       return 0;
                        }

    while(fread(&cli,sizeof(STcliente),1,arquivo))
    {
         printf("Nome completo do cliente: %s\n", cli.nome);
         printf("Data de compra: %s\n", cli.datacompra);
         printf("Data prevista para pagamento: %s\n", cli.datapagamento);
         printf("Telefone fixo do cliente: %s\n", cli.tlfixo);
         printf("Celular do cliente: %s\n", cli.tlmovel);
         printf("Endere�o do cliente: %s\n", cli.endereco);
       
         fflush (stdin);
         printf("\n\n");
    }
    printf ("\nPressione enter para retornar ao menu principal");
    fclose(arquivo);
                                            }

int busca_nome(FILE *arquivo, STcliente cli)    {
    arquivo = fopen("teste.arq","rb");
    char procura[30], procurada[30];
    int i, teste = 0;

    if (cli.nome == NULL){ 
       printf("N�o h� registros neste programa.");
       return 0;
                        }
	printf("CONSULTA POR NOME \n");
	printf("Digite o nome: ");
	fflush(stdin);
	gets(procura);
	for (i=0;i<strlen(procura);i++){
		procura[i] = toupper (procura[i]); //passa para mai�scula
	                               }
	printf("%s\n\n", procura);
	
	
	while(fread(&cli,sizeof(STcliente),1,arquivo))
    {
		strcpy(procurada, cli.nome); //recebe o valor de nome para fazer a busca dos registro
    	for (i=0;i<strlen(procurada);i++){
			procurada[i] = toupper (procurada[i]); //passa tudo para mai�sculo
		                                  }
    
		 if(strstr(procurada,procura))//se a substring � encontrada, passa os respectivos registros do arquivo
         {
          printf("Nome completo do cliente desejado: %s\n", cli.nome);
         printf("O telefone fixo do cliente desejado: %s\n", cli.tlfixo);
         printf("O celular do cliente desejado: %s\n", cli.tlmovel);
         printf("\n\n");
         teste=1; //vari�vel de auxilio caso n�o ache
     	}

    }
    
	if (teste == 0) //se n�o achar exibe mensagem
    {
    	printf("O termo %s n�o foi encontrado!", procura);	
    }
    printf ("\nPressione enter para retornar ao menu principal");
    fclose(arquivo);
                                                }
    int apagardados () {   /*fun��o feita para a op��o adicional '5', onde o cliente pode
                           remover todos os cadastros sem precisar abrir o arquivo manualmente*/
        int condicao;
        printf ("ATEN��O! Esta op��o remove todos os clientes j� cadastrados!\n");
        printf ("Tem certeza que deseja apagar todos os registros da sua agenda?\n\n\nDigite 1 para apag�-los definitivamente ou 2 para mant�-los.\n");
        scanf ("%i", &condicao);
        fflush (stdin);
        switch (condicao) {
            case 1:
            remove("teste.arq");
            system ("cls");
            printf ("Agenda limpa com sucesso! Todos os registros foram removidos.\nPressione enter para voltar ao menu principal."); 
            break;
		    case 2:
            system ("cls");
            printf ("Ok! Os registros n�o foram removidos. \nPressione enter para retornar ao menu principal."); 
            break;
            default:
                printf ("\nOp��o inv�lida.");
            }
        }
                        
                                                    

int main ()    {
	char opcao[0];
	STcliente cli;
    FILE *arquivo;
    system ("color E2"); //Colora��o do programa; a tabela de cores pode ser consultada na internet
    setlocale (LC_ALL, "");
    printf ("Agenda Conceitual 2.0                          Edi��o Copa do Mundo Brasil 2014\n");
	const time_t timer = time(NULL);
    printf("\n\nHoje �: %s\n", ctime(&timer)); //Data fornecida pelo sistema operacional
	printf("\nSEJA BEM-VINDO!\n");
	printf("\n                     Cadastro de Clientes da Merceria Miranda\n");
	printf("\n\n\n");
	printf ("N�o use acentos na inser��o de dados neste programa.\n\n");
	do {
    	printf("\n(1)Cadastrar um novo cliente.\n");
		printf("\n(2)Consulta de telefone de clientes.\n");
		printf("\n(3)Mostrar todos os cadastros.\n");	
		printf("\n(4)Limpar todos os registros.\n");
		printf("\n(5)Sair.\n\n");
		printf("\nDigite sua op��o: ");
		scanf(" %s", &opcao);
		while (strlen(opcao)>1) {//problemas de sele��o de op��o 
		printf ("Por favor digite um n�mero!");
		break;
		                        }	
		printf("\n\n\n");
		system("cls");
		switch (opcao[0]){
		case '1':
			escreveArquivo(arquivo,cli);
		break;
		case '2':
			busca_nome(arquivo,cli);
		break;
		case '3':
			leArquivo(arquivo,cli);
		break;	
		case '4':
            apagardados ();
		break;
		case '5':
            printf("Obrigado por usar este programa!\n\n");
			getch ();
		return 0;
		default: //caso n�o seja digitada nenhuma das op��es pedidas pelo programa, retorna-se ao menu principal.
		    printf ("Op��o inv�lida.\nPressione enter para retornar ao menu principal. \n");
		break;
		              }
	printf("\n");
    getch (); //por quest�es de est�tica no programa, optou-se pelo getch (); ficando assim a mensagem a ser exibida a crit�rio do programador
    system("cls");	
	   } while(opcao[0]!='5');//condi��o de finaliza��o do programa
        }

