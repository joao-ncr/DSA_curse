#include <stdio.h>
#include <limits.h>

int valores[1005];
int n;

int verificar_abb(int i, long minimo, long maximo) {
    if (i >= n || valores[i] == -1) return 1;

    if (valores[i] <= minimo || valores[i] >= maximo) return 0;

    return verificar_abb(2 * i + 1, minimo, valores[i]) &&
           verificar_abb(2 * i + 2, valores[i], maximo);
}

int main(void) {
    int i;

    scanf("%d", &n);

    for (i = 0; i < n; i++)
        scanf("%d", &valores[i]);

    if (verificar_abb(0, LONG_MIN, LONG_MAX))
        printf("ABB\n");
    else
        printf("NAO ABB\n");

    return 0;
}
