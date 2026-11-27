#include <stdio.h>

int valores[1005];
int n;
int balanceada;

int abs_int(int x) {
    return x < 0 ? -x : x;
}

int altura(int i) {
    if (i >= n || valores[i] == -1) return -1;

    int he = altura(2 * i + 1);
    int hd = altura(2 * i + 2);

    if (abs_int(he - hd) > 1)
        balanceada = 0;

    return (he > hd ? he : hd) + 1;
}

int main(void) {
    int i;

    scanf("%d", &n);

    for (i = 0; i < n; i++)
        scanf("%d", &valores[i]);

    balanceada = 1;
    int h = altura(0);

    if (balanceada) {
        printf("BALANCEADA\n");
        printf("Altura: %d\n", h);
    } else {
        printf("NAO BALANCEADA\n");
    }

    return 0;
}
