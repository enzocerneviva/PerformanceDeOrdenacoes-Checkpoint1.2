#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


long comparacoes_qsort = 0;

// FUNÇÃO PARA IMPRESSÃO DOS 20 PRIMEIROS ELEMENTOS

void imprimir_amostra(int *v, int n) {
    printf("\nPrimeiros 20 elementos:\n[");
    int limite = n < 20 ? n : 20;
    for (int i = 0; i < limite; i++) {
        if (i != limite - 1)
            printf("%d, ", v[i]);
        else
            printf("%d", v[i]);
    }
    printf("]\n");
}

// FUNÇÕES DE ORDENAÇÃO

void bubble_sort(int *v, int n, long *comps) {
    int trocou = 1;
    do {
        trocou = 0;
        for (int i = 0; i < n - 1; i++) {
            if (comps) (*comps)++;
            if (v[i] > v[i + 1]) {
                int tmp = v[i];
                v[i] = v[i + 1];
                v[i + 1] = tmp;
                trocou = 1;
            }
        }
        n--;
    } while (trocou);
}

void insertion_sort(int *v, int n, long *comps) {
    for(int i = 1; i < n; i++){
        int chave = v[i];
        int j = i - 1;
        while (j >= 0) {

            if (comps) (*comps)++; // conta a comparação
            
            if (v[j] > chave) {
                v[j + 1] = v[j];
                j--;
            } else {
                break; // não precisa continuar
            }
        }
        v[j+1] = chave;
    }
}

int cmp_asc(const void *a, const void *b) {
    comparacoes_qsort++;
    const int *x = (const int*) a;
    const int *y = (const int*) b;
    return (*x > *y) - (*x < *y);
}


// FUNÇÕES DE GERAÇÃO DE VETORES (CENÁRIOS)

void gerar_aleatorio(int *vetor, int n) {
    srand(42); // sempre a mesma semente

    for (int i = 0; i < n; i++) {
        vetor[i] = rand() % n; // gera número de 0 até limite-1
    }
}

void gerar_crescente(int *v, int n) {
    for (int i = 0; i < n; i++) {
        v[i] = i; 
    }
}

void gerar_reverso(int *v, int n) {
    for (int i = 0; i < n; i++) {
        v[i] = n - 1 - i;
    }
}

void gerar_quase_ordenado(int *v, int n) {
    // 1. começa ordenado crescente
    for (int i = 0; i < n; i++) {
        v[i] = i;
    }

    // 2. define quantidade elementos que vão sofrer perturbação (10%)
    int perturbacoes = n / 10;

    srand(42); // mesma semente p/ consistência

    // 3. aplica perturbações aleatórias
    for (int k = 0; k < perturbacoes; k++) {
        int i = rand() % n; // índice aleatório i
        int j = rand() % n; // índice aleatório j
        // troca posições i e j
        int temp = v[i];
        v[i] = v[j];
        v[j] = temp;
    }
}


// MAIN - MENU PARA TESTES

int main() {

    int sair = 1;
    do{
        int n = 0;
        int tamanhoEscolhido = 0;
        int opcAlg, opcCen = 0;
        int dados[10000];
        long contagem_comparacoes = 0;
        double tempo_de_execucao = 0;
        clock_t inicio, fim;

        // Escolha do tamanho do vetor
        printf("\nEscolha o tamanho do vetor:\n1 - 1000\n2 - 5000\n3 - 10000\n> ");
        scanf("%d", &tamanhoEscolhido);
        if (tamanhoEscolhido == 1) n = 1000;
        else if (tamanhoEscolhido == 2) n = 5000;
        else n = 10000;

        // Escolha do algoritmo
        printf("\nEscolha o algoritmo:\n1 - Bubble Sort\n2 - Insertion Sort\n3 - QSort\n> ");
        scanf("%d", &opcAlg);

        // Escolha do cenário de dados
        printf("\nEscolha o cenário de dados:\n1 - Aleatório\n2 - Crescente\n3 - Reverso\n4 - Quase Ordenado\n> ");
        scanf("%d", &opcCen);

        // Geração do vetor
        switch(opcCen) {
            case 1: gerar_aleatorio(dados, n); break;
            case 2: gerar_crescente(dados, n); break;
            case 3: gerar_reverso(dados, n); break;
            case 4: gerar_quase_ordenado(dados, n); break;
            default: gerar_aleatorio(dados, n);
        }

        // Amostra inicial
        printf("\n--- AMOSTRA INICIAL ---");
        imprimir_amostra(dados, n);

        // Execução do algoritmo e medição de tempo
        contagem_comparacoes = 0;
        comparacoes_qsort = 0; // zera contador do qsort

        inicio = clock();
        switch(opcAlg) {
            case 1: bubble_sort(dados, n, &contagem_comparacoes); break;
            case 2: insertion_sort(dados, n, &contagem_comparacoes); break;
            case 3: qsort(dados, n, sizeof(int), cmp_asc); break;
            default: bubble_sort(dados, n, &contagem_comparacoes);
        }
        fim = clock();

        tempo_de_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;

        // Resultados e Armazenamento de Dados

        printf("\n--- AMOSTRA FINAL ---");
        imprimir_amostra(dados, n);
        printf("\nTempo de execução (ms): %.6f\n", tempo_de_execucao);

        if(opcAlg == 3){
            printf("Número de comparações (estimado qsort): %ld\n", comparacoes_qsort);
        }
        else{
            printf("Número de comparações: %ld\n", contagem_comparacoes);
        }
        
        printf("Deseja fazer mais algum teste?\n0 - Não\n1 - Sim\nResposta: ");
        scanf("%d", &sair);
    }while(sair == 1);

    getchar();
    printf("\n\nPressione enter para sair...");
    getchar();

    return 0;
}