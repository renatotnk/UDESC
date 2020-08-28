!  parimp em Assembly as88
!  versao que le numero e processa string
!
!  (c) rro, 2015-02-24
!
!  para montar o programa:
!    $ ./as88 parimp1.s readnum.s
!
!  para executar o programa:
!    $ ./s88 parimp1
!
!  para depurar o programa:
!    $ ./t88 parimp1

#include "../syscalnr.h"              

.SECT .TEXT

start:
	MOV	BP,SP		! salva SP
	PUSH	pr1		! endereco da string
	PUSH	_PRINTF		! no. da syscall
	SYS			! executa syscall 

	MOV	CX,numf-num	! CX=tamanho da string num
	PUSH	CX
	PUSH	num		! endereco da string
	PUSH	STDIN		! arquivo de entrada
	PUSH	_READ		! no. da syscall
	SYS			! executa syscall 

	MOV	BX,num		! BX aponta para o inicio da string
1:
	CMPB	(BX),'\n'	! compara *BX com \n
	JE	2f		! se for igual, encontrou fim da string
	INC	BX		! senao, avanca para o proximo caracter e...
	JMP	1b		! ... compara novamente
2:
	DEC	BX		! BX=endereco do ultimo digito
	MOV	DX,0		! dividendo=DX:AX - DX=0
	MOVB	AH,0		! AX=ultimo digito
	MOVB	AL,(BX)		! como o valor ASCII de '0' e' 48,
				!   se o valor ASCII do ultimo digito for 
				!   par o valor numerico tambem sera', nao 
				!   precisa conversao ASCII->num
        MOV     CX,2            ! divisor em CX
        IDIV    CX              ! quociente em AX, resto em DX
        CMP     DX,0		! compara DX com 0
        JE      imp_par         ! se for igual, e' par

imp_impar:
	PUSH	str_impar	! 2o argumento de printf() e' "impar"
        JMP     imprime
	
imp_par: 
	PUSH    str_par		! 2o argumento de printf() e' "par"
	
imprime:
	PUSH	pr2		! 1o argumento de printf() e' pr2
	PUSH	_PRINTF
	SYS

encerra:    
	MOV	SP,BP		! limpa pilha
	PUSH	0		! codigo de retorno=0
	PUSH	_EXIT		
	SYS			! encerra o programa
fim:

.SECT	.DATA
pr1:		.ASCIZ	'\nEntre um numero: '
str_impar:	.ASCIZ	'impar'
str_par:	.ASCIZ	'par'
pr2:		.ASCIZ	'O numero eh %s\n'

.SECT	.BSS
num:	.SPACE 8
numf:	.SPACE 1
