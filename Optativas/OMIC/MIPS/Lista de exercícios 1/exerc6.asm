#Alunos: Eduarda Cristina e Renato Tanaka
	.text
	.globl main
main:	#Fibonacci de N
	li $v0, 5
	syscall 
	ori $s0, $v0, 0 
	ori $s1, $zero, 0
	ori $s2, $zero, 1
	
	#aux = s3
	#a = s1
	#b = s2
	
loop:
	beq $s0, $zero, end	#Compara se s0 == 0
	add $s3, $s1, $s2	#aux = a + b
	ori $s1, $s2, 0		# a = b
	ori $s2, $s3, 0		# b = aux
	addi $s0, $s0, -1	#Adiciona -1 ao conteúdo de s0
	j loop			#retorne para o começo do loop
	
end:
	li $v0, 1
	add $a0, $s1, 0		# print s1
	syscall
	li $v0, 10
	syscall
			
