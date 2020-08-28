#Aluno: Renato Tanaka
	.text
	.globl main
main:
	ori $v0,$zero,5
	syscall 		# scan
	ori $a0,$v0, 0		# coloca a em a0 (argumento)
	
	ori $v0,$zero,5
	syscall 		# scan
	ori $a1,$v0, 0		# coloca b em a1 (argumento)
	
	jal euclides
	
	ori $a0,$v0,0		# pega resultado
	ori $v0,$zero,1		# print
	syscall
	j end
	
euclides:
	slt  $t0, $a0, $a1
	bne $t0, $zero, troca	# se A < B, trocar
	
	beq $a0, $zero, ret_b	# se A == 0, retorne B
	beq $a1, $zero, ret_a	# se B == 0, retorne A
	
	addi $sp, $sp, -12	# alocando pilha
	sw $ra, 0($sp)		# armazenando ra
	sw $a0, 4($sp)		# armazenando A
	sw $a1, 8($sp)		# armazenando B
	
	div $a0, $a1 		# dividindo A/B
	
	ori $a0, $a1, 0		# A = B
	mfhi $a1		# B = A % B
	jal euclides		# return euclides(B, A%B)
	
	lw $a1, 8($sp)		# carregando de volta B original
	lw $a0, 4($sp)		# carregando de volta A original
	lw $ra, 0($sp)		# caregando ra original
	addi $sp, $sp, 12	# desalocando pilha
	jr $ra
	
	
troca:
	ori $t0, $a0, 0		# aux = a
	ori $a0, $a1, 0		# a = b
	ori $a0, $t0, 0 	# b = aux
	j euclides
	
ret_a:
	ori $v0, $a0, 0
	jr $ra
ret_b:
	ori $v0, $a1, 0
	jr $ra

	
end:
	li $v0, 10			
	syscall	