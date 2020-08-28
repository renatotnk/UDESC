!  parimp em Assembly as88
!  versao que le numero e processa string usando operacoes de string (SCASB)
!
!  (c) rro, 2015-02-24
!
!  para montar o programa:
!    $ ./as88 parimp1b.s
!
!  para executar o programa:
!    $ ./s88 parimp1b
!
!  para depurar o programa:
!    $ ./t88 parimp1b

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

	MOV	DI,num		! DI aponta para o inicio da string
	MOVB	AL,'\n'		! AL='\n'
	CLD			! direcao para cima (inicio --> fim)
	REPNE	SCASB		! procura o final da string ('\n')
	DEC	DI		! DI=endereco do ultimo digito
	DEC	DI
	MOV	DX,0		! dividendo=DX:AX - DX=0
	MOVB	AH,0		! AX=ultimo digito
	MOVB	AL,(DI)		! como o valor ASCII de '0' e' 48,
				!   se o valor ASCII for par o valor numerico
				!   tambem sera', nao precisa converter
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
