	.data
	quebra: .asciiz "\n"
	
	.text
	.globl main
main:
	ori $s0,$zero,11	# Termina no 10
	ori $s1,$zero,2		# Inicia no 2
principal:
	ori $s2, $zero, 1	# Multiplicando
secundario:

	mult $s1, $s2
	
	mflo $a0		# Resultado da multiplicação
	ori $v0, $zero, 1
	syscall

	la $a0, quebra
	li $v0, 4
	syscall

	addi $s2, $s2, 1
	bne $s2,$s0, secundario
	syscall	
	
	addi $s1, $s1, 1
	bne $s1,$s0,principal
	
end:
	li $v0, 10			
	syscall	

