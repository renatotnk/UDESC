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
	addi $sp, $sp, -4
	sw $fp, 0($sp)
	or $fp, $zero, $sp
	
	addi $sp, $sp, -8	# coloca 2 espacos na pilha
	sw $a0, -4($fp)		# guarda ra
	sw $ra, -8($fp)		# guarda a0 
		
	slti $t0,$a0,2		#colocamos em a0 o parâmetro n
	bne $t0,$zero,fibonacci_break	# n == 00 || n == 1
	
	addi $a0, $a0, -1
	jal fibonacci		# fib(n-1)
	lw $a0, -4($fp)		# recarregar a0
	sw $v0, -4($fp)		# salvar fib(n-1)
	addi $a0, $a0, -2
	jal fibonacci		# fib(n-2)
	lw $t0, -4($fp)		# carregar fib(n-1)
	add $v0,$v0,$t0		# v0 continha fib(n-2)
	lw $ra, -8($fp)		# carregar ra
	lw $fp, 0($fp)
	add $sp, $sp, 12	# limpa pilha
	
	jr $ra
	
fibonacci_break:		#retornar 1 (break)
	lw $fp, 0($fp)
	add $sp, $sp, 12	# limpa pilha
	
	ori $v0,$zero,1
	jr $ra
end:
	li $v0, 10			
	syscall				
