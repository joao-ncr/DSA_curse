#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    int horario;
    struct No *esq;
    struct No *dir;
} No;

No *criar_no(int horario) {
    No *novo = (No *)malloc(sizeof(No));

    if (novo == NULL) exit(1);

    novo->horario = horario;
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}

No *inserir(No *raiz, int horario) {
    if (raiz == NULL)
        return criar_no(horario);

    if (horario < raiz->horario)
        raiz->esq = inserir(raiz->esq, horario);
    else if (horario > raiz->horario)
        raiz->dir = inserir(raiz->dir, horario);

    return raiz;
}

No *menor_no(No *raiz) {
    if (raiz == NULL) return NULL;

    while (raiz->esq != NULL)
        raiz = raiz->esq;

    return raiz;
}

No *remover(No *raiz, int horario) {
    if (raiz == NULL) return NULL;

    if (horario < raiz->horario) {
        raiz->esq = remover(raiz->esq, horario);

    } else if (horario > raiz->horario) {
        raiz->dir = remover(raiz->dir, horario);

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

        raiz->horario = sucessor->horario;

        raiz->dir = remover(raiz->dir, sucessor->horario);
    }

    return raiz;
}

int proximo(No *raiz, int horario, int *resultado) {
    int encontrou = 0;

    while (raiz != NULL) {
        if (raiz->horario >= horario) {
            *resultado = raiz->horario;
            encontrou = 1;
            raiz = raiz->esq;
        } else {
            raiz = raiz->dir;
        }
    }

    return encontrou;
}

int anterior(No *raiz, int horario, int *resultado) {
    int encontrou = 0;

    while (raiz != NULL) {
        if (raiz->horario < horario) {
            *resultado = raiz->horario;
            encontrou = 1;
            raiz = raiz->dir;
        } else {
            raiz = raiz->esq;
        }
    }

    return encontrou;
}

void listar(No *raiz, int *primeiro) {
    if (raiz == NULL) return;

    listar(raiz->esq, primeiro);

    if (!(*primeiro)) printf(" ");

    printf("%d", raiz->horario);

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
        int horario, resultado;

        if (sscanf(linha, "%29s", comando) != 1)
            continue;

        if (strcmp(comando, "FIM") == 0)
            break;

        if (strcmp(comando, "ABRIR") == 0 ||
            strcmp(comando, "CANCELAR") == 0) {

            if (sscanf(linha, "%*s %d", &horario) == 1)
                raiz = inserir(raiz, horario);

        } else if (strcmp(comando, "AGENDAR") == 0) {

            if (sscanf(linha, "%*s %d", &horario) == 1)
                raiz = remover(raiz, horario);

        } else if (strcmp(comando, "PROXIMO") == 0) {

            if (sscanf(linha, "%*s %d", &horario) == 1) {
                if (proximo(raiz, horario, &resultado))
                    printf("%d\n", resultado);
                else
                    printf("NAO EXISTE\n");
            }

        } else if (strcmp(comando, "ANTERIOR") == 0) {

            if (sscanf(linha, "%*s %d", &horario) == 1) {
                if (anterior(raiz, horario, &resultado))
                    printf("%d\n", resultado);
                else
                    printf("NAO EXISTE\n");
            }

        } else if (strcmp(comando, "LISTAR") == 0) {

            int primeiro = 1;

            if (raiz == NULL) {
                printf("VAZIO\n");
            } else {
                listar(raiz, &primeiro);
                printf("\n");
            }
        }
    }

    liberar(raiz);

    return 0;
}