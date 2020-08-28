#!/usr/bin/python
# -*- coding: utf-8 -*-

import numpy as np
import matplotlib
#import matplotlib.pyplot as plt
from copy import deepcopy
import sys

#np.random.seed(5425)

class Ponto:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __eq__(self, ponto):
        return (self.x == ponto.x) and (self.y == ponto.y)

    def __str__(self):
        return ("(%d, %d)" % (self.x, self.y))

class Nodo:
    def __init__(self, x, y, pai=None):
        self.posicao = Ponto(x, y)
        self.pai = pai
        self.f = "NaN"
        self.g = "NaN"
        self.h = "NaN"

    def __eq__(self, nodo):
        return self.posicao == nodo.posicao

class Fabrica:
    def __init__(self, x, y, tipo):
        self.posicao = Ponto(x, y)
        self.tipo = tipo

class Robo:
    def __init__(self, x, y, fov):
        self.posicao = Ponto(x, y)
        self.posicao_inicial = Ponto(x, y)
        self.fov = fov
        self.ferramentas = {"bateria": 0, "braco": 0, "bomba": 0, "refr": 0, "pneum": 0}
        # Modos:
        # 'routine': Escaneia o mapa
        # 'gathering': Recolhe ferramenta(s) no campo de visão
        # 'delivering': Entrega as ferramentas para as fábricas
        self.modo = "routine"
        self.caminho_atual = []
        self.poi = [
            Ponto(0 + self.fov, 0 + self.fov),
            Ponto(0 + self.fov, (N-1) - self.fov),
            Ponto((N-1) - self.fov, 0 + self.fov),
            Ponto((N-1) - self.fov, (N-1) - self.fov),
            Ponto(int( ( (N-1) ) / 2 ), int( ( (N-1) ) / 2 ))
        ]
        self.poi = [p for p in self.poi if matriz[p.x][p.y] != 4]
        if not self.poi:
            print("Pontos de interesse não alcançáveis")
            exit()
        self.buffer = []
        self.custo_total = 0
        self.movimentos = 0
        self.custos = []

    def agir(self):
        global ferramentas
        global fabricas

        if all([self.ferramentas_suficientes(f) for f in self.ferramentas.keys()]) and self.modo != "delivering":
            self.modo = "delivering"
            #print("Trocando para modo delivering")
            self.buffer = fabricas
            self.buffer.sort(key=lambda x: self.distancia(self.posicao, x.posicao))
            self.caminho_atual = self.a_star(self.posicao, self.buffer[0].posicao)

        if self.modo == "routine":
            ferr_encon = self.scan()

            # Caso nenhuma ferramenta tenha sido encontrada no FOV
            if not ferr_encon:
                if not self.caminho_atual:
                    self.caminho_atual = self.a_star(self.posicao, np.random.choice(self.poi))
            else:
                self.buffer = ferr_encon
                self.modo = "gathering"
                #print("Trocando para modo gathering")
                self.buffer.sort(key=lambda x: self.distancia(self.posicao, x.posicao))
                self.caminho_atual = self.a_star(self.posicao, self.buffer[0].posicao)

        elif self.modo == "gathering":
            if not self.caminho_atual:
                self.ferramentas[self.buffer[0].tipo] += 1
                ferramentas.remove(self.buffer[0])
                self.buffer.remove(self.buffer[0])

                if self.buffer:
                    try:
                        while(self.ferramentas_suficientes(self.buffer[0].tipo)):
                            self.buffer.pop(0)
                    except:
                        pass #NEVER DO THIS KIDS

                if self.buffer:
                    self.caminho_atual = self.a_star(self.posicao, self.buffer[0].posicao)
                else:
                    self.modo = "routine"
                    #print(self.ferramentas)
                    #print("Trocando para modo routine")
                    self.caminho_atual = self.a_star(self.posicao, np.random.choice(self.poi))

        elif self.modo == "delivering":
            if not self.caminho_atual:
                self.buffer.pop(0)
                self.buffer.sort(key=lambda x: self.distancia(self.posicao, x.posicao))
                if not self.buffer:
                    return True
                self.caminho_atual = self.a_star(self.posicao, self.buffer[0].posicao)


        custo_movimento = CUSTOS[matriz[self.caminho_atual[0].x][self.caminho_atual[0].y]]
        self.custo_total += custo_movimento
        self.custos.append(custo_movimento)
        self.movimentos += 1
        self.posicao = deepcopy(self.caminho_atual[0])
        self.caminho_atual.pop(0)



    def a_star(self, inicio, fim):
        global matriz
        #print("Calculando A* de", inicio, "para", fim, "...")
        nodo_inicial = Nodo(inicio.x, inicio.y, None)
        nodo_inicial.g = nodo_inicial.h = nodo_inicial.f = 0
        nodo_final = Nodo(fim.x, fim.y, None)
        nodo_final.g = nodo_final.h = nodo_final.f = 0

        aberto = [nodo_inicial]
        fechado = []

        while aberto:
            nodo_atual = aberto[0]
            indice_atual = 0
            for index, item in enumerate(aberto):
                if item.f < nodo_atual.f:
                    nodo_atual = item
                    indice_atual = index

            aberto.pop(indice_atual)
            fechado.append(nodo_atual)

            if nodo_atual == nodo_final:
                caminho = []
                atual = nodo_atual
                while atual is not None:
                    caminho.insert(0, atual.posicao)
                    atual = atual.pai

                return caminho

            #print(nodo_atual.posicao)

            filhos = []
            for nova_posicao in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
                posicao_nodo = Ponto(nodo_atual.posicao.x + nova_posicao[0], nodo_atual.posicao.y + nova_posicao[1])
                if posicao_nodo.x < 0 or posicao_nodo.y < 0 or posicao_nodo.x > N-1 or posicao_nodo.y > N-1:
                    continue
                if matriz[posicao_nodo.x][posicao_nodo.y] == 4:
                    continue

                novo_nodo = Nodo(posicao_nodo.x, posicao_nodo.y, nodo_atual)

                filhos.append(novo_nodo)

            for filho in filhos:
                if filho in fechado:
                    continue

                filho.g = nodo_atual.g + CUSTOS[matriz[filho.posicao.x][filho.posicao.y]]
                filho.h = self.distancia(filho.posicao, fim)
                filho.f = filho.g + filho.h

                for nodo_aberto in aberto:
                    if filho == nodo_aberto and filho.g > nodo_aberto.g:
                        continue

                aberto.append(filho)



    def scan(self):
        x_inicial = max(0, self.posicao.x - self.fov)
        x_final = min((N-1), self.posicao.x + self.fov)
        y_inicial = max(0, self.posicao.y - self.fov)
        y_final = min((N-1), self.posicao.y +self.fov)
        ferramentas_encontradas = []
        for x in range(x_inicial, x_final + 1):
            for y in range(y_inicial, y_final + 1):
                for f in ferramentas:
                    if f.posicao == Ponto(x, y) and not self.ferramentas_suficientes(f.tipo) and matriz[f.posicao.x][f.posicao.y] != 4:
                        ferramentas_encontradas.append(f)

        return ferramentas_encontradas

    def ferramentas_suficientes(self, ferramenta):
        return self.ferramentas[ferramenta] >= necessita_tipos[ferramenta]

    def mover(self, direcao):
        if direcao == "dir":
            self.posicao.x = min(self.posicao.x + 1, N - 1)
        elif direcao == "esq":
            self.posicao.x = max(self.posicao.x - 1, 0)
        elif direcao == "cima":
            self.posicao.y = max(self.posicao.y - 1, 0)
        elif direcao == "baixo":
            self.posicao.y = min(self.posicao.y + 1, N - 1)
        else:
            print("Algo deu errado: mover()")
            exit()

    def distancia(self, ponto1, ponto2):
        return (ponto1.x - ponto2.x) ** 2 + (ponto1.y - ponto2.y) ** 2

