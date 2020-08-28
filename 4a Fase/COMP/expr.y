%{
#include <stdio.h>
#include <stdlib.h>
#include "aux.h"
#define YYSTYPE Atributo
int linha = 1;
%}

%token TADD TMUL TSUB TDIV TAPAR TFPAR TMAIORQ TMENORQ TMENORIGUALQ TMAIORIGUALQ TIGUALCOMP TNEGACAO TDIFCOMP TIF TELSE TWHILE TPRINT TREAD TRETURN TELOGICO TOULOGICO TINT TFLOAT TSTRING TVOID TACHAVE TFCHAVE TID TATRIBUICAO TLIT TPVIRGULA TVIRGULA

%%
Programa: ListaFuncoes BlocoPrincipal
        |BlocoPrincipal {$$.ptr = $1.ptr;
                        printCabecalho();
                        percorreEmPosOrdem($$.ptr);
                        printFim();}
	;
ListaFuncoes: ListaFuncoes Funcao
	| Funcao
	;
Funcao:    DeclFuncao BlocoPrincipal
	;
DeclFuncao: TipoRetorno TID TAPAR DeclParametros TFPAR
	| TipoRetorno TID TAPAR TFPAR 
	;
TipoRetorno: Tipo
	| TVOID
	;
DeclParametros: DeclParametros TVIRGULA Parametro
        | Parametro
        ;
Parametro: Tipo TID
        ;
BlocoPrincipal: TACHAVE Declaracoes ListaCmd TFCHAVE {$$.ptr = $3.ptr;}
        |TACHAVE ListaCmd TFCHAVE {$$.ptr = $2.ptr;}
        ;
Declaracoes: Declaracoes Declaracao
        | Declaracao
        ;
Declaracao: Tipo ListaId TPVIRGULA {inserirTabela($1.tipo, $2.listaId);destroi(&($2.listaId));}
        ;
Tipo:   TINT {$$.tipo=T_INT;}
        |TSTRING {$$.tipo=T_STRING;}
        |TFLOAT {$$.tipo=T_FLOAT;}
        ;
ListaId: ListaId TVIRGULA TID {insereNaLista($1.listaId,$3.id);}
        |TID {criaLista(&($$.listaId));insereNaLista($$.listaId,$1.id);}
        ;
Bloco: TACHAVE ListaCmd TFCHAVE{$$.ptr=$2.ptr;}
        ;
ListaCmd: ListaCmd Comando{$$.ptr=criaNo(LIST,$1.ptr,$2.ptr);}
        |Comando{$$.ptr=criaNo(LIST,$1.ptr,NULL);}
        ;
Comando: CmdSe{$$.ptr=$1.ptr;}
        |CmdEnquanto{$$.ptr=$1.ptr;}
        |CmdAtrib{$$.ptr=$1.ptr;}
        |CmdEscrita{$$.ptr=$1.ptr;}
        |CmdLeitura
        |ChamadaProc
        |Retorno
        ;
Retorno: TRETURN ExpressaoAritmetica1 TPVIRGULA
        |TRETURN TLIT TPVIRGULA
        ;
CmdSe: TIF TAPAR ExpressaoLogica1 TFPAR Bloco {$$.ptr=criaNo(IF,$3.ptr,$5.ptr);}
        |TIF TAPAR ExpressaoLogica1 TFPAR Bloco TELSE Bloco {$$.ptr=criaNoIF(IF_ELSE,$3.ptr,$5.ptr,$7.ptr);}
        ;
CmdEnquanto: TWHILE TAPAR ExpressaoLogica1 TFPAR Bloco {$$.ptr = criaNo(WHILE, $3.ptr, $5.ptr);}
        ;
CmdAtrib: TID TATRIBUICAO ExpressaoAritmetica1 TPVIRGULA {$1.ptr=criaFolha(&($1),ID);
                                                        $1.tipo = consultaTipo($1.id);
                                                        if ($1.tipo == T_INT && $3.tipo == T_FLOAT) {
                                                                printf("ESSE TIPO DE OPERAÇÃO NÃO É PERMITIDA\n");
                                                                exit(EXIT_FAILURE);
                                                        }else if($1.tipo==T_FLOAT && $3.tipo ==T_INT){
                                                                $$.ptr = criaNo(IGUAL, $1.ptr, i2f($3.ptr));
                                                        }else{
                                                                $$.ptr = criaNo(IGUAL, $1.ptr, $3.ptr);
                                                                $$.tipo = $1.tipo;
                                                        }
                                                        }
        |TID TATRIBUICAO TLIT TPVIRGULA
        ;
