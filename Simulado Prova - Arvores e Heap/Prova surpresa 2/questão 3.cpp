/*
Um centro de convenções possui salas identificadas por números inteiros únicos. O sistema de reservas mantém as salas disponíveis em uma Árvore Binária de Busca (ABB). Quando uma sala é reservada, ela é removida da ABB de disponíveis. Quando uma reserva é cancelada, a sala é reinserida na ABB.

Implemente um sistema que processa as seguintes operações:

DISPONIVEL s: inserir a sala s na ABB de disponíveis

RESERVAR s: remover a sala s da ABB (se existir) e registrar a reserva

CANCELAR s: reinserir a sala s na ABB (se não estiver disponível)

MENOR: imprimir o número da menor sala disponível

MAIOR: imprimir o número da maior sala disponível

LISTAR: imprimir todas as salas disponíveis em ordem crescente

CONSULTAR s: imprimir "DISPONIVEL" ou "RESERVADA"

FIM: encerrar

Entrada:

Múltiplas linhas com comandos

A entrada termina com FIM

Saída:

Para MENOR, MAIOR e CONSULTAR: imprimir o resultado

Para LISTAR: imprimir as salas em ordem crescente separadas por espaço (ou "VAZIA" se não houver salas)

Se MENOR ou MAIOR for consultado com a ABB vazia, imprimir "VAZIA"

Por exemplo:

Input	Resultado
DISPONIVEL 42
MENOR
MAIOR
LISTAR
FIM
42
42
42

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    int sala;
    struct No *esq;
    struct No *dir;
} No;

No* criar_no(int sala) {
    No *novo = (No*) malloc(sizeof(No));
    novo->sala = sala;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

No* inserir(No *raiz, int sala) {
    if (raiz == NULL) return criar_no(sala);
    if (sala < raiz->sala) {
        raiz->esq = inserir(raiz->esq, sala);
    } else if (sala > raiz->sala) {
        raiz->dir = inserir(raiz->dir, sala);
    }
    return raiz;
}

No* buscar(No *raiz, int sala) {
    if (raiz == NULL || raiz->sala == sala) return raiz;
    if (sala < raiz->sala) return buscar(raiz->esq, sala);
    return buscar(raiz->dir, sala);
}

No* encontrar_minimo(No *no) {
    while (no != NULL && no->esq != NULL) {
        no = no->esq;
    }
    return no;
}

No* encontrar_maximo(No *no) {
    while (no != NULL && no->dir != NULL) {
        no = no->dir;
    }
    return no;
}

No* remover(No *raiz, int sala) {
    if (raiz == NULL) return NULL;
    if (sala < raiz->sala) {
        raiz->esq = remover(raiz->esq, sala);
    } else if (sala > raiz->sala) {
        raiz->dir = remover(raiz->dir, sala);
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
        No *sucessor = encontrar_minimo(raiz->dir);
        raiz->sala = sucessor->sala;
        raiz->dir = remover(raiz->dir, sucessor->sala);
    }
    return raiz;
}

void listar_in_ordem(No *raiz, int *primeiro) {
    if (raiz == NULL) return;
    listar_in_ordem(raiz->esq, primeiro);
    if (!(*primeiro)) printf(" ");
    printf("%d", raiz->sala);
    *primeiro = 0;
    listar_in_ordem(raiz->dir, primeiro);
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

    while (scanf("%s", cmd) == 1) {
        if (strcmp(cmd, "FIM") == 0) {
            break;
        } else if (strcmp(cmd, "DISPONIVEL") == 0 || strcmp(cmd, "CANCELAR") == 0) {
            int s;
            scanf("%d", &s);
            raiz = inserir(raiz, s);
        } else if (strcmp(cmd, "RESERVAR") == 0) {
            int s;
            scanf("%d", &s);
            raiz = remover(raiz, s);
        } else if (strcmp(cmd, "MENOR") == 0) {
            No *min = encontrar_minimo(raiz);
            if (min == NULL) {
                printf("VAZIA\n");
            } else {
                printf("%d\n", min->sala);
            }
        } else if (strcmp(cmd, "MAIOR") == 0) {
            No *max = encontrar_maximo(raiz);
            if (max == NULL) {
                printf("VAZIA\n");
            } else {
                printf("%d\n", max->sala);
            }
        } else if (strcmp(cmd, "LISTAR") == 0) {
            if (raiz == NULL) {
                printf("VAZIA\n");
            } else {
                int primeiro = 1;
                listar_in_ordem(raiz, &primeiro);
                printf("\n");
            }
        } else if (strcmp(cmd, "CONSULTAR") == 0) {
            int s;
            scanf("%d", &s);
            if (buscar(raiz, s) != NULL) {
                printf("DISPONIVEL\n");
            } else {
                printf("RESERVADA\n");
            }
        }
    }

    liberar_arvore(raiz);
    return 0;
}