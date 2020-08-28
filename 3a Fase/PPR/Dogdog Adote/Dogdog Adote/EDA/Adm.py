#!/usr/bin/python
# -*- coding: utf-8 -*-

class Adm():
	def __init__(self, u, p):
		self.username = u
		self.password = p

	def checaLogin(self, u, p):
		return ((u == self.username) and (p == self.password))
