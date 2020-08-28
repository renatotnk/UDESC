#Aluno: Renato Tanaka
	.data
	quebra: .asciiz      "\n"
	
	.text
	.globl main
main:
	ori $v0,$zero,5
	syscall 		# scan
	ori $a0,$v0, 0		# coloca operacao em a0 (argumento)
	
	jal calcula		#calcule
	
	ori $a0,$v0,0		# pega resultado
	ori $v0,$zero,1		# print
	syscall
	
	li, $v0, 4
	la $a0, quebra		# print mensagem y
	syscall
	
	j main
	
calcula:
	ori $t4, $zero, 5	#t4 = fim
	beq $a0, $t4, end	# se operacao == 5, end
	
	ori $v0,$zero,5
	syscall 		# scan
	ori $a1,$v0, 0		# coloca n1 em a0 (argumento)
	
	ori $v0,$zero,5
	syscall 		# scan
	ori $a2,$v0, 0		# coloca n2 em a0 (argumento)
	
	ori $t0, $zero, 1	#t0 = soma
	ori $t1, $zero, 2	#t1 = sub
	ori $t2, $zero, 3	#t2 = multi
	ori $t3, $zero, 4	#t3 = div
	
	beq $a0, $t0, soma
	beq $a0, $t1, subt
	beq $a0, $t2, multi
	beq $a0, $t3, divi
	
soma:
	add $v0, $a1, $a2
	jr $ra

subt:
	sub $v0, $a1, $a2
	jr $ra
multi:
	mul $v0, $a1, $a2
	jr $ra
divi:
	div $v0, $a1, $a2
	jr $ra
	
end:
	li $v0, 10			
	syscall	