import math
from random import uniform

class Annealer:
    def __init__(self, sat, temperatura=95, n_iteracoes=250000, min_temperatura=0.01, alpha=0.05, max_perturbacoes=100):
        self.sat = sat
        self.clausulas = self.sat.clausulas
        self.solucao = sat.sol_inicial
        self.temperatura = temperatura
        self.min_temperatura = min_temperatura
        self.alpha = 1-alpha
        self.n_iteracoes = n_iteracoes
        self.max_perturbacoes = max_perturbacoes
        self.lista_aux = []
        self.lista_custos = []

    # Calcula a probabilidade de aceitar o novo custo, caso seja menor, a probabilidade é de 100% (exploitation), caso não seja
    # ainda há uma chance da solução ser escolhida (exploration).
    def probabilidade_aceitar(self, custo_anterior, custo_atual, temperatura):
        if custo_atual < custo_anterior:
            return 1.0
        else:
            return math.exp(-(custo_atual - custo_anterior) / temperatura)

    # Inicia a resolução do 3SAT por Annealing
    def resolver(self):
        solucoes = []
        i = 0
        solucao = self.sat.sol_inicial
        solucao_custo = self.sat.avaliar(solucao)
        temp = self.temperatura
        self.lista_aux.append(temp)
        self.lista_custos.append(self.sat.n_clausulas - solucao_custo)
        while temp > self.min_temperatura and i < self.n_iteracoes:
            i = 1
            sucesso = 0
            while i <= self.max_perturbacoes:
                s = self.sat.gerar_perturbacao(solucao)
                s_custo = self.sat.avaliar(s)
                delta = solucao_custo - s_custo
                ap = self.probabilidade_aceitar(solucao_custo, s_custo, temp)
                if ap > uniform(0, 1):
                    solucao = s
                    solucao_custo = s_custo
                    sucesso += 1
                i += 1
            temp = temp*self.alpha
            self.lista_aux.append(temp)
            self.lista_custos.append(self.sat.n_clausulas - solucao_custo)
            i += 1
            if solucao_custo == 0:
                if solucao not in solucoes:
                    solucoes.append(solucao)
        print("Quantidade de Soluções Encontradas: " + str(len(solucoes)))
        print(str(i) + " iterações.")
        print(solucao_custo)
        return solucoes
