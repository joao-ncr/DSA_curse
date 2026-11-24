
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct NoArvore {
    char nome[50];
    NoArvore *primeiro_filho;
    NoArvore *proximo_irmao;
};

NoArvore* criar_no(const char *nome) {
    NoArvore *novo = (NoArvore*) malloc(sizeof(NoArvore));
    strcpy(novo->nome, nome);
    novo->primeiro_filho = NULL;
    novo->proximo_irmao = NULL;
    return novo;
}

void adicionar_filho(NoArvore *pai, NoArvore *filho) {
    filho->proximo_irmao = pai->primeiro_filho;
    pai->primeiro_filho = filho;
}

NoArvore* buscar(NoArvore *no, const char *nome) {
    if (no == NULL) return NULL;
    if (strcmp(no->nome, nome) == 0) return no;

    NoArvore *retorno = NULL;
    NoArvore *filho = no->primeiro_filho;
    while (filho != NULL && retorno == NULL) {
        retorno = buscar(filho, nome);
        filho = filho->proximo_irmao;
    }
    return retorno;
}

// ============================================================================
// a) PRÉ-ORDEM: exibe o nó antes de seus filhos
// ============================================================================
void pre_ordem(NoArvore *no) {
    if (no == NULL) return;

    // 1. Visita a raiz da subárvore atual
    printf(" %s", no->nome);

    // 2. Percorre recursivamente todos os filhos
    NoArvore *filho = no->primeiro_filho;
    while (filho != NULL) {
        pre_ordem(filho);
        filho = filho->proximo_irmao;
    }
}

// ============================================================================
// b) PÓS-ORDEM: exibe o nó depois de seus filhos
// ============================================================================
void pos_ordem(NoArvore *no) {
    if (no == NULL) return;

    // 1. Percorre recursivamente todos os filhos primeiro
    NoArvore *filho = no->primeiro_filho;
    while (filho != NULL) {
        pos_ordem(filho);
        filho = filho->proximo_irmao;
    }

    // 2. Visita a raiz da subárvore atual por último
    printf(" %s", no->nome);
}

// ============================================================================
// c) EM LARGURA (BFS): percurso em nível usando fila auxiliar
// ============================================================================
void em_largura(NoArvore *no) {
    if (no == NULL) return;

    NoArvore* fila[1000];
    int inicio = 0;
    int fim = 0;

    fila[fim++] = no;

    while (inicio < fim) {
        NoArvore *atual = fila[inicio++];
        printf(" %s", atual->nome);

        // Enfileira todos os filhos do nó atual
        NoArvore *filho = atual->primeiro_filho;
        while (filho != NULL) {
            fila[fim++] = filho;
            filho = filho->proximo_irmao;
        }
    }
}

void liberar_subarvore(NoArvore *no) {
    if (no == NULL) return;

    NoArvore *filho = no->primeiro_filho;
    while (filho != NULL) {
        NoArvore *proximo = filho->proximo_irmao;
        liberar_subarvore(filho);
        filho = proximo;
    }
    free(no);
}

int main() {
    int n;
    char pai[50], filho[50];

    if (scanf("%d", &n) != 1) return 0;

    NoArvore *raiz = NULL;
    for (int i = 0; i < n; i++) {
        scanf("%s %s", pai, filho);

        NoArvore *no_pai = buscar(raiz, pai);
        if (no_pai == NULL) {
            raiz = criar_no(pai);
            no_pai = raiz;
        }
        NoArvore *no_filho = criar_no(filho);
        adicionar_filho(no_pai, no_filho);
    }

    // 1. Pré-ordem
    printf("Pre-ordem:");
    pre_ordem(raiz);
    printf("\n");

    // 2. Pós-ordem
    printf("Pos-ordem:");
    pos_ordem(raiz);
    printf("\n");

    // 3. Em largura
    printf("Em largura:");
    em_largura(raiz);
    printf("\n");

    liberar_subarvore(raiz);
    return 0;
}






