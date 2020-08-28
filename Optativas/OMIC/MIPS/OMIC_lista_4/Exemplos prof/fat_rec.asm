	.text
	.globl main
main:
	ori $v0,$zero,5
	syscall 			#lê do teclado
	ori $a0,$v0, 0		#coloca como argumento
	jal fatorial_rec
	ori $a0,$v0,0		#coloca o resultado como argumento
	ori $v0,$zero,1		#impressão de inteiro
	syscall				#imprime o resultado
	j end
fatorial_rec:
	slti $t0,$a0,1		#colocamos em a0 o parâmetro n
	bne $t0,$zero,fatorial_0	#verifica se chegamos em 0
	addi $sp, $sp, -8	#ajusta a pilha para 2 itens
	sw $a0, 0($sp)		#guarda a0 para depois
	sw $ra, 4($sp)		#guarda o endereço de retorno
	addi $a0, $a0, -1
	jal fatorial_rec	#chama fatorial para n-1
	lw $a0, 0($sp)		#carrega o valor antigo de a0
	lw $ra, 4($sp)		#carrega o endereço
	addi $sp, $sp, 8	#apaga os valores da pilha
	mul $v0, $a0,$v0	#multiplica a0 pelo retorno do fatorial
	jr $ra
fatorial_0:				#retornar o fatorial de 0
	ori $v0,$zero,1
	jr $ra
end:
	li $v0, 10			#10 em $v0 para informar que o programa terminou
	syscall				#chama o S.O. para terminar o programa
