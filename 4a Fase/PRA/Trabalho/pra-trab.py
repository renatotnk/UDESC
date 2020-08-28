#!/usr/bin/python
# -*- coding: utf-8 -*-

import time, random, sys, operator, pickle
from datetime import datetime
from arvoreb import *

# Classe registro de previsão do tempo
class Previsao():
	def __init__(self, local, data, hora, temperatura):
		self.local = local
		self.data = data
		#self.data_sort = datetime.strptime(self.data, "%d/%m/%Y").strftime("%Y-%m-%d")
		dt = data.split("/")
		self.data_sort = int(dt[0]) + int(dt[1]) * 30 + int(dt[2]) * 365
		self.hora = hora
		hr = hora.split(":")
		self.hora_sort = (3.6e+6)*int(hr[0]) + (6e+4)*int(hr[1]) + (1e3)*int(hr[2]) + int(hr[3])
		self.temperatura = temperatura.strip()
		self.temp_sort = int(temperatura)

	def toList(self, ind = 1):
		if ind == 1:
			return [self.local, self.data, self.hora, self.temperatura]
		elif ind == 2:
			return [self.data, self.hora, self.temperatura, self.local]
		elif ind == 3:
			return [self.hora, self.temperatura, self.local, self.data]
		else:
			return [self.temperatura, self.local, self.data, self.hora]

locais = ["Alta Floresta D'Oeste","Ariquemes","Cabixi","Cacoal","Cerejeiras","Colorado do Oeste","Corumbiara","Costa Marques","Espigão D'Oeste","Guajará-Mirim","Jaru","Ji-Paraná","Machadinho D'Oeste","Nova Brasilândia D'Oeste","Ouro Preto do Oeste","Pimenta Bueno","Porto Velho","Presidente Médici","Rio Crespo","Rolim de Moura","Santa Luzia D'Oeste","Vilhena","São Miguel do Guaporé","Nova Mamoré","Alvorada D'Oeste","Alto Alegre dos Parecis","Alto Paraíso","Buritis","Novo Horizonte do Oeste","Cacaulândia","Campo Novo de Rondônia","Candeias do Jamari","Castanheiras","Chupinguaia","Cujubim","Governador Jorge Teixeira","Itapuã do Oeste","Ministro Andreazza","Mirante da Serra","Monte Negro","Nova União","Parecis","Pimenteiras do Oeste","Primavera de Rondônia","São Felipe D'Oeste","São Francisco do Guaporé","Seringueiras","Teixeirópolis","Theobroma","Urupá","Vale do Anari","Vale do Paraíso","Acrelândia","Assis Brasil","Brasiléia","Bujari","Capixaba","Cruzeiro do Sul","Epitaciolândia","Feijó","Jordão","Mâncio Lima","Manoel Urbano","Marechal Thaumaturgo","Plácido de Castro","Porto Walter","Rio Branco","Rodrigues Alves","Santa Rosa do Purus","Senador Guiomard","Sena Madureira","Tarauacá","Xapuri","Porto Acre","Alvarães","Amaturá","Anamã","Anori","Apuí","Atalaia do Norte","Autazes","Barcelos","Barreirinha","Benjamin Constant","Beruri","Boa Vista do Ramos","Boca do Acre","Borba","Caapiranga","Canutama","Carauari","Careiro","Careiro da Várzea","Coari","Codajás","Eirunepé","Envira","Fonte Boa","Guajará","Humaitá","Ipixuna","Iranduba","Itacoatiara","Itamarati","Itapiranga","Japurá","Juruá","Jutaí","Lábrea","Manacapuru","Manaquiri","Manaus","Manicoré","Maraã","Maués","Nhamundá","Nova Olinda do Norte","Novo Airão","Novo Aripuanã","Parintins","Pauini","Presidente Figueiredo","Rio Preto da Eva","Santa Isabel do Rio Negro","Santo Antônio do Içá","São Gabriel da Cachoeira","São Paulo de Olivença","São Sebastião do Uatumã","Silves","Tabatinga","Tapauá","Tefé","Tonantins","Uarini","Urucará","Urucurituba","Amajari","Alto Alegre","Boa Vista","Bonfim","Cantá","Caracaraí","Caroebe","Iracema","Mucajaí","Normandia","Pacaraima","Rorainópolis","São João da Baliza","São Luiz","Uiramutã","Abaetetuba","Abel Figueiredo","Acará","Afuá","Água Azul do Norte","Alenquer","Almeirim","Altamira","Anajás","Ananindeua","Anapu","Augusto Corrêa","Aurora do Pará","Aveiro","Bagre","Baião","Brasília"]

# Gera uma data aleatória
def random_date():
	dia = str(random.randint(1, 27)).zfill(2)
	mes = str(random.randint(1, 12)).zfill(2)
	ano = str(random.randint(1910, 2018))
	return "/".join([dia, mes, ano])

