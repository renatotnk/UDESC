#Aluno: Renato Tanaka
	.data
	k: .asciiz      "k: "
	n: .asciiz      "n: "
	quebra: .asciiz "\n"
	oco: .asciiz 	"ocorrencias: "
	.text
	.globl main
	
main:
	li, $v0, 4
	la $a0, k		# print mensagem k
	syscall
	ori $v0,$zero,5
	syscall 		# scan
	ori $a1,$v0, 0		# coloca k em a0 (argumento)
	
	li, $v0, 4
	la $a0, n		# print mensagem n
	syscall
	ori $v0,$zero,5		
	syscall 	
	ori $a2,$v0, 0		# coloca n em a (argumento)
	jal digitos
	
	li, $v0, 4
	la $a0, oco		# print mensagem ocorrencias
	syscall
	
	ori $a0,$v1, 0		# pega resultado
	ori $v0,$zero,1		# print
	syscall
	j end
	
digitos:	#conta quantas vezes um digito k ocorre em um numero n
	slti $t0, $a2 , 1		# compara se a2 < 1
	bne $t0,$zero,digitos_end	# se sim, retorna para $ra
	ori $t1, $zero, 10		# divisor
	addi $sp, $sp, -12
	sw $a1, 0($sp)
	sw $a2, 4($sp)
	sw $ra, 8($sp)
	div $a2, $t1			# n / 10
	mflo $a2
	mfhi $t2			# t2 = n % 10
	beq $t2, $a1, soma		# soma um digito se k = n % 10
	jal digitos
	lw $a1, 0($sp)
	lw $a2 4($sp)
	lw $ra, 8($sp)
	addi $sp, $sp, 12
	jr $ra
	
soma:
	addiu $v1, $v1, 1
	j digitos
	
		
digitos_end:
	jr $ra


end:
	li $v0, 10			
	syscall	
