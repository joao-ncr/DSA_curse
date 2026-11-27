#include <stdio.h>

int pai[1005];
int grau[1005];

int main(void) {
    int n, i;

    scanf("%d", &n);

    for (i = 0; i < n; i++)
        scanf("%d", &pai[i]);

    for (i = 0; i < n; i++)
        if (pai[i] != -1)
            grau[pai[i]]++;

    printf("Graus:");
    for (i = 0; i < n; i++)
        printf(" %d", grau[i]);
    printf("\n");

    printf("Folhas:");
    for (i = 0; i < n; i++)
        if (grau[i] == 0)
            printf(" %d", i);
    printf("\n");

    return 0;
}
