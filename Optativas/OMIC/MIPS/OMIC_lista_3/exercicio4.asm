#Aluno: Renato Tanaka
	.data
	y: .asciiz      "y: "
	quebra: .asciiz      "\n"
	
	.text
	.globl main
	
main:	#Polinomio de Terceiro grau
	li $v0, 5		#ler valor de x do teclado e armazenar em v0
	syscall 
	addiu $s0, $v0, 0 	# carregar valor de x em s0
	ori $a0, $a0, 4		# a = 4
	ori $a1, $a1, 3		# b =  3
	ori $a2, $a2, 2		# c = 2
	ori $a3, $a3, 1		# d = 1
	jal polinomio
	
end:
	li, $v0, 4
	la $a0, y		# print mensagem y
	syscall
	li $v0, 1
	add $a0, $v1, 0		# print valor de y
	syscall
	li $v0, 10
	syscall
	
polinomio:
	addi $sp, $sp, -4	# subindo pilha em 4 bytes para comportar x
	sw $s0, 0($sp)		# empilhando x
	
	add $t0, $t0, $a0	# carregando a em $t0
	add $t1, $t1, $a1	# carregando b em $t1
	add $t2, $t2, $a2	# carregando c em $t2
	add $t3, $t3, $a3	# carregando d em $t3
	
	mult $s0, $s0
	mflo $t4		# $t4 = x²
	
	mult $s0, $t4		# x³
	mflo $t5		# $t5 = x³
	
	mult $t0, $t5		# a * x³
	mflo $t5		# $t5 = a*x³
	
	mult $t1, $t4		# b * x²
	mflo $t4 		# $t4 = b*x²
	
	
	mult $s0, $t2		# c * x
	mflo $t2		# $t2 = c * x
	
	add $t5, $t5, $t4	# $t5 = a * x³ + b * x²
	add $t2, $t2, $t3	# $t2 = c * x + d
	
	add $v1, $t5, $t2	# v0 = $t5 + $t2
	
	lw $s0, 0($sp)		# recarregando valor original de x em $s0
	addi $sp, $sp, 4	# restaurando a pilha
	
	jr $ra
	
	
	
	
	
	