CmdEscrita: TPRINT TAPAR ExpressaoAritmetica1 TFPAR TPVIRGULA {$$.ptr=criaNo(PRINT, $3.ptr,NULL);}
        |TPRINT TAPAR TLIT TFPAR TPVIRGULA {$3.ptr=criaFolhaS($3.buffer); $$.ptr = criaNo(PRINT, $3.ptr, NULL);}
        ;
CmdLeitura: TREAD TAPAR TID TFPAR TPVIRGULA
        ;
ChamadaProc: ChamadaFuncao TPVIRGULA
        ;
ChamadaFuncao: TID TAPAR ListaParametros TFPAR //{$$.tipo = verificar($1.id, $3.lista)}
        | TID TAPAR TFPAR
        ;
ListaParametros: ListaParametros TVIRGULA ExpressaoAritmetica1 //{$$.Lista = insLista($1.lista, $3.tipo);}
        |ListaParametros TVIRGULA TLIT //{$$.Lista = insLista($1.Lista, String);}
        |ExpressaoAritmetica1 //{$$.lista = criarLista($1.tipo);
				//$$.ptr = $1.ptr;}
        |TLIT//{$$.lista = criarLista(String);}
        ;
ExpressaoLogica1: ExpressaoLogica1 TELOGICO ExpressaoRelacional{$$.ptr=criaNo(E,$1.ptr,$3.ptr);}
		|ExpressaoLogica1 TOULOGICO ExpressaoRelacional {$$.ptr=criaNo(OU,$1.ptr,$3.ptr);}
		|ExpressaoLogica2 {$$.ptr=$1.ptr;}
		;
ExpressaoLogica2: TNEGACAO ExpressaoLogica2 {$$.ptr=criaNo(NOT,$2.ptr,NULL);}
		|TAPAR ExpressaoLogica1 TFPAR {$$.ptr=$2.ptr;}
		|ExpressaoRelacional {$$.ptr=$1.ptr;}
		;
