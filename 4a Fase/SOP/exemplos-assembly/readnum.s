! subrotina para ler um numero da entrada padrao em as88
! - numero lido e' retornado em AX
! - nao e' verificado se o numero lido cabe em 16 bits
!
! (c) rro, 2015-02-24

_RNBSIZ=8			! tamanho do buffer de leitura

.SECT	.TEXT
	
readnum:
	PUSH	BP		! salva BP
	MOV	BP,SP		! salva SP em BP
	PUSH	_RNBSIZ		! no. de bytes a ler
	PUSH	_rnbuf		! endereco da string
	PUSH	STDIN		! arquivo de entrada
	PUSH	_READ		! no. da syscall
	SYS			! executa syscall 

	PUSH	_rnum		! onde sera' armazenado o numero
	PUSH	_rnssf		! string de formato
	PUSH	_rnbuf		! string lida
	PUSH	_SSCANF
	SYS

	MOV	AX,(_rnum)	! guarda o numero em AX
	MOV	SP,BP		! limpa a pilha
	POP	BP		! restaura BP
	RET			! encerra funcao
	
.SECT	.DATA
_rnbuf:	.SPACE	_RNBSIZ
_rnssf:	.ASCIZ	'%d'
_rnum:	.WORD	0
	
.SECT	.BSS
