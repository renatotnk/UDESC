from PIL import Image
import numpy as np

imagem = Image.open("casa.jpeg")
h, w = imagem.size

objeto = 255
fundo = 0

border = 30

imagem = imagem.convert('L')
array_p = imagem.load()

for i in range (0, h):
    for j in range (0, w):
        if(array_p[i,j] > 205):
            array_p[i,j] = 255
        else: 
			array_p[i,j] = 0

a = np.array(imagem)

#Ajustando imagem, acrescentando borda
a[ :4, : ] = border
a[-4: , : ] = border
a[ : , :4] = border
a[ : ,-4: ] = border


imagem = Image.fromarray(a) 
imagem.show()
#GREYSCALE

for i in range(4, h-4):
    for j in range(4, w-4):
        array_p2 = imagem.load()
 
        n_sup = array_p2[i-1,j]
        n_inf = array_p2[i+1,j]
        n_esq = array_p2[i,j-1]
        n_dir = array_p2[i,j+1]

        if ((array_p2[i,j] == objeto) and (n_esq == border or n_dir == border or n_inf == border or n_sup == border)):
            imagem.putpixel((i,j), border)

for i in range(h-4, 4, -1):
    for j in range(w-4, 4,-1):
        array_p2 = imagem.load()

        n_sup = array_p2[i-1,j]
        n_inf = array_p2[i+1,j]
        n_esq = array_p2[i,j-1]
        n_dir = array_p2[i,j+1]

        if ((array_p2[i,j] == objeto) and (n_esq == border or n_dir == border or n_inf == border or n_sup == border)):
            imagem.putpixel((i,j), border)


for i in range(4, h-4):
    for j in range(4, w-4):
        array_p2 = imagem.load()

        n_sup = array_p2[i-1,j]
        n_inf = array_p2[i+1,j]
        n_esq = array_p2[i,j-1]
        n_dir = array_p2[i,j+1]

        if ((array_p2[i,j] == objeto) and (n_esq == border or n_dir == border or n_inf == border or n_sup == border)):
            imagem.putpixel((i,j), border)

for i in range (0, h):
    for j in range (0, w):
        if(array_p2[i,j] > 180):
            array_p2[i,j] = 255
        else: 
			array_p2[i,j] = 0

for i in range(1, h-1):
    for j in range(1, w-1):
        array_p2 = imagem.load()

        n_sup = array_p2[i-1,j]
        n_inf = array_p2[i+1,j]
        n_esq = array_p2[i,j-1]
        n_dir = array_p2[i,j+1]

        if ((array_p2[i,j] == objeto) and (n_esq == fundo and n_dir == fundo and n_inf == fundo and n_sup == fundo)):
            imagem.putpixel((i,j), fundo)



imagem.save("casa-output.jpeg")
imagem.show()
