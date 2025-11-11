#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//     Estrutura de Inicio     


typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Nó da lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;


// Funções Comuns       


void mostrarItem(Item item) {
    printf("Nome: %s | Tipo: %s | Quantidade: %d\n", item.nome, item.tipo, item.quantidade);
}


//    Mochila (Vetor)   


#define MAX_ITENS 100

typedef struct {
    Item itens[MAX_ITENS];
    int tamanho;
} MochilaVetor;

// Inserir item no vetor
void inserirItemVetor(MochilaVetor* mochila) {
    if (mochila->tamanho >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }

    Item novo;
    printf("Nome do item: ");
    scanf("%s", novo.nome);
    printf("Tipo do item: ");
    scanf("%s", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila->itens[mochila->tamanho++] = novo;
    printf("Item inserido com sucesso!\n");
}

// Listar itens no vetor
void listarItensVetor(MochilaVetor* mochila) {
    printf("\n--- Itens da mochila (vetor) ---\n");
    for (int i = 0; i < mochila->tamanho; i++) {
        mostrarItem(mochila->itens[i]);
    }
}

// Remover item por nome
void removerItemVetor(MochilaVetor* mochila, char nome[]) {
    int i, j;
    for (i = 0; i < mochila->tamanho; i++) {
        if (strcmp(mochila->itens[i].nome, nome) == 0) {
            for (j = i; j < mochila->tamanho - 1; j++) {
                mochila->itens[j] = mochila->itens[j + 1];
            }
            mochila->tamanho--;
            printf("Item removido com sucesso!\n");
            return;
        }
    }
    printf("Item nao encontrado.\n");
}

// Busca sequencial por nome
void buscaSequencialVetor(MochilaVetor* mochila, char nome[]) {
    int comparacoes = 0;
    for (int i = 0; i < mochila->tamanho; i++) {
        comparacoes++;
        if (strcmp(mochila->itens[i].nome, nome) == 0) {
            printf("Item encontrado:\n");
            mostrarItem(mochila->itens[i]);
            printf("Comparacoes: %d\n", comparacoes);
            return;
        }
    }
    printf("Item nao encontrado.\nComparacoes: %d\n", comparacoes);
}

// Ordenar por nome 
void ordenarVetor(MochilaVetor* mochila) {
    for (int i = 0; i < mochila->tamanho - 1; i++) {
        for (int j = 0; j < mochila->tamanho - i - 1; j++) {
            if (strcmp(mochila->itens[j].nome, mochila->itens[j + 1].nome) > 0) {
                Item temp = mochila->itens[j];
                mochila->itens[j] = mochila->itens[j + 1];
                mochila->itens[j + 1] = temp;
            }
        }
    }
    printf("Itens ordenados por nome.\n");
}

// Busca binária (após ordenação)
void buscaBinariaVetor(MochilaVetor* mochila, char nome[]) {
    int inicio = 0, fim = mochila->tamanho - 1;
    int comparacoes = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes++;
        int cmp = strcmp(mochila->itens[meio].nome, nome);

        if (cmp == 0) {
            printf("Item encontrado:\n");
            mostrarItem(mochila->itens[meio]);
            printf("Comparacoes: %d\n", comparacoes);
            return;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    printf("Item nao encontrado.\nComparacoes: %d\n", comparacoes);
}


// Mochila (Lista Encadeada) 


typedef struct {
    No* inicio;
} MochilaLista;

// Inserir item na lista
void inserirItemLista(MochilaLista* mochila) {
    No* novo = (No*)malloc(sizeof(No));

    printf("Nome do item: ");
    scanf("%s", novo->dados.nome);
    printf("Tipo do item: ");
    scanf("%s", novo->dados.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = mochila->inicio;
    mochila->inicio = novo;

    printf("Item inserido na lista!\n");
}

// Listar itens da lista
void listarItensLista(MochilaLista* mochila) {
    printf("\n--- Itens da mochila (lista) ---\n");
    No* atual = mochila->inicio;
    while (atual != NULL) {
        mostrarItem(atual->dados);
        atual = atual->proximo;
    }
}

// Remover item por nome na lista
void removerItemLista(MochilaLista* mochila, char nome[]) {
    No *atual = mochila->inicio, *anterior = NULL;

    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Item nao encontrado.\n");
        return;
    }

    if (anterior == NULL)
        mochila->inicio = atual->proximo;
    else
        anterior->proximo = atual->proximo;

    free(atual);
    printf("Item removido com sucesso!\n");
}

// Busca sequencial na lista
void buscaSequencialLista(MochilaLista* mochila, char nome[]) {
    int comparacoes = 0;
    No* atual = mochila->inicio;

    while (atual != NULL) {
        comparacoes++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("Item encontrado:\n");
            mostrarItem(atual->dados);
            printf("Comparacoes: %d\n", comparacoes);
            return;
        }
        atual = atual->proximo;
    }

    printf("Item nao encontrado.\nComparacoes: %d\n", comparacoes);
}


//        Menu Vetor        


void menuVetor() {
    MochilaVetor mochila = {.tamanho = 0};
    int opc;
    char nome[30];

    do {
        printf("\n--- Mochila (Vetor) ---\n");
        printf("1. Inserir item\n2. Remover item\n3. Listar itens\n4. Buscar (sequencial)\n5. Ordenar\n6. Buscar (binária)\n0. Voltar\nEscolha: ");
        scanf("%d", &opc);

        switch (opc) {
            case 1: inserirItemVetor(&mochila); break;
            case 2:
                printf("Nome do item a remover: ");
                scanf("%s", nome);
                removerItemVetor(&mochila, nome);
                break;
            case 3: listarItensVetor(&mochila); break;
            case 4:
                printf("Nome do item a buscar: ");
                scanf("%s", nome);
                buscaSequencialVetor(&mochila, nome);
                break;
            case 5: ordenarVetor(&mochila); break;
            case 6:
                printf("Nome do item a buscar: ");
                scanf("%s", nome);
                buscaBinariaVetor(&mochila, nome);
                break;
        }
    } while (opc != 0);
}

void menuLista() {
    MochilaLista mochila = {.inicio = NULL};
    int opc;
    char nome[30];

    do {
        printf("\n--- Mochila (Lista Encadeada) ---\n");
        printf("1. Inserir item\n2. Remover item\n3. Listar itens\n4. Buscar (sequencial)\n0. Voltar\nEscolha: ");
        scanf("%d", &opc);

        switch (opc) {
            case 1: inserirItemLista(&mochila); break;
            case 2:
                printf("Nome do item a remover: ");
                scanf("%s", nome);
                removerItemLista(&mochila, nome);
                break;
            case 3: listarItensLista(&mochila); break;
            case 4:
                printf("Nome do item a buscar: ");
                scanf("%s", nome);
                buscaSequencialLista(&mochila, nome);
                break;
        }
    } while (opc != 0);
}


//        Main interativo          


int main() {
    int opc;

    do {
        printf("\n=== SISTEMA DE MOCHILA ===\n");
        printf("1. Usar Mochila (Vetor)\n");
        printf("2. Usar Mochila (Lista Encadeada)\n");
        printf("0. Sair\nEscolha: ");
        scanf("%d", &opc);

        switch (opc) {
            case 1: menuVetor(); break;
            case 2: menuLista(); break;
        }
    } while (opc != 0);

    printf("Encerrando o programa...\n");
    return 0;
}
