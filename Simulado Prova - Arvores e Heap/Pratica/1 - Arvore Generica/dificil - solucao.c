#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1005

typedef struct NoArvore {
    char nome[50];
    struct NoArvore *primeiro_filho;
    struct NoArvore *proximo_irmao;
} NoArvore;

typedef struct {
    NoArvore *no;
    NoArvore *prox_filho;
} Frame;

NoArvore *nos[MAXN];
int eh_filho[MAXN];
int quantidade = 0;

NoArvore *buscar_ou_criar(char *nome) {
    int i;

    for (i = 0; i < quantidade; i++)
        if (strcmp(nos[i]->nome, nome) == 0)
            return nos[i];

    NoArvore *novo = (NoArvore *)malloc(sizeof(NoArvore));
    if (novo == NULL) exit(1);

    strcpy(novo->nome, nome);
    novo->primeiro_filho = NULL;
    novo->proximo_irmao = NULL;

    nos[quantidade] = novo;
    eh_filho[quantidade] = 0;
    quantidade++;

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

void preordem_iterativa(NoArvore *raiz) {
    NoArvore *pilha[MAXN];
    int topo = 0;
    int primeiro = 1;

    pilha[topo++] = raiz;

    while (topo > 0) {
        NoArvore *atual = pilha[--topo];

        if (!primeiro) printf(" ");
        printf("%s", atual->nome);
        primeiro = 0;

        NoArvore *filhos[MAXN];
        int nf = 0;
        NoArvore *f = atual->primeiro_filho;

        while (f != NULL) {
            filhos[nf++] = f;
            f = f->proximo_irmao;
        }

        int i;
        for (i = nf - 1; i >= 0; i--)
            pilha[topo++] = filhos[i];
    }

    printf("\n");
}

void posordem_iterativa(NoArvore *raiz) {
    Frame pilha[MAXN];
    int topo = 0;
    int primeiro = 1;

    pilha[topo].no = raiz;
    pilha[topo].prox_filho = raiz->primeiro_filho;
    topo++;

    while (topo > 0) {
        Frame *topo_frame = &pilha[topo - 1];

        if (topo_frame->prox_filho != NULL) {
            NoArvore *filho = topo_frame->prox_filho;
            topo_frame->prox_filho = filho->proximo_irmao;

            pilha[topo].no = filho;
            pilha[topo].prox_filho = filho->primeiro_filho;
            topo++;
        } else {
            if (!primeiro) printf(" ");
            printf("%s", topo_frame->no->nome);
            primeiro = 0;

            topo--;
        }
    }

    printf("\n");
}

char *maior_subarvore(NoArvore *raiz) {
    NoArvore *ordem_bfs[MAXN];
    int pai_idx[MAXN];
    int tamanho[MAXN];
    int inicio = 0, fim = 0;

    ordem_bfs[fim] = raiz;
    pai_idx[fim] = -1;
    fim++;

    while (inicio < fim) {
        NoArvore *atual = ordem_bfs[inicio];
        int idx_atual = inicio;
        inicio++;

        NoArvore *filho = atual->primeiro_filho;
        while (filho != NULL) {
            ordem_bfs[fim] = filho;
            pai_idx[fim] = idx_atual;
            fim++;
            filho = filho->proximo_irmao;
        }
    }

    int i;
    for (i = 0; i < fim; i++)
        tamanho[i] = 1;

    for (i = fim - 1; i > 0; i--)
        tamanho[pai_idx[i]] += tamanho[i];

    int melhor = 1;
    for (i = 2; i < fim; i++)
        if (tamanho[i] > tamanho[melhor])
            melhor = i;

    return ordem_bfs[melhor]->nome;
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

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        char nome_pai[50], nome_filho[50];
        scanf("%s %s", nome_pai, nome_filho);

        NoArvore *pai = buscar_ou_criar(nome_pai);
        NoArvore *filho = buscar_ou_criar(nome_filho);

        int idx_filho;
        for (idx_filho = 0; idx_filho < quantidade; idx_filho++)
            if (nos[idx_filho] == filho) break;

        eh_filho[idx_filho] = 1;
        adicionar_filho(pai, filho);
    }

    NoArvore *raiz = NULL;
    for (i = 0; i < quantidade; i++) {
        if (!eh_filho[i]) {
            raiz = nos[i];
            break;
        }
    }

    printf("Pre-ordem: ");
    preordem_iterativa(raiz);

    printf("Pos-ordem: ");
    posordem_iterativa(raiz);

    printf("Maior subarvore: %s\n", maior_subarvore(raiz));

    liberar(raiz);

    return 0;
}
