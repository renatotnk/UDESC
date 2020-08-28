	.text
	.globl main
main:
	li $v0, 5		#5 para ler um inteiro para $v0
	syscall
	ori $s0,$v0,0		#x para $s0
	li $v0, 5		#5 para ler um inteiro para $v0
	syscall
	ori $s1,$v0,0		#y para $s1
	ori $s2, $zero, 0	#s2 vai conter o quadrante
	slt $t0, $s0, 0		#verificando se x < 0
	beq $t0,$zero,x_maior_igual_zero
	ori $s2, $zero, 2	#2 quadrante
	j fim_se_x_menor
x_maior_igual_zero:
	beq $s0,$zero,x_zero
	ori $s2,$zero,1		#1 quadrante
	j fim_se_x_menor
x_zero:
	la $a0, str_eixo_x
	li $v0, 4
	syscall
fim_se_x_menor:
	slt $t0, $s1, 0		#verificando se y < 0
	beq $t0,$zero,y_maior_igual_zero
	beq $s2, $zero, end #y != 0 e já imprimiu que está no eixo x
	slti $t0,$s2,2	#se é menor que 2, mas não é 0, só pode ser 1
	bne $t0,$zero,quarto_quadrante
	ori $s2,$zero, 3	#x e y <0, 3 quadrante
	j fim_se_y_menor
quarto_quadrante:
	ori $s2,$zero,4		#x>0 e y<0, 4 quadrante
	j fim_se_y_menor
y_maior_igual_zero:
	bne $s1,$zero,fim_se_y_menor	#se y maior que zero, nada se altera nos quadrantes
	la $a0, str_eixo_y
	li $v0, 4
	syscall
	j end
fim_se_y_menor:
	beq $s2, $zero, end	#se $s2 contém zero, está na origem, e não deve imprimir o quadrante
	ori $a0, $s2,0		#caso esteja em algum quadrante, chega aqui e imprime $s2
	li $v0, 1			#imprimir inteiro
	syscall
end:
	li $v0, 10			#10 em $v0 para informar que o programa terminou
	syscall				#chama o S.O. para terminar o programa
	.data
str_eixo_x: .asciiz "eixo x "
str_eixo_y: .asciiz "eixo y "
