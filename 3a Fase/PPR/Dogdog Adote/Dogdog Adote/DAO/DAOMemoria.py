#!/usr/bin/python
# -*- coding: latin-1 -*-

# encoding=utf8  
import sys  

reload(sys)  
sys.setdefaultencoding('utf8')

from EDA import Doguinho
from EDA import Tutor
from EDA import Adocao
import datetime

class DAOMemoria():
	def __init__(self):
		self.doguinhos = []
		data = ''
		with open('DAO/dogs.dat', 'r') as f:
			while True:
				data = f.read(1)
				tamanho = len(data.split(':::'))
				while(tamanho < 9):
					data += f.read(1)
					data = data.strip('\n')
					if not data:
						break
					tamanho = len(data.split(':::'))
				if not data:
					break
				else:
					self.adicionaDoguinho(data.split(':::')[:-1])
				data = ''
		f.close()
		self.doguinhosAdotados = []
		self.doguinhosNaoAdotados = []
		for dog in self.doguinhos:
			if dog.getInfos()[6] == "2":
				self.doguinhosAdotados.append(dog)
			else:
				self.doguinhosNaoAdotados.append(dog)

		self.tutores = []
		data = ''
		with open('DAO/tutores.dat', 'r') as f:
			while True:
				data = f.read(1)
				tamanho = len(data.split(':::'))
				while(tamanho < 6):
					data += f.read(1)
					data = data.strip('\n')
					if not data:
						break
					tamanho = len(data.split(':::'))
				if not data:
					break
				else:
					self.adicionaTutor(data.split(':::')[:-1])
				data = ''
		f.close()
		
		self.adocoes = []
		data = ''
		with open('DAO/adocoes.dat', 'r') as f:
			while True:
				data = f.read(1)
				tamanho = len(data.split(':::'))
				while(tamanho < 4):
					data += f.read(1)
					data = data.strip('\n')
					if not data:
						break
					tamanho = len(data.split(':::'))
				if not data:
					break
				else:
					self.adicionaAdocao(data.split(':::')[:-1])
				data = ''
		f.close()

	def adota(self, idCao, idTutor, nome, endereco, cpf, telefone):
		tutor = Tutor.Tutor(idTutor,nome,endereco,cpf,telefone)
		achado = False
		for dog in self.doguinhos:
			if dog.getId() == idCao:
				if dog.status == "0":
					return
				else:
					achado = True
					dog.status = "2"
					break
		if achado:
			self.salvaDoguinhos()
			self.criarAdocao(idCao, tutor)
		else:
			return

	def adicionaAdocao(self, data):
		self.adocoes.append(Adocao.Adocao(data[0], data[1], data[2]))
		print 'adicionado ' + data[0] + ' ' + data[1] + ' ' + data[2]

	def adicionaTutor(self, data):
		self.tutores.append(Tutor.Tutor(data[0], data[1], data[2], data[3], data[4]))

	def adicionaDoguinho(self, data):
		self.doguinhos.append(Doguinho.Doguinho(data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]))

	def cadastrarDoguinho(self, dog):
		self.doguinhos.append(dog)
		self.salvaDoguinhos()

	def criarAdocao(self, dog_id, tutor):
		self.tutores.append(tutor)
		data = str(datetime.date.today()).split('-')
		data = data[2] + "/" + data[1] + "/" + data[0]
		self.adicionaAdocao([dog_id, tutor.getInfos()[0], data])
		self.salvaTutores()
		self.salvaAdocoes()

	def removerDoguinho(self, dog_id):
		print "Removendo cão de ID = " + str(dog_id)
		cont = 0
		for dog in self.doguinhos:
			if dog.getInfos()[0] == str(dog_id):
				break
			cont += 1
		
		if cont == len(self.doguinhos):
			print "ID inexistente"
		else:
			self.doguinhos.pop(cont)
			print "Removido"
			self.salvaDoguinhos()

	def getDoguinhosNaoAdotados(self):
		return self.doguinhosNaoAdotados

	def getDoguinhosAdotados(self):
		return self.doguinhosAdotados
	
	def getTutores(self):
		return self.tutores
	
	def getAdocoes(self):
		return self.adocoes

	def salvaDoguinhos(self):
		with open('DAO/dogs.dat', 'w') as f:
			data = ''
			for dog in self.doguinhos:
				data += ":::".join(dog.getInfos())
				data += ":::\n"
			f.write(data)
		f.close()
		self.doguinhos = []
		data = ''
		with open('DAO/dogs.dat', 'r') as f:
			while True:
				data = f.read(1)
				tamanho = len(data.split(':::'))
				while(tamanho < 9):
					data += f.read(1)
					data = data.strip('\n')
					if not data:
						break
					tamanho = len(data.split(':::'))
				if not data:
					break
				else:
					self.adicionaDoguinho(data.split(':::')[:-1])
				data = ''
		f.close()
		self.doguinhosAdotados = []
		self.doguinhosNaoAdotados = []
		for dog in self.doguinhos:
			if dog.getInfos()[6] == "2":
				self.doguinhosAdotados.append(dog)
			else:
				self.doguinhosNaoAdotados.append(dog)

	def salvaTutores(self):
		with open('DAO/tutores.dat', 'w') as f:
			data = ''
			for tutor in self.tutores:
				data += ":::".join(tutor.getInfos())
				data += ":::\n"
			f.write(data)
		f.close()
		self.tutores = []
		data = ''
		with open('DAO/tutores.dat', 'r') as f:
			while True:
				data = f.read(1)
				tamanho = len(data.split(':::'))
				while(tamanho < 6):
					data += f.read(1)
					data = data.strip('\n')
					if not data:
						break
					tamanho = len(data.split(':::'))
				if not data:
					break
				else:
					self.adicionaTutor(data.split(':::')[:-1])
				data = ''
		f.close()

	def salvaAdocoes(self):
		with open('DAO/adocoes.dat', 'w') as f:
			data = ''
			for adocao in self.adocoes:
				data += ":::".join(adocao.getInfos())
				data += ":::\n"
			f.write(data)
		f.close()
		self.adocoes = []
		data = ''
		with open('DAO/adocoes.dat', 'r') as f:
			while True:
				data = f.read(1)
				tamanho = len(data.split(':::'))
				while(tamanho < 4):
					data += f.read(1)
					data = data.strip('\n')
					if not data:
						break
					tamanho = len(data.split(':::'))
				if not data:
					break
				else:
					self.adicionaAdocao(data.split(':::')[:-1])
				data = ''
		f.close()

