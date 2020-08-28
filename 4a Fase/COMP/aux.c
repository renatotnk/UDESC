#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "aux.h"

int ordem = 1;
int label = 0;
int variaveis=0;
/***********************************************************
*  MANIPULAÇÃO DE ARVORE BINÁRIA PARA A TABELA DE SÍMBOLOS *
***********************************************************/
void criaABB(ABB **arvore){
    *arvore = (ABB *) malloc(sizeof(ABB));
   	(*arvore)->raiz = NULL;
}

void destroiABB(ABB **arvore)
{
	reiniciaABB(*arvore);
    free(*arvore);
    (*arvore)= NULL;
}
void reiniciaABB(ABB *arvore)
{
   apagaNoABB(arvore->raiz);
   arvore->raiz = NULL;
}

void apagaNoABB(TabSim *p)
{ if(p!=NULL)
   {   apagaNoABB(p->esq);
       apagaNoABB(p->dir);
       free(p);
   }

}
TabSim* buscaTabela(char *chaveDeBusca)
{
	TabSim *aux;

   	aux = arvore->raiz;
   	while( aux != NULL && strcmp(chaveDeBusca,aux->id) != 0)
   	{

       aux = strcmp(chaveDeBusca,aux->id) < 0 ? aux->esq : aux->dir;
   	}
   	if (aux != NULL)
    {
        return aux;
    }

	return NULL;
}
int consultaTipo(char *chaveDeBusca)
{
	TabSim *aux;

   	aux = arvore->raiz;
   	while( aux != NULL && strcmp(chaveDeBusca,aux->id) != 0)
   	{

       aux = strcmp(chaveDeBusca,aux->id) < 0 ? aux->esq : aux->dir;
   	}
   	if (aux != NULL)
    {
        return aux->tipo;
    }

	return -1;
}


void inserirTabela(int tipo, LDSE *l)
{
	TabSim *p =arvore->raiz, *q =NULL ,*novoNoABB=NULL;

	while(l->lista != NULL){
		p=arvore->raiz;
	 	while(p!= NULL )
	    {
	      		q = p;
	      		if (strcmp(l->lista->idi,p->id) == 0){
	      		}
	            else if(strcmp(l->lista->idi,p->id)>0){
	     				p=p->dir;
	     		}else if(strcmp(l->lista->idi,p->id)<0){
	     				p=p->esq;
	     		}
	    }
	  	if ((novoNoABB = (TabSim*) malloc (sizeof(TabSim))) != NULL){
			strncpy(novoNoABB->id, l->lista->idi, MAX_ID);
			novoNoABB->tipo =tipo;
		    novoNoABB->dir = novoNoABB->esq = NULL;
		    novoNoABB->posicao=ordem;
		    ordem++;



		        if (q != NULL){
		            if(strcmp(novoNoABB->id,q->id)<0){
		                q->esq = novoNoABB;
		            }
					else{
	               		q->dir=novoNoABB;
					}
	            }else{
			        arvore->raiz = novoNoABB;
	           	}

	    }
	    l->lista = l->lista->prox;
 	}
}
void percorreEmPreOrdem(TabSim *p)
{  if(p != NULL)
    {
    	printf("%s\n",p->id);
    	percorreEmPreOrdem(p->esq);
    	percorreEmPreOrdem(p->dir);
    }
}

void preOrdem(ABB *pa)
{
	if(pa->raiz == NULL){
        printf("raiz nula\n");
	}
    else
    {
        percorreEmPreOrdem(pa->raiz);
        //return SUCESSO;
    }
}

int contaVariaveis(ABB *p){

	if(p->raiz == NULL){
		return variaveis;
	}else{
		contaVariaveis2(p->raiz);
	}
	return variaveis;
}

void contaVariaveis2(TabSim *p){

	if(p != NULL){
		variaveis++;
		contaVariaveis2(p->esq);
		contaVariaveis2(p->dir);
	}
}

/***************************************
* MANIPULAÇÃO DE LISTA PARA ATRIBUTOS  *
***************************************/

void criaLista(LDSE **p)
{

	LDSE *desc = (LDSE*)malloc(sizeof(LDSE));
    desc->lista = NULL;
    (*p) = desc;
}

