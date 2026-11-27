/*
Uma família possui uma árvore genealógica onde cada pessoa pode ter vários filhos. Um patrimônio deve ser distribuído seguindo a regra: cada pessoa herda igualmente entre seus filhos, que por sua vez distribuem entre os seus, e assim por diante.

Dada a árvore genealógica e o valor total do patrimônio, determine:

O valor herdado por cada pessoa (considerando que a distribuição é igualitária entre irmãos)

A pessoa que herda o maior valor

A quantidade de pessoas que herdam exatamente zero (por terem antepassados que consumiram tudo ou por serem de ramos sem filhos)

Entrada:

Primeira linha: N (número de pessoas, 1 ≤ N ≤ 1000)

Próximas N linhas: pai filho (pai = -1 indica a raiz da árvore, o ancestral comum)

Última linha: V (valor total do patrimônio, 1 ≤ V ≤ 10^9)

Saída:

Primeira linha: HERDEIROS: seguida por pessoa:valor ordenados pelo nome, com 2 casas decimais

Segunda linha: MAIOR: <pessoa> <valor>

Terceira linha: ZERADOS: <n>

Por exemplo:

Input	Resultado
3
-1 A
A B
A C
100
HERDEIROS: A:0.00 B:50.00 C:50.00
MAIOR: B 50.00
ZERADOS: 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pessoa {
    char nome[100];
    double valor;
    struct Pessoa *primeiro_filho;
    struct Pessoa *proximo_irmao;
} Pessoa;

Pessoa *lista_pessoas[1005];
int total_pessoas = 0;

Pessoa* obter_ou_criar(const char *nome) {
    for (int i = 0; i < total_pessoas; i++) {
        if (strcmp(lista_pessoas[i]->nome, nome) == 0) {
            return lista_pessoas[i];
        }
    }
    Pessoa *nova = (Pessoa*) malloc(sizeof(Pessoa));
    strcpy(nova->nome, nome);
    nova->valor = 0.0;
    nova->primeiro_filho = NULL;
    nova->proximo_irmao = NULL;
    lista_pessoas[total_pessoas++] = nova;
    return nova;
}

void adicionar_filho(Pessoa *pai, Pessoa *filho) {
    if (pai->primeiro_filho == NULL) {
        pai->primeiro_filho = filho;
    } else {
        Pessoa *atual = pai->primeiro_filho;
        while (atual->proximo_irmao != NULL) {
            atual = atual->proximo_irmao;
        }
        atual->proximo_irmao = filho;
    }
}

void distribuir_heranca(Pessoa *atual, double quantia, int eh_raiz) {
    if (atual == NULL) return;

    int qtd_filhos = 0;
    Pessoa *filho = atual->primeiro_filho;
    while (filho != NULL) {
        qtd_filhos++;
        filho = filho->proximo_irmao;
    }

    // A raiz fica com 0.00 se tiver filhos; os demais registram a quantia recebida
    if (eh_raiz && qtd_filhos > 0) {
        atual->valor = 0.0;
    } else {
        atual->valor = quantia;
    }

    if (qtd_filhos > 0) {
        double cota = quantia / qtd_filhos;
        filho = atual->primeiro_filho;
        while (filho != NULL) {
            distribuir_heranca(filho, cota, 0);
            filho = filho->proximo_irmao;
        }
    }
}

int comparar_pessoas(const void *a, const void *b) {
    Pessoa *p1 = *(Pessoa**)a;
    Pessoa *p2 = *(Pessoa**)b;
    return strcmp(p1->nome, p2->nome);
}

void liberar_memoria() {
    for (int i = 0; i < total_pessoas; i++) {
        free(lista_pessoas[i]);
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    Pessoa *raiz = NULL;

    for (int i = 0; i < n; i++) {
        char pai_nome[100], filho_nome[100];
        scanf("%s %s", pai_nome, filho_nome);

        Pessoa *filho = obter_ou_criar(filho_nome);

        if (strcmp(pai_nome, "-1") == 0) {
            raiz = filho;
        } else {
            Pessoa *pai = obter_ou_criar(pai_nome);
            adicionar_filho(pai, filho);
        }
    }

    double v;
    scanf("%lf", &v);

    distribuir_heranca(raiz, v, 1);

    qsort(lista_pessoas, total_pessoas, sizeof(Pessoa*), comparar_pessoas);

    printf("HERDEIROS:");
    int idx_maior = 0;
    int zerados = 0;

    for (int i = 0; i < total_pessoas; i++) {
        printf(" %s:%.2lf", lista_pessoas[i]->nome, lista_pessoas[i]->valor);

        if (lista_pessoas[i]->valor > lista_pessoas[idx_maior]->valor + 1e-9) {
            idx_maior = i;
        }

        if (lista_pessoas[i]->valor < 1e-9) {
            zerados++;
        }
    }
    printf("\n");

    if (total_pessoas > 0) {
        printf("MAIOR: %s %.2lf\n", lista_pessoas[idx_maior]->nome, lista_pessoas[idx_maior]->valor);
    }
    printf("ZERADOS: %d\n", zerados);

    liberar_memoria();
    return 0;
}