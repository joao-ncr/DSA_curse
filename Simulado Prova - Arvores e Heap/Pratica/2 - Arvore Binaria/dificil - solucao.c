#include <stdio.h>
#include <stdlib.h>

#define MAXV 100005

typedef struct No {
    int valor;
    struct No *esq;
    struct No *dir;
} No;

int pre[1005], em[1005];
int pos_em[MAXV];
int pre_idx;
int diametro_global;

No *criar_no(int valor) {
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL) exit(1);
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

No *construir(int esq_i, int dir_i) {
    if (esq_i > dir_i) return NULL;

    int valor_raiz = pre[pre_idx++];
    No *raiz = criar_no(valor_raiz);

    int meio = pos_em[valor_raiz];

    raiz->esq = construir(esq_i, meio - 1);
    raiz->dir = construir(meio + 1, dir_i);

    return raiz;
}

int primeiro;

void posordem(No *no) {
    if (no == NULL) return;

    posordem(no->esq);
    posordem(no->dir);

    if (!primeiro) printf(" ");
    printf("%d", no->valor);
    primeiro = 0;
}

int altura_e_diametro(No *no) {
    if (no == NULL) return 0;

    int he = altura_e_diametro(no->esq);
    int hd = altura_e_diametro(no->dir);

    int candidato = he + hd + 1;
    if (candidato > diametro_global)
        diametro_global = candidato;

    return (he > hd ? he : hd) + 1;
}

void liberar(No *no) {
    if (no == NULL) return;
    liberar(no->esq);
    liberar(no->dir);
    free(no);
}

int main(void) {
    int n, i;

    scanf("%d", &n);

    for (i = 0; i < n; i++)
        scanf("%d", &pre[i]);

    for (i = 0; i < n; i++) {
        scanf("%d", &em[i]);
        pos_em[em[i]] = i;
    }

    pre_idx = 0;
    No *raiz = construir(0, n - 1);

    primeiro = 1;
    posordem(raiz);
    printf("\n");

    diametro_global = 0;
    altura_e_diametro(raiz);
    printf("Diametro: %d\n", diametro_global);

    liberar(raiz);

    return 0;
}
