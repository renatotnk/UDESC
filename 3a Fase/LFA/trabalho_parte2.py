#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys, os

#@Classe de cores para o terminal
class cores:
	if os.name == "nt":
		AZUL = ''
		VERDE = ''
		AMARELO = ''
		VERMELHO = ''
		BOLD = ''
		FIM = ''
	else:
		AZUL = '\033[94m'
		VERDE = '\033[92m'
		AMARELO = '\033[93m'
		VERMELHO = '\033[91m'
		BOLD = '\033[1m'
		FIM = '\033[0m'

#@Checa se foi passado um arquivo
if len(sys.argv) < 2:
    print """Copyright (c) 2017 Kleiton Pereira & Renato Tanaka
Testador de Autômatos Finitos Determinísticos v1.0
Usage: python arquivo.py <nome_do_arquivo.afd>"""
    exit()

#@Classe de transição
class Transicao(object):
	#@Inicialização
	def __init__(self,e_t,s,e_c):
		self.est_atual = e_t
		self.simbolo = s
		self.est_chegada = e_c
	
	#@Ferramenta para testes
	def debug(self):
		print self.est_atual + " lendo " + self.simbolo + " vai para " + self.est_chegada

#@Variáveis globais para reuso em diversas partes do código
#####################
estado_inicial = ''
n_estados = 0
estados = []
n_estados_finais = 0
estados_finais = []
n_termos = 0
alfabeto = []
n_transicoes = 0
transicoes = []
#####################

#@Função de leitura dos arquivos
def leitura(f):
	#######################
	global estado_inicial
	global n_estados
	global estados
	global n_estados_finais
	global estados_finais
	global n_termos
	global alfabeto
	global n_transicoes
	global transicoes
	#######################	

	arquivo = str(f)

	afd_input = open(arquivo,"r")
	afd_linhas = afd_input.read().split("\n")
	estado_inicial = afd_linhas[0]
	n_estados = int((afd_linhas[1]).split(" ")[0])
	estados = []
	for i in range(1,n_estados + 1):
		estados.append(afd_linhas[1].split(" ")[i])

	n_estados_finais = int((afd_linhas[2]).split(" ")[0])
	estados_finais = []
	for i in range(1,n_estados_finais + 1):
		estados_finais.append(afd_linhas[2].split(" ")[i])

	n_termos = int((afd_linhas[3]).split(" ")[0])
	alfabeto = []
	for i in range(1,n_termos + 1):
		alfabeto.append(afd_linhas[3].split(" ")[i])

	n_transicoes = int((afd_linhas[4]))
	transicoes = []
	for linha in afd_linhas[5:-1]:
		l_split = linha.split(" ")
		transicoes.append(Transicao(l_split[0],l_split[1],l_split[2]))

	print "AUTÔMATO CARREGADO COM " + cores.VERDE + cores.BOLD + "SUCESSO!" + cores.FIM + "\n"

#@Armazenando o nome original para uso posterior
nome_original = sys.argv[1]
#@Le o arquivo bruto
leitura(sys.argv[1])
print "\n"

#@Checando se o arquivo é um AFN
if (sys.argv[1].endswith(".afn")):
	#@Função do conjunto das partes
	def conjunto_das_partes(conj):
		r = []
		x = len(conj)
		for i in range(1 << x):
			r.append([conj[j] for j in range(x) if (i & (1 << j))])
		return r

	print "ARQUIVO IDENTIFICADO COMO " + cores.AMARELO + cores.BOLD + "AFN" + cores.FIM
	print "COMEÇANDO CONVERSÃO...\n"
				
	#@Começando a conversão de AFN para AFD
	novos_estados = conjunto_das_partes(estados)
	str_estados = [''.join(x) for x in novos_estados[1:]]

	novas_transicoes = []
	
	for est in novos_estados[1:]:
		for simb in alfabeto:
			temp = []
			for e in est:
				for t in transicoes:
					if (t.est_atual == e) and (t.simbolo == simb):
						temp.append(t.est_chegada)
			if(len(temp) > 0):
				novas_transicoes.append(Transicao(''.join(est),simb,''.join(temp)))
	
	novos_estados_finais = []
	for est in str_estados:
		for est_f in estados_finais:
			if (est_f in est) and (est not in novos_estados_finais):
				novos_estados_finais.append(est)		

	#@Escrevendo no arquivo para escrita
	novo_arquivo = estado_inicial + "\n" + str(2**n_estados - 1) + " " + " ".join(str_estados) + "\n" + str(len(novos_estados_finais)) + " " + " ".join(novos_estados_finais) + "\n" + str(n_termos) + " " + " ".join(alfabeto) + "\n" + str(len(novas_transicoes)) + "\n"
	
	for t in novas_transicoes:
		novo_arquivo = novo_arquivo + t.est_atual + " " + t.simbolo + " " + t.est_chegada + "\n"
	
	#@Escrevendo o arquivo com estados inuteis .afd
	nome = "com_estados_inuteis_"+sys.argv[1][:-4]+".afd"
	f = open(nome,"w")
	print "SALVANDO O AFD EQUIVALENTE NÃO OTIMIZADO EM: " + cores.AMARELO + cores.BOLD + nome + cores.FIM
	f.write(novo_arquivo)
	f.close()
	print "ARQUIVO " + cores.AZUL + cores.BOLD + "SALVO\n" + cores.FIM
	
	#@Recarregando o autômato, como agora se trata de um AFD serão removidos seus estados inuteis no próximo passo
	sys.argv[1] = nome
	print "RECARREGANDO AUTÔMATO..."
	leitura(nome)
	print "\n"


