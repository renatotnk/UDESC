%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expr.tab.h"
#include "eda.h"
#include "cmd.h"

typedef struct {
    struct List *listaId;
    char nomeId[10];
    char* strg;
    TIPO tipo;
    TIPO* listaTipo;
    double double_value;
    struct IntList* listav;
    struct IntList* listaf;
    int label;
}Atributo;

struct arvore* tabelaSimbolosGlobais;
struct arvore* tabelaSimbolosFuncoes;
#define YYSTYPE Atributo
int __linha__ = 1;

int funcNargs = 0;


%}

%token T_SQRT T_BIT_DIREITA T_BIT_ESQUERDA T_ADICAO T_SUBTRACAO T_MULTIPLICACAO T_DIVISAO T_RESTO T_IGUAL T_ABRE_PARENTESES T_FECHA_PARENTESES T_ABRE_CHAVES T_FECHA_CHAVES T_INT T_DOUBLE T_STRING T_VOID T_IF T_WHILE T_ELSE T_PRINT T_READ T_RETURN T_ID T_LITERAL T_FIM T_NUM T_VIRGULA T_PONTO_E_VIRGULA T_AND T_NOT T_OR T_TRUE T_FALSE T_MAIOR_IGUAL T_MENOR_IGUAL T_DIFERENTE T_IGUAL_IGUAL T_MAIOR T_MENOR

%%
Programa : ListaFuncoes MMain BlocoPrincipal {writeJasminMain();clearJasmin();}
	| MMain BlocoPrincipal {writeJasminMain();clearJasmin();}
	;

MMain : {clearJasmin();tabelaSimbolosGlobais = criarArvore();insereArvore(tabelaSimbolosGlobais,"args");}

ListaFuncoes :  ListaFuncoes MZerador Funcao {writeJasminFunc($3.tipo,$3.nomeId, $3.listaTipo);ShowCmdAscii();clearJasmin();tabelaSimbolosGlobais = criarArvore();}
	| Funcao {writeJasminFunc($1.tipo,$1.nomeId, $1.listaTipo);ShowCmdAscii();clearJasmin();tabelaSimbolosGlobais = criarArvore();}
	;

MZerador : {funcNargs = 0;}

Funcao : EscopoFuncao BlocoPrincipal
	| EscopoFuncaoVazia BlocoPrincipal
	;

EscopoFuncaoVazia : TipoRetorno T_ID T_ABRE_PARENTESES T_FECHA_PARENTESES  {createFunction(tabelaSimbolosFuncoes, $2.nomeId, $1.tipo,funcNargs, NULL);funcNargs = 0;}

EscopoFuncao : TipoRetorno T_ID T_ABRE_PARENTESES DeclParametros T_FECHA_PARENTESES {$$.tipo = $1.tipo; strcpy($$.nomeId,$2.nomeId); $$.listaTipo = createListaTipoIntNVezes(funcNargs);createFunction(tabelaSimbolosFuncoes, $2.nomeId, $1.tipo,funcNargs,createListaTipoIntNVezes(funcNargs)); funcNargs = 0; }

TipoRetorno : T_VOID
	| T_INT {$$.tipo = INT; }
	| T_DOUBLE
	| T_STRING
	;

DeclParametros : DeclParametros T_VIRGULA Parametro {  }
	| Parametro { }
	;

Parametro : Tipo T_ID {insereArvore(tabelaSimbolosGlobais,$2.nomeId); funcNargs++;}
	;

BlocoPrincipal : T_ABRE_CHAVES Declaracoes ListaCmd T_FECHA_CHAVES  {}
	| T_ABRE_CHAVES ListaCmd T_FECHA_CHAVES {}
	;

Declaracoes : Declaracoes Declaracao
	| Declaracao
	;

Declaracao : Tipo ListaId T_PONTO_E_VIRGULA {insereListaNaArvore($2.listaId, tabelaSimbolosGlobais, $1.tipo);}
	;


Tipo : T_INT {$$.tipo = INT;}
	| T_DOUBLE {$$.tipo = DOUBLE;}
	| T_STRING {$$.tipo = STRING;}
	;

ListaId : ListaId T_VIRGULA T_ID {insereLista($1.listaId, $3.nomeId); $$.listaId = $1.listaId;}
	| T_ID {$$.listaId = criaLista($1.nomeId);}
	;

