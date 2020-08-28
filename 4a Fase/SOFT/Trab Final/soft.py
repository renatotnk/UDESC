# -*- coding: utf-8 -*-
import csv, sys
from collections import Counter, OrderedDict
from operator import itemgetter
import pandas as pd


if sys.argv[1] == "gerar":
    assembly_devs = []
    javascript_devs = []
    pascal_devs = []
    perl_devs = []
    python_devs = []
    ruby_devs = []
    vb_devs = []

    with open('GitSED2017/developers_social_network/AS_developers_social_network.csv') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            assembly_devs.append(row['developer_id_1'])
            assembly_devs.append(row['developer_id_2'])

    print("Desenvolvedores Assembly retornados.")

    assembly_dict = Counter(assembly_devs)

    with open('GitSED2017/developers_social_network/JS_developers_social_network.csv') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            javascript_devs.append(row['developer_id_1'])
            javascript_devs.append(row['developer_id_2'])

    print("Desenvolvedores Javascript retornados.")

    javascript_dict = Counter(javascript_devs)

    with open('GitSED2017/developers_social_network/PA_developers_social_network.csv') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            pascal_devs.append(row['developer_id_1'])
            pascal_devs.append(row['developer_id_2'])

    print("Desenvolvedores Pascal retornados.")

    pascal_dict = Counter(pascal_devs)

    with open('GitSED2017/developers_social_network/PL_developers_social_network.csv') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            perl_devs.append(row['developer_id_1'])
            perl_devs.append(row['developer_id_2'])

    print("Desenvolvedores Perl retornados.")

    perl_dict = Counter(perl_devs)

    with open('GitSED2017/developers_social_network/PY_developers_social_network.csv') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            python_devs.append(row['developer_id_1'])
            python_devs.append(row['developer_id_2'])

    print("Desenvolvedores Python retornados.")

    python_dict = Counter(python_devs)

    with open('GitSED2017/developers_social_network/RB_developers_social_network.csv') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            ruby_devs.append(row['developer_id_1'])
            ruby_devs.append(row['developer_id_2'])

    print("Desenvolvedores Ruby retornados.")

    ruby_dict = Counter(ruby_devs)

    with open('GitSED2017/developers_social_network/VB_developers_social_network.csv') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            vb_devs.append(row['developer_id_1'])
            vb_devs.append(row['developer_id_2'])

    print("Desenvolvedores VB retornados.")

    vb_dict = Counter(vb_devs)

    final_dict = { k: assembly_dict.get(k, 0) + javascript_dict.get(k, 0) + pascal_dict.get(k, 0) +
            perl_dict.get(k, 0) + python_dict.get(k, 0) + ruby_dict.get(k, 0) + vb_dict.get(k, 0)
            for k in set(assembly_dict) & set(javascript_dict) & set(pascal_dict) & set(perl_dict)
            & set(python_dict) & set(ruby_dict) & set(vb_dict) }

    with open('final_dict.csv', 'w') as csv_arq:
        writer = csv.writer(csv_arq)
        for key, value in final_dict.items():
            writer.writerow([key, value])

elif(sys.argv[1] == "mostrar"):
    maiores_contribuintes = {}
    with open('final_dict.csv', 'r') as arq_demo:
        reader = csv.reader(arq_demo, delimiter=',')
        for row in reader:
            if row:
                maiores_contribuintes[int(row[0])] = int(row[1])

    maiores_contribuintes_ordenado = sorted(maiores_contribuintes.items(), key=lambda x: x[1])
    maiores_contribuintes_ordenado = [[x[0], x[1]] for x in maiores_contribuintes_ordenado[::-1]]
    ids = [str(x[0]) for x in maiores_contribuintes_ordenado]
    df = pd.read_csv('GitSED2017/developer.csv', dtype=str)
    dados = []
    for id in ids:
        dados.append(df.loc[df['developer_id'].isin([id]), ['login','usr_type','created_at', 'developer_id']].values.tolist())
        
    tabela = pd.DataFrame(columns=['ID', 'Username', 'Tipo', 'Usuário desde', 'Repositórios'])
    #tabela.set_option('expand_frame_repr', False)
    for i in range(len(maiores_contribuintes_ordenado)):
        tabela.loc[i] = [maiores_contribuintes_ordenado[i][0], dados[i][0][0], dados[i][0][1], dados[i][0][2], maiores_contribuintes_ordenado[i][1]]

    print(tabela)
    exit()
