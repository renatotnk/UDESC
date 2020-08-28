# Código para hashing sort a partir do calculo baseado em endereço
  
# Tamanho da tabela de endereços
SIZE = 10
 
# Nó de fila encadeada simples
class Node(object): 
	def __init__(self, data = None): 
		self.data = data 
		self.nextNode = None

# Fila encadeada
class LinkedList(object): 
	def __init__(self): 
		self.head = None
  
	# Inserindo valores sem retirar a ordenação
	def insert(self, data): 
		newNode = Node(data) 

		if self.head == None or data < self.head.data: 
			newNode.nextNode = self.head 
			self.head = newNode 
  
		else: 
			current = self.head 
			while current.nextNode != None and current.nextNode.data < data: 
				current = current.nextNode 
  
			newNode.nextNode = current.nextNode 
			current.nextNode = newNode 
			  
# Função que ordena uma lista usando Hashing para calculo de endereço 
def hashing_sort(lista_entrada): 
	# Declarando uma lista de listas encadeadas
	lista_de_listas = [] 
	for i in range(SIZE): 
		lista_de_listas.append(LinkedList()) 
  
	# Calculando valor máximo
	maximum = max(lista_entrada) 
  
	# Encontrando o endereço de cada valor e inserindo na tabela de endereços
	for val in lista_entrada: 
		endereco = funcao_hash(val, maximum) 
		lista_de_listas[endereco].insert(val) 
	  
	# Após os valores serem encontrados, a tabela de endereços é impressa
	for i in range(SIZE): 
		current = lista_de_listas[i].head 
		print("endereco " + str(i), end = ": ") 
  
		while current != None: 
			print(current.data, end = " ") 
			current = current.nextNode 
  
		print() 
	  
	# Passando os valores ordenados para a lista passada como entrada
	index = 0
	for i in range(SIZE): 
		current = lista_de_listas[i].head 
  
		while current != None: 
			lista_entrada[index] = current.data 
			index += 1
			current = current.nextNode 
			  
  
# Função de hash (espalhamento), que utiliza como base o tamanho da tabela e o maior valor
def funcao_hash(num, maximum): 
	# Escalando para que fique sempre entre 0 e 9
	endereco = int((num * 1.0 / maximum) * (SIZE-1)) 
	return endereco 

  
# Lista de entrada não ordenada
lista_entrada = [29, 23, 14, 5, 15, 10, 3, 18, 1] 
  
# Imprimindo a lista não ordenada
print("\nLista de entrada não ordenada: " + " ".join([str(x) for x in lista_entrada])) 
  
# Fazendo a ordenação
hashing_sort(lista_entrada) 
  
# Imprimindo a lista já ordenada
print("\nLista de entrada ordenada: " + " ".join([str(x) for x in lista_entrada])) 
