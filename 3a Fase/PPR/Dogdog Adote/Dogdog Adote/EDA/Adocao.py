#!/usr/bin/python
# -*- coding: utf-8 -*-

class Adocao:
	#Variável de classe para contar o número de adocoes
	n_adocoes = 0

	def __init__(self, idDoguinho, idTutor, data):
		self.idCao = idDoguinho
		self.idTutor = idTutor
		self.dia = data.split("/")[0]
		self.mes = data.split("/")[1]
		self.ano = data.split("/")[2]
		#Cada cão adiciona 1 ao contador
		Adocao.n_adocoes += 1

	def getInfos(self):
		return [self.idCao, self.idTutor, self.dia+"/"+self.mes+"/"+self.ano]

	@classmethod
	def quantasAdocoes(cls):
		print "Temos " + str(cls.n_adocoes) + " adoções!"

