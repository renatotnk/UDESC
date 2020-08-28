	.text
	.globl main
main:
	la $a0, ola_mundo
	li $v0, 4
	syscall
end:
	li $v0, 10			#10 em $v0 para informar que o programa terminou
	syscall				#chama o S.O. para terminar o programa
	.data
ola_mundo: .asciiz "Ola Mundo\n"