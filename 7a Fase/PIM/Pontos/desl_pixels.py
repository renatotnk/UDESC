#coding utf-8

# Autores: Henrique W. P. da SIlva
#           Mateus L. Bittencourt

from PIL import Image
from time import time

# Funcao para pegar os pontos centrais de cada linha e coluna do gabarito
def matrix(n_lin, n_col, px_in, py_in, px_fim, py_fim):
    mat = []
    # Diferenca de espaco em pixels de uma coluna para outra
    delta_x = (px_fim - px_in) / (n_col - 1)
    # Diferenca de espaco em pixels de uma linha para outra
    delta_y = (py_fim - py_in) / (n_lin - 1)

    # percorrendo cada linha da matrix / tabela
    for l in range(n_lin):
        linha = []

        for c in range(n_col):
            # calculando o ponto x(w) e y(h) do centro da 'bolinha'
            x = px_in + (delta_x * c)
            y = py_in + (delta_y * l)
            linha.append((x,y))

        mat.append(linha)

    return mat

# ------------------- Inicio do script -------------------------- #
# Tempo inicial do script
start_time = time()

# numero de linhas e colunas da matrix / tabela gabarito:
l = 15
c = 5

# altura e largura da caixa em pixels:
cx_w = 48
cx_h = 50

img = Image.open("gabarito.jpg")
img = img.convert('L')

# Largura e altura do ponto central da primeira bolinha mais a esquerda
#   da primeira parte do gabarito:
in_gab_w = 320
in_gab_h = 694
# Largura e altura do ponto central da ultima bolinha mais a direita
#   da primeira parte do gabarito:
fim_gab_w = 773
fim_gab_h = 2080
# Gerando a matrix de coord (x,y) dos pontos centrais da primeira parte do gabarito:
tabela1 = matrix(l, c, in_gab_w, in_gab_h, fim_gab_w, fim_gab_h)

# Largura e altura do ponto central da primeira bolinha mais a esquerda
#   da segunda parte do gabarito:
in_gab_w = 1307
in_gab_h = 704
# Largura e altura do ponto central da ultima bolinha mais a direita
#   da segunda parte do gabarito:
fim_gab_w = 1742
fim_gab_h = 2092
# Gerando a matrix de coord (x,y) dos pontos centrais da segunda parte do gabarito:
tabela2 = matrix(l, c, in_gab_w, in_gab_h, fim_gab_w, fim_gab_h)

# Unindo as duas partes do gabarito num so:
gabarito = tabela1 + tabela2

# Percorrendo o gabarito:
q_nr = 0
q_letra = 0
for i in range(l*2):
    q_nr += 1
    q_letra = 0
    print
    for j in range(c):
        q_letra += 1

        if q_letra == 1:
            letra = 'A'
        elif q_letra == 2:
            letra = 'B'
        elif q_letra == 3:
            letra = 'C'
        elif q_letra == 4:
            letra = 'D'
        else:
            letra = 'E'

        # Percorrendo a caixa pra fazer a media de intensidade de cor:
        cor_caixa = 0
        for y in range(cx_h):
            for x in range(cx_w):
                px_w = gabarito[i][j][0] - (cx_w / 2) + x
                px_h = gabarito[i][j][1] - (cx_h / 2) + y
                cor_caixa += img.getpixel((px_w, px_h))
        media_cor = cor_caixa / (cx_h * cx_w)

        # Limiar de decicao entre a bolinha estar preenchida ou nao:
        if media_cor <= 85:
            resposta = True
        else:
            resposta = False

        print("{}-{}: {}; \tPt central caixa(px): ({},{}); \tMedia caixa: {}.".format(q_nr, letra, resposta, gabarito[i][j][0], gabarito[i][j][1], media_cor))

# Tempo final do script
final_time = time()

# Tempo que o programa levou para executar o script
tempo_exec = final_time - start_time
print("\n\nTempo de execucao do Script: {:.2f} seg.".format(tempo_exec))

# ---------------------- Fim do script -------------------------- #