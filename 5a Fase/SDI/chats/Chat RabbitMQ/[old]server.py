#!/usr/bin/env python

import pika, threading

def callback(ch, method, properties, msg):
	ch.basic_publish(exchange='', routing_key='entrada', body=msg)
	print("enviando mensagem")

conexao = pika.BlockingConnection(pika.ConnectionParameters('127.0.0.1'))
canal = conexao.channel()

canal.queue_declare(queue='entrada')
canal.queue_declare(queue='saida')

print("Iniciando servidor.")

canal.basic_consume(callback, queue='saida', no_ack=True)
canal.start_consuming()

conexao.close()
