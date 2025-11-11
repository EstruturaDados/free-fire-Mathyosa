#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>


//       Estrutura de inicio      //


typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;


//     Funções de exibição


void mostrarComponente(Componente c) {
    printf("Nome: %-20s | Tipo: %-15s | Prioridade: %d\n", c.nome, c.tipo, c.prioridade);
}

void mostrarTodos(Componente componentes[], int n) {
    printf("\n=== LISTA DE COMPONENTES ===\n");
    for (int i = 0; i < n; i++) {
        mostrarComponente(componentes[i]);
    }
}


//     Ordenação Clássica


// Bubble Sort por nome 
int bubbleSortNome(Componente v[], int n) {
    int comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(v[j].nome, v[j + 1].nome) > 0) {
                Componente temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
    return comparacoes;
}

// Insertion Sort por tipo 
int insertionSortTipo(Componente v[], int n) {
    int comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = v[i];
        int j = i - 1;

        while (j >= 0 && strcmp(v[j].tipo, chave.tipo) > 0) {
            comparacoes++;
            v[j + 1] = v[j];
            j--;
        }
        comparacoes++; // última comparação falsa
        v[j + 1] = chave;
    }
    return comparacoes;
}

// Selection Sort por prioridade 
int selectionSortPrioridade(Componente v[], int n) {
    int comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (v[j].prioridade < v[min].prioridade)
                min = j;
        }
        if (min != i) {
            Componente temp = v[i];
            v[i] = v[min];
            v[min] = temp;
        }
    }
    return comparacoes;
}


//     Busca Binária


int buscaBinariaPorNome(Componente v[], int n, char chave[]) {
    int inicio = 0, fim = n - 1, comparacoes = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes++;
        int cmp = strcmp(v[meio].nome, chave);

        if (cmp == 0) {
            printf("\nComponente encontrado:\n");
            mostrarComponente(v[meio]);
            printf("Comparações: %d\n", comparacoes);
            return meio;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    printf("\nComponente não encontrado.\nComparações: %d\n", comparacoes);
    return -1;
}


//     Medindo o tempo de execução


void medirTempo(const char* nomeAlgoritmo, int (*func)(Componente[], int), Componente vetor[], int n) {
    Componente copia[20];
    memcpy(copia, vetor, n * sizeof(Componente)); // copia para não alterar original

    clock_t inicio = clock();
    int comparacoes = func(copia, n);
    clock_t fim = clock();

    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("\n--- %s ---\n", nomeAlgoritmo);
    mostrarTodos(copia, n);
    printf("Comparações: %d\n", comparacoes);
    printf("Tempo de execução: %.6f segundos\n", tempo);
}

//         Menu interativo


void menu() {
    Componente componentes[20];
    int n = 0;
    int opc;

    do {
        printf("\n=== MONTAGEM DA TORRE ===\n");
        printf("1. Cadastrar componente\n");
        printf("2. Listar componentes\n");
        printf("3. Ordenar (Bubble Sort por Nome)\n");
        printf("4. Ordenar (Insertion Sort por Tipo)\n");
        printf("5. Ordenar (Selection Sort por Prioridade)\n");
        printf("6. Busca Binária por Nome (após ordenar por nome)\n");
        printf("0. Sair\nEscolha: ");
        scanf("%d", &opc);
        getchar(); // limpar buffe

        switch (opc) {
            case 1:
                if (n >= 20) {
                    printf("Limite de componentes atingido!\n");
                    break;
                }
                printf("Nome do componente: ");
                fgets(componentes[n].nome, 30, stdin);
                componentes[n].nome[strcspn(componentes[n].nome, "\n")] = '\0';

                printf("Tipo do componente: ");
                fgets(componentes[n].tipo, 20, stdin);
                componentes[n].tipo[strcspn(componentes[n].tipo, "\n")] = '\0';

                do {
                    printf("Prioridade (1 a 10): ");
                    scanf("%d", &componentes[n].prioridade);
                } while (componentes[n].prioridade < 1 || componentes[n].prioridade > 10);
                getchar(); // limpar buffer

                n++;
                printf("Componente cadastrado com sucesso!\n");
                break;

            case 2:
                if (n == 0) printf("Nenhum componente cadastrado.\n");
                else mostrarTodos(componentes, n);
                break;

            case 3:
                medirTempo("Bubble Sort (por Nome)", bubbleSortNome, componentes, n);
                break;

            case 4:
                medirTempo("Insertion Sort (por Tipo)", insertionSortTipo, componentes, n);
                break;

            case 5:
                medirTempo("Selection Sort (por Prioridade)", selectionSortPrioridade, componentes, n);
                break;

            case 6: {
                if (n == 0) {
                    printf("Nenhum componente cadastrado.\n");
                    break;
                }
                bubbleSortNome(componentes, n); // garantir ordenação antes de buscar
                char chave[30];
                printf("Digite o nome do componente-chave: ");
                fgets(chave, 30, stdin);
                chave[strcspn(chave, "\n")] = '\0';
                buscaBinariaPorNome(componentes, n, chave);
                break;
            }
        }
    } while (opc != 0);
}


//           Main da estrutura


int main() {
    menu();
    printf("\nEncerrando montagem...\n");
    return 0;
}
