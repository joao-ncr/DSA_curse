#include <stdio.h>
#include <stdlib.h>

typedef struct NoArvore {
    int id;
    struct NoArvore *primeiro_filho;
    struct NoArvore *proximo_irmao;
} NoArvore;

NoArvore *nos[1005];
int diametro_global;

NoArvore *criar_no(int id) {
    NoArvore *novo = (NoArvore *)malloc(sizeof(NoArvore));
    if (novo == NULL) exit(1);

    novo->id = id;
    novo->primeiro_filho = NULL;
    novo->proximo_irmao = NULL;

    return novo;
}

void adicionar_filho(NoArvore *pai, NoArvore *filho) {
    if (pai->primeiro_filho == NULL) {
        pai->primeiro_filho = filho;
    } else {
        NoArvore *atual = pai->primeiro_filho;
        while (atual->proximo_irmao != NULL)
            atual = atual->proximo_irmao;
        atual->proximo_irmao = filho;
    }
}

int altura(NoArvore *no) {
    int top1 = 0, top2 = 0;
    NoArvore *filho = no->primeiro_filho;

    while (filho != NULL) {
        int h = altura(filho) + 1;

        if (h > top1) {
            top2 = top1;
            top1 = h;
        } else if (h > top2) {
            top2 = h;
        }

        filho = filho->proximo_irmao;
    }

    if (top1 + top2 > diametro_global)
        diametro_global = top1 + top2;

    return top1;
}

void liberar(NoArvore *no) {
    if (no == NULL) return;

    NoArvore *filho = no->primeiro_filho;
    while (filho != NULL) {
        NoArvore *proximo = filho->proximo_irmao;
        liberar(filho);
        filho = proximo;
    }

    free(no);
}

int main(void) {
    int n, i;
    int pai[1005];

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d", &pai[i]);
        nos[i] = criar_no(i);
    }

    NoArvore *raiz = NULL;

    for (i = 0; i < n; i++) {
        if (pai[i] == -1)
            raiz = nos[i];
        else
            adicionar_filho(nos[pai[i]], nos[i]);
    }

    diametro_global = 0;
    altura(raiz);

    printf("Diametro: %d\n", diametro_global);

    liberar(raiz);

    return 0;
}
