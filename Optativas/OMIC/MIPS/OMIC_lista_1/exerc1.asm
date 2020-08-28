#Alunos: Eduarda Cristina e Renato Tanaka
	.text
	.globl main
main:	#Fatorial de 9
	ori $s1, $zero, 9	#Carregar 9 em s1
	ori $s0, $zero, 1	#Carregar 1 em s0
loop:
	beq $s1, $zero, end	#Compara se s1 == 0
	mul $s0, $s1, $s0	#Se não, multiplica conteúdo de s1 por s0 
	addi $s1, $s1, -1	#Adiciona -1 ao conteúdo de s1
	j loop			#retorne para o começo do loop
end:
	li $v0, 10
	syscall
	
	
