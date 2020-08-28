#Aluno: Renato Tanaka
	.data
	lenght: .asciiz      "lenght: "
	quebra: .asciiz      "\n"
	
	.text
	.globl main
	
main:	#Numero de digitos em um numero
	li $v0, 5		#ler valor do teclado e armazenar em V0
	syscall 
	addiu $s0, $v0, 0 	##carregar valor de v0 em s0
	ori $v1, $v1, 0		# s1 = contador de numeros
	ori $s2, $s2, 10	# s2 = 10
	ori $v1, $v1, 0
	
loop:
	beq $s0, $zero, end
	div $s0, $s0, $s2
	addiu $v1, $v1, 1
	j loop	
	
end:
	li, $v0, 4
	la $a0, lenght		# print mensagem lenght
	syscall
	li $v0, 1
	add $a0, $v1, 0		# print s1
	syscall
	li $v0, 10
	syscall