#Aluno: Renato Tanaka
	.data
	n: .asciiz      "n: "
	quebra: .asciiz "\n"
	soma_s: .asciiz 	"soma: "
	.text
	.globl main
	
main:
	li, $v0, 4
	la $a0, n		# print mensagem k
	syscall
	ori $v0,$zero,5
	syscall 		# scan
	ori $a1,$v0, 0		# coloca n em a1 (argumento)
	jal soma
	
	li, $v0, 4
	la $a0, soma_s		# print mensagem soma
	syscall
	
	ori $a0,$v1, 0		# pega resultado
	ori $v0,$zero,1		# print
	syscall
	j end
	
soma:	#conta a soma dos digitos de n
	addi $sp, $sp, -4
	sw $fp, 0($sp)
	ori $fp, $sp, 0		
	slti $t0, $a1 , 1		# compara se a1 < 1
	bne $t0,$zero,soma_end		# se sim, retorna para $ra
	ori $t1, $zero, 10		# divisor
	addi $sp, $sp, -8
	sw $a1, -4($fp)
	sw $ra, -8($fp)
	div $a1, $t1			# n / 10
	mflo $a1
	mfhi $t2			# t2 = n % 10
	add $v1, $v1, $t2		# v1 serve como retorno que acumula a soma
	jal soma
	lw $ra -4($fp)
	lw $a1, -8($fp)
	lw $fp, 0($fp)
	addi $sp, $sp, 12
	jr $ra
	
	
soma_end:
	jr $ra


end:
	li $v0, 10			
	syscall	
