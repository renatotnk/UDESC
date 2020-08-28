from annealing import Annealer
from sat3cnf import SAT3CNF
from random_search import RandomSearch
import numpy as np

def imprime_solucao(solucao):
    for (c, v) in solucao.items():
        print('Clausula %s: %d' % (c, v))

if __name__ == '__main__':
    files = ['uf20-01.cnf', 'uf100-01.cnf', 'uf250-01.cnf']
    for fname in files:
        print("Resolvendo ", fname)
        sat = SAT3CNF(fname)
        print(str(sat.n_clausulas) + ' clausulas')

        sim_annealing = Annealer(sat)
        print("\nSimulated Annealing")
        s_ann = sim_annealing.resolver()[0]
         
        random_search = RandomSearch(sat)
        print("\nRandom Search")
        s_random = random_search.resolver()
        imprime_solucao(s_ann)
        
        print("\n\n")