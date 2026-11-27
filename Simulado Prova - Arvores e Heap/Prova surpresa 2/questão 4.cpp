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
#include <limits.h>

int eh_abb(int v[], int n, int i, long long min_val, long long max_val) {
    if (i >= n || v[i] == -1) return 1;

    if (v[i] <= min_val || v[i] >= max_val) return 0;

    return eh_abb(v, n, 2 * i + 1, min_val, v[i]) &&
           eh_abb(v, n, 2 * i + 2, v[i], max_val);
}

void coletar_in_ordem(int v[], int n, int i, int arr[], int *tam) {
    if (i >= n || v[i] == -1) return;
    coletar_in_ordem(v, n, 2 * i + 1, arr, tam);
    arr[(*tam)++] = v[i];
    coletar_in_ordem(v, n, 2 * i + 2, arr, tam);
}

int buscar_caminho_abb(int v[], int n, int i, int x, int caminho[], int *tam_caminho) {
    if (i >= n || v[i] == -1) return 0;

    caminho[(*tam_caminho)++] = v[i];

    if (v[i] == x) return 1;
    if (x < v[i]) return buscar_caminho_abb(v, n, 2 * i + 1, x, caminho, tam_caminho);
    return buscar_caminho_abb(v, n, 2 * i + 2, x, caminho, tam_caminho);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    int arvore[1005];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arvore[i]);
    }

    int x, a, b;
    scanf("%d", &x);
    scanf("%d %d", &a, &b);

    // 1. Verifica se é uma ABB válida
    if (!eh_abb(arvore, n, 0, LLONG_MIN, LLONG_MAX)) {
        printf("NAO ABB\n");
        printf("SUCESSOR: NAO EXISTE\n");
        printf("ANTECESSOR: NAO EXISTE\n");
        printf("SOMA [%d,%d]: 0\n", a, b);
        printf("CAMINHO: NAO EXISTE\n");
        return 0;
    }

    printf("ABB\n");

    int arr[1005];
    int tam = 0;
    coletar_in_ordem(arvore, n, 0, arr, &tam);

    // 2. Sucessor e Antecessor de X
    int sucessor = -1, tem_sucessor = 0;
    int antecessor = -1, tem_antecessor = 0;

    for (int i = 0; i < tam; i++) {
        if (arr[i] < x) {
            antecessor = arr[i];
            tem_antecessor = 1;
        } else if (arr[i] > x && !tem_sucessor) {
            sucessor = arr[i];
            tem_sucessor = 1;
        }
    }

    if (tem_sucessor) {
        printf("SUCESSOR: %d\n", sucessor);
    } else {
        printf("SUCESSOR: NAO EXISTE\n");
    }

    if (tem_antecessor) {
        printf("ANTECESSOR: %d\n", antecessor);
    } else {
        printf("ANTECESSOR: NAO EXISTE\n");
    }

    // 3. Soma no intervalo [A, B]
    long long soma = 0;
    for (int i = 0; i < tam; i++) {
        if (arr[i] >= a && arr[i] <= b) {
            soma += arr[i];
        }
    }
    printf("SOMA [%d,%d]: %lld\n", a, b, soma);

    // 4. Caminho da raiz até X na ABB
    int caminho[1005];
    int tam_caminho = 0;
    if (buscar_caminho_abb(arvore, n, 0, x, caminho, &tam_caminho)) {
        printf("CAMINHO:");
        for (int i = 0; i < tam_caminho; i++) {
            printf(" %d", caminho[i]);
        }
        printf("\n");
    } else {
        printf("CAMINHO: NAO EXISTE\n");
    }

    return 0;
}