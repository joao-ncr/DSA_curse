/*
Um jogo online mantém um ranking de jogadores identificados por pontuações únicas. O sistema usa uma ABB para armazenar as pontuações dos jogadores ativos. Quando um jogador é banido, sua pontuação é removida da ABB. Quando um jogador é reativado, sua pontuação é reinserida.

Implemente um sistema que processa as seguintes operações:

ENTRAR p: inserir a pontuação p no ranking (jogador ativo)

BANIR p: remover a pontuação p do ranking

REATIVAR p: reinserir a pontuação p no ranking

TOP k: imprimir as k maiores pontuações em ordem decrescente

BOTTOM k: imprimir as k menores pontuações em ordem crescente

MEDIANA: imprimir a mediana das pontuações ativas (se par, média dos dois centrais; se ímpar, o central)

POSICAO p: imprimir a posição (1-indexada) da pontuação p no ranking ordenado decrescente

FIM: encerrar

Entrada:

Múltiplas linhas com comandos

A entrada termina com FIM

Saída:

Para TOP k e BOTTOM k: imprimir as pontuações separadas por espaço (ou "VAZIO" se não houver jogadores suficientes)

Para MEDIANA: imprimir a mediana com 1 casa decimal se necessário, ou inteiro se exata

Para POSICAO p: imprimir a posição ou "NAO ENCONTRADO"

Por exemplo:

Input	Resultado
ENTRAR 42
TOP 1
BOTTOM 1
MEDIANA
POSICAO 42
FIM
42
42
42.0
1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    int valor;
    struct No *esq;
    struct No *dir;
} No;

No* criar_no(int valor) {
    No *novo = (No*) malloc(sizeof(No));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

No* inserir(No *raiz, int valor) {
    if (raiz == NULL) return criar_no(valor);
    if (valor < raiz->valor) {
        raiz->esq = inserir(raiz->esq, valor);
    } else if (valor > raiz->valor) {
        raiz->dir = inserir(raiz->dir, valor);
    }
    return raiz;
}

No* minimo(No *no) {
    while (no != NULL && no->esq != NULL) {
        no = no->esq;
    }
    return no;
}

No* remover(No *raiz, int valor) {
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
        } else if (raiz->dir == NULL) {
            No *temp = raiz->esq;
            free(raiz);
            return temp;
        }
        No *sucessor = minimo(raiz->dir);
        raiz->valor = sucessor->valor;
        raiz->dir = remover(raiz->dir, sucessor->valor);
    }
    return raiz;
}

// Preenche o vetor em ordem crescente (in-ordem)
void coletar_crescente(No *raiz, int v[], int *tam) {
    if (raiz == NULL) return;
    coletar_crescente(raiz->esq, v, tam);
    v[(*tam)++] = raiz->valor;
    coletar_crescente(raiz->dir, v, tam);
}

void liberar_arvore(No *raiz) {
    if (raiz == NULL) return;
    liberar_arvore(raiz->esq);
    liberar_arvore(raiz->dir);
    free(raiz);
}

int main() {
    No *raiz = NULL;
    char cmd[30];
    int arr[10005];

    while (scanf("%s", cmd) == 1) {
        if (strcmp(cmd, "FIM") == 0) {
            break;
        } else if (strcmp(cmd, "ENTRAR") == 0 || strcmp(cmd, "REATIVAR") == 0) {
            int p;
            scanf("%d", &p);
            raiz = inserir(raiz, p);
        } else if (strcmp(cmd, "BANIR") == 0) {
            int p;
            scanf("%d", &p);
            raiz = remover(raiz, p);
        } else if (strcmp(cmd, "TOP") == 0) {
            int k;
            scanf("%d", &k);
            int tam = 0;
            coletar_crescente(raiz, arr, &tam);

            if (tam < k || k <= 0) {
                printf("VAZIO\n");
            } else {
                for (int i = 0; i < k; i++) {
                    if (i > 0) printf(" ");
                    printf("%d", arr[tam - 1 - i]);
                }
                printf("\n");
            }
        } else if (strcmp(cmd, "BOTTOM") == 0) {
            int k;
            scanf("%d", &k);
            int tam = 0;
            coletar_crescente(raiz, arr, &tam);

            if (tam < k || k <= 0) {
                printf("VAZIO\n");
            } else {
                for (int i = 0; i < k; i++) {
                    if (i > 0) printf(" ");
                    printf("%d", arr[i]);
                }
                printf("\n");
            }
        } else if (strcmp(cmd, "MEDIANA") == 0) {
            int tam = 0;
            coletar_crescente(raiz, arr, &tam);

            if (tam == 0) {
                printf("VAZIO\n");
            } else if (tam % 2 == 1) {
                printf("%.1f\n", (double)arr[tam / 2]);
            } else {
                double med = (arr[tam / 2 - 1] + arr[tam / 2]) / 2.0;
                printf("%.1f\n", med);
            }
        } else if (strcmp(cmd, "POSICAO") == 0) {
            int p;
            scanf("%d", &p);
            int tam = 0;
            coletar_crescente(raiz, arr, &tam);

            int pos = -1;
            for (int i = 0; i < tam; i++) {
                if (arr[tam - 1 - i] == p) {
                    pos = i + 1;
                    break;
                }
            }

            if (pos == -1) {
                printf("NAO ENCONTRADO\n");
            } else {
                printf("%d\n", pos);
            }
        }
    }

    liberar_arvore(raiz);
    return 0;
}