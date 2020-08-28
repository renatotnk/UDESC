import numpy as np
import matplotlib.pyplot as plt

def f(x, iteracao = False):
	if not iteracao: 
		return (np.exp(-2*x) - x**3 + 1)

	return np.cbrt(np.exp(-2*x) + 1)	

def g(x, iteracao = False):
	if not iteracao:
		return (np.log(x + np.sin(x)))

	return (1 - np.sin(x))
	
def h(x, iteracao = False):
	if not iteracao:
		return (np.cos(1/np.log(x)))

	return (x + (x**2) * np.cos(1/np.log(x)))
	

def iteracao(funcao, aprox, max_iter=1000):
	print("Iniciando a iteracao para a funcao %s(x) com chute inicial igual a %.2f e iterando %d vezes." % (funcao.__name__, aprox, max_iter))
	aproximacoes = [aprox]
	for i in range(1,max_iter):
		aprox = funcao(aprox, True)
		aproximacoes.append(aprox)
		#print "Iter #", i, "xk =", aprox, "f(xk) =", funcao(aprox)
	
	erros = []
	for i in range(max_iter):
		erros.append(abs(aproximacoes[i] - aprox))

	plt.plot(range(1000), erros)
	plt.show()

	iteracoes = []
	for i in range(len(erros)):
		if erros[i] < 1e-1:
			iteracoes.append(i)
			break

	for i in range(len(erros)):
		if erros[i] < 1e-2:
			iteracoes.append(i)
			break

	for i in range(len(erros)):
		if erros[i] < 1e-3:
			iteracoes.append(i)
			break

	for i in range(len(erros)):
		if erros[i] < 1e-4:
			iteracoes.append(i)
			break

	for i in range(len(erros)):
		if erros[i] < 1e-5:
			iteracoes.append(i)
			break

	for i in range(len(erros)):
		if erros[i] < 1e-6:
			iteracoes.append(i)
			break

	for i in range(len(erros)):
		if erros[i] < 1e-7:
			iteracoes.append(i)
			break

	for i in range(len(erros)):
		if erros[i] < 1e-8:
			iteracoes.append(i)
			break

	for i in range(len(erros)):
		if erros[i] < 1e-9:
			iteracoes.append(i)
			break

	for i in range(len(erros)):
		if erros[i] < 1e-10:
			iteracoes.append(i)
			break

	for i in range(len(iteracoes)):
		print("O algoritmo encontrou um erro absoluto menor que 10^-%d apos %d iteracoes.\n\tx%d = %.17f | erro = %.17f" % (i+1, iteracoes[i], iteracoes[i], aproximacoes[iteracoes[i]], erros[iteracoes[i]]))


	print("\nx%d = %.17f \t f(x%d) = %.17f" % (max_iter, aprox, max_iter, funcao(aprox)))
	print "\n"

x = np.linspace(0,3,500)
y0 = [f(i) for i in x]
y1 = [g(i) for i in x]
y2 = [h(i) for i in x]

#plt.plot(x, y0, c='r')
#plt.plot(x, y1, c='g')
#plt.plot(x, y2, c='b')
#plt.show()

iteracao(f, 1)
iteracao(g, 2)
iteracao(h, 0.2)
