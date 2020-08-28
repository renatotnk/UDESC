#!/usr/bin/env python

import pika, threading

def callback(ch, method, properties, body):
	print("[x] Received %r" % body)

def recebe_dados(canal):
	print ("comecei")
	canal.basic_consume(callback, queue='entrada', no_ack=True)
	canal.start_consuming()

conexao = pika.BlockingConnection(pika.ConnectionParameters(host='127.0.0.1'))
canal_saida = conexao.channel()
canal_saida.queue_declare(queue='saida')
canal_entrada = conexao.channel()
canal_entrada.queue_declare(queue='entrada')

consumidor = threading.Thread(target=recebe_dados, args=(canal_entrada,))
consumidor.start()

while True:
	dados = input()
	if dados.strip() == '':
		continue
	elif dados == 'exit':
		break
	else:
		canal_saida.basic_publish(exchange='', routing_key='saida', body=dados)


conexao.close()
