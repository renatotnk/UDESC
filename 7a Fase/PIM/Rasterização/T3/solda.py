from PIL import Image
import numpy as np

imagem = Image.open("solda.png")
h, w = imagem.size

fundo = 0
objeto = 255

border = 160

imagem = imagem.convert('L')
array_p = imagem.load()

for i in range (0, h):
    for j in range (0, w):
        if(array_p[i,j] > 160):
            array_p[i,j] = 255
        else: 
			array_p[i,j] = 0

a = np.array(imagem)

#Ajustando imagem, acrescentando borda
a[ :30, : ] = border
a[-30: , : ] = border
a[ : , :30] = border
a[ : ,-30: ] = border


imagem = Image.fromarray(a) 
imagem.show()
#GREYSCALE e borders


for i in range(16, h-16):
    for j in range(16, w-16):
        array_p2 = imagem.load()

        n_sup = array_p2[i-1,j]
        n_inf = array_p2[i+1,j]
        n_left = array_p2[i,j-1]
        n_right = array_p2[i,j+1]

        if ((array_p2[i,j] == objeto) and (n_left == border or n_right == border or n_inf == border or n_sup == border)):
            imagem.putpixel((i,j), border)

for i in range(h-16, 16, -1):
    for j in range(w-16, 16,-1):
        array_p2 = imagem.load()

        n_sup = array_p2[i-1,j]
        n_inf = array_p2[i+1,j]
        n_left = array_p2[i,j-1]
        n_right = array_p2[i,j+1]

        if ((array_p2[i,j] == objeto) and (n_left == border or n_right == border or n_inf == border or n_sup == border)):
            imagem.putpixel((i,j), border)


for i in range(16, h-16):
    for j in range(16, w-16):
        array_p2 = imagem.load()

        n_sup = array_p2[i-1,j]
        n_inf = array_p2[i+1,j]
        n_left = array_p2[i,j-1]
        n_right = array_p2[i,j+1]

        if ((array_p2[i,j] == objeto) and (n_left == border or n_right == border or n_inf == border or n_sup == border)):
            imagem.putpixel((i,j), border)

for i in range (0, h):
    for j in range (0, w):
        if(array_p2[i,j] > 180):
            array_p2[i,j] = 255
        else: 
			array_p2[i,j] = 0


for i in range(16, h-16):
    for j in range(16, w-16):
        array_p2 = imagem.load()

        n_sup = array_p2[i-1,j]
        n_inf = array_p2[i+1,j]
        n_left = array_p2[i,j-1]
        n_right = array_p2[i,j+1]

        if ((array_p2[i,j] == objeto) and (n_left == border or n_right == border or n_inf == border or n_sup == border)):
            imagem.putpixel((i,j), border)





imagem.save("solda_output.png")
imagem.show()
