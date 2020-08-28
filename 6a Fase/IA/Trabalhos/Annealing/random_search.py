class RandomSearch:
    def __init__(self, sat, n_iteracoes=250000):
        self.sat = sat
        self.clausulas = self.sat.clausulas
        self.n_iteracoes = n_iteracoes
        self.lista_custos = []

    # Resolve o 3SAT por random search
    def resolver(self):
        i = 0
        solucao = self.sat.sol_inicial
        solucao_custo = self.sat.avaliar(solucao)
        while i < self.n_iteracoes:
            s = self.sat.gera_solucao_inicial()
            s_custo = self.sat.avaliar(s)
            i += 1
            if s_custo < solucao_custo:
                solucao = s
                solucao_custo = s_custo
            self.lista_custos.append(self.sat.n_clausulas - solucao_custo)

        print(solucao_custo)
        return(solucao)
