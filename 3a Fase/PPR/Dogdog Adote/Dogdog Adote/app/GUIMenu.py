#!/usr/bin/python
# -*- coding: utf-8 -*-

from kivy.app import App
from kivy.uix.gridlayout import GridLayout
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.label import Label
from kivy.uix.textinput import TextInput
from kivy.uix.button import Button
from kivy.uix.image import Image
from kivy.uix.behaviors import ButtonBehavior
from kivy.uix.popup import Popup
from kivy.uix.listview import ListView
from kivy.adapters.simplelistadapter import SimpleListAdapter
from DAO import DAOMemoria
from EDA import Doguinho

from kivy.config import Config
Config.set('graphics','width','800')
Config.set('graphics','height','800')

class TelaMenu(App):
	def build(self):
		from kivy.core.window import Window
		Window.maximize()		

		print "Importando dados..."
		self.dados = DAOMemoria.DAOMemoria()
		print "Dados importados com sucesso!"		
		self.title = "Menu"
		layout = GridLayout(cols=1,rows=8,spacing=1)
		self.cadastrarCao = Button(text='Cadastrar Cão')
		self.cadastrarCao.bind(on_press=self.cadastraCao)
		self.alterarCao = Button(text='Alterar Cadastro')
		self.alterarCao.bind(on_press=self.alteraCao)
		self.excluirCao = Button(text='Excluir Cadastro')
		self.excluirCao.bind(on_press=self.excluiCao)
		self.adotar = Button(text='Adotar Cão')
		self.adotar.bind(on_press=self.adota)
		self.listarCaes = Button(text='Listar Cães')
		self.listarCaes.bind(on_press=self.listaCaes)
		self.listarTut = Button(text='Listar Tutores')
		self.listarTut.bind(on_press=self.listaTut)
		self.listarAdoc = Button(text='Listar Adoções')
		self.listarAdoc.bind(on_press=self.listaAdoc)
		self.fechar = Button(text='Fechar')
		self.fechar.bind(on_press=App.get_running_app().stop)
		layout.add_widget(self.cadastrarCao)
		layout.add_widget(self.alterarCao)
		layout.add_widget(self.excluirCao)
		layout.add_widget(self.adotar)
		layout.add_widget(self.listarCaes)
		layout.add_widget(self.listarTut)
		layout.add_widget(self.listarAdoc)
		layout.add_widget(self.fechar)

		return layout

	def cadastraCao(self, a):
		out_box = GridLayout(cols=1,rows=2)
		box = GridLayout(cols=2)
		box.add_widget(Label(text='Informe o nome do cão:'))
		self.nome_cao = TextInput(multiline=False,size_hint_y=None,height=40,write_tab=False)
		box.add_widget(self.nome_cao)
		
		box.add_widget(Label(text='Informe a raça do cão:'))
		self.raca_cao = TextInput(multiline=False,size_hint_y=None,height=40,write_tab=False)
		box.add_widget(self.raca_cao)

		box.add_widget(Label(text='Informe o sexo do cão:'))
		self.sexo_cao = TextInput(multiline=False,size_hint_y=None,height=40,write_tab=False)
		box.add_widget(self.sexo_cao)

		box.add_widget(Label(text='Informe o porte do cão:'))
		self.porte_cao = TextInput(multiline=False,size_hint_y=None,height=40,write_tab=False)
		box.add_widget(self.porte_cao)

		box.add_widget(Label(text='Informe a idade do cão:'))
		self.idade_cao = TextInput(multiline=False,size_hint_y=None,height=40,write_tab=False)
		box.add_widget(self.idade_cao)

		box.add_widget(Label(text='Informe o status do cão:'))
		self.stat_cao = TextInput(multiline=False,size_hint_y=None,height=40,write_tab=False)
		box.add_widget(self.stat_cao)

		box.add_widget(Label(text='Adicione as notas do veterinário:'))
		self.notas_cao = TextInput(multiline=True,size_hint_y=None,height=150)
		box.add_widget(self.notas_cao)
		
		out_box.add_widget(box)
		self.confirmaBotao = Button(text="Cadastrar", size_hint_y=0.1)
		self.confirmaBotao.bind(on_press=self.cadastroLogica)
		out_box.add_widget(self.confirmaBotao)

		self.popupCadastro = Popup(title='Cadastrar',content=out_box,size_hint=(None, None),size=(600, 620))
		
		self.popupCadastro.open()

	def cadastroLogica(self, a):
		if (self.nome_cao.text and self.raca_cao.text and self.sexo_cao.text and self.porte_cao.text and self.idade_cao.text and self.stat_cao.text and self.notas_cao.text):
			id_cao = str(int(self.dados.doguinhos[-1].getInfos()[0]) + 1)
			cao = Doguinho.Doguinho(id_cao,self.nome_cao.text,self.raca_cao.text,self.sexo_cao.text,self.porte_cao.text,self.idade_cao.text,self.stat_cao.text,self.notas_cao.text)
			self.dados.cadastrarDoguinho(cao)
			self.popupCadastro.dismiss()




	def test(self, a, b):
		for dog in self.dados.doguinhos:
			if dog.getId() == self.id_cao.text:
				self.nome_cao.text = dog.getNome()
				self.raca_cao.text = dog.getRaca()
				self.sexo_cao.text = dog.getSexo()
				self.porte_cao.text = dog.getPorte()
				self.idade_cao.text = dog.getIdade()
				self.stat_cao.text = dog.getStatus()
				self.notas_cao.text = dog.getObs()
				return 
	
		self.nome_cao.text = ''
		self.raca_cao.text = ''
		self.sexo_cao.text = ''
		self.porte_cao.text = ''
		self.idade_cao.text = ''
		self.stat_cao.text = ''
		self.notas_cao.text = ''
	
	def alteraCao(self, a):
		out_box = GridLayout(cols=1,rows=2)
		box = GridLayout(cols=2)
		box.add_widget(Label(text='Informe o ID do cão:'))
		self.id_cao = TextInput(multiline=False,size_hint_y=None,height=40,write_tab=False)
		self.id_cao.bind(text=self.test)
		box.add_widget(self.id_cao)

		box.add_widget(Label(text='Informe o nome do cão:'))
		self.nome_cao = TextInput(multiline=False,size_hint_y=None,height=40,write_tab=False)
		box.add_widget(self.nome_cao)
		
		box.add_widget(Label(text='Informe a raça do cão:'))
		self.raca_cao = TextInput(multiline=False,size_hint_y=None,height=40,write_tab=False)
		box.add_widget(self.raca_cao)

		box.add_widget(Label(text='Informe o sexo do cão:'))
		self.sexo_cao = TextInput(multiline=False,size_hint_y=None,height=40,write_tab=False)
		box.add_widget(self.sexo_cao)

		box.add_widget(Label(text='Informe o porte do cão:'))
		self.porte_cao = TextInput(multiline=False,size_hint_y=None,height=40,write_tab=False)
		box.add_widget(self.porte_cao)

		box.add_widget(Label(text='Informe a idade do cão:'))
		self.idade_cao = TextInput(multiline=False,size_hint_y=None,height=40,write_tab=False)
		box.add_widget(self.idade_cao)

		box.add_widget(Label(text='Informe o status do cão:'))
		self.stat_cao = TextInput(multiline=False,size_hint_y=None,height=40,write_tab=False)
		box.add_widget(self.stat_cao)

		box.add_widget(Label(text='Adicione as notas do veterinário:'))
		self.notas_cao = TextInput(multiline=True,size_hint_y=None,height=150)
		box.add_widget(self.notas_cao)
		
		out_box.add_widget(box)
		self.confirmaBotao = Button(text="Salvar", size_hint_y=0.1)
		self.confirmaBotao.bind(on_press=self.editarLogica)
		out_box.add_widget(self.confirmaBotao)

		self.popupEdicao = Popup(title='Editar',content=out_box,size_hint=(None, None),size=(600, 620))
		
		self.popupEdicao.open()

	def editarLogica(self, a):
		if(self.id_cao.text and self.nome_cao.text and self.raca_cao.text and self.sexo_cao.text and self.porte_cao.text and self.idade_cao.text and self.stat_cao.text and self.notas_cao.text):
			self.dados.removerDoguinho(self.id_cao.text)
			cao = Doguinho.Doguinho(self.id_cao.text,self.nome_cao.text,self.raca_cao.text,self.sexo_cao.text,self.porte_cao.text,self.idade_cao.text,self.stat_cao.text,self.notas_cao.text)
			self.dados.cadastrarDoguinho(cao)
			self.popupEdicao.dismiss()




	def excluiCao(self, a):
		out_box = GridLayout(cols=1,rows=2)
		box = GridLayout(cols=2)
		box.add_widget(Label(text='Insira o ID do cão:', size_hint=(1,None),height=40,width=100))
		self.idCao = TextInput(multiline=False,size_hint=(None,None),width=40,height=40,write_tab=False)
		box.add_widget(self.idCao)
		out_box.add_widget(box)
		self.confirmaBotao = Button(text="Excluir", size_hint_y=0.7)
		self.confirmaBotao.bind(on_press=self.exclusaoLogica)
		out_box.add_widget(self.confirmaBotao)

		self.popupExclusao = Popup(title='Excluir',content=out_box,size_hint=(None, None),size=(300, 175))
		
		self.popupExclusao.open()

	def exclusaoLogica(self, a):
		if(self.idCao.text):
			self.dados.removerDoguinho(self.idCao.text)
			self.popupExclusao.dismiss()

	def adota(self, a):
		box = GridLayout(cols=2, rows=5, spacing=[0,20])
		box.add_widget(Label(text='ID do cão:',size_hint=(None,None),width=140,height=40))
		self.idCao = TextInput(multiline=False,size_hint=(None,None),height=40,width=40,write_tab=False)
		box.add_widget(self.idCao)
		box.add_widget(Label(text='Nome:',size_hint=(None,None),width=140,height=40))
		self.nome = TextInput(multiline=False,size_hint_y=None,height=40,write_tab=False)
		box.add_widget(self.nome)
		box.add_widget(Label(text='Endereço:',size_hint=(None,None),width=140,height=40))
		self.end = TextInput(multiline=False,size_hint_y=None,height=40,write_tab=False)
		box.add_widget(self.end)
		box.add_widget(Label(text='CPF:',size_hint=(None,None),width=140,height=40))
		self.cpf = TextInput(multiline=False,size_hint_y=None,height=40,write_tab=False)
		box.add_widget(self.cpf)
		box.add_widget(Label(text='Telefone:',size_hint=(None,None),width=140,height=40))
		self.tel = TextInput(multiline=False,size_hint_y=None,height=40,write_tab=False)
		box.add_widget(self.tel)
		out_box = GridLayout(cols=1, rows=2)
		out_box.add_widget(box)
		
		self.confirmaBotao = Button(text="Adotar", size_hint_y=0.17)
		self.confirmaBotao.bind(on_press=self.adocaoLogica)
		out_box.add_widget(self.confirmaBotao)

		self.popupAdocao = Popup(title='Adoção',content=out_box,size_hint=(None, None),size=(600, 400))
		
		self.popupAdocao.open()

	def adocaoLogica(self, a):
		if (self.idCao.text and self.nome.text and self.end.text and self.cpf.text and self.tel.text):
			self.dados.adota(self.idCao.text,str(int(self.dados.tutores[-1].getId()) + 1),self.nome.text,self.end.text,self.cpf.text,self.tel.text)
			self.popupAdocao.dismiss()

	def listaCaes(self, a):
		box = GridLayout(cols=1, rows=5, spacing=[0,10])

		nao_adotados = self.dados.getDoguinhosNaoAdotados()

		adotados = self.dados.getDoguinhosAdotados()
		box.add_widget(Label(text='Cães Não Adotados',size_hint_y=0.15))
		dados_nao_adotados = []
		for dog in nao_adotados:
			dog_infos = dog.getInfos()
			dados_nao_adotados.append("ID: {0}     Nome: {1}".format(dog_infos[0], dog_infos[1]))
			dados_nao_adotados.append("Raça: {0}     Sexo: {1}".format(dog_infos[2], dog_infos[3]))
			dados_nao_adotados.append("Porte: {0}     Idade: {1}".format(dog_infos[4], dog_infos[5]))
			if dog_infos[6] == "1":
				stat = "Apto para adoção."
			else:
				stat = "Inapto para adoção."
			dados_nao_adotados.append("Status: {0}".format(stat))
			dados_nao_adotados.append("{0}".format(dog_infos[7]))
			dados_nao_adotados.append('')
			dados_nao_adotados.append('')

		simple_list_adapter = SimpleListAdapter(data=dados_nao_adotados,cls=Label)
		list_view1 = ListView(adapter=simple_list_adapter)
		box.add_widget(list_view1)

		box.add_widget(Label(text='Cães Adotados',size_hint_y=0.15))

		dados_adotados = []
		for dog in adotados:
			dog_infos = dog.getInfos()
			dados_adotados.append("ID: {0}     Nome: {1}".format(dog_infos[0], dog_infos[1]))
			dados_adotados.append("Raça: {0}     Sexo: {1}".format(dog_infos[2], dog_infos[3]))
			dados_adotados.append("Porte: {0}     Idade: {1}".format(dog_infos[4], dog_infos[5]))
			dados_adotados.append("{0}".format(dog_infos[7]))
			dados_adotados.append('')
			dados_adotados.append('')

		simple_list_adapter2 = SimpleListAdapter(data=dados_adotados,cls=Label)
		list_view2 = ListView(adapter=simple_list_adapter2)
		box.add_widget(list_view2)

		fechar_botao = Button(text='Fechar',size_hint_y=0.2)
		box.add_widget(fechar_botao)
		self.popupListaCaes = Popup(title='Lista de Cães',content=box,size_hint=(None,None),size=(600,600))
		fechar_botao.bind(on_press=self.popupListaCaes.dismiss)
		
		self.popupListaCaes.open()

	def listaTut(self, a):
		box = GridLayout(cols=1, rows=3)
		box.add_widget(Label(text='Lista de Tutores', size_hint_y=0.15))
		tutores = self.dados.getTutores()
		dados = []
		for tut in tutores:
			tutInfos = tut.getInfos()
			dados.append("ID: {0}   Nome: {1}   CPF: {2}".format(tutInfos[0],tutInfos[1],tutInfos[3]))
			telefone = tutInfos[4]
			telefone = telefone[:-4]+"-"+telefone[-4:]
			dados.append("Endereço: {0}   Telefone: {1}".format(tutInfos[2],telefone))
			dados.append('')
			dados.append('')
		
		simple_list_adapter = SimpleListAdapter(data=dados,cls=Label)
		list_view1 = ListView(adapter=simple_list_adapter)
		box.add_widget(list_view1)
		botao = Button(text='Fechar',size_hint_y=0.2)
		box.add_widget(botao)
		self.popupListaTutores = Popup(title='Lista de Tutores',content=box,size_hint=(None,None),size=(600,600))
		botao.bind(on_press=self.popupListaTutores.dismiss)

		self.popupListaTutores.open()
		

	def listaAdoc(self, a):
		box = GridLayout(cols=1,rows=3)
		box.add_widget(Label(text='Lista de Adoções', size_hint_y=0.15))
		adocoes = self.dados.getAdocoes()
		dados = []
		for ad in adocoes:
			adInfos = ad.getInfos()
			for dog in self.dados.doguinhos:
				if dog.getId() == adInfos[0]:
					nome = dog.getNome()
			for tutor in self.dados.tutores:
				if tutor.getId() == adInfos[1]:
					nome_tutor = tutor.getNome()
			dados.append("ID do cão: {0}   Nome do cão: {1}".format(adInfos[0],nome))
			dados.append("ID do tutor: {0}   Nome do tutor: {1}".format(adInfos[1],nome_tutor))
			dados.append("Data de adoção: {0}".format(adInfos[2]))
			dados.append('')
			dados.append('')	

		simple_list_adapter = SimpleListAdapter(data=dados,cls=Label)
		list_view1 = ListView(adapter=simple_list_adapter)
		box.add_widget(list_view1)
		botao = Button(text='Fechar',size_hint_y=0.2)
		box.add_widget(botao)
		self.popupListaAdoc = Popup(title='Lista de Adoções',content=box,size_hint=(None,None),size=(600,600))
		botao.bind(on_press=self.popupListaAdoc.dismiss)

		self.popupListaAdoc.open()
