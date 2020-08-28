#!/usr/bin/python
# -*- coding: utf-8 -*-

import xmlrpclib as rpc
import sys, curses, threading, time, socket

# Classe que controla a interface do terminal
class Interface(object):
	# Inicia o modulo curses
	def _init_curses(self):
		self.scr = curses.initscr()

	# Encerra o modulo curses
	def _end_curses(self):
		curses.endwin()

	# Imprime algo na tela
	def imprime_texto(self, y, x, msg):
		try:
			self.scr.addstr(y, x, msg)
			return True
		except curses.error:
			return False

	# Instancia a classe com um nick e imprime uma requisição de entrada
	def __init__(self, nick):
		self._init_curses()
		self.nick = nick
		self.mensagens = []
		self.imprime_texto(0, 0, nick + ' > ')

	# Captura efetivamente a entrada do usuario
	def entrada(self):
		inicio = len(self.nick) + 3
		msg = self.scr.getstr(0, inicio)
		self.imprime_texto(0, inicio, ' ' * len(msg))
		self.scr.refresh()
		return msg

	# Limpa as mensagens da tela
	def limpar_mensagens(self):
		i = 1
		for caractere in self.mensagens:
			if not self.imprime_texto(i, 0, ' ' * len(caractere)):	
				break
			i += 1

	# Escreve as mensagens na tela
	def escrever_mensagens(self):
		i = 1
		for mensagem in self.mensagens:
			if not self.imprime_texto(i, 0, mensagem):
				break
			i += 1

	# Ciclo principal de limpeza e impressão das mensagens
	def trocar_mensagens(self, msg):
		y, x = curses.getsyx()
		self.limpar_mensagens()
		self.mensagens.insert(0, msg)
		self.escrever_mensagens()
		self.scr.move(y, x)
		self.scr.refresh()

	# Termina o módulo curses
	def sair(self):
		self._end_curses()


# Classe que herda da classe de Thread comum
class MinhaThread(threading.Thread):
	# Instancia da classe com id, servidor e ui
	def __init__(self, id, server, ui):
		threading.Thread.__init__(self)
		self.id = id
		self.ui = ui
		self.server = server
		self.ativa = True

	# Método que sobrescreve o run comum da Thread
	def run(self):
		ultima_mensagem = -1
		while self.ativa:
			try:
				mensagens = self.server.Chat.get(self.id, int(ultima_mensagem) + 1)
			except socket.error, e:
				UI.trocar_mensagens('[!]Erro de conexão com o servidor, tentando novamente...')
				mensagens = []
				time.sleep(3)			

			for mensagem in mensagens:
				if int(mensagem['id']) > ultima_mensagem:
					ultima_mensagem = int(mensagem['id'])
				UI.trocar_mensagens('%s: %s' % (mensagem['nick'], mensagem['msg']))

			time.sleep(0.2)
	
	# Metodo que termina a thread
	def close(self):
		self.ativa = False




# Classe que faz a conexão com o servidor
def conecta_servidor(url, nick):
	servidor = rpc.ServerProxy(url)
	id = servidor.Session.start(nick)
	
	return servidor, id

# URL de conexao RPC via HTTP (sdi02)
url = 'http://192.168.100.9:10001'
# Escolha do nick
nick = raw_input('Escolha seu nick: ')

# Conecta com o servidor
servidor, id = conecta_servidor(url, nick)
# Inicializa a interface
UI = Interface(nick)

# Instance of Terminal Thread
itt = MinhaThread(id, servidor, UI)
# Inicia a thread pelo método comum da classe pai
itt.start()

# Loop principal
while True:
	try:
		# Captura a entrada
		msg = UI.entrada()
		# Caso vazia retorna ao inicio do loop
		if msg.strip() == '':
			continue
		# Caso exit sai do loop
		elif msg == 'exit':
			break
		# Senão tenta enviar a mensagem, caso algo de errado uma mensagem de erro é exibida
		else:
			if not servidor.Chat.post(id, msg):
				UI.trocar_mensagens('[!]Erro! A mensagem não pode ser entrege ao servidor.')
			
	# Captura Ctrl+C
	except KeyboardInterrupt, e:
		break


# Encerra as threads e a conexão
itt.close()
itt.join()
servidor.Session.end(id)
UI.sair()
