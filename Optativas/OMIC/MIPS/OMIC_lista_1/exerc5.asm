	.text
	.globl main
main:	#Fibonacci de 20
	ori $s0, $zero, 20	#Carregar 1 em s0
	ori $s1, $zero, 0	#Carregar 9 em s1
	ori $s2, $zero, 1
	
loop:
	beq $s0, $zero, end	#Compara se s0 == 0
	add $s3, $s1, $s2
	ori $s1, $s2, 0		
	ori $s2, $s3, 0
	addi $s0, $s0, -1	#Adiciona -1 ao conteúdo de s1
	j loop			#retorne para o começo do loop
	
end:
	li $v0, 1
	add $a0, $s1, 0
	syscall
	li $v0, 10
	syscall
			
