#!/usr/bin/python
# -*- coding: utf-8 -*-

class Doguinho:
	#Variável de classe para contar o número de cães
	n_doguinhos = 0

	def __init__(self, dogId, nome, raca, sexo, porte, idade, status, obs):
		self.id = dogId
		self.nome = nome
		self.raca = raca
		self.sexo = sexo
		self.porte = porte
		self.idade = idade
		self.status = status
		self.obs = obs
		#Cada cão adiciona 1 ao contador
		Doguinho.n_doguinhos += 1

	def getId(self):
		return self.id
	
	def getNome(self):
		return self.nome
	
	def getRaca(self):
		return self.raca
	
	def getSexo(self):
		return self.sexo

	def getIdade(self):
		return self.idade
	
	def getPorte(self):
		return self.porte
	
	def getStatus(self):
		return self.status
	
	def getObs(self):
		return self.obs

	def getInfos(self):
		return [self.id,self.nome,self.raca,self.sexo,self.porte,self.idade,self.status,self.obs]

	@classmethod
	def quantosDogs(cls):
		print "Temos " + str(cls.n_doguinhos) + " doguinhos!"

