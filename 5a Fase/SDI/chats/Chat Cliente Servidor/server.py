#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
2018 @ SDI0001
Trabalho de SDI sobre Sockets em TCP e UDP, realizado por Kleiton Pereira e Renato Tanaka.
'''


from socket import socket, AF_INET, SOCK_DGRAM, SOCK_STREAM
from threading import Thread

# Criando Socket UDP
sock = socket(AF_INET, SOCK_DGRAM)

# Guardando as informações para conexão
host = 'sdi02'
port = 14643
MTU = 65536

# Ouvindo na porta definida
sock.bind((host, port))
print "Servidor iniciado na porta", port

# Loop principal
while True:
	# Recebendo dados do cliente
	data, addr = sock.recvfrom(MTU)
	# Imprimindo os dados recebidos e a resposta a ser enviada
	print "received:", data, "sending:", data.upper()
	# Enviando os dados para o cliente
	sock.sendto(data.upper(), addr)