class Ferramenta:
    def __init__(self, x, y, tipo):
        self.posicao = Ponto(x, y)
        self.tipo = tipo

cmap = matplotlib.colors.ListedColormap(['#90CB53', '#908653', '#548AC6', '#DF6A10', '#000000'])
CUSTOS = {0: 1, 1: 5, 2: 10, 3: 15, 4: float("inf")}

if len(sys.argv) < 3:
    print("Usage: python main.py <seu_ambiente.txt> <posicoes.txt>\n")

    print("seu_ambiente.txt: Este é um arquivo que contém a configuração inicial do ambiente.")
    print("  São 42 linhas com 42 números (0-4) separados por espaços em cada linha, segue abaixo os numerais e suas representações")
    print("\t0: Plano")
    print("\t1: Montanhoso")
    print("\t2: Pântano")
    print("\t3: Árido")
    print("\t4: Intransponível\n")

    print("posicoes.txt: Este é um arquivo que contém as posições iniciais do agente e das fábricas")
    print("  São 6 linhas contendo um identificador e 2 números separados por espaço, os identificadores são listados abaixo")
    print("\tagente: Agente")
    print("\tbateria: Indústria de Melhoramento Genético de Grãos")
    print("\tbraco: Empresa de Manutenção de Cascos de Embarcações")
    print("\tbomba: Indústria Petrolífera")
    print("\trefr: Fábrica de Fundição")
    print("\tpneum: Indústria de Vigas de Aço")
    exit()

