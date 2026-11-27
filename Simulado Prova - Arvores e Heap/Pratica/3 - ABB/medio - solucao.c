#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    int valor;
    struct No *esq;
    struct No *dir;
} No;

No *criar_no(int valor) {
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL) exit(1);
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

No *inserir(No *raiz, int valor) {
    if (raiz == NULL) return criar_no(valor);

    if (valor < raiz->valor)
        raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->valor)
        raiz->dir = inserir(raiz->dir, valor);

    return raiz;
}

No *menor_no(No *raiz) {
    if (raiz == NULL) return NULL;
    while (raiz->esq != NULL)
        raiz = raiz->esq;
    return raiz;
}

No *remover(No *raiz, int valor) {
    if (raiz == NULL) return NULL;

    if (valor < raiz->valor) {
        raiz->esq = remover(raiz->esq, valor);
    } else if (valor > raiz->valor) {
        raiz->dir = remover(raiz->dir, valor);
    } else {
        if (raiz->esq == NULL) {
            No *temp = raiz->dir;
            free(raiz);
            return temp;
        }

        if (raiz->dir == NULL) {
            No *temp = raiz->esq;
            free(raiz);
            return temp;
        }

        No *sucessor = menor_no(raiz->dir);
        raiz->valor = sucessor->valor;
        raiz->dir = remover(raiz->dir, sucessor->valor);
    }

    return raiz;
}

int contar_menores(No *raiz, int x) {
    if (raiz == NULL) return 0;

    if (raiz->valor < x)
        return 1 + contar_menores(raiz->esq, x) + contar_menores(raiz->dir, x);

    return contar_menores(raiz->esq, x);
}

int altura(No *raiz) {
    if (raiz == NULL) return -1;

    int he = altura(raiz->esq);
    int hd = altura(raiz->dir);

    return (he > hd ? he : hd) + 1;
}

void listar(No *raiz, int *primeiro) {
    if (raiz == NULL) return;

    listar(raiz->esq, primeiro);

    if (!(*primeiro)) printf(" ");
    printf("%d", raiz->valor);
    *primeiro = 0;

    listar(raiz->dir, primeiro);
}

void liberar(No *raiz) {
    if (raiz == NULL) return;
    liberar(raiz->esq);
    liberar(raiz->dir);
    free(raiz);
}

int main(void) {
    No *raiz = NULL;
    char linha[200];

    while (fgets(linha, sizeof(linha), stdin) != NULL) {
        char comando[30];
        int valor;

        if (sscanf(linha, "%29s", comando) != 1)
            continue;

        if (strcmp(comando, "FIM") == 0)
            break;

        if (strcmp(comando, "INSERIR") == 0) {

            if (sscanf(linha, "%*s %d", &valor) == 1)
                raiz = inserir(raiz, valor);

        } else if (strcmp(comando, "REMOVER") == 0) {

            if (sscanf(linha, "%*s %d", &valor) == 1)
                raiz = remover(raiz, valor);

        } else if (strcmp(comando, "MENORES") == 0) {

            if (sscanf(linha, "%*s %d", &valor) == 1)
                printf("%d\n", contar_menores(raiz, valor));

        } else if (strcmp(comando, "ALTURA") == 0) {

            printf("%d\n", altura(raiz));

        } else if (strcmp(comando, "LISTAR") == 0) {

            int primeiro = 1;

            if (raiz == NULL) {
                printf("VAZIA\n");
            } else {
                listar(raiz, &primeiro);
                printf("\n");
            }
        }
    }

    liberar(raiz);
    return 0;
}
