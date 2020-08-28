#Aluno: Renato Tanaka
	.data
	n: .asciiz      "n: "
	binario_s: .asciiz 	"binario: "
	.text
	.globl main
	
main:
	li, $v0, 4
	la $a0, n		# print mensagem n
	syscall
	ori $v0,$zero,5
	syscall 		# scan
	ori $a1,$v0, 0		# coloca n em a1 (argumento)
	
	li, $v0, 4
	la $a0, binario_s		# print mensagem binario
	syscall
	jal binario
	
	ori $a0,$v1, 0		# pega resultado
	ori $v0,$zero,1		# print
	syscall
	j end
	
binario:	#calcula um numero de decimal para binario
	slti $t0, $a1 , 1		# compara se a2 < 1
	bne $t0,$zero,binario_end		# se sim, retorna para $ra
	ori $t1, $zero, 2		# divisor
	addi $sp, $sp, -8
	sw $a1, 0($sp)
	sw $ra, 4($sp)
	div $a1, $t1			# n / 2
	mflo $a1
	mfhi $t2			# t2 = n % 2
	ori $a0, $t2, 0
	ori $v0, $zero, 1
	syscall
	jal binario
	lw $a1, 0($sp)
	lw $ra 4($sp)
	addi $sp, $sp, 8
	jr $ra
	
	
binario_end:
	jr $ra


end:
	li $v0, 10			
	syscall	
