#!/usr/bin/env python2
# -*- coding: utf-8 -*- 

from socket import *
import json 
from collections import Counter
import random as rand
import time

#sudo tc qdisc change dev lo root netem delay/loss

class Pacote():
	def __init__(self):
		self.pacote = {}		
		self.pacote['orig'] = None
		self.pacote['dest'] = None
		self.pacote['seq'] = None
		self.pacote['ack_number'] = None
		self.pacote['flags'] = {'ACK' : False, 'SYN' : False, 'FIN' : False}
		self.pacote['data'] = ""
		self.pacote['RTT'] = None

	def set_chaves(self, chaves):
		for chave,valor in chaves.items():
			if chave  == "ACK" or chave == "SYN" or chave == "FIN":
				self.mudar_dicionario_interno(self.pacote['flags'], chave, valor)
			else:
				self.mudar_dicionario_interno(self.pacote, chave, valor)

	def __getitem__(self,key):
		return self.pacote[key]
	
	def mudar_dicionario_interno(self, dicionario, chave, valor):
		for chave_a in dicionario.keys():
			if chave_a == chave:	
				dicionario[chave_a] = valor
				break


class TCP():
	def __init__(self):
		self.sock = socket(AF_INET, SOCK_DGRAM)
		self.MTU = 1500
		self.MSS = self.MTU - 169
		self.janela = []
		self.indicejanela = 0
		self.seq = rand.randint(0,50)
		self.listACK = []
		self.cwnd = 1
		self.ssthresh = 64 * 1024
		self.exponencial = True
				

	

	def conectar(self, endereco_dest, porta):
		if str(endereco_dest) == "localhost":
			endereco_dest = "127.0.0.1"
		#handshake comecando pelo cliente!
		tmp_pacote = Pacote()
		tmp_pacote.set_chaves({
					'seq': self.seq,
					'dest': porta,
					'SYN' : True,
					'RTT' : time.time()
				      })
		pacote_comprimido = json.dumps(tmp_pacote.pacote, indent = 4)
		self.sock.sendto(pacote_comprimido, (endereco_dest,porta))
		self.sock.settimeout(8.0)
		print "Enviando pacote com flag 'SYN' e sequencia:", tmp_pacote.pacote['seq']
		print "\tRealizando primeira via handshake\t"

		while True:
			try:
				pacote_comprimido, (endereco_dest, porta) = self.sock.recvfrom(self.MTU)
				break
			except:
				print "Timeout excedido, reenviando pacote"
				self.sock.sendto(pacote_comprimido, (endereco_dest, porta)) 
		
		tmp_pacote.pacote = json.loads(pacote_comprimido)
		print "Pacote de sincronizacao recebido, com seq:", tmp_pacote.pacote['seq'], "e numero de ACK:",  tmp_pacote.pacote['ack_number'] 
		if tmp_pacote['flags']['SYN'] == True and tmp_pacote.pacote['flags']['ACK'] == True:
			self.timeout = min(6, tmp_pacote.pacote['RTT'])
			self.sock.settimeout(self.timeout)
			self.ack = tmp_pacote.pacote['seq'] + 1
			tmp_pacote.set_chaves({'orig' : tmp_pacote.pacote['dest'],
					       'dest' : tmp_pacote.pacote['orig'],
					       'ack_number': self.ack ,
					       'SYN' : False,
					       'seq' : self.seq,
					       'RTT': time.time()
						})
			pacote_comprimido = json.dumps(tmp_pacote.pacote)
			self.sock.sendto(pacote_comprimido, (endereco_dest, porta))
			print "\tRealizando terceira via handshake\t"
			print "Enviando pacote com flag 'SYN' , sequencia:", tmp_pacote.pacote['seq'] , "e ACK number:", self.ack
			print "Conexao estabelecida com o servidor! Handshake completo!"
			return (self.sock, (endereco_dest,porta))


	def fechar_conexao(self,conexao):
		self.sock, (endereco_dest, porta) = conexao

		tmp_pacote = Pacote()
		tmp_pacote.set_chaves({'FIN' : True})
		pacote_comprimido = json.dumps(tmp_pacote.pacote, sort_keys = True)
		print "Enviando pacote para finalizacao de conexao"
		self.sock.sendto(pacote_comprimido, (endereco_dest,porta))
		while True:
			try:
				pacote_comprimido, (endereco_dest,porta) = self.sock.recvfrom(self.MTU)
				break
			except:
				print "Tempo limite esgotado, reenviando pacote"
				pacote_comprimido, (endereco_dest,porta) = self.sock.recvfrom(self.MTU)
		tmp_pacote.pacote = json.loads(pacote_comprimido)
		if tmp_pacote.pacote['flags']['FIN'] == True and tmp_pacote.pacote['flags']['ACK'] == True:
			print "Conexao finalizada com sucesso"
		else:
			opcao = raw_input("O servidor nao respondeu o pacote de finalizacao. Deseja forcar a finalizacao? [s/n]\n>>")
			if opcao == 's':
				self.sock.close()
				print "Conexao finalizada com sucesso"
			else:
				print "Reenviando o mesmo pacote para tentar finalizar a conexao"
				self.fechar_conexao(conexao)
				



	
	def server(self, endereco, porta):
		
		self.sock.bind((endereco,porta))
		if endereco == 'localhost':
			endereco = '127.0.0.1'
		print "Servidor iniciado em %s:%d" %(str(endereco), porta) 
		assembler = []
		tmp_pacote = Pacote()
		self.sock.settimeout(7)
		
		while True:
			cont = 0
		
			while cont < self.cwnd:
				if self.cwnd * self.MSS > self.ssthresh:
					self.exponencial = False
				while True:
					try:
						pacote_comprimido, (endereco_dest,porta_dest) = self.sock.recvfrom(self.MTU)						
						break
					except:
						self.ssthresh = self.cwnd * self.MSS/2
						self.exponencial = True
						self.cwnd = 1

				tmp_pacote.pacote = json.loads(pacote_comprimido)
				tmp_pacote.set_chaves(
							{'orig': tmp_pacote.pacote['dest'],
						 	'dest': porta_dest}
						     )
			
				if tmp_pacote['flags']['SYN'] == True :
					self.ack = tmp_pacote.pacote['seq'] + 1
					print "Recebido pacote com flag SYN do cliente e numero de sequencia:", tmp_pacote.pacote['seq']				
					self.timeout = min(8, round(4 *(time.time() - tmp_pacote.pacote['RTT']), 4))				
					tmp_pacote.set_chaves({
	 						       'ack_number': self.ack,
							       'seq': self.seq,
							       'ACK': True,
							       'SYN' : True,
							       'RTT' : self.timeout
								})
					pacote_comprimido = json.dumps(tmp_pacote.pacote)
					self.sock.settimeout(self.timeout)
					self.sock.sendto(pacote_comprimido, (endereco_dest, porta_dest))
				
					print "\tRealizando segunda via handshake\t"
					print "Enviando pacote com flag 'SYN', 'ACK', sequencia:", self.seq , "e numero de ack:", self.ack
			
					while True:
						try:
							pacote_comprimido, (endereco_dest, porta_dest) = self.sock.recvfrom(self.MTU)
							break
						except:
							print "Timeout, partida lenta"
							self.serv_slow_start(pacote_comprimido, (endereco_dest,porta_dest), send = True)
					tmp_pacote.pacote = json.loads(pacote_comprimido)
					if tmp_pacote.pacote['flags']['ACK'] and tmp_pacote.pacote['ack_number'] - 1 == self.seq:
						print "Conexão estabelecida!"
					else:
						print "Erro ao estabelecer conexão!"
						break
					
				elif tmp_pacote.pacote['flags']['FIN'] == True:
					tmp_pacote.set_chaves({
							       'ACK': True,
							       'FIN' : True,
								})				
					pacote_comprimido = json.dumps(tmp_pacote.pacote)
					print "Recebido pacote com flag FIN, terminando conexao"
					self.sock.sendto(pacote_comprimido, (endereco_dest, porta_dest))
					self.sock.close()
					print "Conexao com o cliente terminada"
					exit()
			
				else:
					if self.ack - 1  == tmp_pacote.pacote['seq'] :
						print "Pacote recebido com sequencia:", tmp_pacote.pacote['seq'] + len(tmp_pacote.pacote['data']), "numero ACK:", tmp_pacote.pacote['ack_number'], "e tamanho de dados=", len(tmp_pacote.pacote['data'])
						if tmp_pacote.pacote['flags']['ACK'] == True:
							if self.seq == tmp_pacote.pacote['ack_number'] - 1:
								self.ack += len(tmp_pacote.pacote['data'])
								assembler.append(tmp_pacote.pacote['data'])
								self.timeout = min(8, round(4*(time.time() - tmp_pacote.pacote['RTT']), 4))
								tmp_pacote.set_chaves({
										'seq' : self.seq,
										'ACK': True,									
										'ack_number' : self.ack,
										'data' : "",
										'RTT': self.timeout									
										})							
								self.janela.append(tmp_pacote.pacote)
								self.seq += len(tmp_pacote.pacote['data'])
								print "Segmento Recebido"
								print "".join(assembler)
								if self.exponencial:
									self.cwnd = self.cwnd * 2
								else:
									self.cwnd = self.cwnd + 1
								assembler = []
								break
							else:
								self.listACK.append(tmp_pacote.pacote['ack_number'])
								if self.verificaACK() == True:
									serv_fast_recovery(self, ack_number , a = False)

						else:
							self.ack += len(tmp_pacote.pacote['data'])
							assembler.append(tmp_pacote.pacote['data'])
							tmp_pacote.set_chaves({
									'ack_number': self.ack,
									'seq': self.seq,
									'ACK': False,
									'data': ''
								})
							self.janela.append(tmp_pacote.pacote)
							if self.exponencial:
								self.cwnd = self.cwnd * 2
							else:
								self.cwnd = self.cwnd + 1
							print "O pacote foi segmentado, esperando o restante e enviando ack de reconhecimento"

					else:
						tmp_pacote.set_chaves({
								'ack_number': self.ack,
								'seq': self.seq,
								'data': '',	
								'ACK': True	
							})
						self.janela.append(tmp_pacote.pacote)
						self.listACK.append(self.ack)
						if self.verificaACK() == True:
							serv_fast_recovery(self, ack_number , a = True)
						print "3 ACKs duplicados, reduzindo tamanho da janela"
				cont += 1
			pacotes_recebidos = cont + 1
			cont = 0

			if not self.janela:
				print "Janela vazia."
			else:
				while self.indicejanela < len(self.janela):
					while cont < pacotes_recebidos:
						if self.indicejanela >= len(self.janela):
							break
						pacote_comprimido = json.dumps(self.janela[self.indicejanela])
						self.sock.sendto(pacote_comprimido, (endereco_dest,porta_dest))
						print "Segmento enviado com numero de sequencia:", self.seq , "e numero de ack:", self.ack
						self.indicejanela += 1
						cont+= 1
					print "Foram reconhecidos", cont, "pacotes"
	
	def serv_slow_start(self,pacote_comprimido, (endereco_dest,porta_dest), send = False):
		if send:		
			self.ssthresh = self.cwnd * self.MSS/2
			self.exponencial = True
			self.cwnd = 1
			self.sock.sendto(pacote_comprimido, (endereco_dest,porta_dest))
		else:
			self.ssthresh = self.cwnd * self.MSS/2
			self.exponencial = True
			self.cwnd = 1		
	
	def serv_fast_recovery(self, ack_number , a = False):
		if a:
			if self.cwnd > 1:
				self.cwnd /= 2
				self.ssthresh = self.cwnd * self.MSS/2
				for i in range(len(self.janela)):
					if self.janela[i]['ack_number'] == tmp_pacote.pacote['ack_number'] - 1:
						self.indicejanela = i
				print "3 ACKs duplicados."			
		else:
			if self.cwnd > 1:
				self.cwnd /= 2
				self.ssthresh = self.cwnd * self.MSS/2
			self.exponencial = False
			print "Enviados 3 ACKs duplicados, a janela de congestionamento foi diminuida."
			self.listACKS = []


	def enviar_dados(self, conexao, dados):
		self.sock, (endereco_dest, porta) = conexao
		tmp_pacote = Pacote()
		
		if len(dados) >= self.MSS:
			print "O pacote e maior do que a janela comporta, o pacote sera fragmentado"
			self.segmentar_dados(porta, dados)
		else:
			self.empacotar(dados,porta)		
			
		if not self.janela:
			print "Janela vazia"
		else:

			while self.indicejanela < len(self.janela):
				cont = 0
				if self.cwnd * self.MSS > self.ssthresh:
					self.exponencial = False

				pacotes_enviados = 0

				while cont < self.cwnd:
					if self.indicejanela >= len(self.janela):
						pacotes_enviados = cont
						break
					pacote_comprimido = json.dumps(self.janela[self.indicejanela])
					self.sock.sendto(pacote_comprimido, (endereco_dest,porta))
					print "Enviando pacote com seq:", self.seq, "e numero de ack:", self.ack
					self.indicejanela += 1
					cont += 1
					pacotes_enviados += 1

				print cont, "segmentos enviados."

				cont = 0

				while cont < pacotes_enviados:
					while True:
						try:
							pacote_comprimido, (endereco_dest,porta_dest) = self.sock.recvfrom(self.MTU)
							break
						except:
							print "Timeout na partida lenta, reiniciando"
							print self.timeout
							self.ssthresh = self.cwnd * self.MSS/2
							self.exponencial = True
							self.cwnd = 1
							self.sock.sendto(pacote_comprimido, (endereco_dest,porta))
					
					tmp_pacote.pacote = json.loads(pacote_comprimido)
					if self.ack - 1 == tmp_pacote.pacote['seq']:
						if self.seq == tmp_pacote.pacote['ack_number'] - 1:
							print "Pacote recebido com sequencia:", tmp_pacote.pacote['seq'] + 1, "e numero de ACK:", tmp_pacote.pacote['ack_number']
							self.ack += len(tmp_pacote.pacote['data'])
							self.timeout = min(6, tmp_pacote.pacote['RTT'])
							self.sock.settimeout(self.timeout)
							print "Novo valor de timeout:", self.timeout
							print "ACK do pacote final recebido."
							if self.exponencial:
								self.cwnd = self.cwnd * 2
							else:
								self.cwnd = self.cwnd + 1

						else:
							self.listACK.append(tmp_pacote.pacote['ack_number'])
							if self.verificaACK():
								self.fast_recovery(tmp_pacote.pacote['ack_number'])
							else:
								if self.exponencial:
									self.cwnd = self.cwnd * 2
								else:
									self.cwnd = self.cwnd + 1
					else:
						tmp_pacote.set_chaves({
								'ACK': True,
								'ack_number': self.ack,
								'seq': self.seq,
								'data': '',
								'RTT': time.time()			
							})
						self.buffer.append(tmp_pacote.pacote)
						print "Esse pacote esta fora de ordem, enviando ACK."			
					cont += 1
	
	def fast_recovery(self, ack_number):
		if self.cwnd > 1:
			self.cwnd /= 2
			self.ssthresh = self.cwnd * self.MSS/2
		self.exponencial = False
		for i in range(len(self.buffer)):
			if self.buffer[i]['seq'] == tmp_pacote.pacote['ack_number'] - 1:
				self.indiceBuffer = i
				break
		print "3 ACKs duplicados."
		self.listACK = []
	

	def verificaACK(self):
		double_ack = Counter(self.listACK)
		for chave, valor in double_ack.items():
			if valor >= 3:
				return True
		return False
		
	def segmentar_dados(self, porta, dados):
		while len(dados) > self.MSS:
			self.empacotar(dados[0:self.MSS], porta, segmentacao = True)
			dados = dados[self.MSS:]	
		if len(dados):
			self.empacotar(dados, porta)
		

	def empacotar(self, dados, porta, segmentacao = False):
		tmp_pacote = Pacote()
		if segmentacao:
			tmp_pacote.set_chaves({
						'seq' : self.seq,
						'ack_number' : -1,
						'dest': porta,
						'data' : dados,
						'ACK': False,
						'RTT': time.time()							
						})
			self.seq += len(dados)
			self.janela.append(tmp_pacote.pacote)
			#print json.dumps(tmp_pacote.pacote, indent = 4)
		else:
			tmp_pacote.set_chaves({
						'seq' : self.seq,
						'ack_number' : self.ack,
						'dest': porta,
						'data' : dados,
						'ACK': True,
						'RTT': time.time()							
						})
			self.seq += len(dados)
			self.janela.append(tmp_pacote.pacote)
			#print json.dumps(tmp_pacote.pacote, indent = 4)
			
