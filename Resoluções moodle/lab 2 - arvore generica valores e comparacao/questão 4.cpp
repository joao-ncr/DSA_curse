#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NoArvore {
    char nome[50];
    int valor;
    struct NoArvore *primeiro_filho;
    struct NoArvore *proximo_irmao;
} NoArvore;

NoArvore* criar_no(const char *nome, int valor) {
    NoArvore *novo = (NoArvore*) malloc(sizeof(NoArvore));
    strcpy(novo->nome, nome);
    novo->valor = valor;
    novo->primeiro_filho = NULL;
    novo->proximo_irmao = NULL;
    return novo;
}

void adicionar_filho(NoArvore *pai, NoArvore *filho) {
    if (pai->primeiro_filho == NULL) {
        pai->primeiro_filho = filho;
    } else {
        NoArvore *atual = pai->primeiro_filho;
        while (atual->proximo_irmao != NULL) {
            atual = atual->proximo_irmao;
        }
        atual->proximo_irmao = filho;
    }
}

// a) Soma todos os valores da árvore
int soma_valores(NoArvore *no) {
    if (no == NULL) return 0;

    int total = no->valor;
    NoArvore *filho = no->primeiro_filho;
    while (filho != NULL) {
        total += soma_valores(filho);
        filho = filho->proximo_irmao;
    }
    return total;
}

// b) Encontra o maior valor da árvore
int maior_valor(NoArvore *no) {
    if (no == NULL) return -2147483648;

    int maior = no->valor;
    NoArvore *filho = no->primeiro_filho;
    while (filho != NULL) {
        int m_filho = maior_valor(filho);
        if (m_filho > maior) {
            maior = m_filho;
        }
        filho = filho->proximo_irmao;
    }
    return maior;
}

// c) Encontra o menor valor da árvore
int menor_valor(NoArvore *no) {
    if (no == NULL) return 2147483647;

    int menor = no->valor;
    NoArvore *filho = no->primeiro_filho;
    while (filho != NULL) {
        int m_filho = menor_valor(filho);
        if (m_filho < menor) {
            menor = m_filho;
        }
        filho = filho->proximo_irmao;
    }
    return menor;
}

void liberar_arvore(NoArvore *no) {
    if (no == NULL) return;
    NoArvore *filho = no->primeiro_filho;
    while (filho != NULL) {
        NoArvore *prox = filho->proximo_irmao;
        liberar_arvore(filho);
        filho = prox;
    }
    free(no);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    NoArvore *nos[205];
    int tem_pai[205] = {0};
    int total_nos = 0;

    for (int i = 0; i < n; i++) {
        char nome_pai[50], nome_filho[50];
        int valor;
        if (scanf("%s %s %d", nome_pai, nome_filho, &valor) != 3) break;

        int idx_pai = -1, idx_filho = -1;

        for (int j = 0; j < total_nos; j++) {
            if (strcmp(nos[j]->nome, nome_pai) == 0) idx_pai = j;
            if (strcmp(nos[j]->nome, nome_filho) == 0) idx_filho = j;
        }

        if (idx_pai == -1) {
            idx_pai = total_nos++;
            nos[idx_pai] = criar_no(nome_pai, 0);
        }

        if (idx_filho == -1) {
            idx_filho = total_nos++;
            nos[idx_filho] = criar_no(nome_filho, valor);
        } else {
            nos[idx_filho]->valor = valor;
        }

        adicionar_filho(nos[idx_pai], nos[idx_filho]);
        tem_pai[idx_filho] = 1;
    }

    NoArvore *raiz = NULL;
    for (int i = 0; i < total_nos; i++) {
        if (!tem_pai[i]) {
            raiz = nos[i];
            break;
        }
    }

    if (raiz != NULL) {
        // Como a raiz não recebe valor explícito na entrada (fica com 0),
        // inicializamos a busca de maior e menor a partir dos filhos caso existam
        int soma = soma_valores(raiz);
        int maior = raiz->primeiro_filho ? maior_valor(raiz->primeiro_filho) : raiz->valor;
        int menor = raiz->primeiro_filho ? menor_valor(raiz->primeiro_filho) : raiz->valor;

        // Percorre os demais irmãos da raiz (todos os filhos diretos da raiz)
        NoArvore *filho = raiz->primeiro_filho;
        while (filho != NULL) {
            int max_sub = maior_valor(filho);
            int min_sub = menor_valor(filho);
            if (max_sub > maior) maior = max_sub;
            if (min_sub < menor) menor = min_sub;
            filho = filho->proximo_irmao;
        }

        printf("Soma: %d\n", soma);
        printf("Maior: %d\n", maior);
        printf("Menor: %d\n", menor);

        liberar_arvore(raiz);
    }

    return 0;
}