ExpressaoRelacional: ExpressaoAritmetica1 TMAIORQ ExpressaoAritmetica1 {if($1.tipo==T_INT && $3.tipo==T_FLOAT){
                                                               $$.ptr = criaNo(MAIOR, i2f($1.ptr), $3.ptr);
                                                               $$.tipo=T_FLOAT;
                                                               }else if($1.tipo==T_FLOAT && $3.tipo==T_INT){
                                                                       $$.ptr = criaNo(MAIOR,$1.ptr, i2f($3.ptr));
                                                                       $$.tipo=T_FLOAT;
                                                                }else if($1.tipo == T_STRING || $3.tipo == T_STRING){
                                                                	printf("ESSE TIPO DE OPERAÇÃO NÃO É PERMITIDA\n");
                                                                	exit(EXIT_FAILURE);
                                                                }else{
                                                                $$.ptr = criaNo(MAIOR, $1.ptr, $3.ptr);
                                                                $$.tipo=$1.tipo;
                                                                }
}
		|ExpressaoAritmetica1 TMENORQ ExpressaoAritmetica1 {if($1.tipo==T_INT && $3.tipo==T_FLOAT){
                                                        $$.ptr = criaNo(MENOR, i2f($1.ptr), $3.ptr);
                                                        $$.tipo=T_FLOAT;
                                                        }else if($1.tipo==T_FLOAT && $3.tipo==T_INT){
                                                              $$.ptr = criaNo(MAIOR,$1.ptr, i2f($3.ptr));
                                                              $$.tipo=T_FLOAT;
                                                        }else if($1.tipo == T_STRING || $3.tipo == T_STRING){
                                                        	  printf("ESSE TIPO DE OPERAÇÃO NÃO É PERMITIDA\n");
                                                        	  exit(EXIT_FAILURE);
                                                        }else{
                                                              $$.ptr = criaNo(MENOR, $1.ptr, $3.ptr);
                                                              $$.tipo=$1.tipo;
                                                              }
}
		|ExpressaoAritmetica1 TMAIORIGUALQ ExpressaoAritmetica1{if($1.tipo==T_INT && $3.tipo==T_FLOAT){
                                                               $$.ptr = criaNo(MAIORIG, i2f($1.ptr), $3.ptr);
                                                               $$.tipo=T_FLOAT;
                                                               }else if($1.tipo==T_FLOAT && $3.tipo==T_INT){
                                                                       $$.ptr = criaNo(MAIORIG,$1.ptr, i2f($3.ptr));
                                                                       $$.tipo=T_FLOAT;
                                                               }else if($1.tipo == T_STRING || $3.tipo == T_STRING){
                                                        	  			printf("ESSE TIPO DE OPERAÇÃO NÃO É PERMITIDA\n");
                                                        	  			exit(EXIT_FAILURE);
                                                        	   }else{
                                                                	$$.ptr = criaNo(MAIORIG, $1.ptr, $3.ptr);
                                                                	$$.tipo=$1.tipo;
                                                                }
		}
		|ExpressaoAritmetica1 TMENORIGUALQ ExpressaoAritmetica1{if($1.tipo==T_INT && $3.tipo==T_FLOAT){
                                                                $$.ptr = criaNo(MENORIG, i2f($1.ptr), $3.ptr);
                                                                $$.tipo=T_FLOAT;
                                                                }else if($1.tipo==T_FLOAT && $3.tipo==T_INT){
                                                                    $$.ptr = criaNo(MENORIG,$1.ptr, i2f($3.ptr));
                                                                    $$.tipo=T_FLOAT;
                                                                }else if($1.tipo == T_STRING || $3.tipo == T_STRING){
                                                                	printf("ESSE TIPO DE OPERAÇÃO NÃO É PERMITIDA\n");
                                                        	  		exit(EXIT_FAILURE);
                                                        	    }else{
                                                                	$$.ptr = criaNo(MENORIG, $1.ptr, $3.ptr);
                                                                	$$.tipo=$1.tipo;
                                                                }
		}
		|ExpressaoAritmetica1 TIGUALCOMP ExpressaoAritmetica1{if($1.tipo==T_INT && $3.tipo==T_FLOAT){
                                                               	$$.ptr = criaNo(COMPIG, i2f($1.ptr), $3.ptr);
                                                               	$$.tipo=T_FLOAT;
                                                               	}else if($1.tipo==T_FLOAT && $3.tipo==T_INT){
                                                                    $$.ptr = criaNo(COMPIG,$1.ptr, i2f($3.ptr));
                                                                    $$.tipo=T_FLOAT;
                                                               	}else if($1.tipo == T_STRING || $3.tipo == T_STRING){
                                                        	  		printf("ESSE TIPO DE OPERAÇÃO NÃO É PERMITIDA\n");
                                                        	  		exit(EXIT_FAILURE);
                                                        		}else{
                                                                	$$.ptr = criaNo(COMPIG, $1.ptr, $3.ptr);
                                                                	$$.tipo=$1.tipo;
                                                                }
		}
		|ExpressaoAritmetica1 TDIFCOMP ExpressaoAritmetica1{if($1.tipo==T_INT && $3.tipo==T_FLOAT){
                                                               	$$.ptr = criaNo(COMPDIF, i2f($1.ptr), $3.ptr);
                                                               	$$.tipo=T_FLOAT;
                                                               	}else if($1.tipo==T_FLOAT && $3.tipo==T_INT){
                                                                       $$.ptr = criaNo(COMPDIF,$1.ptr, i2f($3.ptr));
                                                                       $$.tipo=T_FLOAT;
                                                                }else if($1.tipo == T_STRING || $3.tipo == T_STRING){
                                                        	  		printf("ESSE TIPO DE OPERAÇÃO NÃO É PERMITIDA\n");
                                                        	  		exit(EXIT_FAILURE);
                                                        		}else{
                                                                	$$.ptr = criaNo(COMPDIF, $1.ptr, $3.ptr);
                                                                	$$.tipo=$1.tipo;
                                                                }
		}
		;
