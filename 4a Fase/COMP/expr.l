delim	 [ \t]
ws	 {delim}+
digito	 [0-9]
int 		{digito}+
float {digito}+(\.{digito}*(E[+-]?{digito}+)?)?
literal  \".*\"
car	 [a-zA-Z]
id ({car})+({digito}|\_|{car})*

%%
{ws}	 {}
"\n"     {linha++;}
"+"	 {return TADD;}
">"      {return TMAIORQ;}
"<"      {return TMENORQ;}
"<="     {return TMENORIGUALQ;}
">="     {return TMAIORIGUALQ;}
"=="     {return TIGUALCOMP;}
"!"      {return TNEGACAO;}
"!="     {return TDIFCOMP;}
"if"     {return TIF;}
"else"   {return TELSE;}
"while"  {return TWHILE;}
"print"  {return TPRINT;}
"read"   {return TREAD;}
"return" {return TRETURN;}
"&&"     {return TELOGICO;}
"||"     {return TOULOGICO;}
"-"	 {return TSUB;}
"*"	 {return TMUL;}
"/"	 {return TDIV;}
"("	 {return TAPAR;} 
")"	 {return TFPAR;}
"int"    {return TINT;}
"float"  {return TFLOAT;}
"String" {return TSTRING;}
"void"   {return TVOID;}
"{"      {return TACHAVE;}
"}"      {return TFCHAVE;}
"="      {return TATRIBUICAO;}
","      {return TVIRGULA;}
";"      {return TPVIRGULA;}
{int}	{yylval.valorInt = atoi(yytext); return TINT;}
{float} {yylval.valorFloat = atof(yytext); return TFLOAT;}
{literal} {strncpy(yylval.buffer, yytext, T_MAX - 1); return TLIT;}
{id}     {strncpy(yylval.id, yytext, MAX_ID-1); return TID;}