#@Checando se o arquivo é um AFD para começar a retirada de estados inúteis
if (sys.argv[1].endswith(".afd")):
	print "ARQUIVO IDENTIFICADO COMO " + cores.AMARELO + cores.BOLD + "AFD" + cores.FIM
	print "COMEÇANDO REMOÇÃO DE ESTADOS INÚTEIS...\n"
	#@Retirando estados não alcançáveis à partir do estado inicial
	estados_alcancaveis = [estado_inicial]
	temp = len(estados_alcancaveis)
	for simb in alfabeto:
		for est in estados_alcancaveis:
			for t in transicoes:
				if (est == t.est_atual) and (simb == t.simbolo):
					if not (t.est_chegada) in estados_alcancaveis:
						estados_alcancaveis.append(t.est_chegada)

	while(len(estados_alcancaveis) != temp):
		temp = len(estados_alcancaveis)
		for simb in alfabeto:
			for est in estados_alcancaveis:
				for t in transicoes:
					if (est == t.est_atual) and (simb == t.simbolo):
						if not (t.est_chegada) in estados_alcancaveis:
							estados_alcancaveis.append(t.est_chegada)

	#@Retirando estados que não chegam ao estado final
	#@O [:] serve para indicar que é uma cópia e portanto não deve ser interpretada com global
	estados_que_alcancam = estados_finais[:]
	temp = len(estados_que_alcancam)
	for simb in alfabeto:
		for est in estados_que_alcancam:
			for t in transicoes:
				if (est == t.est_chegada) and (simb == t.simbolo):
					if not (t.est_atual) in estados_que_alcancam:
						estados_que_alcancam.append(t.est_atual)

	while(len(estados_que_alcancam) != temp):
		temp = len(estados_que_alcancam)
		for simb in alfabeto:
			for est in estados_que_alcancam:
				for t in transicoes:
					if (est == t.est_chegada) and (simb == t.simbolo):
						if not (t.est_atual) in estados_que_alcancam:
							estados_que_alcancam.append(t.est_atual)
	
	#@Removendo os estados inúteis
	estados_uteis = list(set(estados_que_alcancam).intersection(estados_alcancaveis))
	estados_finais_final = []
	for est in estados_uteis:
		for est_f in estados_finais:
			if (est_f in est) and not(est in estados_finais_final):
				estados_finais_final.append(est)

	transicoes_final = []
	for t in transicoes:
		if (t.est_atual in estados_uteis) and (t.est_chegada in estados_uteis):
			transicoes_final.append(t)
	
	#@Criando o arquivo à ser gravado
	arquivo_final = estado_inicial + "\n" + str(len(estados_uteis)) + " " + " ".join(estados_uteis) + "\n" + str(len(estados_finais_final)) + " " + " ".join(estados_finais_final) + "\n" + str(n_termos) + " " + " ".join(alfabeto) + "\n" + str(len(transicoes_final)) + "\n"

	for t in transicoes_final:
		arquivo_final = arquivo_final + t.est_atual + " " + t.simbolo + " " + t.est_chegada + "\n"
	print "FORAM REMOVIDOS " + str(len(estados) - len(estados_uteis)) + " ESTADOS"

	nome = "sem_estados_inuteis_"+nome_original[:-4]+".afd"
	print "SALVANDO O AFD EQUIVALENTE NÃO OTIMIZADO EM: " + cores.AMARELO + cores.BOLD + nome + cores.FIM
	f = open(nome, "w")
	f.write(arquivo_final)
	f.close()
	print "ARQUIVO " + cores.AZUL + cores.BOLD + "SALVO\n" + cores.FIM

	print "RECARREGANDO AUTÔMATO..."
	leitura("sem_estados_inuteis_"+nome_original[:-4]+".afd")


#@Processamento do novo autômato otimizado
while True:
	try:
		palavra = list(raw_input(cores.AMARELO + ">>" + cores.FIM + "Insira a palavra (Ctrl + C para encerrar): "))
		cabecote = estado_inicial
		contador = 0
		indeterminacao = False
		for p in palavra:
		    for t in transicoes:
			if (t.est_atual == cabecote) and (t.simbolo == p):
			    cabecote = t.est_chegada
			    print cores.AZUL + t.est_atual + cores.FIM + " lendo " + cores.AMARELO + t.simbolo + cores.FIM + " vai para " + cores.AZUL + t.est_chegada + cores.FIM
			    break
			contador += 1
			if contador == (n_transicoes):
			    indeterminacao = True
		    contador = 0
		    if indeterminacao:
			cabecote = ""
			print "Morte por indefinição!"
			break


		if cabecote in estados_finais:
		    print cores.BOLD + cores.VERDE + "Palavra aceita!" + cores.FIM
		else:
		    print cores.BOLD + cores.VERMELHO + "Palavra rejeitada!" + cores.FIM
	except KeyboardInterrupt:
		print "\n\nPAREM AS MÁQUINAS!"
		sys.exit(0)
