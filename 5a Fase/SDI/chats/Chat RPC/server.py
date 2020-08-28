#!/usr/bin/python
# -*- coding: utf-8 -*-

from SimpleXMLRPCServer import SimpleXMLRPCServer
import random, time, sys

# Inicia a lista de clientes conectados
clientes = {'nicks': {}, 'ids': {}}

# Adiciona o servidor como pseudo cliente
clientes['ids'][-1] = {'nick': 'Servidor'}
clientes['nicks']['Servidor'] = -1

# Inicia a lista de mensagens com uma mensagem de bem-vindo padrão
mensagens = [{ 'id': '0', 'nick': 'Servidor', 'msg':'Bem-vindo ao servidor.' }]


# Função que inicia uma sessão com um cliente
def comeca_sessao(nick):
	if nick == 'Servidor' or nick in clientes['nicks']:
		return False

	id = random.randint(0, 150)
	while id in clientes['ids']:
		id = random.randint(0, 150)

	clientes['nicks'][nick] = id
	clientes['ids'][id] = {'nick': nick}
	multicast(-1, nick + " acabou de entrar.")
	return id

# Função que finaliza uma sessão com um cliente através do id
def finaliza_sessao(id):
	if id in clientes['ids']:
		multicast(-1, clientes['ids'][id]['nick'] + " acabou de sair")
		del(clientes['nicks'][clientes['ids'][id]['nick']])
		del(clientes['ids'][id])	
	
	return True

# Função que faz o multicast de uma mensagem para todos os clientes
def multicast(id, msg):
	global ID_MSG

	if id not in clientes['ids']:
		return False

	nick = clientes['ids'][id]['nick']

	mensagens.append({'id': str(ID_MSG), 'nick': nick, 'msg': msg})
	ID_MSG += 1

	return True

# Função que retorna as mensagens em uma lista a partir de um id
def get_mensagens(id, ultimo_id):
	if id not in clientes['ids']:
		return []

	return [m for m in mensagens if int(m['id']) >= ultimo_id]

# Função que retorna os usuários conectados
def get_usuarios(id):
	if id not in clientes['ids']:
		return []

	return clientes['nicks'].keys()


# Variavel que é utilizada para marcar o id atual das mensagens (inicia em 1 pois a mensagem 0 é a padrão do servidor
ID_MSG = 1

# Porta de conexão
porta = 10001
# Inicia um servidor simples RPC no IP e na Porta especificada (sdi02)
servidor = SimpleXMLRPCServer(('192.168.100.9', porta))
# Inicializa as funções padrão
servidor.register_introspection_functions()

# Registra as funções criadas a cima com seus pseudonimos 
servidor.register_function(comeca_sessao, 'Session.start')
servidor.register_function(finaliza_sessao, 'Session.end')
servidor.register_function(multicast, 'Chat.post')
servidor.register_function(get_mensagens, 'Chat.get')
servidor.register_function(get_usuarios, 'Chat.getUsers')
#########################################################

try:
	servidor.serve_forever()
except KeyboardInterrupt, e:
	exit()	
