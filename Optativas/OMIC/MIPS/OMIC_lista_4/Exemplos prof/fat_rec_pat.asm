	.text
	.globl main
main:
	ori $v0,$zero,5
	syscall 		#lê do teclado
	ori $a0,$v0, 0	#coloca como argumento
	jal fatorial_rec
	ori $a0,$v0,0		#resultado como argumento
	ori $v0,$zero,1	#impressão de inteiro
	syscall		#imprime o resultado
end:
	li $v0, 10		#10 em $v0 para fim de programa
	syscall		#chama o S.O. para terminar
	
fatorial_rec:
	addi $sp, $sp, -8	# alocando espaço para 2 itens
	sw $ra, 4($sp)	#salvando o endereço de retorno
	sw $a0, 0($sp) 	#salvando o argumento n (a0)
	slti  $t0, $a0, 1  	#verifica se a0 < 1
	beq $t0, $zero, calcular_fat 	#se a0 >= 1, saltar
	addi  $v0,$zero,1	#retornar 1
	addi  $sp,$sp,8	#desalocar itens da pilha
	jr  $ra  		#retornar ao chamador
calcular_fat:
	addi $a0,$a0,-1 	#n = n-1
	jal fatorial_rec	#fatorial(n-1)
	lw  $a0, 0($sp)	#restaurar a0
	lw  $ra, 4($sp)	#restaurar end. de retorno
	addi $sp, $sp, 8 	#desalocar itens da pilha
	mul  $v0,$a0,$v0 	#retornar n * fatorial (n – 1)
	jr  $ra			#retornar ao chamador