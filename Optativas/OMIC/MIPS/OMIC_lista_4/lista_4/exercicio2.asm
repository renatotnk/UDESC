#Aluno: Renato Tanaka
	.text
	.globl main
main:
	ori $v0,$zero,5
	syscall 		# scan
	ori $a0,$v0, 0		# coloca n em a0 (argumento)
	jal fibonacci
	ori $a0,$v0,0		# pega resultado
	ori $v0,$zero,1		# print
	syscall
	j end
	
fibonacci:
	slti $t0,$a0,2		#colocamos em a0 o parâmetro n
	bne $t0,$zero,fibonacci_break	# n == 00 || n == 1
	addi $sp, $sp, -8	# coloca 2 espacos na pilha
	sw $ra, 4($sp)		# guarda ra
	sw $a0, 0($sp)		# guarda a0 
	addi $a0, $a0, -1
	jal fibonacci		# fib(n-1)
	lw $a0, 0($sp)		# recarregar a0
	sw $v0, 0($sp)		# salvar fib(n-1)
	addi $a0, $a0, -2
	jal fibonacci		# fib(n-2)
	lw $t0, 0($sp)		# carregar fib(n-1)
	lw $ra, 4($sp)		# carregarra
	add $sp, $sp, 8		# limpa pilha
	add $v0,$v0,$t0		# v0 continha fib(n-2)
	jr $ra
	
fibonacci_break:		#retornar 1 (break)
	ori $v0,$zero,1
	jr $ra
end:
	li $v0, 10			
	syscall				
