#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NoArvore {
    char nome[50];
    struct NoArvore *primeiro_filho;
    struct NoArvore *proximo_irmao;
} NoArvore;

NoArvore *nos[205];
int eh_filho[205];
int quantidade = 0;

NoArvore *buscar_ou_criar(char *nome) {
    int i;

    for (i = 0; i < quantidade; i++) {
        if (strcmp(nos[i]->nome, nome) == 0)
            return nos[i];
    }

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

int contar_usuarios(NoArvore *no) {
    if (no == NULL) return 0;

    int total = 1;
    NoArvore *filho = no->primeiro_filho;

    while (filho != NULL) {
        total += contar_usuarios(filho);
        filho = filho->proximo_irmao;
    }

    return total;
}

int contar_sem_convidados(NoArvore *no) {
    if (no == NULL) return 0;

    if (no->primeiro_filho == NULL) return 1;

    int total = 0;
    NoArvore *filho = no->primeiro_filho;

    while (filho != NULL) {
        total += contar_sem_convidados(filho);
        filho = filho->proximo_irmao;
    }

    return total;
}

NoArvore *encontrar(NoArvore *no, char *nome) {
    if (no == NULL) return NULL;

    if (strcmp(no->nome, nome) == 0) return no;

    NoArvore *filho = no->primeiro_filho;

    while (filho != NULL) {
        NoArvore *achado = encontrar(filho, nome);
        if (achado != NULL) return achado;
        filho = filho->proximo_irmao;
    }

    return NULL;
}

int contar_filhos_diretos(NoArvore *no, char *nome) {
    NoArvore *alvo = encontrar(no, nome);

    if (alvo == NULL) return 0;

    int total = 0;
    NoArvore *filho = alvo->primeiro_filho;

    while (filho != NULL) {
        total++;
        filho = filho->proximo_irmao;
    }

    return total;
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

    char consulta[50];
    scanf("%s", consulta);

    NoArvore *raiz = NULL;
    for (i = 0; i < quantidade; i++) {
        if (!eh_filho[i]) {
            raiz = nos[i];
            break;
        }
    }

    printf("Total de usuarios: %d\n", contar_usuarios(raiz));
    printf("Sem convidados: %d\n", contar_sem_convidados(raiz));
    printf("Convidados diretos de %s: %d\n", consulta, contar_filhos_diretos(raiz, consulta));

    liberar(raiz);

    return 0;
}