# Gera uma hora aleatória
def random_hour():
	hora = str(random.randint(1, 23))
	min = str(random.randint(1, 59))
	sec = str(random.randint(1, 59))
	ms = str(random.randint(1, 1000))
	return ":".join([hora, min, sec, ms])

# Gera uma temperatura aleatória
def random_temp():
	return str(random.randint(0, 45))

# Gera dados por quantidade de registros
def gerar_qnt_regs(n_reg):
	global locais

	arq = open("registro.txt", "w")

	for i in range(n_reg):
		registro = Previsao(random.choice(locais), random_date(), random_hour(), random_temp()).toList()
		arq.write("||".join(registro) + "\n")

	arq.close()

# Gera dados por tamanho de arquivo final
def gerar_tam_arq(tam_arq):
	tam_atual = 0
	reg_count = 0
	tam_arq = tam_arq*1024*1024

	arq = open("registro.txt", "w")

	registros = []

	while tam_atual < tam_arq:
		registro = "||".join([random.choice(locais), random_date(), random_hour(), random_temp()])+"\n"
		registros.append(registro)
		tam_atual += len(registro) + 1
		reg_count += 1

		if reg_count % 1000000 == 0:
			reg_count = 0
			arq.write("".join(registros))
			registros = []
			print("%.2f MB/ %.2f MB" % ((tam_atual/1024)/1024, (tam_arq/1024)/1024))


	arq.write("".join(registros))

	arq.close()

# Exibe n registros
def exibir_regs(qnt_reg):
	with open("registro.txt", 'r') as raw_input:
		i = 0
		for line in raw_input:
			i += 1
			print(" ".join(line.split("||")))
			if i == qnt_reg:
				break

# Ordena os dados
def indexa_dados(lista):
	global indices
	global lista_objetos

	lista_objetos = []
	indices = []
	if '1' in lista:
		indices.append('local')
	elif '2' in lista:
		indices.append('data_sort')
	elif '3' in lista:
		indices.append('hora_sort')
	elif '4' in lista:
		indices.append('temp_sort')



	with open('registro.txt', 'r') as arquivo:
		for linha in arquivo:
			attrs = linha.split("||")
			lista_objetos.append(Previsao(attrs[0], attrs[1], attrs[2], attrs[3]))

		lista_objetos = sorted(lista_objetos, key=operator.attrgetter(*indices))


# Exibe a tabela de indices onde os dados ordenados são apresentados conforme o byte inicial
def tabela_de_indices():
	if not indices:
		print("Escolha uma forma de indexação utilizando a opção 4.")
		return

	tam = 0
	ind = 0
	for registro in lista_objetos:
		print("#%d | End: %d | Tam: %d" % (ind, tam, len("  ".join(registro.toList()))))
		ind += 1
		tam += len("  ".join(registro.toList()))

# Salva os dados indexados no arquivo registros_ordenados.txt
def salva_dados_indexados():
	if not indices:
		print("Escolha uma forma de indexação utilizando a opção 4.")
		return

	with open("registros_ordenados.txt", "w") as arquivo:
		dados = []
		cont = 0
		for registro in lista_objetos:
			dados.append("||".join(registro.toList()))
			cont += 1
			if cont % 10000 == 0:
				cont = 0
				arquivo.write("\n".join(dados))
				dados = []

		arquivo.write("\n".join(dados))

# Cria arvore B a partir da lista de registros ordenados
def cria_arvore_b(k):
	if not indices:
		print("Escolha uma forma de indexação utilizando a opção 4.")
		return -1

	b = BTree(k)
	if not lista_objetos:
		indexa_dados(indices)

	ordem_objetos = range(len(lista_objetos))

	for registro in ordem_objetos:
		b.insert(registro)

	return b



indices = []
lista_objetos = []
arvore_b = -1
ind = []

