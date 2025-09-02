# Atividade Checkpoint - Medindo Performance de Ordenações em C

Este repositório contém dois programas em C que implementam algoritmos de ordenação e permitem a análise de desempenho em diferentes cenários de dados. Os algoritmos disponíveis são: **Bubble Sort**, **Insertion Sort** e **QSort** (função padrão da biblioteca C).

## Arquivos

### `main.c`
- Permite ao usuário escolher **uma execução única** com:
  - Tamanho do vetor (1000, 5000 ou 10000)
  - Algoritmo de ordenação
  - Cenário de dados (aleatório, crescente, reverso ou quase ordenado)
- Exibe no console:
  - Amostra inicial e final dos 20 primeiros elementos do vetor
  - Tempo de execução
  - Número de comparações (aproximado para o qsort)

### `testes.c`
- Realiza uma **análise completa** para todas as combinações possíveis de:
  - Tamanhos do vetor: 1000, 5000, 10000
  - Algoritmos: Bubble Sort, Insertion Sort, QSort
  - Cenários de dados: Aleatório, Crescente, Reverso, Quase Ordenado
- Cada combinação é executada **5 vezes** para calcular:
  - **Mediana do tempo de execução**
  - **Média das comparações**
- Armazena os resultados no arquivo `resultados.csv` em formato CSV.

### `graficos.py`
- Script em **Python** para visualização dos resultados obtidos pelo `testes.c`.  
- Lê o arquivo `resultados.csv` gerado pelos testes de desempenho.  
- Gera **gráficos de barras agrupadas** mostrando o **número médio de comparações** para cada algoritmo em cada cenário de vetor.  
- Cada gráfico é gerado para **um tamanho específico de vetor** (1000, 5000, 10000).  
- Utiliza escala **logarítmica** no eixo Y para melhor visualização de grandes diferenças entre algoritmos simples (Bubble/Insertion) e QSort.  
- **Bibliotecas utilizadas:** `pandas`, `matplotlib`, `numpy`.
- Permite identificar visualmente como o desempenho dos algoritmos varia conforme o **cenário de entrada** e o **tamanho do vetor**.

### `resultados.csv`
- Contém os resultados finais do programa `testes.c`.
- Cada linha representa uma combinação de tamanho, algoritmo e cenário.
- Colunas:
  - `Tamanho` – tamanho do vetor testado
  - `Algoritmo` – 1 = Bubble Sort, 2 = Insertion Sort, 3 = QSort
  - `Cenario` – 1 = Aleatório, 2 = Crescente, 3 = Reverso, 4 = Quase Ordenado
  - `Tempo(ms)` – mediana do tempo de execução em milissegundos
  - `Comparacoes` – média de comparações realizadas

## Compilação

Para compilar qualquer um dos programas, utilize o `gcc` (ou outro compilador C compatível):

```bash
gcc main.c -o main
gcc testes.c -o testes
```

## Responsável pelo Projeto

- Enzo Cardilli Cerneviva | Turma: 1CCA | RM: 563480