void reinicia(LDSE *p)
{
    No *aux = NULL;

    if(p->lista != NULL) {
        aux = p->lista->prox;
        while(aux != NULL) {
            free(p->lista);
            p->lista = aux;
            aux = aux->prox;
        }
        free(p->lista);
        p->lista = NULL;
    }
}
void destroi(LDSE **p)
{
	reinicia(*p);
    free(*p);
    (*p) = NULL;
}
void insereNaLista(LDSE *p, char *id)
{
    No *temp = NULL, *aux = NULL;

    if((temp = (No*) malloc(sizeof(No))) != NULL ) {
        strncpy(temp->idi, id, MAX_ID);
        temp->prox = NULL;
        if( p->lista == NULL ) {
            p->lista=temp;
        }
        else{
            aux = p->lista;
            while( aux->prox != NULL ) {
                aux = aux->prox;
            }
            aux->prox=temp;
        }
    }
}

/************************************************
*    MANIPULAÇÃO DE ÁRVORE BINÁRIA ARITMÉTICA   *
************************************************/

void destroiAB_Aritmetica(AST *arvore)
{
   apagaNoAB_Aritmetica(arvore);
   arvore = NULL;
}

void apagaNoAB_Aritmetica(AST *p)
{ if(p!=NULL)
   {   apagaNoAB_Aritmetica(p->ptr1);
       apagaNoAB_Aritmetica(p->ptr2);
       free(p);
   }

}
AST *i2f(AST *at){
	AST *node=malloc(sizeof(AST));
	if (node == NULL)
	{
		exit(EXIT_FAILURE);
	}
	node->cod  = I2F;
	node->ptr1  = at;

	return node;
}

AST *criaNo(int operacao, AST *at1, AST *at2){
	AST *novo = NULL;

	novo = (AST*)malloc(sizeof(AST));

	if(novo == NULL){
		printf("Erro ao alocar memória\n");
	}
	novo->cod = operacao;
	novo->ptr1 = at1;
	novo->ptr2 = at2;
	return novo;

}
AST *criaNoIF(int operacao, AST *at1, AST *at2,AST *at3){
	AST *novo = NULL;

	novo = (AST*)malloc(sizeof(AST));


	if(novo == NULL){
		printf("Erro ao alocar memória\n");
	}
	novo->cod = operacao;
	novo->ptr1 = at1;
	novo->ptr2 = at2;
	novo->ptr3=at3;
	return novo;

}
AST *criaFolhaS(char *at1){

	AST *novo = NULL;

	novo = (AST*)malloc(sizeof(AST));

	if(novo == NULL){
		printf("Erro ao alocar memória\n");
	}

	novo->cod = T_STRING;
	novo->constInt = -1;
	novo->constFloat = -1;
	novo->ptr1 = NULL;
	novo->ptr2 = NULL;
	strncpy(novo->buffer, at1, T_MAX);

	return novo;
}


AST *criaFolha(Atributo *at1, int tipo){
	AST *novo = NULL;

	novo = (AST*)malloc(sizeof(AST));

	if(novo == NULL){
		printf("Erro ao alocar memória\n");
	}

	if(tipo == T_INT){
		novo->cod = T_INT;
		novo->constInt = at1->valorInt;
		novo->constFloat = -1;
		novo->ptr1 = NULL;
		novo->ptr2 = NULL;
		//novo->tab = NULL;
	}else if(tipo == T_FLOAT){
		novo->cod = T_FLOAT;
		novo->constFloat = at1->valorFloat;
		novo->constInt = -1;
		novo->ptr1 = NULL;
		novo->ptr2 = NULL;
		//novo->tab = NULL;
	}else if(tipo == ID){
		novo->cod = ID;
		novo->tab = buscaTabela(at1->id);
		novo->constInt = -1;
		novo->constFloat = -1;
		novo->ptr1 = NULL;
		novo->ptr2 = NULL;
	}

	return novo;
}

