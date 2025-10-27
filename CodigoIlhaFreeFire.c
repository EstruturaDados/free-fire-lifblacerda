#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// ===========================================
// Código da Ilha – Edição Free Fire
// Nível: Mestre 🏝️
// Simula o gerenciamento de uma mochila virtual
// com funções de inserção, remoção, ordenação e busca
// ===========================================

#define MAX_ITENS 10

// ---------- STRUCT ----------
typedef struct {
    char nome[50];
    char tipo[50];
    int quantidade;
    int prioridade; // 1 a 5
} Item;

// ---------- ENUM ----------
typedef enum {
    ORDENAR_NOME = 1,
    ORDENAR_TIPO,
    ORDENAR_PRIORIDADE
} CriterioOrdenacao;

// ---------- VARIÁVEIS GLOBAIS ----------
Item mochila[MAX_ITENS];
int numItens = 0;
bool ordenadaPorNome = false;

// ---------- FUNÇÕES AUXILIARES ----------
void limparTela() {
    for (int i = 0; i < 20; i++) printf("\n");
}

void exibirMenu() {
    printf("====================================\n");
    printf("        MOCHILA DA ILHA MISTERIOSA  \n");
    printf("====================================\n");
    printf("1. Adicionar item\n");
    printf("2. Remover item\n");
    printf("3. Listar itens\n");
    printf("4. Ordenar mochila\n");
    printf("5. Buscar item (sequencial)\n");
    printf("6. Buscar item (binária)\n");
    printf("0. Sair\n");
    printf("------------------------------------\n");
    printf("Escolha uma opção: ");
}

// ---------- INSERIR ITEM ----------
void inserirItem() {
    if (numItens >= MAX_ITENS) {
        printf("A mochila está cheia!\n");
        return;
    }

    Item novo;
    printf("Digite o nome do item: ");
    scanf(" %[^\n]", novo.nome);
    printf("Digite o tipo do item: ");
    scanf(" %[^\n]", novo.tipo);
    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);
    printf("Digite a prioridade (1 a 5): ");
    scanf("%d", &novo.prioridade);

    mochila[numItens] = novo;
    numItens++;
    ordenadaPorNome = false;
    printf("Item adicionado com sucesso!\n");
}

// ---------- REMOVER ITEM ----------
void removerItem() {
    if (numItens == 0) {
        printf("A mochila está vazia!\n");
        return;
    }

    char nomeBusca[50];
    printf("Digite o nome do item a remover: ");
    scanf(" %[^\n]", nomeBusca);

    bool encontrado = false;
    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            for (int j = i; j < numItens - 1; j++)
                mochila[j] = mochila[j + 1];
            numItens--;
            encontrado = true;
            printf("Item removido com sucesso!\n");
            break;
        }
    }

    if (!encontrado)
        printf("Item não encontrado na mochila.\n");
}

// ---------- LISTAR ITENS ----------
void listarItens() {
    if (numItens == 0) {
        printf("Nenhum item na mochila.\n");
        return;
    }

    printf("\n%-20s %-20s %-10s %-10s\n", "NOME", "TIPO", "QTD", "PRIORIDADE");
    printf("--------------------------------------------------------------\n");
    for (int i = 0; i < numItens; i++)
        printf("%-20s %-20s %-10d %-10d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
}

// ---------- ORDENAÇÃO ----------
void insertionSort(CriterioOrdenacao criterio, int *comparacoes) {
    *comparacoes = 0;

    for (int i = 1; i < numItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;

        while (j >= 0) {
            (*comparacoes)++;
            bool cond = false;

            if (criterio == ORDENAR_NOME)
                cond = strcmp(chave.nome, mochila[j].nome) < 0;
            else if (criterio == ORDENAR_TIPO)
                cond = strcmp(chave.tipo, mochila[j].tipo) < 0;
            else if (criterio == ORDENAR_PRIORIDADE)
                cond = chave.prioridade > mochila[j].prioridade; // maior prioridade vem primeiro

            if (cond) {
                mochila[j + 1] = mochila[j];
                j--;
            } else break;
        }

        mochila[j + 1] = chave;
    }
}

void menuDeOrdenacao() {
    int opcao, comparacoes;
    printf("Escolha o critério de ordenação:\n");
    printf("1. Nome\n2. Tipo\n3. Prioridade\n");
    printf("Opção: ");
    scanf("%d", &opcao);

    insertionSort(opcao, &comparacoes);
    printf("Mochila ordenada com sucesso!\n");
    printf("Comparações realizadas: %d\n", comparacoes);

    ordenadaPorNome = (opcao == ORDENAR_NOME);
}

// ---------- BUSCA SEQUENCIAL ----------
void buscaSequencial() {
    if (numItens == 0) {
        printf("A mochila está vazia!\n");
        return;
    }

    char nomeBusca[50];
    printf("Digite o nome do item para buscar: ");
    scanf(" %[^\n]", nomeBusca);

    bool encontrado = false;
    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s\nTipo: %s\nQuantidade: %d\nPrioridade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
            encontrado = true;
            break;
        }
    }

    if (!encontrado)
        printf("Item não encontrado.\n");
}

// ---------- BUSCA BINÁRIA ----------
void buscaBinariaPorNome() {
    if (!ordenadaPorNome) {
        printf("⚠️ A mochila precisa estar ordenada por nome para usar a busca binária.\n");
        return;
    }

    char nomeBusca[50];
    printf("Digite o nome do item para buscar: ");
    scanf(" %[^\n]", nomeBusca);

    int ini = 0, fim = numItens - 1;
    bool encontrado = false;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        int cmp = strcmp(nomeBusca, mochila[meio].nome);

        if (cmp == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s\nTipo: %s\nQuantidade: %d\nPrioridade: %d\n",
                   mochila[meio].nome, mochila[meio].tipo, mochila[meio].quantidade, mochila[meio].prioridade);
            encontrado = true;
            break;
        } else if (cmp < 0)
            fim = meio - 1;
        else
            ini = meio + 1;
    }

    if (!encontrado)
        printf("Item não encontrado.\n");
}

// ---------- MAIN ----------
int main() {
    int opcao;

    do {
        printf("\n");
        exibirMenu();
        scanf("%d", &opcao);
        limparTela();

        switch (opcao) {
            case 1: inserirItem(); break;
            case 2: removerItem(); break;
            case 3: listarItens(); break;
            case 4: menuDeOrdenacao(); break;
            case 5: buscaSequencial(); break;
            case 6: buscaBinariaPorNome(); break;
            case 0: printf("Encerrando o programa...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}
