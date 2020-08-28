#!/usr/bin/python
# -*- coding: utf-8 -*-

class Tutor:
	def __init__(self, idd, nome, endereco, cpf, telefone):
		self.id = idd
		self.nome = nome
		self.endereco = endereco
		self.cpf = cpf
		self.telefone = telefone
	
	def getInfos(self):
		return [self.id, self.nome, self.endereco, self.cpf, self.telefone]
	
	def getNome(self):
		return self.nome

	def getEndereco(self):
		return self.endereco

	def getCpf(self):
		return self.cpf

	def getTelefone(self):
		return self.telefone

	def getDoquinho(self):
		return self.doguinho

	def getId(self):
		return self.id