void percorreEmPosOrdem(AST *p)
{
  int lv, lf, laux;
	if(p != NULL)
    {
    	switch(p->cod){

    		case T_INT:

		    	percorreEmPosOrdem(p->ptr1);
		        percorreEmPosOrdem(p->ptr2);

		        if(p->constInt>=-1 && p->constInt <=5){
		        	fprintf(bytearq, "\ticonst_%d\n", p->constInt);
		        }else{
		        	if (p->constInt>-128 && p->constInt<127)
		        	{
		        		fprintf(bytearq, "\tbipush %d\n", p->constInt);
		        	}
		        	else{
		        		fprintf(bytearq, "\tldc %d\n",p->constInt);
		        	}

		        }

		        break;

    		case T_FLOAT:
	    		percorreEmPosOrdem(p->ptr1);
	        	percorreEmPosOrdem(p->ptr2);
	        	fprintf(bytearq, "\tldc %f\n", p->constFloat);
	        	break;

	    	case DIV:
	    		percorreEmPosOrdem(p->ptr1);
	        	percorreEmPosOrdem(p->ptr2);
	        	if (p->ptr1->cod==T_INT || p->ptr2->cod==T_INT)
	        	{
	        		fprintf(bytearq, "\tidiv \n");
	        	}
	        	else if (p->ptr1->cod==T_FLOAT || p->ptr2->cod==T_FLOAT)
	        	{
	        		fprintf(bytearq, "\tfdiv \n");
	        	}
	        	else if (p->ptr1->cod==I2F || p->ptr2->cod==I2F)
	        	{
	        		fprintf(bytearq, "\tfdiv \n");
	        	}else if(p->ptr1->cod==ID || p->ptr2->cod==ID){
	        		if (p->ptr1->tab->tipo==T_INT && p->ptr2->tab->tipo==T_INT)
	        		{
	        			fprintf(bytearq, "\tidiv \n");
	        		}else if (p->ptr1->tab->tipo==T_INT && p->ptr2->cod==T_INT)
	        		{
	        			fprintf(bytearq, "\tidiv\n");
	        		}else if (p->ptr1->cod==T_INT && p->ptr2->tab->tipo==T_INT)
	        		{
	        			fprintf(bytearq, "\tidiv\n");
	        		}
	        		else{
	        			fprintf(bytearq, "\tfdiv\n");
	        		}
	        	}
	        	break;

	    	case MULT:

	    		percorreEmPosOrdem(p->ptr1);
	        	percorreEmPosOrdem(p->ptr2);
	        	if (p->ptr1->cod==T_INT || p->ptr2->cod==T_INT)
	        	{
	        		fprintf(bytearq,"\timul \n");
	        	}
	        	else if (p->ptr1->cod==T_FLOAT || p->ptr2->cod==T_FLOAT)
	        	{
	        		fprintf(bytearq, "\tfmul \n");
	        	}
	        	else if (p->ptr1->cod==I2F || p->ptr2->cod==I2F)
	        	{
	        		fprintf(bytearq, "\tfmul \n");
	        	}else if(p->ptr1->cod==ID || p->ptr2->cod==ID){
	        		if (p->ptr1->tab->tipo==T_INT && p->ptr2->tab->tipo==T_INT)
	        		{
	        			fprintf(bytearq, "\timul \n");
	        		}else if (p->ptr1->tab->tipo==T_INT && p->ptr2->cod==T_INT)
	        		{
	        			fprintf(bytearq,"\timul\n");
	        		}else if (p->ptr1->cod==T_INT && p->ptr2->tab->tipo==T_INT)
	        		{
	        			fprintf(bytearq, "\timul\n");
	        		}
	        		else{
	        			fprintf(bytearq, "\tfmul\n");
	        		}

	        	}
	        	break;

	    	case SUB:
	    		percorreEmPosOrdem(p->ptr1);
	        	percorreEmPosOrdem(p->ptr2);
	        	if (p->ptr1->cod==T_INT || p->ptr2->cod==T_INT)
	        	{
	        		fprintf(bytearq, "\tisub \n");
	        	}
	        	else if (p->ptr1->cod==T_FLOAT || p->ptr2->cod==T_FLOAT)
	        	{
	        		fprintf(bytearq, "\tfsub \n");
	        	}
	        	else if (p->ptr1->cod==I2F || p->ptr2->cod==I2F)
	        	{
	        		fprintf(bytearq, "\tfsub \n");
	        	}else if(p->ptr1->cod==ID || p->ptr2->cod==ID){
	        		if (p->ptr1->tab->tipo==T_INT && p->ptr2->tab->tipo==T_INT)
	        		{
	        			fprintf(bytearq, "\tisub \n");
	        		}else if (p->ptr1->tab->tipo==T_INT && p->ptr2->cod==T_INT)
	        		{
	        			fprintf(bytearq, "\tisub\n");
	        		}else if (p->ptr1->cod==T_INT && p->ptr2->tab->tipo==T_INT)
	        		{
	        			fprintf(bytearq, "\tisub\n");
	        		}
	        		else{
	        			fprintf(bytearq, "\tfsub\n");
	        		}

	        	}
	        	break;
	        case NEG:
	        	percorreEmPosOrdem(p->ptr1);
	        	if(p->ptr1->cod==T_INT){
	        		fprintf(bytearq, "\tineg\n");
	        	}if(p->ptr1->cod==T_FLOAT){
	        		fprintf(bytearq, "\tfneg\n");
	        	}if(p->ptr1->cod==ID){
	        		if(p->ptr1->tab->tipo==T_INT){
	        			fprintf(bytearq, "\tineg\n");
	        		}if(p->ptr1->tab->tipo==T_FLOAT){
	        			fprintf(bytearq, "\tfneg\n");
	        		}
	        	}

	        	break;

	    	case ADD:
	    		percorreEmPosOrdem(p->ptr1);
	        	percorreEmPosOrdem(p->ptr2);
	        	if (p->ptr1->cod==T_INT || p->ptr2->cod==T_INT)
	        	{
	        		fprintf(bytearq, "\tiadd \n");
	        	}
	        	else if (p->ptr1->cod==T_FLOAT || p->ptr2->cod==T_FLOAT)
	        	{
	        		fprintf(bytearq, "\tfadd \n");
	        	}
	        	else if (p->ptr1->cod==I2F || p->ptr2->cod==I2F)
	        	{
	        		fprintf(bytearq, "\tfadd \n");
	        	}else if(p->ptr1->cod==ID || p->ptr2->cod==ID){
	        		if (p->ptr1->tab->tipo==T_INT && p->ptr2->tab->tipo==T_INT)
	        		{
	        			fprintf(bytearq, "\tiadd \n");
	        		}else if (p->ptr1->tab->tipo==T_INT && p->ptr2->cod==T_INT)
	        		{
	        			fprintf(bytearq, "\tiadd\n");
	        		}else if (p->ptr1->cod==T_INT && p->ptr2->tab->tipo==T_INT)
	        		{
	        			fprintf(bytearq, "\tiadd\n");
	        		}
	        		else{
	        			fprintf(bytearq, "\tfadd\n");
	        		}

	        	}
	        	break;

	    	case ID:
	    		percorreEmPosOrdem(p->ptr1);
	        	percorreEmPosOrdem(p->ptr2);
	        	if(p->tab->tipo==T_INT){
	        		fprintf(bytearq, "\tiload %d \n",p->tab->posicao);
	        	}if (p->tab->tipo==T_FLOAT)
	        	{
	        		fprintf(bytearq, "\tfload %d \n",p->tab->posicao);
	        	}
	        	break;

	        case IGUAL:
	        	percorreEmPosOrdem(p->ptr2);
	        	if (p->ptr1->cod==T_INT)
	        	{
	        		fprintf(bytearq, "\tistore %d\n", p->ptr1->tab->posicao);
	        	}
	        	else if (p->ptr1->cod==T_FLOAT)
	        	{
	        		fprintf(bytearq, "\tfstore %d\n", p->ptr1->tab->posicao);
	        	}
	        	else if (p->ptr1->cod==I2F)
	        	{
	        		fprintf(bytearq, "\tfstore %d\n", p->ptr1->tab->posicao);
	        	}else if(p->ptr1->cod==ID){
	        		if (p->ptr1->tab->tipo==T_INT)
	        		{
	        			fprintf(bytearq, "\tistore %d\n", p->ptr1->tab->posicao);
	        		}else if (p->ptr1->tab->tipo==T_INT)
	        		{
	        			fprintf(bytearq, "\tistore %d\n", p->ptr1->tab->posicao);
	        		}else if (p->ptr1->cod==T_INT)
	        		{
	        			fprintf(bytearq, "\tistore %d\n", p->ptr1->tab->posicao);
	        		}
	        		else{
	        			fprintf(bytearq, "\tfstore %d\n", p->ptr1->tab->posicao);
	        		}
	        	}
	        	break;

	        case I2F:	        
	        	percorreEmPosOrdem(p->ptr1);
	        	fprintf(bytearq, "\ti2f \n");
	        	break;

	        case LIST:
	        	percorreEmPosOrdem(p->ptr1);
	        	percorreEmPosOrdem(p->ptr2);
	        	break;

	        case IF:
	        	lv = geraLabel();
	        	lf = geraLabel();
	        	imprimeLogicaRelacional(p->ptr1, lv, lf);
	        	fprintf(bytearq, "l%d:\n", lv);
	        	//imprimeLogicaRelacional(p->ptr2, lv, lf);
	        	percorreEmPosOrdem(p->ptr2);

	        	fprintf(bytearq, "l%d:\n", lf);
            	break;

            case IF_ELSE:
              lv = geraLabel();
              lf = geraLabel();
              imprimeLogicaRelacional(p->ptr1, lv, lf);
              fprintf(bytearq, "l%d:\n", lv);
              percorreEmPosOrdem(p->ptr2);
              laux = geraLabel();
              fprintf(bytearq, "\tgoto l%d\n", laux);
              fprintf(bytearq, "l%d:\n", lf);
              percorreEmPosOrdem(p->ptr3);
              fprintf(bytearq, "l%d:\n", laux);
              break;

            case WHILE:
              laux = geraLabel();
              lv = geraLabel();
              lf = geraLabel();
              fprintf(bytearq, "l%d:\n",laux);
              imprimeLogicaRelacional(p->ptr1,lv,lf);
              fprintf(bytearq, "l%d:\n",lv);
              percorreEmPosOrdem(p->ptr2);
              fprintf(bytearq, "\tgoto l%d\n",laux);
              fprintf(bytearq, "l%d:\n",lf);
              break;

            case PRINT:
            	fprintf(bytearq, "\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n");
				percorreEmPosOrdem(p->ptr1);
				fprintf(bytearq, "\tinvokevirtual java/io/PrintStream/println(");

				if(p->ptr1->cod == ADD || p->ptr1->cod == SUB || p->ptr1->cod == DIV || p->ptr1->cod == MULT){
					if(p->ptr1->ptr1->cod == T_INT){
						fprintf(bytearq, "I");
					}else if(p->ptr1->ptr1->cod == T_FLOAT){
						fprintf(bytearq, "F");
					}else if(p->ptr1->ptr1->cod == ID){
						if(p->ptr1->ptr1->tab->tipo == T_INT){
							fprintf(bytearq, "I");
						}else if(p->ptr1->ptr1->tab->tipo == T_FLOAT){
							fprintf(bytearq, "F");
						}
					}else if(p->ptr1->ptr1->cod == I2F){
						fprintf(bytearq, "F");
					}
				}

				if(p->ptr1->cod == ID){
					switch (p->ptr1->tab->tipo)
					{ 
					case T_INT: 
						fprintf(bytearq, "I"); 
						break;
					case T_FLOAT: 
						fprintf(bytearq, "F"); 
						break;
					case T_STRING:
						fprintf(bytearq, "Ljava/lang/String;"); 
						break;
					}
				}
				if(p->ptr1->cod == T_STRING){
					fprintf(bytearq, "Ljava/lang/String;");
				}

				fprintf(bytearq, ")V\n");
				break;

			case T_STRING:
				fprintf(bytearq, "\t");
				fprintf(bytearq, "\tldc %s", p->buffer);
				fprintf(bytearq, "\n");
			    break;

    	}
    }
}

