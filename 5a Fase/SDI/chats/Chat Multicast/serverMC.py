#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
2018 @ SDI0001
Trabalho de SDI sobre Sockets em TCP,
realizado por Kleiton Pereira e Renato Tanaka.
'''

from socket import socket, AF_INET, SOCK_STREAM
from threading import Thread

# Cria nova thread para cada cliente novo
def criar_conexoes():
	while True:
		conn, addr = server_sock.accept()
		print "[!]Conexao recebida."
		print "[-]--> %s:%s" % (addr)
		conn.send("Servidor: Bem vindo ao chat!\nEscolha seu nick...")
		addr_lista[conn] = addr
		print "[-]Iniciando thread de comunicação."
		Thread(target=comunicacao, args=(conn,)).start()

# Gerencia comunicação entre um único cliente e o servidor
def comunicacao(soquete):
	nome = soquete.recv(MTU)
	soquete.send("Servidor: Seja bem-vindo %s!" % (nome))
	multicast("%s entrou para o chat." % (nome), nick="Servidor")
	client_lista[soquete] = nome

	while True:
		mensagem = soquete.recv(MTU)
		if mensagem != "exit":
			multicast(mensagem, nick=nome)
		else:
			soquete.send("exit")
			soquete.close()
			del client_lista[soquete]
			break

def multicast(mensagem, nick="NaN"):
	for sock in client_lista:
		sock.send(nick+": "+mensagem)

# Criando dicionários que armazenarão os endereços e os clientes
client_lista = {}
addr_lista = {}

# Parametros
host = 'sdi02'
port = 14643
MTU = 2048

# Criando o socket principal do servidor
server_sock = socket(AF_INET, SOCK_STREAM)
server_sock.bind((host, port))

# Iniciando o servidor
server_sock.listen(5)
print("[!]Servidor iniciado na porta %d." % (port))

# Começa a thread principal e aguarda os retornos
aceitar_thread = Thread(target=criar_conexoes)
aceitar_thread.start()
aceitar_thread.join()
server_sock.close()



