!  parimp em Assembly as88
!  versao com valor hardcoded
! 
!  (c) rro, 2015-02-24
!
!  para montar o programa:
!    $ ./as88 parimp.s
!
!  para executar o programa:
!    $ ./s88 parimp
!
!  para depurar o programa:
!    $ ./t88 parimp

#include "../syscalnr.h"              

.SECT .TEXT

NUM=171				! numero a ser testado
	
start:
	MOV	BP,SP		! salva SP em BP
	MOV	(num),NUM	! armazena o numero em 'num'
	MOV	DX,0		! dividendo=DX:AX - DX=0
	MOV	AX,(num)	! AX=valor em num
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
str_impar:	.ASCIZ	'impar'
str_par:	.ASCIZ	'par'
pr2:		.ASCIZ	'O numero eh %s\n'

.SECT	.BSS
num:	.WORD	0
