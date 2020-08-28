from zeep.client import Client
import sys, curses, threading, time, socket


class Interface(object):
	def _init_curses(self):
		self.scr = curses.initscr()

	def _end_curses(self):
		curses.endwin()

	def imprime_texto(self, y, x, msg):
		try:
			self.scr.addstr(y, x, msg)
			return True
		except curses.error:
			return False

	def __init__(self, nick):
		self._init_curses()
		self.nick = nick
		self.mensagens = []
		self.imprime_texto(0, 0, nick + '> ')

	def entrada(self):
		inicio = len(self.nick) + 3
		msg = self.scr.getstr(0, inicio)
		self.imprime_texto(0, inicio, ' ' * len(msg))
		self.scr.refresh()
		return msg

	def limpar_mensagens(self):
		i = 1
		for caractere in self.mensagens:
			if not self.imprime_texto(i, 0, ' ' * len(caractere)):
				break
			i += 1

	def escrever_mensagens(self):
		i = 1
		for mensagem in self.mensagens:
			if not self.imprime_texto(i, 0, mensagem):
				break
			i += 1

	def trocar_mensagens(self, msg):
		y, x = curses.getsyx()
		self.limpar_mensagens()
		self.mensagens.insert(0, msg)
		self.escrever_mensagens()
		self.scr.move(y, x)
		self.scr.refresh()

	def sair(self):
		self._end_curses()



class MinhaThread(threading.Thread):
	def __init__(self, id, client, ui):
		threading.Thread.__init__(self)
		self.id = id
		self.ui = ui
		self.client = client
		self.ativa = True

	def run(self):
                ultima_mensagem = -1
                while self.ativa:
                        try:
                                mensagens = self.client.service.get_mensagens(int(ultima_mensagem) + 1)
                                if mensagens is not None:
                                        mensagens = mensagens.split("\n")
                                else:
                                        continue

                        except socket.error as e:
                                UI.trocar_mensagens('[!]Erro de conexão com o servidor, tentando novamente...')
                                UI.trocar_mensagens(e)
                                mensagens = []
                                time.sleep(3)

                        for mensagem in mensagens:
                                if mensagem != '':
                                        msg_id = int(mensagem.split("||")[0])
                                        msg_corpo = "||".join(mensagem.split("||")[1:])
                                        if msg_id > ultima_mensagem:
                                                ultima_mensagem = msg_id
                                        UI.trocar_mensagens('%s' % (msg_corpo))

                        time.sleep(0.2)

        # Metodo que termina a thread
	def close(self):
		self.ativa = False



def conecta_servidor(nick):
	id = client.service.comeca_sessao(nick)

	return id



client = Client('http://192.168.100.9:10001/WSChat?wsdl')
nickname = input('Escolha seu nick: ')

id = conecta_servidor(nickname)
UI = Interface(nickname)

itt = MinhaThread(id, client, nickname)
itt.start()

while True:
	try:
		msg = UI.entrada()
		if msg.strip() == b'':
			continue
		elif msg == b'exit':
			break
		else:
			client.service.multicast(id, msg)
		
	except KeyboardInterrupt:
		break

itt.close()
itt.join()
client.service.finaliza_sessao(id)
UI.sair()

	



