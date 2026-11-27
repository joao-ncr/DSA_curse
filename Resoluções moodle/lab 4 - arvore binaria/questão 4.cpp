/*
Dada uma árvore binária representada por um array no formato heap (para o nó no índice i, o filho esquerdo está em 2i+1 e o direito em 2i+2), determine se ela é simétrica (ou seja, se é espelho de si mesma em relação à raiz).

Uma árvore é simétrica se a subárvore esquerda é o espelho da subárvore direita.

Entrada:

Primeira linha: N (número de nós, 1 ≤ N ≤ 1000)

Segunda linha: N inteiros representando os valores dos nós (-1 indica nó vazio)

A árvore é representada em formato heap (índice 0 = raiz)

Saída:

"SIMETRICA" se a árvore for simétrica

"NAO SIMETRICA" caso contrário

Por exemplo:

Input	Resultado
1
5
SIMETRICA
7
1 2 2 3 4 4 3
SIMETRICA

*/

#include <stdio.h>

int valores[1005];
int n;

int vazio(int i) {
    return i >= n || valores[i] == -1;
}

int eh_espelho(int i, int j) {
    if (vazio(i) && vazio(j)) return 1;
    if (vazio(i) || vazio(j)) return 0;
    if (valores[i] != valores[j]) return 0;

    return eh_espelho(2 * i + 1, 2 * j + 2) &&
           eh_espelho(2 * i + 2, 2 * j + 1);
}

int main(void) {
    int i;

    scanf("%d", &n);

    for (i = 0; i < n; i++)
        scanf("%d", &valores[i]);

    if (eh_espelho(1, 2))
        printf("SIMETRICA\n");
    else
        printf("NAO SIMETRICA\n");

    return 0;
}
