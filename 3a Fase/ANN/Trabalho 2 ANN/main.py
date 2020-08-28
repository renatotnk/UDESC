#!/usr/bin/python
# -*- coding: utf-8 -*-

import numpy as np
import sys 
# Primeira função e suas derivadas parciais
def f1(x1, x2, derivada=False, dx=1):
	if derivada:
		if dx == 1:
			return -2 * x1 - np.exp(-x1)
		if dx == 2:
			return np.exp(x2) - 6*(x2** 2)

	return np.exp(-x1) + np.exp(x2) - x1 ** 2 - 2*(x2**3)

# Segunda função e suas derivadas parciais
def f2(x1, x2, p, derivada=False, dx=1):
	if derivada:
		if dx == 1:
			return p - np.sin(x1 + p*x2)
		if dx == 2:
			return -p*np.sin(x1 + p*x2) - 1

	return np.cos(x1 + p*x2) + p*x1 - x2 -1

# Chute inicial e p

#x1,x2 = 0,1
#x1, x2 = 6, 6
if len(sys.argv) < 3:
	print "Por favor, forneca 2 pontos iniciais como entrada da funcao"
	exit()  
x1 = int(sys.argv[1])
x2 = int(sys.argv[2])
p = 10
erro = 0

for i in range(1000):
	# Cria matriz x1 e x2
	xk = np.matrix([[x1],[x2]])
	# Cria matriz Jacobiana
	jacobi = np.matrix([
		[f1(x1, x2, derivada=True, dx=1), f1(x1, x2, derivada=True, dx=2)],
		[f2(x1, x2, p, derivada=True, dx=1), f2(x1, x2, p, derivada=True, dx=2)]
	])
	# Encontra a inversa da matriz Jacobiana
	jacobi_inv = np.linalg.inv(jacobi)
	# Cria a matriz das funções
	matriz_f = np.matrix([[f1(x1, x2)],[f2(x1, x2, p)]])
	# Encontra os valores de xk+1
	xk = xk - np.matmul(jacobi_inv, matriz_f)
	# Encontrando o erro absoluto
	erro = max(abs(xk.item(0) - x1), abs(xk.item(1) - x2))
	# Atribui os novos valores
	x1 = xk.item(0)
	x2 = xk.item(1)

	# Imprimindo as aproximações e o erro
	print "Iteração: %d    x1: %f    x2: %f    Erro: %f" % (i + 1, x1, x2, erro)

# Imprimindo as aproximações finais
print "%.14f"  % f1(x1, x2)
print "%.14f" % f2(x1, x2, p)

print x1, x2
	

'''
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
import numpy as np


X = range(40)
Y = range(40)
X, Y = np.meshgrid(X, Y)

# Plotando a primeira curva
fig = plt.figure()
ax = fig.gca(projection='3d')
Z = f1(X, Y)
surf = ax.plot_surface(X, Y, Z, cmap=cm.coolwarm, linewidth=0, antialiased=True)
plt.show()

# Plotando a segunda curva
fig = plt.figure()
ax = fig.gca(projection='3d')
Z = f2(X, Y, p)
surf = ax.plot_surface(X, Y, Z, cmap=cm.coolwarm, linewidth=0, antialiased=True)
plt.show()
'''









