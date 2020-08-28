#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys, random, threading
from heapq import *

# Função que implementa a impressão de um grafo
def imprime_grafo():
    # Percorre o dicionário e imprime os vértices e suas respectivas conexões
    '''for chave, valor in grafo.items():
        print ("Vértice %s -> %s" % (chave, ", ".join(valor)))'''
    for vertice, vizinhos in grafo.items():
        print(vertice) + " -> ",
        for vizinho in vizinhos:
            print("%s com peso %d  " % (vizinho['nome'], vizinho['peso'])),
	print("")
    print("")

def dijkstra(no_inicial, no_final, resultados, ind):
	g = grafo
	
	fila, visto, mins = [(0, no_inicial, [])], set(), {no_inicial: 0}
	while fila:
		(custo, v1, caminho) = heappop(fila)
		if v1 not in visto:
			visto.add(v1)
			#caminho = (v1, caminho)
                        caminho = caminho + [v1]
			if v1 == no_final:
				resultados[ind] = (custo, caminho)
				return (custo, caminho)		

			for vizinho in g[v1]:
				if vizinho['nome'] in visto:
					continue
				if vizinho['nome'] in mins.keys():
					prev = mins[vizinho['nome']]
				else:
					prev = None
				next = custo + vizinho['peso']
				if prev is None or next < prev:
					mins[vizinho['nome']] = next
					heappush(fila, (next, vizinho['nome'], caminho))
	
	resultados[ind] = custo			
	return float("inf")

# O grafo é inicializado por um dicionário vazio
grafo = {}

# FUNÇÃO MAIN()
if __name__ == "__main__":
	# O nome do arquivo que contém o grafo é passado como parâmetro, o grafo é então lido e construído
	with open(sys.argv[1], "r") as arquivo:
		for linha in arquivo:
		    linha = linha.replace("\n", "")
		    v1 = linha.split(" : ")[0]
		    v2 = [{'nome':x.split("|")[0], 'peso':int(x.split("|")[1])} for x in list(linha.split(" : ")[1].split(" "))]
		    grafo[v1] = v2


	imprime_grafo()
	no = raw_input("Nó elegido: ").strip()
	threads = [None] * len(grafo.keys())
	resultados = [None] * len(grafo.keys())

	vertices = list(grafo.keys())

	for i in range(len(vertices)):
		threads[i] = threading.Thread(target = dijkstra, args=(vertices[i], no, resultados, i))
		threads[i].start()

	for i in range(len(threads)):
		threads[i].join()

	for r in resultados:
		print "%d\t|\t%s" % (r[0], " -> ".join(r[1]))
	




