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

No *buscar(No *raiz, int valor) {
    if (raiz == NULL || raiz->valor == valor) return raiz;

    if (valor < raiz->valor)
        return buscar(raiz->esq, valor);

    return buscar(raiz->dir, valor);
}

No *menor_no(No *raiz) {
    if (raiz == NULL) return NULL;
    while (raiz->esq != NULL)
        raiz = raiz->esq;
    return raiz;
}

No *maior_no(No *raiz) {
    if (raiz == NULL) return NULL;
    while (raiz->dir != NULL)
        raiz = raiz->dir;
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

        if (strcmp(comando, "DISPONIVEL") == 0 ||
            strcmp(comando, "CANCELAR") == 0) {

            if (sscanf(linha, "%*s %d", &valor) == 1)
                raiz = inserir(raiz, valor);

        } else if (strcmp(comando, "RESERVAR") == 0) {

            if (sscanf(linha, "%*s %d", &valor) == 1)
                raiz = remover(raiz, valor);

        } else if (strcmp(comando, "MENOR") == 0) {

            No *no = menor_no(raiz);

            if (no == NULL)
                printf("VAZIA\n");
            else
                printf("%d\n", no->valor);

        } else if (strcmp(comando, "MAIOR") == 0) {

            No *no = maior_no(raiz);

            if (no == NULL)
                printf("VAZIA\n");
            else
                printf("%d\n", no->valor);

        } else if (strcmp(comando, "CONSULTAR") == 0) {

            if (sscanf(linha, "%*s %d", &valor) == 1) {
                if (buscar(raiz, valor) != NULL)
                    printf("DISPONIVEL\n");
                else
                    printf("RESERVADA\n");
            }

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