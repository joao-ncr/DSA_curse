#include <stdio.h>

void posOrdem(int preOrdem[], int emOrdem[], int *indice, int esquerda, int direita)
{
    if (esquerda > direita)
        return;

    int raiz = preOrdem[(*indice)++];
    int i = esquerda;

    while (emOrdem[i] != raiz)
        i++;

    posOrdem(preOrdem, emOrdem, indice, esquerda, i - 1);
    posOrdem(preOrdem, emOrdem, indice, i + 1, direita);
    printf("%d ", raiz);
}

int main(void)
{
    int n, i, indice = 0;
    int preOrdem[1000], emOrdem[1000];

    scanf("%d", &n);

    for (i = 0; i < n; i++)
        scanf("%d", &preOrdem[i]);

    for (i = 0; i < n; i++)
        scanf("%d", &emOrdem[i]);

    posOrdem(preOrdem, emOrdem, &indice, 0, n - 1);
    return 0;
}
