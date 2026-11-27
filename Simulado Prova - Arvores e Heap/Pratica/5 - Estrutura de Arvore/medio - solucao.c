#include <stdio.h>

int pai[1005];
int profundidade[1005];
int n;

int calcular_profundidade(int no) {
    if (pai[no] == -1) {
        profundidade[no] = 0;
        return 0;
    }
    if (profundidade[no] != -1) return profundidade[no];

    profundidade[no] = calcular_profundidade(pai[no]) + 1;
    return profundidade[no];
}

int lca(int u, int v) {
    int pu = profundidade[u];
    int pv = profundidade[v];

    while (pu > pv) {
        u = pai[u];
        pu--;
    }

    while (pv > pu) {
        v = pai[v];
        pv--;
    }

    while (u != v) {
        u = pai[u];
        v = pai[v];
    }

    return u;
}

int main(void) {
    int i, u, v;

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d", &pai[i]);
        profundidade[i] = -1;
    }

    scanf("%d %d", &u, &v);

    for (i = 0; i < n; i++)
        calcular_profundidade(i);

    printf("Profundidades:");
    for (i = 0; i < n; i++)
        printf(" %d", profundidade[i]);
    printf("\n");

    int altura = 0;
    for (i = 0; i < n; i++)
        if (profundidade[i] > altura)
            altura = profundidade[i];

    printf("Altura: %d\n", altura);
    printf("LCA: %d\n", lca(u, v));

    return 0;
}
