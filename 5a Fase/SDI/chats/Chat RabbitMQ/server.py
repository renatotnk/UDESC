#!/usr/bin/env python
# -*- coding: utf-8 -*-


import pika, random, socket, threading

def callback(ch, method, properties, msg):
	usuario = clientes[int(msg.decode().split("::")[0])]
	corpo = "::".join(msg.decode().split("::")[1:])
	for cliente in clientes.keys():
		nome_fila = 'entrada_' + str(cliente)
		ch.basic_publish(exchange='', routing_key=nome_fila, body=usuario + ": " + corpo)
	print("Enviando mensagem..")

def novo_cliente(nick, sock):
	id = random.randint(0, 500)
	while id in clientes.keys():
		id = random.randint(0, 500)

	clientes[id] = nick.decode()
	sock.send(str(id).encode())

def espera_novo_cliente():
	while executando:
		s.listen(1)
		conn, addr = s.accept()
		data = conn.recv(1024)
		data = data.rstrip()
		novo_cliente(data, conn)
		print ("Novo cliente: ", data)
	
	
	

executando = True

TCP_IP = '192.168.100.9'
TCP_PORT = 5005
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind((TCP_IP, TCP_PORT))

t = threading.Thread(target=espera_novo_cliente)
t.start()


# dicionario de clientes {id:'nick'}
clientes = {}

credentials = pika.PlainCredentials('aluno11', 'aluno11')
conexao = pika.BlockingConnection(pika.ConnectionParameters('192.168.100.9', 5672, '/', credentials))
canal = conexao.channel()
canal.queue_declare(queue='saida')

print ("Iniciando servidor...")

canal.basic_consume(callback, queue='saida', no_ack=True)
canal.start_consuming()

executando = False

conexao.close()
