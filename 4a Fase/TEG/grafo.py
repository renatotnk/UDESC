#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
Algoritmo que implementa os conceitos vistos nas aulas de Teoria dos Grafos
da UDESC-CCT 2018-02
Aqui estão implementados os exercícios 2, 3 e 4
Autores: Kleiton Pereira e Renato Tanaka @ 2018
'''

import sys, random
from heapq import *
#import numpy as np

# Função que implementa a criação de um vértice
def cria_vertice(vertice):
    # Caso o vértice já exista uma mensagem é exibida
    if vertice in grafo.keys():
        print ("O vértice já existe.")
    else:
        # Inicializa no dicionário uma nova chave e a inicia com lista de arestas vazia
        grafo[vertice] = []

# Função que implementa a remoção de um vértice
def remove_vertice(vertice):
    # Caso o vértice não exista uma mensagem é exibida
    if vertice not in grafo:
        print ("A aresta não pertence ao grafo")
    else:
        # Remove do grafo o vértice escolhido
        grafo.pop(vertice)

# Função que implementa a criação de uma aresta
def cria_aresta(vertice1, vertice2):
    # Caso a aresta já exista uma mensagem é exibida
    if (vertice2 in grafo[vertice1]):
        print("A aresta já existe.")
    # Caso o primeiro vértice já exista a aresta é colocada na lista de arestas
    elif (vertice1 in grafo.keys()):
        grafo[vertice1].append(vertice2)
    # Caso o primeiro vértice não exista ele é criado e a nova aresta
    # é colocada na sua lista de arestas
    elif (vertice2 in grafo.keys()):
        grafo[vertice1] = [vertice2]
    # Caso nenhum vértice exista uma mensagem de erro é exibida
    else:
        print ("A conexão não pode ser feita pois os vértices não existem.")

# Função que implementa a remoção de uma aresta
def remove_aresta(vertice, aresta):
    # Caso a aresta não exista uma mensagem é exibida
    if(aresta not in grafo[vertice]):
        print("A aresta não existe.")
    # Caso a aresta exista ela é removida da lista de arestas
    else:
        grafo[vertice].remove(aresta)

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

#Função que imprime a matriz de adjacência do grafo
def matriz_adjacencia():
	nomes_vertices = sorted(grafo.keys())
	#Fazendo a correlacao entre nomes de vértices e seus respectivos índices
	indices_vertices = dict(zip(nomes_vertices, range(len(nomes_vertices))))
	#Cria uma matriz zerada com dimensões equivalentes ao número de vértices do grafo
	matriz_adj = np.zeros((len(grafo.keys()),len(grafo.keys())))
	#Percorrendo o grafo para preencher a matriz de adjacência
	for i in range(len(nomes_vertices)):
		for j in range(i, len(grafo.keys())):
			for k in grafo[nomes_vertices[i]]:
				j = indices_vertices[k]			
				matriz_adj[i][j] = 1 	
	print (matriz_adj)
# Função que determina se um grafo é conexo
def conexo(v_encontrados=None, v_inicial=None, g=None):
    # Caso não seja especificado um grafo a função busca o grafo padrão (lido do arquivo)
    if g is None:
        g = grafo
    # Caso não haja lista prévia de vértices encontrados ela é
    # inicializada como um conjunto vazio
    if v_encontrados is None:
        v_encontrados = set()
    # Recupera os vértices do grafo
    vertices = list(grafo.keys())
    # Caso não seja definido um vértice inicial o primeiro da lista é escolhido
    if not v_inicial:
        v_inicial = vertices[0]
    # Insere o primeiro vértice na lista de vértices encontrados
    v_encontrados.add(v_inicial)
    # Caso todos os nós ainda não tenham sido encontrados inicia o loop
    if len(v_encontrados) != len(vertices):
        # Para cada vértice vizinho do vértice inicial se ele ainda não tiver
        # sido vizitado há então uma chamada recursiva usando esse vértice como
        # vértice inicial, e assim é percorrido todo o grafo
        for vertice in grafo[v_inicial]:
            if vertice not in v_encontrados:
                if conexo(v_encontrados, vertice, g):
                    return True
    # Caso todos os nós tenham sido percorridos e encontrados retorna-se True (o grafo é conexo)
    else:
        return True

    # Caso não haja mais vértices, porém nem todos puderam ser alcançados, o grafo não é conexo
    return False

# Retorna a lista de componentes conectados do grafo
def componentes(g):
    # Inicializa a lista de nós visitados como um conjunto vazio
    visitado = set()
    # Inicializa a lista de componentes como uma lista vazia
    resultado = []
    # Para cada vértice do grafo se o vértice não foi visitado é então encontrado seu grupo conectado
    for vertice in g:
        if vertice not in visitado:
            grupo, visitado = grupo_conectado(vertice, visitado)
            resultado.append(grupo)

    # Retorna a lista de componentes
    return resultado

# Função que encontra grupos conectados a partir de um vértice
def grupo_conectado(vertice, visitado):
    # Inicializa a lista de grupos como uma lista vazia
    resultado = []
    # Inicializa a lista de vértices com o vértice inicial
    vertices = set([vertice])
    # Enquanto restarem vértices a serem percorridos um vértice é selecionado
    # e removido, ele então é inserido na lista de vértices visitados e, então
    # a lista de vértices é definida pela união da própria lista com os grafos vizinhos
    # do vértice atual tirando os nós já visitados
    while vertices:
        vertice = vertices.pop()
        visitado.add(vertice)
        vertices = vertices or set(grafo[vertice]) - visitado
        resultado.append(vertice)

    #o grupo conectado é então retornado, juntamente com os vértices visitados durante a operação
    return resultado, visitado

# Retorna uma lista de tuplas que indicam as conexões do grafo
def adjacentes(g):
    # Inicializa a lista de conexões como uma lista vazia
    conexoes = []
    # Para cada vértice do grafo é adicionada à lista uma tupla com os vértices que compõem uma aresta
    for vertice in g:
        for aresta in g[vertice]:
            conexoes.append((vertice, aresta))

    # Retorna a lista de conexões
    return conexoes

# Função que encontra os nós que possuem grau ímpar (UTILIZADO NO ALGORITMO DE FLEURY)
def encontra_nos_impares():
    # Cria lista de nós ímpares
    nos_impares = []
    # Para cada vértice do grafo
    for vertice in grafo:
        if len(grafo[vertice]) % 2 != 0:
            nos_impares.append(vertice)

    return nos_impares

# Função que verifica se um grafo é conectado utilizando BFS (busca em largura)
def grafo_conectado(g=None):
    # Caso não seja especificado um grafo a função busca o grafo padrão (lido do arquivo)
    if g is None:
        g = grafo
    # Pega o primeiro vértice da lista de vértices do grafo
    no_inicial = list(g.keys())[0]
    # Cria um dicionário de vértices e atribui a cor branco para todos
    cor = {v: 'branco' for v in g.keys()}
    # Atribui a cor cinza para o primeiro vértice
    cor[no_inicial] = 'cinza'
    # Inicializa a lista de nós vizitados com o primeiro vértice
    S = [no_inicial]
    # Enquanto há nós sendo vizitados
    while len(S) != 0:
        # Remove o primeiro vértice da lista
    	vertice = S.pop()
        # Para cada vértice vizinho do vértice analizado:
    	for v in g[vertice]:
            # Caso sua cor seja branca ele é marcado como vizitado e é pintado de cinza
    		if cor[v] == 'branco':
    			cor[v] = 'cinza'
    			S.append(v)
            # Pinta o vértice vizitado de preto
    		cor[vertice] = 'preto'

    # Caso todos os vértices estejam pintados de preto ao final da execução
    # a função retorna True, caso contrário retorna False
    return list(cor.values()).count('preto') == len(g.keys())

# Função que implementa o algoritmo de Fleury para encontrar um caminho Euleuriano no grafo
def fleury():
    # Inicializa um grafo auxiliar como uma cópia do grafo principal
    grafo_auxiliar = grafo.copy()
    # Encontra os nós ímpares
    nos_impares = encontra_nos_impares()
    # Caso o número de nós ímpares seja 1 ou > 2 o grafo não é euleriano ou caso o grafo não seja conectado
    if len(nos_impares) == 1 or len(nos_impares) > 2 or not grafo_conectado(grafo):
        return "O grafo não é euleriano."
    # Caso contrário inicia o algoritmo
    else:
        # Inicializa a lsita do caminho euleuriano como uma lista vazia
        caminho = []
        # Caso hajam exatamente 2 nós ímpares, um nó ímpar sempre é escolhido
        if len(nos_impares) == 2:
            v = nos_impares[0]
        # Caso contrário o primeiro nó inserido no grafo é selecionado
        else:
            v = list(grafo_auxiliar)[0]

        # Enquanto houverem nós a serem analizados no grafo:
        while len(adjacentes(grafo_auxiliar)) > 0:
            # O vértice é escolhido como nó atual
            no_atual = v
            # Para cada vértice vizinho do vértice escolhido esse vizinho é removido do grafo
            # auxiliar, então é checado se esse vértice removida era uma ponte, se era outro
            # vértice é escolhido para ser retirado e a ponte é reinserida no grafo
            for v in grafo_auxiliar[no_atual]:
                grafo_auxiliar[no_atual].remove(v)
                grafo_auxiliar[v].remove(no_atual)
                ponte = not grafo_conectado(g=grafo_auxiliar)
                if ponte:
                    grafo_auxiliar[no_atual].append(v)
                    grafo_auxiliar[v].append(no_atual)
                else:
                    break

            # Caso todos os nós vizinhos sejam pontes o vértice em si é removido do grafo auxiliar
            if ponte:
                grafo_auxiliar[no_atual].remove(v)
                grafo_auxiliar[v].remove(no_atual)
                grafo_auxiliar.pop(no_atual)
            # A tupla de vértices é então inserida no caminho
            caminho.append((no_atual, v))

    # Ao fim da execução um caminho Euleriano é retornado
    return caminho

def hamiltoniano(g = None, v_inicial = None, caminho = []):
		if g is None:
			g = grafo
		if v_inicial is None:
			v_inicial = g.keys()[0]
		print ("TSP chamado , no vertice %s, caminho atual: %s" % (v_inicial, " ".join(caminho)))
		if v_inicial not in set(caminho):
			caminho.append(v_inicial)
			if len(caminho) == len(g.keys()):
				if caminho is not None:
					caminho.append(caminho[0])				
				return caminho
			for v_proximo in g[v_inicial]:
				backup_caminho = [v for v in caminho]
				candidato = hamiltoniano(g, v_proximo, backup_caminho)
				if candidato is not None:
					return candidato			


def DFS(g = None, v_inicial = None):
	if g is None:
		g = grafo
	if v_inicial is None:
		g = grafo.keys()[0]

	pilha = [v_inicial]
	caminho = []
	
	while pilha:
		vertice = pilha.pop()
		if vertice in caminho:
			continue
		caminho.append(vertice)
		for vizinho in g[vertice]:
			pilha.append(vizinho)

	print " ".join(caminho)


def BFS(g = None, v_inicial = None):
	if g is None:
		g = grafo
	if v_inicial is None:
		g = grafo.keys()[0]		
	fila = [v_inicial]
	visitado = [v_inicial]

	while fila:
		v_inicial = fila.pop(0)
		
		print (v_inicial), 

		for vertice in g[v_inicial]:
			if vertice not in visitado:
				fila.append(vertice)
				visitado.append(vertice)	

def dijkstra(no_inicial, no_final):
	g = grafo
	
	fila, visto, mins = [(0, no_inicial, [])], set(), {no_inicial: 0}
	while fila:
		(custo, v1, caminho) = heappop(fila)
		if v1 not in visto:
			visto.add(v1)
			#caminho = (v1, caminho)
                        caminho = caminho + [v1]
			if v1 == no_final:
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

    ################################################ FUNÇÕES ################################################
	imprime_grafo()
	print dijkstra("s", "v")
	
    #########################################################################################################


