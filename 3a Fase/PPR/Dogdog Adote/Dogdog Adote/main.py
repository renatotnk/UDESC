#!/usr/bin/python
# -*- coding: utf-8 -*-

from EDA import Tutor
from EDA import Adm
from EDA import Doguinho
from app import AppConsole
from app import GUILogin
from getpass import getpass
from DAO import DAOMemoria

def getCredenciais():
	usuario = raw_input("Login: ")
	senha = getpass("Senha: ")
	return usuario, senha

def logaConsole():
	novo_app = AppConsole.AppConsole()

def login():	
	admin = Adm.Adm("dogdog", "adote")
	print "Dog Dog Adote v1.0 -- Bem Vindo"
	usuario, senha = getCredenciais()
	check = admin.checaLogin(usuario, senha)
	if check:
		logaConsole()
	else:
		while not(check):
			print "\nLogin ou senha inválidos, tente novamente..."
			usuario, senha = getCredenciais()
			check = admin.checaLogin(usuario, senha)
		if check:
			logaConsole()	

if __name__ == "__main__":
	#login()
	GUILogin.TelaLogin().run()
