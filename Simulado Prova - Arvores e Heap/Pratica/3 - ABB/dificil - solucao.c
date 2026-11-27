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

int contar_intervalo(No *raiz, int a, int b) {
    if (raiz == NULL) return 0;

    int total = 0;

    if (raiz->valor >= a && raiz->valor <= b)
        total++;

    if (raiz->valor > a)
        total += contar_intervalo(raiz->esq, a, b);

    if (raiz->valor < b)
        total += contar_intervalo(raiz->dir, a, b);

    return total;
}

void coletar(No *raiz, int *valores, int *n) {
    if (raiz == NULL) return;

    coletar(raiz->esq, valores, n);
    valores[(*n)++] = raiz->valor;
    coletar(raiz->dir, valores, n);
}

No *construir_balanceada(int *valores, int inicio, int fim) {
    if (inicio > fim) return NULL;

    int meio = (inicio + fim) / 2;
    No *raiz = criar_no(valores[meio]);

    raiz->esq = construir_balanceada(valores, inicio, meio - 1);
    raiz->dir = construir_balanceada(valores, meio + 1, fim);

    return raiz;
}

void preordem(No *raiz, int *primeiro) {
    if (raiz == NULL) return;

    if (!(*primeiro)) printf(" ");
    printf("%d", raiz->valor);
    *primeiro = 0;

    preordem(raiz->esq, primeiro);
    preordem(raiz->dir, primeiro);
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
        int valor, a, b;

        if (sscanf(linha, "%29s", comando) != 1)
            continue;

        if (strcmp(comando, "FIM") == 0)
            break;

        if (strcmp(comando, "INSERIR") == 0) {

            if (sscanf(linha, "%*s %d", &valor) == 1)
                raiz = inserir(raiz, valor);

        } else if (strcmp(comando, "INTERVALO") == 0) {

            if (sscanf(linha, "%*s %d %d", &a, &b) == 2)
                printf("%d\n", contar_intervalo(raiz, a, b));

        } else if (strcmp(comando, "BALANCEAR") == 0) {

            if (raiz == NULL) {
                printf("VAZIA\n");
            } else {
                int valores[100005];
                int n = 0;

                coletar(raiz, valores, &n);
                liberar(raiz);

                raiz = construir_balanceada(valores, 0, n - 1);

                int primeiro = 1;
                preordem(raiz, &primeiro);
                printf("\n");
            }
        }
    }

    liberar(raiz);
    return 0;
}
