	.data
	str_par: .asciiz " Par\n"
	str_impar: .asciiz " Impar\n"
	
	.text
	.globl main
main:
	li $s0, -10
	li $s1, 2			#divisor
loop:
	or $a0, $zero, $s0
	li $v0, 1
	syscall
	
	div $s0, $s1
	mfhi $t0			# Pega valor em HI
	bne $t0, $zero, impar		# if/else
	la $a0, str_par
	j else
impar:
	la $a0, str_impar
else:
	li $v0, 4		# Print
	syscall
	addi $s0, $s0, 1
	slti $t0, $s0, 11
	bne $t0, $zero, loop
end:
	li $v0, 10			
	syscall				

