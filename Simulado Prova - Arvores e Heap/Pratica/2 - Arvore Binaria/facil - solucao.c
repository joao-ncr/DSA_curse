#include <stdio.h>

int valores[1005];
int n;
int primeiro;

void preordem(int i) {
    if (i >= n || valores[i] == -1) return;

    if (!primeiro) printf(" ");
    printf("%d", valores[i]);
    primeiro = 0;

    preordem(2 * i + 1);
    preordem(2 * i + 2);
}

void emordem(int i) {
    if (i >= n || valores[i] == -1) return;

    emordem(2 * i + 1);

    if (!primeiro) printf(" ");
    printf("%d", valores[i]);
    primeiro = 0;

    emordem(2 * i + 2);
}

void posordem(int i) {
    if (i >= n || valores[i] == -1) return;

    posordem(2 * i + 1);
    posordem(2 * i + 2);

    if (!primeiro) printf(" ");
    printf("%d", valores[i]);
    primeiro = 0;
}

int main(void) {
    int i;

    scanf("%d", &n);

    for (i = 0; i < n; i++)
        scanf("%d", &valores[i]);

    printf("Pre-ordem: ");
    primeiro = 1;
    preordem(0);
    printf("\n");

    printf("Em-ordem: ");
    primeiro = 1;
    emordem(0);
    printf("\n");

    printf("Pos-ordem: ");
    primeiro = 1;
    posordem(0);
    printf("\n");

    return 0;
}