Bloco : T_ABRE_CHAVES ListaCmd T_FECHA_CHAVES
	;

ListaCmd : ListaCmd Comando
	| Comando
	;

Comando : CmdSe
	| CmdEnquanto
	| CmdAtrib
	| CmdEscrita
	| CmdLeitura
	| ChamadaProc
	| Retorno
	;

Retorno : T_RETURN ExpressaoAritmetica T_PONTO_E_VIRGULA {CmdIreturn();}
	| T_RETURN T_LITERAL T_PONTO_E_VIRGULA
	;

CmdSe : T_IF T_ABRE_PARENTESES ExpressaoLogica T_FECHA_PARENTESES MLogico Bloco { LabelUpdate($3.listav, $5.label); LabelUpdate($3.listaf, LabelCreate());  }
	| T_IF T_ABRE_PARENTESES ExpressaoLogica T_FECHA_PARENTESES MLogico Bloco NLogico T_ELSE MLogico Bloco {LabelUpdate($3.listav, $5.label); LabelUpdate($3.listaf, $9.label); LabelUpdate($7.listav, LabelCreate());}
	;

NLogico: {$$.listav = criaIntList(GetIndexPosition()); CmdGOTO();}

CmdEnquanto : T_WHILE MLogico T_ABRE_PARENTESES ExpressaoLogica T_FECHA_PARENTESES MLogico Bloco {LabelUpdate($4.listav, $6.label); CmdGOTOLabel($2.label); LabelUpdate($4.listaf, LabelCreate()); CmdEndWhile();}
	;

CmdAtrib : T_ID T_IGUAL ExpressaoAritmetica T_PONTO_E_VIRGULA {CmdIstore(tabelaSimbolosGlobais, $1.nomeId);}
	| T_ID T_IGUAL T_LITERAL T_PONTO_E_VIRGULA
  | T_ID T_ADICAO T_IGUAL ExpressaoAritmetica T_PONTO_E_VIRGULA{CmdIload(tabelaSimbolosGlobais, $1.nomeId); CmdIadd(); CmdIstore(tabelaSimbolosGlobais, $1.nomeId); }
  | T_ID T_SUBTRACAO T_IGUAL ExpressaoAritmetica T_PONTO_E_VIRGULA {CmdIload(tabelaSimbolosGlobais, $1.nomeId); CmdIneg(); CmdIadd(); CmdIneg(); CmdIstore(tabelaSimbolosGlobais, $1.nomeId); }
  | T_ID T_ADICAO T_ADICAO T_PONTO_E_VIRGULA { CmdIload(tabelaSimbolosGlobais, $1.nomeId); CmdBipush(1); CmdIadd(); CmdIstore(tabelaSimbolosGlobais, $1.nomeId); }
  | T_ID T_SUBTRACAO T_SUBTRACAO T_PONTO_E_VIRGULA { CmdIload(tabelaSimbolosGlobais, $1.nomeId);  CmdBipush(1); CmdIsub(); CmdIstore(tabelaSimbolosGlobais, $1.nomeId); }
  ;

CmdEscrita : T_PRINT CmdEscritaMarcador T_ABRE_PARENTESES ExpressaoAritmetica T_FECHA_PARENTESES T_PONTO_E_VIRGULA {CmdInvokeOutInt();}
	| T_PRINT CmdEscritaMarcador T_ABRE_PARENTESES T_LITERAL T_FECHA_PARENTESES T_PONTO_E_VIRGULA {
                                                        CmdLdc($4.strg);
                                                        CmdInvokeOutLiteral();
							}
	;

CmdEscritaMarcador : {CmdGetStaticOut();}



CmdLeitura : T_READ T_ABRE_PARENTESES T_ID T_FECHA_PARENTESES T_PONTO_E_VIRGULA { CmdReadInt(tabelaSimbolosGlobais, $3.nomeId); }
	;

ChamadaProc :  ChamadaFuncao T_PONTO_E_VIRGULA
	;

ChamadaFuncao : T_ID T_ABRE_PARENTESES ListaParametros T_FECHA_PARENTESES {CmdInvokeFunction($1.nomeId);}
	| T_ID T_ABRE_PARENTESES T_FECHA_PARENTESES
  | T_SQRT T_ABRE_PARENTESES ExpressaoAritmetica T_FECHA_PARENTESES { CmdI2d(); CmdSqrt(); CmdD2i(); }
	;

