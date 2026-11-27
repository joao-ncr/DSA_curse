/*
Uma empresa possui um servidor de arquivos organizado em uma árvore de diretórios. Cada diretório pode conter subdiretórios ou arquivos, e cada arquivo tem um tamanho em KB. O servidor tem um limite de armazenamento, e você precisa calcular algumas estatísticas.

Dada a estrutura de diretórios, determine:

O tamanho total de cada diretório (incluindo todos os arquivos em seus subdiretórios)

O maior diretório em termos de tamanho total

A quantidade de arquivos com tamanho maior que um limite X

Entrada:

Primeira linha: N (número de entradas, 1 ≤ N ≤ 1000)

Próximas N linhas: caminho tipo tamanho onde:

caminho: caminho completo do diretório pai (ex: /root/docs)

tipo: D para diretório ou A para arquivo

tamanho: tamanho em KB (0 para diretórios)

Última linha: X (limite para contagem de arquivos, 1 ≤ X ≤ 10^6)

A raiz é sempre /root

Saída:

Primeira linha: TOTAIS: seguida pelos diretórios e seus totais, ordenados alfabeticamente, no formato caminho:tamanho

Segunda linha: MAIOR: <caminho> <tamanho>

Terceira linha: ARQUIVOS_ACIMA_<X>: <n>

Por exemplo:

Input	Resultado
3
/root D 0
/root/docs D 0
/root/docs/a.pdf A 1500
1000
TOTAIS: /root:1500 /root/docs:1500
MAIOR: /root/docs 1500
ARQUIVOS_ACIMA_1000: 1

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    char nome[100];
    char caminho[300];
    char tipo; // 'D' ou 'A'
    long long tamanho;
    struct No *primeiro_filho;
    struct No *proximo_irmao;
} No;

No* criar_no(const char *nome, const char *caminho, char tipo, long long tamanho) {
    No *novo = (No*) malloc(sizeof(No));
    strcpy(novo->nome, nome);
    strcpy(novo->caminho, caminho);
    novo->tipo = tipo;
    novo->tamanho = tamanho;
    novo->primeiro_filho = NULL;
    novo->proximo_irmao = NULL;
    return novo;
}

void adicionar_filho(No *pai, No *filho) {
    if (pai->primeiro_filho == NULL) {
        pai->primeiro_filho = filho;
    } else {
        No *atual = pai->primeiro_filho;
        while (atual->proximo_irmao != NULL) {
            atual = atual->proximo_irmao;
        }
        atual->proximo_irmao = filho;
    }
}

No* buscar_no(No *atual, const char *caminho) {
    if (atual == NULL) return NULL;
    if (strcmp(atual->caminho, caminho) == 0) return atual;

    No *encontrado = buscar_no(atual->primeiro_filho, caminho);
    if (encontrado != NULL) return encontrado;

    return buscar_no(atual->proximo_irmao, caminho);
}

long long calcular_tamanhos(No *no) {
    if (no == NULL) return 0;
    if (no->tipo == 'A') return no->tamanho;

    long long soma = 0;
    No *filho = no->primeiro_filho;
    while (filho != NULL) {
        soma += calcular_tamanhos(filho);
        filho = filho->proximo_irmao;
    }
    no->tamanho = soma;
    return soma;
}

int comparar_dirs(const void *a, const void *b) {
    No *d1 = *(No**)a;
    No *d2 = *(No**)b;
    return strcmp(d1->caminho, d2->caminho);
}

void liberar_arvore(No *no) {
    if (no == NULL) return;
    No *filho = no->primeiro_filho;
    while (filho != NULL) {
        No *prox = filho->proximo_irmao;
        liberar_arvore(filho);
        filho = prox;
    }
    free(no);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    No *raiz = NULL;
    No *lista_dirs[1005];
    int qtd_dirs = 0;

    char caminhos[1005][300];
    char tipos[1005];
    long long tamanhos[1005];

    for (int i = 0; i < n; i++) {
        scanf("%s %c %lld", caminhos[i], &tipos[i], &tamanhos[i]);
    }

    long long x;
    scanf("%lld", &x);

    int arquivos_acima = 0;

    for (int i = 0; i < n; i++) {
        if (tipos[i] == 'A' && tamanhos[i] > x) {
            arquivos_acima++;
        }

        char caminho_pai[300];
        char nome[100];
        strcpy(caminho_pai, caminhos[i]);

        char *ultima_barra = strrchr(caminho_pai, '/');
        if (ultima_barra != NULL) {
            strcpy(nome, ultima_barra + 1);
            *ultima_barra = '\0';
        } else {
            strcpy(nome, caminhos[i]);
            caminho_pai[0] = '\0';
        }

        No *novo = criar_no(nome, caminhos[i], tipos[i], tamanhos[i]);

        if (strcmp(caminhos[i], "/root") == 0 || caminho_pai[0] == '\0') {
            raiz = novo;
        } else {
            No *pai = buscar_no(raiz, caminho_pai);
            if (pai != NULL) {
                adicionar_filho(pai, novo);
            }
        }

        if (tipos[i] == 'D') {
            lista_dirs[qtd_dirs++] = novo;
        }
    }

    calcular_tamanhos(raiz);
    qsort(lista_dirs, qtd_dirs, sizeof(No*), comparar_dirs);

    printf("TOTAIS:");
    for (int i = 0; i < qtd_dirs; i++) {
        printf(" %s:%lld", lista_dirs[i]->caminho, lista_dirs[i]->tamanho);
    }
    printf("\n");

    // Ignora /root (índice 0) se existirem subdiretórios
    if (qtd_dirs > 0) {
        int inicio_busca = (qtd_dirs > 1) ? 1 : 0;
        int idx_maior = inicio_busca;

        for (int i = inicio_busca + 1; i < qtd_dirs; i++) {
            if (lista_dirs[i]->tamanho > lista_dirs[idx_maior]->tamanho) {
                idx_maior = i;
            }
        }
        printf("MAIOR: %s %lld\n", lista_dirs[idx_maior]->caminho, lista_dirs[idx_maior]->tamanho);
    }

    printf("ARQUIVOS_ACIMA_%lld: %d\n", x, arquivos_acima);

    liberar_arvore(raiz);
    return 0;
}