with open(sys.argv[1], 'r') as arquivo:
    linhas = arquivo.readlines()
    linhas = [l.strip() for l in linhas]
    linhas = [[int(k) for k in l.split(' ')] for l in linhas]


N = len(linhas[0])
matriz = np.reshape(linhas, [N, N])

ferramentas = []
fabricas = []


qnt_tipos = {20: "bateria", 10: "braco", 8: "bomba", 6: "refr", 4: "pneum"}
necessita_tipos = {"bateria": 8, "braco": 5, "bomba": 2, "refr": 5, "pneum": 2}
ferramenta_cor = {"bateria": (80, 11, 89), "braco": (43, 43, 43), "bomba": (215, 230, 18), "refr": (219, 0, 216), "pneum": (92, 250, 250)}

for qnt in qnt_tipos.keys():
    for _ in range(qnt):
        posicao = Ponto(np.random.randint(N), np.random.randint(N))
        while(matriz[posicao.x][posicao.y] != 0 or posicao in [f.posicao for f in ferramentas]):
            posicao = Ponto(np.random.randint(N), np.random.randint(N))
        ferramentas.append(Ferramenta(posicao.x, posicao.y, qnt_tipos[qnt]))

'''for tipo in necessita_tipos.keys():
    posicao = Ponto(np.random.randint(N), np.random.randint(N))
    while(posicao in [f.posicao for f in fabricas + ferramentas]):
        posicao = Ponto(np.random.randint(N), np.random.randint(N))
    fabricas.append(Fabrica(posicao.x, posicao.y, tipo))'''



with open(sys.argv[2], 'r') as arquivo:
    linhas = arquivo.readlines()
    linhas = [l.strip() for l in linhas]
    for l in linhas:
        linha_split = l.split(" ")
        identificador, x, y = linha_split[0], int(linha_split[1]), int(linha_split[2])
        if identificador == "agente":
            agente = Robo(x, y, 4)
        else:
            fabricas.append(Fabrica(x, y, identificador))


import pygame as pg #Import aqui embaixo para não gerar mensagem

pg.init()
pg.font.init()
tam_fonte = 18
fonte = pg.font.SysFont('Trebuchet MS', tam_fonte)
fonte_alvo = pg.font.SysFont('Arial', tam_fonte)


