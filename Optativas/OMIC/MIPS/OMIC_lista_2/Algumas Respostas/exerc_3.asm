	.data
	init: .asciiz      "Digite sua idade em dias:\n"
	
	.text
	.globl main
	
main:
	li, $v0, 4
	la $a0, init 
	syscall				# Print mensagem init
	
	li $v0, 5			# Ler inteiro para $v0
	syscall
	
	li $t0, 365			# Divide por dias
	div $v0,$t0
	mflo $a0			# Pega resultado em LO 
	
	li $v0, 1			# Imprimir inteiro em $a0
	syscall
	
	ori $a0,47			# 47 == barra
	li $v0, 11			#11 em $v0 para S.O escrever $a0 na tela como char
	syscall
	
	mfhi $t1			#Pega resultado em HI
	li $t0, 30
	div $t1,$t0
	mflo $a0			# Pega resultado em LO
	
	li $v0, 1			# Imprimir inteiro em $a0
	syscall
	
	ori $a0,47			# 47 == barra
	li $v0, 11			#11 em $v0 para S.O escrever $a0 na tela como char
	syscall
	
	mfhi $a0			# Pega conteudo em HI
	li $v0, 1			# Imprimir inteiro em $a0
	syscall
end:
	li $v0, 10			
	syscall				
	.data 
