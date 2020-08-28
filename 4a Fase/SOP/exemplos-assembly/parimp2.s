!  parimp em Assembly as88
!  versao usando readnum
!
!  (c) rro, 2015-02-24
!
!  para montar o programa:
!    $ ./as88 parimp2.s readnum.s
!
!  para executar o programa:
!    $ ./s88 parimp2
!
!  para depurar o programa:
!    $ ./t88 parimp2

#include "../syscalnr.h"              

.SECT .TEXT

start:
	MOV	BP,SP		! salva SP
	PUSH	pr1		! endereco da string
	PUSH	_PRINTF		! no. da syscall
	SYS			! executa syscall 

	CALL	readnum		! le string e converte para numero
	MOV	(num),AX	! armazena o numero lido em 'num'

	MOV	DX,0		! dividendo=DX:AX - DX=0, AX=num
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
num:	.SPACE 30
numf:	.SPACE 1
