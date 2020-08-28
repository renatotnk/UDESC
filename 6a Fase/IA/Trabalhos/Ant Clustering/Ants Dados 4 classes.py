#!/usr/bin/python
# -*- coding: utf-8 -*-

import numpy as np
import matplotlib
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from copy import deepcopy

class Formiga:
	# Método construtor
	def __init__(self, fov, x, y):
		self.fov = fov
		self.posicao = [x, y]
		self.movimentos = ['esq', 'dir', 'cima', 'baixo']
		self.carregando = False
		self.obj_carregado = []

	# Função de movimento da formiga
	def mover(self):
		escolha = np.random.choice(self.movimentos)
		if escolha == 'esq':
			if self.posicao[0] > 0:
				self.posicao[0] -= 1
		elif escolha == 'dir':
			if self.posicao[0] < N-1:
				self.posicao[0] += 1
		elif escolha == 'cima':
			if self.posicao[1] > 0:
				self.posicao[1] -= 1
		else:
			if self.posicao[1] < N-1:
				self.posicao[1] += 1

	def dist(self, dado1, dado2):
		return np.sqrt((dado1[0] - dado2[0]) ** 2 + (dado1[1] - dado2[1]) ** 2)

	# Função que calcula a semelhanca da região interna do FOV da formiga
	def semelhanca_fov(self):
		global matriz
		x_inicial = max(0, self.posicao[0] - self.fov)
		x_final = min(N-1, self.posicao[0] + self.fov)
		y_inicial = max(0, self.posicao[1] - self.fov)
		y_final = min(N-1, self.posicao[1] + self.fov)
		somatorio = 0
		for x in range(x_inicial, x_final + 1):
			for y in range(y_inicial, y_final + 1):
				if matriz[x][y] != 0.0:
					if not self.carregando:
						somatorio += 1 - self.dist(matriz[self.posicao[0]][self.posicao[1]], matriz[x][y]) / ALPHA
					else:
						somatorio += 1 - self.dist(self.obj_carregado, matriz[x][y]) / ALPHA

		somatorio = somatorio / (self.fov**2)

		return max(0, somatorio)

	# Função que realiza as ações da formiga
	def agir(self):
		global matriz
		# Caso esteja carregando
		if self.carregando:
			# Caso carregando e se depara com espaço vazio
			if matriz[self.posicao[0]][self.posicao[1]] == 0.0:
				prob_largar = (self.semelhanca_fov() / (k2 + self.semelhanca_fov())) ** 2
				if np.random.rand() < prob_largar:
					self.carregando = False
					matriz[self.posicao[0]][self.posicao[1]] = deepcopy(self.obj_carregado)
		# Caso não esteja carregando
		else:
			# Caso não carregando e se depara com uma formiga morta
			if matriz[self.posicao[0]][self.posicao[1]] != 0.0:
				prob_pegar = (k1 / (k1 + self.semelhanca_fov())) ** 2
				if np.random.rand() < prob_pegar:
					self.carregando = True
					self.obj_carregado = matriz[self.posicao[0]][self.posicao[1]]
					matriz[self.posicao[0]][self.posicao[1]] = 0.0

		self.mover()


def matriz_plot(matriz_original):
	nova_matriz = deepcopy(matriz_original)
	for i in range(len(nova_matriz)):
		for j in range(len(nova_matriz[0])):
			if nova_matriz[i][j] != 0.0:
				nova_matriz[i][j] = nova_matriz[i][j][2]
			else:
				nova_matriz[i][j] = 0

	return nova_matriz

def gera_matriz(N):
	nova_matriz = [[] for i in range(N)]
	for i in range(N):
		for _ in range(N):
			nova_matriz[i].append(0.0)

	for _ in range(N_DADOS):
		linha = input().strip()
		linha = linha.split('\t')
		linha = [float(l.replace(',', '.')) for l in linha]

		nova_matriz[np.random.randint(N)][np.random.randint(N)] = deepcopy(linha)

	return nova_matriz

N = 75 # Dimensões da matriz
N_DADOS = 400
QNT_FORMIGAS = int((N*N)/25) # Número de agentes (formigas)
FOV_PADRAO = 2 # Raio do FOV padrão dos agentes
STEPS = 10000 # Número de iterações
ALPHA = 3.0 # Alpha usado na função de semelhanca
GAMMA = 0.35 # Probabilidade de cada ponto possuiruma formiga morta
k1, k2 = 1.0 , 1.0 # Definindo k1 e k2

#CORES = {1: , 2, 3, 4}
CORES = ['black', 'red', 'blue', 'magenta', 'yellow']
cmap = matplotlib.colors.ListedColormap(CORES, name='CORES', N=None)

#matriz = np.zeros((N, N)) # Inicializando a matriz com zeros
matriz = gera_matriz(N)

'''for x in range(N):
	for y in range(N):
		if np.random.rand() < GAMMA:
			matriz[x][y] = [np.random.randint(1, 10), np.random.randint(1, 10)]'''

formigas = []
for _ in range(QNT_FORMIGAS):
	formigas.append(Formiga(FOV_PADRAO, int(np.random.randint(0, N)), int(np.random.randint(0, N)))) # !!!FUTURO IMPLEMENTAR FORMIGAS NAO COLIDINDO!!!

plt.imsave('inicial.png', matriz_plot(matriz), cmap=cmap, dpi=400)
#plt.savefig('inicial.png', dpi=350)

for i in range(STEPS):
	for fmg in formigas:
		fmg.agir()

plt.imsave('final.png', matriz_plot(matriz), cmap=cmap, dpi=400)
#plt.savefig('final.png', dpi=350)
