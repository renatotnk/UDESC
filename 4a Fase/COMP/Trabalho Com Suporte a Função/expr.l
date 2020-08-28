delim	[ \t\r]
ws	{delim}+
digito	[0-9]
num	{digito}+(\.{digito}*(E[+-]?{digito}+)?)?
id [a-zA-Z_][a-zA-Z0-9_]*
literal \".*\"

%%
{ws}	{}
"sqrt" {return T_SQRT;}
">=" {return T_MAIOR_IGUAL;}
"<=" {return T_MENOR_IGUAL;}
"!=" {return T_DIFERENTE;}
"==" {return T_IGUAL_IGUAL;}
">>" {return T_BIT_DIREITA;}
"<<" {return T_BIT_ESQUERDA;}
">" {return T_MAIOR;}
"<" {return T_MENOR;}
"+"	{return T_ADICAO;}
"-"	{return T_SUBTRACAO;}
"*"	{return T_MULTIPLICACAO;}
"/"	{return T_DIVISAO;}
"%" {return T_RESTO;}
"="	{return T_IGUAL;}
"("	{return T_ABRE_PARENTESES;}
")"	{return T_FECHA_PARENTESES;}
"{"	{return T_ABRE_CHAVES;}
"}"	{return T_FECHA_CHAVES;}
"," {return T_VIRGULA;}
";" {return T_PONTO_E_VIRGULA;}
"int" {return T_INT;}
"double" {return T_DOUBLE;}
"String" {return T_STRING;}
"void" {return T_VOID;}
"if" {return T_IF;}
"while" {return T_WHILE;}
"else" {return T_ELSE;}
"print" {return T_PRINT;}
"read" {return T_READ;}
"return" {return T_RETURN;}
"!" {return T_NOT;}
"&&" {return T_AND;}
"||" {return T_OR;}
"true" {return T_TRUE;}
"false" {return T_FALSE;}
{id} { strncpy(yylval.nomeId, yytext, 10); return T_ID;}
{literal} {yylval.strg = yytext;return T_LITERAL;}
\0	{return T_FIM;}
\n  {__linha__ ++;}
{num}	{yylval.double_value=atof(yytext); return T_NUM;}
