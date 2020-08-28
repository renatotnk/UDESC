#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
2018 @ SDI0001
Trabalho de SDI sobre Sockets em TCP e UDP, realizado por Kleiton Pereira e Renato Tanaka.
'''


from socket import socket, AF_INET, SOCK_DGRAM, SOCK_STREAM


# Criando Socket UDP
sock = socket(AF_INET, SOCK_DGRAM)

# Guardando as informações para conexão
host = 'sdi02'
port = 14643
MTU = 65536

# Loop principal
while True:
	# Recebe os dados que serão enviados ao servidor
	data = raw_input(">>")
	# Caso os dados == "exit" então ele encerra o socket e termina o programa
	if data == "exit":
		sock.close()
		break

	# Caso a entrada contenha o caractere '*' o programa repetira o que esta a esquerda do * tantas vezes quanto o numero a direita
	# Ex: hello*3 == hellohellohello
	if "*" in data:
		data = data.split("*")[0] * int(data.split("*")[1])

	# Enviando os dados para o servidor
	sock.sendto(data, (host, port))
	# Esperando a resposta do servidor, tamanho do buffer == MTU
	response, addr = sock.recvfrom(MTU)
	# Imprimindo a resposta do servidor
	print len(response)
