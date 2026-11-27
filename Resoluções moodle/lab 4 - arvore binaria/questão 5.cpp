/*
Dada uma Árvore Binária de Busca (ABB) representada em formato heap, encontre o K-ésimo menor elemento da árvore.

Entrada:

Primeira linha: N e K (1 ≤ K ≤ N ≤ 1000)

Segunda linha: N inteiros representando os valores dos nós em formato heap (-1 indica nó vazio)

A árvore é garantidamente uma ABB válida

Saída:

O K-ésimo menor elemento da árvore

Por exemplo:

Input	Resultado
7 3
10 5 15 3 7 12 20
7

*/

#include <stdio.h>

int valores[1005];
int n;
int ordenados[1005];
int qtd;

void em_ordem(int i) {
    if (i >= n || valores[i] == -1) return;

    em_ordem(2 * i + 1);
    ordenados[qtd++] = valores[i];
    em_ordem(2 * i + 2);
}

int main(void) {
    int k, i;

    scanf("%d %d", &n, &k);

    for (i = 0; i < n; i++)
        scanf("%d", &valores[i]);

    qtd = 0;
    em_ordem(0);

    printf("%d\n", ordenados[k - 1]);

    return 0;
}
