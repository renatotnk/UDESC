#!/usr/bin/python
# -*- coding: utf-8 -*-

from DAO import DAOMemoria
from EDA import Doguinho
from EDA import Toolbox

class AppConsole():

	def menu(self):
		print "Escolha uma das opções abaixo:"
		print "1. Cadastrar cão"
		print "2. Alterar cadastro de cão"
		print "3. Excluir cadastro de cão"
		print "4. Listar cães não adotados"
		print "5. Listar cães adotados"
		print "6. Listar Tutores"
		print "7. Listar Adoções"
		print "8. Adotar cão"
		print "0. Sair"
		opcao = raw_input(">>")
		opcao = int(opcao)
		if opcao == 1:
			#cadastraCao()
			nome_cao = raw_input("Informe o nome do cão: ")
			raca_cao = raw_input("Informe a raça do cão: ")
			sexo_cao = raw_input("Informe o sexo do cão: ")
			porte_cao = raw_input("Informe o porte do cão: ")
			idade_cao = raw_input("Informe a idade do cão: ")
			status_cao = raw_input("Informe o status do cão: ")
			obs_cao = raw_input("Adicione as notas do veterinário: ")
			id_cao = str(int(self.dados.doguinhos[-1].getInfos()[0]) + 1)
			cao = Doguinho.Doguinho(id_cao, nome_cao, raca_cao, sexo_cao, porte_cao, idade_cao, status_cao, obs_cao)
			self.dados.cadastrarDoguinho(cao)
			print "Cão cadastrado com sucesso!"
			Toolbox.Toolbox.getEnter()
			return True
		elif opcao == 2:
			#alteraCadastro()
			
			return True
		elif opcao == 3:
			idd = raw_input("Informe o ID do cão a ser removido: ")
			self.dados.removerDoguinho(idd)
			print "Cão removido com sucesso!"
			Toolbox.Toolbox.getEnter()
			return True
		elif opcao == 4:
			#listaNaoAdotados()
			nao_adotados = self.dados.getDoguinhosNaoAdotados()
			for adot in nao_adotados:
				adotInfos = adot.getInfos()
				print "-"*50
				print "Nome: "+ adotInfos[1]
				print "Raça: "+ adotInfos[2]
				print "Sexo: "+ adotInfos[3]
				print "Porte: "+ adotInfos[4]
				print "Descrição: "+ adotInfos[7]
				print "-"*50
			Toolbox.Toolbox.getEnter()
			return True
		elif opcao == 5:
			#listaAdotados()
			adotados = self.dados.getDoguinhosAdotados()
			for adot in adotados:
				adotInfos = adot.getInfos()
				print "-"*50
				print "ID: " + adotInfos[0]
				print "Nome: " + adotInfos[1]
				print "Raça: " + adotInfos[2]
				print "Sexo: " + adotInfos[3]
				print "Porte: " + adotInfos[4]
				print "Descrição: " + adotInfos[7]
				print "-"*50
			Toolbox.Toolbox.getEnter()
			return True
		elif opcao == 6:
			#listaTutores()
			tutores = self.dados.getTutores()
			for tut in tutores:
				tutInfos = tut.getInfos()
				print "-"*50
				print "ID de tutor: " + tutInfos[0]
				print "Nome: " + tutInfos[1]
				print "Endereço: "+ tutInfos[2]
				print "CPF: "+ tutInfos[3]
				print "Telefone para contato: "+ tutInfos[4]
				print "-"*50
			Toolbox.Toolbox.getEnter()
			return True
		elif opcao == 7:
			#listaAdocoes()
			adocoes = self.dados.getAdocoes()
			for ad in adocoes:
				adInfos = ad.getInfos()
				for dog in self.dados.doguinhos:
					if dog.getId() == adInfos[0]:
						nome = dog.getNome()
				print "-"*50
				print "ID do doguinho Adotado: " + adInfos[0]
				print "ID do tutor que adotou o doguinho: " + adInfos[1]
				print "Nome do cão: " + nome
				print "Data de adoção: " + adInfos[2]
				print "-"*50
			Toolbox.Toolbox.getEnter()
			return True
		elif opcao == 0:
			return False
		else:
			print "Código inválido!"
			return True
		

	def chamaMenu(self):
		print "Carregando dados..."
		self.dados = DAOMemoria.DAOMemoria()
		print "Dados carregados com sucesso!"
		#testeDog = Doguinho.Doguinho("1","Teste","TRaca","T","TPorte","99","66","Isso é um teste.")
		print "Bem-vindo! Abaixo se encontra o menu de opções..."
		while True:
			if not(self.menu()):
				break

	def __init__(self):
		self.chamaMenu()
