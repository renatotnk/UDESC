# Aluno(a):
	.text
	.globl main
main:
	ori $v0,$zero,5
	syscall 		# scan
	ori $a0,$v0, 0		# coloca argumento em a0
	
	jal 			# chamada da funcao, se necessario (ajustar)
	
	ori $a0,$v0,0		# coloca retorno (v0) em a0
	ori $v0,$zero,1		# print
	syscall
	j end
	

	
end:
	li $v0, 10			
	syscall	
