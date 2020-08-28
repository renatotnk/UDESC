#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
2018 @ SDI0001
Trabalho de SDI sobre Sockets em TCP,
realizado por Kleiton Pereira e Renato Tanaka.
'''

from socket import socket, AF_INET, SOCK_STREAM
from threading import Thread, Lock

# Função para receber os dados e imprimir na tela
def receber_dados():
	while True:
		mensagem = client_socket.recv(MTU)
		if mensagem == "exit":
			client_socket.close()
			break

		print mensagem
		

# Função que pede a entrada de dados e os envia para o servidor
def enviar_dados():
	nome = raw_input("Nome: ")
	client_socket.send(nome)
	while True:
		mensagem = raw_input(">>")
		client_socket.send(mensagem)
		if mensagem == "exit":
			break

# Parametros
host = 'sdi02'
port = 14643
MTU = 2048
semaforo = Lock()

# Criando o socket principal do cliente
client_socket = socket(AF_INET, SOCK_STREAM)
client_socket.connect((host, port))

# Começando as threads principais de recebimento e envio de dados
thread_receber = Thread(target=receber_dados)
thread_enviar = Thread(target=enviar_dados)
thread_receber.start()
thread_enviar.start()

