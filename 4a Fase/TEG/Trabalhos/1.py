#!/usr/bin/python
#-*- coding: utf-8 -*-
from __future__ import print_function
import operator
import numpy as np
import networkx as nx
from time import sleep
from termcolor import colored
import matplotlib.pyplot as plt

cores = ['red', 'green', 'grey', 'yellow', 'blue', 'magenta', 'cyan', 'white']

def sublist(lst1, lst2):
	for i in lst1:
		if i not in lst2:
			return False

	return True


def DFS(g = None, v_inicial = None):
	if g is None:
		g = grafo

	if v_inicial is None:
		v_inicial = grafo[np.random.randint(0, N)].id

	pilha = [v_inicial]
	caminho = []
	
	while pilha:
		vertice = pilha.pop()
		if vertice in caminho:
			continue
		caminho.append(vertice)
		print(vertice, end=" ")
		sleep(0.2)

		for vizinho in [x[0] for x in g[vertice].vizinhos]:
			pilha.append(vizinho)

		if sublist([x[0] for x in g[vertice].vizinhos], caminho) == 0:
			print("")

	print("")

	#print (" ".join([str(x) for x in caminho]))


def BFS(g = None, v_inicial = None):
	if g is None:
		g = grafo

	if v_inicial is None:
		v_inicial = grafo[np.random.randint(0, N)].id
		
	fila = [v_inicial]
	visitado = [v_inicial]
	
	v_raiz = v_inicial
	v_bckp = v_inicial

	cor_atual = np.random.choice(cores)
	caminho = []

	print (colored(v_inicial, cor_atual, attrs=["bold"]))
	sleep(0.2)

	nova_cor = np.random.choice(cores)
	while nova_cor == cor_atual:
		nova_cor = np.random.choice(cores)
	cor_atual = nova_cor

	while fila:
		v_inicial = fila.pop(0)
		
		if v_inicial != v_raiz:
			#print (cor_atual + v_inicial + '\033[0m', end=" ")
			print(colored(v_inicial, cor_atual, attrs=["bold"]), end=" ")
			caminho.append(v_inicial)
			sleep(0.2)

		if set([x[0] for x in g[v_bckp].vizinhos]) == set(caminho):
			print("")
			v_bckp = v_inicial
			nova_cor = np.random.choice(cores)
			while nova_cor == cor_atual:
				nova_cor = np.random.choice(cores)
			cor_atual = nova_cor
		
		for vertice in [x[0] for x in g[v_inicial].vizinhos]:	
			if vertice not in visitado:
				fila.append(vertice)
				visitado.append(vertice)
	print()


class No:
	def __init__(self, x, y, no_id):
		self.x = x
		self.y = y
		self.id = no_id
		self.vizinhos = []

	def imprime(self):
		print("id: %d | x: %f | y: %f | vizinhos: %s" % (self.id, self.x, self.y, " ".join([str(x[0]) for x in self.vizinhos])))

N = int(raw_input("Qual o número de vértices? "))
K = int(np.log2(N))
grafo = []
for i in range(N):
	grafo.append(No(np.random.rand(), np.random.rand(), i))

for no_inicial in grafo:
	vizinhos = {}
	for no_alvo in grafo:
		if no_inicial.id != no_alvo.id:
			vizinhos[no_alvo.id] = np.sqrt((no_inicial.x - no_alvo.x)**2 + (no_inicial.y - no_alvo.y)**2)

	vizinhos = sorted(vizinhos.items(), key=operator.itemgetter(1))
	no_inicial.vizinhos = vizinhos[0:K]

for no in grafo:
	no.imprime()

print("Busca em profundidade")
DFS()
print("-"*25)
print("Busca em largura")
BFS()

'''
# Plotando o grafo
if N <= 50:
	G_1 = nx.DiGraph()
	lista_arestas = []
	for no in grafo:
		for v in vizinhos:
			lista_arestas.append([no.id, v[0]])
	G_1.add_edges_from(lista_arestas)
	pos = {i: (grafo[i].x, grafo[i].y) for i in range(len(grafo))}
	plt.axis('on')
	plt.ylim(0.0, 1.1)
	plt.xlim(0.0, 1.1)
	nx.draw(G_1, pos, with_labels=True)
	plt.show()'''

