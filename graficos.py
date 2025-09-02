import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Mapeamento dos códigos para os nomes dos algoritmos e cenários
algoritmos = {1: "Bubble Sort", 2: "Insertion Sort", 3: "QSort"}
cenarios = {1: "Aleatório", 2: "Crescente", 3: "Reverso", 4: "Quase Ordenado"}

# --- LEITURA DO ARQUIVO CSV ---
try:
    df = pd.read_csv('resultados.csv', sep=';')
except FileNotFoundError:
    print("Erro: O arquivo 'resultados.csv' não foi encontrado.")
    print("Por favor, verifique se o nome do arquivo e o caminho estão corretos.")
    exit()

# Substitui os códigos numéricos pelos nomes textuais
df['Algoritmo'] = df['Algoritmo'].map(algoritmos)
df['Cenario'] = df['Cenario'].map(cenarios)

# Separa os dados por tamanho
tamanhos_unicos = df['Tamanho'].unique()

for tamanho in tamanhos_unicos:
    df_tamanho = df[df['Tamanho'] == tamanho]

    # Prepara os dados para o gráfico de barras agrupadas
    labels = df_tamanho['Cenario'].unique()
    x = np.arange(len(labels))  # Localizações dos rótulos
    width = 0.25  # Largura das barras

    # Cria a figura e os eixos
    fig, ax = plt.subplots(figsize=(14, 8))

    # Obtém os valores de cada algoritmo para o tamanho atual
    valores_alg1 = df_tamanho[df_tamanho['Algoritmo'] == "Bubble Sort"]['Media_Comparacoes']
    valores_alg2 = df_tamanho[df_tamanho['Algoritmo'] == "Insertion Sort"]['Media_Comparacoes']
    valores_alg3 = df_tamanho[df_tamanho['Algoritmo'] == "QSort"]['Media_Comparacoes']

    # Plota as barras agrupadas
    ax.bar(x - width, valores_alg1, width, label='Bubble Sort', color='red')
    ax.bar(x, valores_alg2, width, label='Insertion Sort', color='blue')
    ax.bar(x + width, valores_alg3, width, label='QSort', color='green')

    # Adiciona rótulos, título e legenda
    ax.set_ylabel('Média de Comparações (Escala Logarítmica)')
    ax.set_xlabel('Cenário de Entrada')
    ax.set_title(f'Comparação de Comparações por Cenário (Tamanho do Array: {tamanho})')
    ax.set_xticks(x)
    ax.set_xticklabels(labels)
    ax.legend()
    ax.grid(axis='y', linestyle='--', alpha=0.7)

    # Aplica a escala logarítmica ao eixo Y
    ax.set_yscale('log')

    plt.tight_layout()
    plt.show()