#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long comparacoes_qsort = 0;

// IMPRESSÃO DOS 20 PRIMEIROS ELEMENTOS
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

// ORDENAÇÕES
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
            if (comps) (*comps)++;
            if (v[j] > chave) {
                v[j + 1] = v[j];
                j--;
            } else break;
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

// GERAÇÃO DE VETORES
void gerar_aleatorio(int *vetor, int n) {
    srand(42);
    for (int i = 0; i < n; i++) vetor[i] = rand() % n;
}

void gerar_crescente(int *v, int n) {
    for (int i = 0; i < n; i++) v[i] = i;
}

void gerar_reverso(int *v, int n) {
    for (int i = 0; i < n; i++) v[i] = n - 1 - i;
}

void gerar_quase_ordenado(int *v, int n) {
    for (int i = 0; i < n; i++) v[i] = i;
    int perturbacoes = n / 10;
    srand(42);
    for (int k = 0; k < perturbacoes; k++) {
        int i = rand() % n;
        int j = rand() % n;
        int temp = v[i]; v[i] = v[j]; v[j] = temp;
    }
}

// MÉDIA E MEDIANA
double media(long arr[], int n) {
    double soma = 0;
    for(int i=0;i<n;i++) soma += arr[i];
    return soma / n;
}

double mediana(double arr[], int n) {
    for(int i=0;i<n-1;i++)
        for(int j=i+1;j<n;j++)
            if(arr[i]>arr[j]){
                double tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
    if(n%2==1) return arr[n/2];
    else return (arr[n/2-1]+arr[n/2])/2.0;
}

int main() {
    int tamanhos[] = {1000, 5000, 10000};
    int algoritmos[] = {1, 2, 3};
    int cenarios[] = {1, 2, 3, 4};
    int nTamanhos = 3, nAlg = 3, nCen = 4;
    int repeticoes = 5;

    FILE* arquivo = fopen("resultados.csv", "w");
    fprintf(arquivo, "Tamanho;Algoritmo;Cenario;Mediana_Tempo(ms);Media_Comparacoes\n");

    for(int t=0;t<nTamanhos;t++){

        for(int a=0;a<nAlg;a++){

            for(int c=0;c<nCen;c++){
                
                long comps[repeticoes];
                double tempos[repeticoes];
                int n = tamanhos[t];

                for(int r=0;r<repeticoes;r++){
                    int dados[10000];
                    comparacoes_qsort=0;
                    comps[r]=0;

                    switch(cenarios[c]){
                        case 1: gerar_aleatorio(dados,n); break;
                        case 2: gerar_crescente(dados,n); break;
                        case 3: gerar_reverso(dados,n); break;
                        case 4: gerar_quase_ordenado(dados,n); break;
                    }

                    clock_t inicio = clock();
                    switch(algoritmos[a]){
                        case 1: bubble_sort(dados,n,&comps[r]); break;
                        case 2: insertion_sort(dados,n,&comps[r]); break;
                        case 3: qsort(dados,n,sizeof(int),cmp_asc); comps[r]=comparacoes_qsort; break;
                    }
                    clock_t fim = clock();
                    tempos[r] = ((double)(fim-inicio))/CLOCKS_PER_SEC*1000;
                }

                double medTempo = mediana(tempos,repeticoes);
                double medComp = media(comps,repeticoes);

                fprintf(arquivo,"%d;%d;%d;%.6f;%.0f\n", n, algoritmos[a], cenarios[c], medTempo, medComp);
                printf("Tamanho=%d, Alg=%d, Cen=%d => MedianaTempo=%.3f ms, MediaComps=%.0f\n",
                       n, algoritmos[a], cenarios[c], medTempo, medComp);
            }
        }
    }

    fclose(arquivo);
    printf("\nTodos os testes concluídos. Resultados salvos em 'Tabela_de_Resultados.csv'.\n");
    return 0;
}
