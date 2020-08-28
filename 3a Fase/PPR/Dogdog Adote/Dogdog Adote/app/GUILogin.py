from kivy.app import App
from kivy.uix.gridlayout import GridLayout
from kivy.uix.floatlayout import FloatLayout
from kivy.uix.label import Label
from kivy.uix.textinput import TextInput
from kivy.uix.button import Button
from kivy.uix.image import Image
from kivy.uix.behaviors import ButtonBehavior
from kivy.uix.popup import Popup

from EDA import Adm
import GUIMenu

from kivy.config import Config
Config.set('graphics','width','400')
Config.set('graphics','height','80')

class TelaLogin(App):
	def build(self):
		self.admin = Adm.Adm("dogdog", "adote")
		
		self.title = "Login"
		#return GUILogin()
		layout = GridLayout(cols=2,rows=1,row_force_default=True, row_default_height=80)
		inLayout = GridLayout(rows=2)

		inLayout.add_widget(Label(text='Username',size_hint=(None,None),height=40,width=100))
		self.username = TextInput(multiline=False,size_hint_y=None,height=40,write_tab=False)
		inLayout.add_widget(self.username)
		inLayout.add_widget(Label(text='Password',size_hint=(None,None),height=40,width=100))
		self.password = TextInput(password=True,multiline=False,size_hint_y=None,height=40,write_tab=False)
		inLayout.add_widget(self.password)

		layout.add_widget(inLayout)
		self.botao_login = Button(text='Entrar',size_hint=(None,None),height=80,width=100)
		self.botao_login.bind(on_press=self.loga)
		layout.add_widget(self.botao_login)		
		self.username.focus = True
		return layout

	def loga(self,a):
		check = self.admin.checaLogin(self.username.text, self.password.text)
		if check:
			from kivy.core.window import Window
			Window.size = (750, 750)
			GUIMenu.TelaMenu().run()
		else:
			self.username.text = ''
			self.password.text = ''
	