ExpressaoAritmetica1: ExpressaoAritmetica1 TADD ExpressaoAritmetica2 {if($1.tipo==T_INT && $3.tipo==T_FLOAT){
                                                               $$.ptr = criaNo(ADD, i2f($1.ptr), $3.ptr);
                                                               $$.tipo=T_FLOAT;
                                                        }else if($1.tipo==T_FLOAT && $3.tipo==T_INT){
                                                                $$.ptr = criaNo(ADD,$1.ptr, i2f($3.ptr));
                                                                $$.tipo=T_FLOAT;
                                                        }else if($1.tipo == T_STRING || $3.tipo == T_STRING){
                                                        	  	printf("ESSE TIPO DE OPERAÇÃO NÃO É PERMITIDA\n");
                                                        	  	exit(EXIT_FAILURE);
                                                        }else{
                                                                $$.ptr = criaNo(ADD, $1.ptr, $3.ptr);
                                                                $$.tipo=$1.tipo;
                                                        }
}
		|ExpressaoAritmetica1 TSUB ExpressaoAritmetica2 {if($1.tipo==T_INT && $3.tipo==T_FLOAT){
                                                               $$.ptr = criaNo(TSUB, i2f($1.ptr), $3.ptr);
                                                               $$.tipo=T_FLOAT;
                                                        }else if($1.tipo==T_FLOAT && $3.tipo==T_INT){
                                                                $$.ptr = criaNo(TSUB,$1.ptr, i2f($3.ptr));
                                                                $$.tipo=T_FLOAT;
                                                        }else if($1.tipo == T_STRING || $3.tipo == T_STRING){
                                                        	  	printf("ESSE TIPO DE OPERAÇÃO NÃO É PERMITIDA\n");
                                                        	  	exit(EXIT_FAILURE);
                                                        }else{
                                                                $$.ptr = criaNo(TSUB, $1.ptr, $3.ptr);
                                                                $$.tipo=$1.tipo;
                                                        }
}
		|ExpressaoAritmetica2 {$$.ptr = $1.ptr; $$.tipo=$1.tipo;}
		;
ExpressaoAritmetica2: ExpressaoAritmetica2 TMUL Numero {
                                                        if($1.tipo==T_INT && $3.tipo==T_FLOAT){
                                                               $$.ptr = criaNo(MULT, i2f($1.ptr), $3.ptr);
                                                               $$.tipo=T_FLOAT;
                                                        }else if($1.tipo==T_FLOAT && $3.tipo==T_INT){
                                                                $$.ptr = criaNo(MULT,$1.ptr, i2f($3.ptr));
                                                                $$.tipo=T_FLOAT;
                                                        }else if($1.tipo == T_STRING || $3.tipo == T_STRING){
                                                        		printf("ESSE TIPO DE OPERAÇÃO NÃO É PERMITIDA\n");
                                                        	  	exit(EXIT_FAILURE);
                                                       	}else{
                                                                $$.ptr = criaNo(MULT, $1.ptr, $3.ptr);
                                                                $$.tipo=$1.tipo;
                                                        }
}
		|ExpressaoAritmetica2 TDIV Numero {if($1.tipo==T_INT && $3.tipo==T_FLOAT){
                                                               $$.ptr = criaNo(DIV, i2f($1.ptr), $3.ptr);
                                                               $$.tipo=T_FLOAT;
                                                        }else if($1.tipo==T_FLOAT && $3.tipo==T_INT){
                                                                $$.ptr = criaNo(DIV,$1.ptr, i2f($3.ptr));
                                                                $$.tipo=T_FLOAT;
                                                        }else if($1.tipo == T_STRING || $3.tipo == T_STRING){
                                                        		printf("ESSE TIPO DE OPERAÇÃO NÃO É PERMITIDA\n");
                                                        	  	exit(EXIT_FAILURE);
                                                        }else{
                                                                $$.ptr = criaNo(DIV, $1.ptr, $3.ptr);
                                                                $$.tipo=$1.tipo;
                                                        }
}
		|Numero {$$.ptr = $1.ptr;$$.tipo = $1.tipo;}
		;
Numero: TSUB Numero { $$.ptr = criaNo(NEG, $2.ptr, NULL);$$.tipo = $2.tipo;}
        |TINT {$$.ptr = criaFolha(&($1), T_INT); $$.tipo=T_INT;}
        |TFLOAT {$$.ptr = criaFolha(&($1), T_FLOAT); $$.tipo=T_FLOAT;}
		|TAPAR ExpressaoAritmetica1 TFPAR { $$.ptr = $2.ptr;$$.tipo = $2.tipo;}
		|TID {$$.ptr = criaFolha(&($1), ID);$$.tipo = consultaTipo($1.id);}
        |ChamadaFuncao
	;

%%
#include "lex.yy.c"

int yyerror (char *str)
{
	printf("%s - antes %s, Linha: %d\n", str, yytext, linha);


}

int yywrap()
{
	return 1;
}
