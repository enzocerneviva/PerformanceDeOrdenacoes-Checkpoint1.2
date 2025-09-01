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

## Compilação

Para compilar qualquer um dos programas, utilize o `gcc` (ou outro compilador C compatível):

```bash
gcc main.c -o main
gcc testes.c -o testes
```

## Responsável pelo Projeto

- Enzo Cardilli Cerneviva | Turma: 1CCA | RM: 563480