# Loop principal que mostra o menu e recebe os dados
while True:
	# Menu
	print("Escolha uma opção:")
	print("1. Gerar dados (por quantidade de registros)")
	print("2. Gerar dados (por tamanho - MB)")
	print("3. Exibir registros por paginação")
	print("4. Escolher indexação")
	print("5. Tabela de índices")
	print("6. Salvar lista indexada")
	print("7. Gerar Árvore B")
	print("8. Imprimir Árvore B")
	print("9. Busca na Árvore B")
	print("10. Salvar/Carregar Árvore B")
	print("0. Sair")

	opcao = int(raw_input(">>"))

	# Caso opção 1 seja escolhida
	if opcao == 1:
		# Recebe quantidade de registros
		qnt_reg = int(raw_input("\nQuantidade de Registros: "))
		inicio = time.time()
		gerar_qnt_regs(qnt_reg)
		fim = time.time()
		# Imprime as informações, inclusive o tempo utilizado para o processamento
		print str(qnt_reg), "registros gerados em ", str(round(fim - inicio, 4)), "segundos."
		# Espera Enter para mostra o menu novamente
		raw_input("...")

	# Caso opção 2 seja escolhida
	elif opcao == 2:
		# Recebe tamanho do arquivo
		tam_arq = int(raw_input("\nTamanho do Arquivo: "))
		inicio = time.time()
		gerar_tam_arq(tam_arq)
		fim = time.time()
		# Imprime as informações, inclusive o tempo utilizado para o processamento
		print str(tam_arq), "MB gerados em ", str(round(fim - inicio, 4)), "segundos."
		# Espera Enter para mostra o menu novamente
		raw_input("...")

	# Caso opção 3 seja escolhida
	elif opcao == 3:
		# Recebe quantidade de registros
		qnt_reg = int(raw_input("\nQuantidade de Registros: "))
		inicio = time.time()
		exibir_regs(qnt_reg)
		fim = time.time()
		# Imprime as informações, inclusive o tempo utilizado para o processamento
		print str(qnt_reg), "registros exibidos em ", str(round(fim - inicio, 4)), "segundos."
		# Espera Enter para mostra o menu novamente
		raw_input("...")

	# Caso opção 4 seja escolhida
	elif opcao == 4:
		# Pede ao usuário o critério de ordenação
		print("Escolha uma ou mais indexações (separadas por espaço):")
		print("1. Local")
		print("2. Data")
		print("3. Hora")
		print("4. Temperatura")
		ind = raw_input(">>").strip().split(" ")
		inicio = time.time()
		indexa_dados(ind)
		fim = time.time()
		# Imprime as informações, inclusive o tempo utilizado para o processamento
		print "Registros indexados em", str(round(fim - inicio, 4)), "segundos."
		# Espera Enter para mostra o menu novamente
		raw_input("...")

	# Caso opção 5 seja escolhida
	elif opcao == 5:
		inicio = time.time()
		tabela_de_indices()
		fim = time.time()
		# Imprime as informações, inclusive o tempo utilizado para o processamento
		print "Tabela de indices exibida em", str(round(fim - inicio, 4)), "segundos."
		# Espera Enter para mostra o menu novamente
		raw_input("...")

	# Caso opção 6 seja escolhida
	elif opcao == 6:
		inicio = time.time()
		salva_dados_indexados()
		fim = time.time()
		# Imprime as informações, inclusive o tempo utilizado para o processamento
		print "Dados indexados salvos em", str(round(fim - inicio, 4)), "segundos."
		# Espera Enter para mostra o menu novamente
		raw_input("...")

        # Caso opçao 7 seja escolhida
	elif opcao == 7:
		k = int(raw_input("Escolha o tamanho de página: "))
		inicio = time.time()
		arvore_b = cria_arvore_b(k)
		fim = time.time()
                # Imprime as informacoes, inclusive o tempo utilizado para o processamento
		print "Arvore B criada em", str(round(fim - inicio, 4)), "segundos."
                # Espera Enter para mostrar o menu novamente
		raw_input("...")

        # Caso opçao 8 seja escolhida
	elif opcao == 8:
                if not ind:
                    print "Dados nao ordenados, por favor utilize a funçao 4."
		elif arvore_b != -1:
			inicio = time.time()
			print arvore_b
			for item_arvore in arvore_b:
				print " ".join(lista_objetos[item_arvore].toList(int(ind[0])))
			fim = time.time()
			print "Arvore B impressa em", str(round(fim - inicio, 4)), "segundos."
		else:
			print "Arvore B ainda não criada, utilize a função 7."

                # Espera Enter para mostrar o menu novamente
		raw_input("...")

        # Caso opcao 9 seja escolhida
	elif opcao == 9:
                if not ind:
                    print "Dados nao ordenados, por favor utilize a funcao 4."
		elif arvore_b != -1:
			procura = int(raw_input("Qual indice deseja encontrar? "))
			inicio = time.time()
			for caminho in arvore_b._path_to(procura):
				print "Está em", caminho[0], "ir para o indice", caminho[1]
			fim = time.time()
			print "Caminho para o nó encontrado em", str(round(fim - inicio, 4)), "segundos."
                        print " ".join(lista_objetos[procura].toList())
		else:
			print "Arvore B ainda não criada, utilize a função 7."
		# Espera Enter para mostrar o menu novamente
		raw_input("...")

        # Caso opcao 10 seja escolhida
	elif opcao == 10:
		if arvore_b != -1:
			inicio = time.time()
			with open("arvb.pkl", "wb") as arq:
				pickle.dump(arvore_b, arq, pickle.HIGHEST_PROTOCOL)
			fim = time.time()
			print "Arvore B salva em", str(round(fim - inicio, 4)), "segundos."
		else:
			inicio = time.time()
			with open("arvb.pkl", "rb") as arq:
				arvore_b = pickle.load(arq)
			fim = time.time()
			print "Arvore B carregada em", str(round(fim - inicio, 4)), "segundos."

                # Espra Enter para mostrar o menu novamente
		raw_input("...")

	# Caso outra opção seja escolhida finaliza o programa
	else:
		arvore_b = []
		lista_objetos = []
		print("Fim")
		break