int geraLabel(){
		label++;
	  return label;
}

void imprimeLogicaRelacional(AST *p, int lv, int lf){
 int laux;
	if(p!=NULL){

		switch(p->cod){
			case E:
       			laux=geraLabel();
				imprimeLogicaRelacional(p->ptr1, laux, lf);
				fprintf(bytearq, "l%d:\n", laux);
	    		imprimeLogicaRelacional(p->ptr2, lv, lf);
				break;

			case OU:
        		laux=geraLabel();
				imprimeLogicaRelacional(p->ptr1, lv, laux);
        		fprintf(bytearq, "l%d:\n", laux);
	      		imprimeLogicaRelacional(p->ptr2, lv, lf);
			  	break;

			case MAIOR:
				percorreEmPosOrdem(p->ptr1);
	        	percorreEmPosOrdem(p->ptr2);
				fprintf(bytearq, "\tif_icmpgt l%d \n", lv);
				fprintf(bytearq, "\tgoto l%d\n", lf);
				break;

			case MENOR:
				percorreEmPosOrdem(p->ptr1);
	        	percorreEmPosOrdem(p->ptr2);
				fprintf(bytearq, "\tif_icmplt l%d\n", lv);
				fprintf(bytearq, "\tgoto l%d\n", lf);
				break;

			case MENORIG:
				percorreEmPosOrdem(p->ptr1);
	      		percorreEmPosOrdem(p->ptr2);
				fprintf(bytearq, "\tif_icmple l%d\n", lv);
				fprintf(bytearq, "\tgoto l%d\n", lf);
				break;

			case MAIORIG:
				percorreEmPosOrdem(p->ptr1);
	     	 	percorreEmPosOrdem(p->ptr2);
				fprintf(bytearq, "\tif_icmpge l%d\n", lv);
				fprintf(bytearq, "\tgoto l%d\n", lf);
				break;

			case COMPIG:
				percorreEmPosOrdem(p->ptr1);
	      		percorreEmPosOrdem(p->ptr2);
				fprintf(bytearq, "\tif_icmpeq l%d\n", lv);
				fprintf(bytearq, "\tgoto l%d\n", lf);
				break;

			case COMPDIF:
				percorreEmPosOrdem(p->ptr1);
	      		percorreEmPosOrdem(p->ptr2);
				fprintf(bytearq, "\tif_icmpne l%d\n", lv);
				fprintf(bytearq, "\tgoto l%d\n", lf);
				break;

			case IGUAL:
				//printf("L%d:\n", lv);
				//percorreEmPosOrdem(p->ptr1); não precisa imprimir iload a para atribuir
				percorreEmPosOrdem(p->ptr2);
				if (p->ptr1->cod==T_INT){
	        		fprintf(bytearq, "\tistore %d\n", p->ptr1->tab->posicao);
	        	}
	        	else if (p->ptr1->cod==T_FLOAT)
	        	{
	        		fprintf(bytearq, "\tfstore %d\n", p->ptr1->tab->posicao);
	        	}
	        	else if (p->ptr1->cod==I2F)
	        	{
	        		fprintf(bytearq, "\tfstore %d\n", p->ptr1->tab->posicao);
	        	}else if(p->ptr1->cod==ID){
	        		if (p->ptr1->tab->tipo==T_INT)
	        		{
	        			fprintf(bytearq, "\tistore %d\n", p->ptr1->tab->posicao);
	        		}else if (p->ptr1->tab->tipo==T_INT)
	        		{
	        			fprintf(bytearq, "\tistore %d\n", p->ptr1->tab->posicao);
	        		}else if (p->ptr1->cod==T_INT)
	        		{
	        			fprintf(bytearq, "\tistore %d\n", p->ptr1->tab->posicao);
	        		}
	        		else{
	        			fprintf(bytearq, "\tfstore %d\n", p->ptr1->tab->posicao);
	        		}
	        	}
				break;

				case NOT:
					imprimeLogicaRelacional(p->ptr1, lf, lv);
					break;

		}
	}
}

void printCabecalho(){
	int local=contaVariaveis(arvore);
	local++;
	fprintf(bytearq, "\n.method public <init>()V\n" "\taload_0\n" "\tinvokenonvirtual java/lang/Object/<init>()V\n" 
		"\treturn\n" ".end method\n" "\n.method public static main([Ljava/lang/String;)V\n" "\t.limit stack 10\n" "\t.limit locals %d\n\n",local);
}

void printFim(){
	fprintf(bytearq, "\n\treturn\n.end method\n" );
}
