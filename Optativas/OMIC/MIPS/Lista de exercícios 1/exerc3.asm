#Alunos: Eduarda Cristina e Renato Tanaka	
        .data
	soma: 	.asciiz      "Soma:"
	media: 	.asciiz      "\nMedia (truncado para cima):"
	
	.text
	.globl main
main:	
	li $v0, 5
	syscall 
	ori $s0, $s0, 1	# s0 = soma
	ori $s1, $s1, 0	# s1 = contador de numeros
	ori $s2, $zero, -1 
	
loop:
	li $v0, 5
	syscall
	ori $t0, $v0, 0
	beq $t0, $s2, end	# Se o numero digitado for igual a -1, end
	addi $s1, $s1, 1	# Adicionando 1 ao contador de numeros
	add $s0, $s0, $t0	# Adicionando o numero de input a variavel de soma  
	j loop			
end:
	
	li, $v0, 4
	la $a0, soma		
	syscall			# print mensagem soma
	li $v0, 1
	add $a0, $s0, 0		
	syscall			# print soma
	
	
	div $t1, $s0, $s1	# Calculo media
	li, $v0, 4
	la $a0, media		# print mensagem media
	syscall
	li $v0, 1
	add $a0, $t1, 0		
	syscall			# print soma
 
	li $v0, 10
	syscall


	
	
