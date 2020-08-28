from random import randint
from copy import deepcopy


class SAT3CNF:
    def __init__(self, nome_arq):
        self.n_vars = 0
        self.n_clausulas = 0
        self.nome_arq = nome_arq
        self.clausulas = self.carregar_proposicoes()
        self.sol_inicial = self.gera_solucao_inicial()

    # Lendo proposições do arquivo padronizado
    def carregar_proposicoes(self):
        f = open(self.nome_arq, 'r').readlines()
        cabecalho, clausulas = f[7:8], f[8:-3]
        cabecalho_split = cabecalho[0].split()
        n_vars = int(cabecalho_split[2])
        n_clausulas = int(cabecalho_split[3])

        map_clausulas = []
        # Mapeando as clausulas para uma lista de inteiros
        for i in range(0, n_clausulas):
            mapped = list(map(int, clausulas[i].split()[:-1]))
            map_clausulas.append(mapped)

        self.n_vars = n_vars
        self.n_clausulas = n_clausulas
        return map_clausulas

    # Retorna solução inicial aleatória
    def gera_solucao_inicial(self):
        solucao = {}
        for i in range(1, self.n_vars + 1):
            val = randint(-1, 1) == 0
            solucao[i] = val
        return solucao

    # Avalia uma solução comparando o número de cláusulas totais com o número de cláusulas verdadeiras. 
    def avaliar(self, solucao):
        clausulas_true = 0
        for clausula in self.clausulas:
            a, b, c = clausula[0], clausula[1], clausula[2]

            sol_a, sol_b, sol_c = solucao.get(a), solucao.get(b), solucao.get(c)

            if a < 0: 
                sol_a = not sol_a
            if b < 0: 
                sol_b = not sol_b
            if c < 0: 
                sol_c = not sol_c

            if sol_a or sol_b or sol_c:
                clausulas_true += 1
                continue
        return self.n_clausulas - clausulas_true

    # Gera uma perturbação na solução
    def gerar_perturbacao(self, solucao):
        nova_sol = deepcopy(solucao)
        mudanca = randint(1, self.n_vars)
        val = nova_sol.get(mudanca)
        nova_sol[mudanca] = not val
        return nova_sol
