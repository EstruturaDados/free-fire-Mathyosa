#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


//Criando o free fire

struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

//Cadastrando 10 itens

void cadastrarItem(struct Item *item) {
    printf("Digite o nome do item: ");
    scanf("%s", item->nome);
    printf("Digite o tipo do item: ");
    scanf("%s", item->tipo);
    printf("Digite a quantidade do item: ");
    scanf("%d", &item->quantidade);
}

void mostrarItem(struct Item item) {
    printf("Nome: %s\n", item.nome);
    printf("Tipo: %s\n", item.tipo);
    printf("Quantidade: %d\n", item.quantidade);
}

void liberarMemoria(struct Item *itens);

int main(void) {
    struct Item itens[10];

    // Cadastrando os itens
    for (int i = 0; i < 10; i++) {
        printf("\nCadastro do item %d:\n", i + 1);
        cadastrarItem(&itens[i]);
    }

    // Mostrando os itens cadastrados
    printf("\n--- Itens cadastrados ---\n");
    for (int i = 0; i < 10; i++) {
        printf("\nItem %d:\n", i + 1);
        mostrarItem(itens[i]);
    }

    // Remover item pelo nome
    char nomeBusca[30];
    printf("\nDigite o nome do item que deseja remover: ");
    scanf("%s", nomeBusca);

    for (int i = 0; i < 10; i++) {
        if (strcmp(itens[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado e removido:\n");
            mostrarItem(itens[i]);
            itens[i].nome[0] = '\0';  // Remove o nome do item
            itens[i].quantidade = 0;   // Remove a quantidade do item
            break;
        }
    }

    // Mostrando os itens apos a remocao
    printf("\n--- Itens apos remocao ---\n");
    for (int i = 0; i < 10; i++) {
        if (itens[i].nome[0] != '\0') {
            mostrarItem(itens[i]);
        }
    }

    //Buscar item pelo tipo
    char tipoBusca[20];
    printf("\nDigite o tipo do item que deseja buscar: ");
    scanf("%s", tipoBusca);
    int encontrado = 0;
    for (int i = 0; i < 10; i++) {
        if (strcmp(itens[i].tipo, tipoBusca) == 0) {
            printf("\nItem encontrado:\n");
            mostrarItem(itens[i]);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Item nao encontrado.\n");
    }


    
    // Liberando memória
    liberarMemoria(itens);



    return 0;
}

void liberarMemoria(struct Item *itens) {
    free(itens);
}

