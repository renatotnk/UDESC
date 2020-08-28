#!/usr/bin/env python
# -*- coding: utf-8 -*-

import pika, threading, socket

def callback(ch, method, properties, body):
	print(body.decode())
	if not executando:
		ch.stop_consuming()

def recebe_dados():
	credentials = pika.PlainCredentials('aluno11', 'aluno11')
	conexao_entrada = pika.BlockingConnection(pika.ConnectionParameters('192.168.100.9', 5672, '/', credentials))
	canal_entrada = conexao_entrada.channel()
	minha_fila = "entrada_"+meu_id
	canal_entrada.queue_declare(queue=minha_fila)

	canal_entrada.basic_consume(callback, queue=minha_fila, no_ack=True)
	canal_entrada.start_consuming()

	canal_entrada.close()

nick = input('Escolha um nickname: ')

executando = True

TCP_IP = '192.168.100.9'
TCP_PORT = 5005
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))
s.send(nick.encode())
meu_id = s.recv(1024).decode()
s.close()
print("Seu id é: ", meu_id)

credentials = pika.PlainCredentials('aluno11', 'aluno11')
conexao_saida = pika.BlockingConnection(pika.ConnectionParameters('192.168.100.9', 5672, '/', credentials))
canal_saida = conexao_saida.channel()
canal_saida.queue_declare(queue='saida')

consumidor = threading.Thread(target=recebe_dados)
consumidor.start()

while True:
	dados = input()
	if dados.strip() == '':
		continue
	elif dados.strip() == 'exit':
		canal_saida.basic_publish(exchange='', routing_key='saida', body=str(meu_id)+"::"+"Saiu!")
		executando = False
		break
	else:
		canal_saida.basic_publish(exchange='', routing_key='saida', body=str(meu_id)+"::"+dados)

canal_saida.close()
