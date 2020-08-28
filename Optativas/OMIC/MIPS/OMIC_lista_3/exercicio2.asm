#Aluno: Renato Tanaka
	.data
	fibo: 	.asciiz      "Fibo: "
	quebra: .asciiz      "\n"
	
	.text
	.globl main
	
main:	#Fibonacci de N
	ori $s1, $zero, 0
	ori $s2, $zero, 1
	li $v0, 5		#ler valor do teclado e armazenar em V0
	syscall 
	ori $s0, $v0, 0 	##carregar valor de v0 em s0
	bltz $v0, end		#compara se valor em v0 < 0. Se sim, jump para end
	j loop
	
loop:
	beq $s0, $zero, print	#Compara se s0 == 0. Se sim, jump para print
	add $s3, $s1, $s2	#aux = a + b
	ori $s1, $s2, 0		# a = b
	ori $s2, $s3, 0		# b = aux
	addi $s0, $s0, -1	#Adiciona -1 ao conteúdo de s0
	j loop		#retorne para o começo do loop
	
print:
	li, $v0, 4
	la $a0, fibo		# print mensagem fibo
	syscall
	li $v0, 1
	add $a0, $s1, 0		# print s1
	syscall
	li, $v0, 4
	la $a0, quebra		# print quebra
	syscall
	j main
	
end:
	li $v0, 10
	syscall
			
