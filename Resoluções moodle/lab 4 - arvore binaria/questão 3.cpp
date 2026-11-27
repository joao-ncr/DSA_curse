/*
Dada uma árvore binária, imprima seus nós em ordem zigue-zague (ou seja, nível 0 da esquerda para a direita, nível 1 da direita para a esquerda, nível 2 da esquerda para a direita, e assim por diante).

Entrada:

Primeira linha: N (número de nós, 1 ≤ N ≤ 1000)

Segunda linha: N inteiros representando os valores dos nós em formato heap (-1 indica nó vazio)

A árvore é representada em formato heap (índice 0 = raiz)

Saída:

Os valores dos nós em ordem zigue-zague, separados por espaço
*/

#include <stdio.h>
int valores[1005];
int n;

int main(void) {
    int i;

    scanf("%d", &n);

    for (i = 0; i < n; i++)
        scanf("%d", &valores[i]);

    int fila[1005];
    int inicio = 0, fim = 0;
    fila[fim++] = 0;

    int nivel = 0;
    int primeiro = 1;

    while (inicio < fim) {
        int qtd_no_nivel = fim - inicio;
        int nivel_atual[1005];
        int qtd = 0;

        for (i = 0; i < qtd_no_nivel; i++) {
            int indice = fila[inicio++];

            nivel_atual[qtd++] = valores[indice];

            int esq = 2 * indice + 1;
            int dir = 2 * indice + 2;

            if (esq < n && valores[esq] != -1) fila[fim++] = esq;
            if (dir < n && valores[dir] != -1) fila[fim++] = dir;
        }

        if (nivel % 2 == 0) {
            for (i = 0; i < qtd; i++) {
                if (!primeiro) printf(" ");
                printf("%d", nivel_atual[i]);
                primeiro = 0;
            }
        } else {
            for (i = qtd - 1; i >= 0; i--) {
                if (!primeiro) printf(" ");
                printf("%d", nivel_atual[i]);
                primeiro = 0;
            }
        }

        nivel++;
    }

    printf("\n");

    return 0;
}
