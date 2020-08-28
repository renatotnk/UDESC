import matplotlib.pyplot as plt
import numpy as np
import cv2
import glob

for arquivo in glob.glob('*.jpg'):
	imagem = cv2.imread(arquivo, 0)
	print ("Análise do arquivo %s\n" % (arquivo))
	print('Média: %.2f\nVariância: %.2f' % (np.mean(imagem), np.var(imagem)))
	plt.hist(imagem, bins=10)
	plt.savefig('histogramas/hist_' + arquivo)
	print('Histograma salvo em: %s\n' % ('histogramas/hist_' + arquivo))
	plt.clf()