screen = pg.display.set_mode((672, 672))
clock = pg.time.Clock()

colors = np.array([
    [144, 203, 83],
    [144, 134, 83],
    [84, 138, 198],
    [223, 106, 16],
    [0, 0, 0]
])

running = True
ready = False

surface = pg.surfarray.make_surface(colors[matriz.T])
surface = pg.transform.scale(surface, (672, 672))

escala = (672/42)

while running:
    for event in pg.event.get():
        if event.type == pg.QUIT:
            running = False

        if event.type == pg.MOUSEBUTTONDOWN:
            pos = pg.mouse.get_pos()
            x_obs, y_obs = int(pos[0] / escala), int(pos[1] / escala)
            matriz[y_obs][x_obs] = 4

        if event.type == pg.KEYDOWN:
            ready = True

    if not ready:
        surface = pg.surfarray.make_surface(colors[matriz.T])
        surface = pg.transform.scale(surface, (672, 672))

    screen.fill((30, 30, 30))
    screen.blit(surface, (0, 0))

    posicao_agente = (int(escala*agente.posicao.y), int(escala*agente.posicao.x), escala, escala)

    for f in ferramentas:
        pg.draw.rect(screen, ferramenta_cor[f.tipo], (int(escala * f.posicao.y), int(escala * f.posicao.x), escala, escala))

    for f in fabricas:
        pg.draw.circle(screen, ferramenta_cor[f.tipo], [int(escala * f.posicao.y + 1.2*escala/2), int(escala * f.posicao.x + 1.2*escala/2)], int(1.2*escala))

    if ready:
        campo_visao = pg.Surface((escala * (2 * agente.fov + 1), escala * (2 * agente.fov + 1)))
        campo_visao.set_alpha(128)
        campo_visao.fill((255,255,255))
        screen.blit(campo_visao, (posicao_agente[0] - escala * agente.fov, posicao_agente[1] - escala * agente.fov))
        pg.draw.rect(screen, (255, 0, 0), posicao_agente)
        pg.draw.rect(screen, (255, 0, 0), (posicao_agente[0] - escala * agente.fov, posicao_agente[1] - escala * agente.fov, escala * (2 * agente.fov + 1), escala * (2 * agente.fov + 1)), 2)

        infos = ['Modo: %s' % (agente.modo),
            'Baterias: %d' % (agente.ferramentas["bateria"]),
            'Braços de Solda: %d' % (agente.ferramentas["braco"]),
            'Bombas: %d' % (agente.ferramentas["bomba"]),
            'Refrigação: %d' % (agente.ferramentas["refr"]),
            'Braços Pneumáticos: %d' % (agente.ferramentas["pneum"]),
            'Custo Atual: %d' % (agente.custo_total)
            ]

        for info in infos:
            texto = fonte.render(info, True, (0, 0, 0))
            screen.blit(texto, (3, infos.index(info) * tam_fonte))

        if agente.caminho_atual:
            alvo = fonte_alvo.render('X', True, (255, 0, 0))
            screen.blit(alvo, (int(escala * agente.caminho_atual[-1].y + tam_fonte/4), int(escala * agente.caminho_atual[-1].x - tam_fonte/6)))

        done = agente.agir()
        #print(agente.custo_total, end='\r')
        if done:
            break

    pg.display.flip()
    clock.tick(24)



print(agente.ferramentas)
print("Numero de movimentos realizados:", agente.movimentos)
print("Custo final:", agente.custo_total)
print("Média de custo por movimento", agente.custo_total/agente.movimentos)

'''plt.hist(agente.custos)
plt.xlabel("Custo do terreno")
plt.ylabel("Vezes em que o terreno foi escolhido")
plt.xticks([1, 5, 10, 15], ["Plano", "Montanhoso", "Pântano", "Árido"])
plt.show()'''