ListaParametros : ListaParametros T_VIRGULA ExpressaoAritmetica
	| ListaParametros T_VIRGULA T_LITERAL
	| ExpressaoAritmetica
	| T_LITERAL

// Trabalho 1
// Expressões Aritméticas

ExpressaoAritmetica : ExpressaoAritmetica T_ADICAO TExpressaoAritmetica {CmdIadd();}
	| ExpressaoAritmetica T_SUBTRACAO TExpressaoAritmetica {CmdIsub();}
  | ExpressaoAritmetica T_BIT_DIREITA TExpressaoAritmetica {CmdIshr();}
  | ExpressaoAritmetica T_BIT_ESQUERDA TExpressaoAritmetica {CmdIshl();}
	| TExpressaoAritmetica
	;

TExpressaoAritmetica : TExpressaoAritmetica T_MULTIPLICACAO FExpressaoAritmetica {CmdImull();}
	| TExpressaoAritmetica T_DIVISAO FExpressaoAritmetica {CmdIdiv();}
  | TExpressaoAritmetica T_RESTO FExpressaoAritmetica {CmdIrem();}
  | FExpressaoAritmetica
	;

FExpressaoAritmetica : T_ABRE_PARENTESES ExpressaoAritmetica T_FECHA_PARENTESES
	| T_SUBTRACAO FExpressaoAritmetica {CmdIneg();}
	| T_NUM {CmdBipush((int)$1.double_value);}
	| T_ID {CmdIload(tabelaSimbolosGlobais, $1.nomeId);}
  | ChamadaFuncao
	;

ExpressaoLogica : ExpressaoLogica T_AND MLogico FExpressaoLogica  { LabelUpdate($1.listav, $3.label); $$.listaf =  juntarIntList($1.listaf, $4.listaf);  $$.listav = $4.listav;}
	| ExpressaoLogica T_OR MLogico FExpressaoLogica { LabelUpdate($1.listaf, $3.label); $$.listav = juntarIntList($1.listav, $4.listav); $$.listaf = $4.listaf; }
	| FExpressaoLogica { $$.listav = $1.listav; $$.listaf = $1.listaf;}
	;

MLogico : {$$.label = LabelCreate();}

FExpressaoLogica : T_NOT FExpressaoLogica { $$.listav = $2.listaf; $$.listaf = $2.listav; }
	| T_ABRE_PARENTESES ExpressaoLogica T_FECHA_PARENTESES { $$.listav = $2.listav; $$.listaf = $2.listaf; }
	| ExpressaoAritmetica T_IGUAL_IGUAL ExpressaoAritmetica { $$.listav =  criaIntList(GetIndexPosition()); $$.listaf = criaIntList(GetIndexPosition()+1); CmdIfEQ(); CmdGOTO();}
  | ExpressaoAritmetica T_DIFERENTE ExpressaoAritmetica { $$.listav =  criaIntList(GetIndexPosition()); $$.listaf = criaIntList(GetIndexPosition()+1); CmdIfNE(); CmdGOTO();}
  | ExpressaoAritmetica T_MAIOR ExpressaoAritmetica { $$.listav =  criaIntList(GetIndexPosition()); $$.listaf = criaIntList(GetIndexPosition()+1); CmdIfGT(); CmdGOTO();}
  | ExpressaoAritmetica T_MAIOR_IGUAL ExpressaoAritmetica { $$.listav =  criaIntList(GetIndexPosition()); $$.listaf = criaIntList(GetIndexPosition()+1); CmdIfGE(); CmdGOTO();}
  | ExpressaoAritmetica T_MENOR ExpressaoAritmetica { $$.listav =  criaIntList(GetIndexPosition()); $$.listaf = criaIntList(GetIndexPosition()+1); CmdIfLT(); CmdGOTO();}
  | ExpressaoAritmetica T_MENOR_IGUAL ExpressaoAritmetica { $$.listav =  criaIntList(GetIndexPosition()); $$.listaf = criaIntList(GetIndexPosition()+1); CmdIfLE(); CmdGOTO();}



  ;



%%
#include "lex.yy.c"

int yyerror (char *str)
{
	printf("[Linha%d] - %s - antes %s\n", __linha__,str, yytext);

}

int yywrap()
{
	return 1;
}
