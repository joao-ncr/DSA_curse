#include <stdio.h>

#define MAXN 1000

int v[MAXN];

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    if (n > 1000) n = 1000;

    for (int i = 0; i < n; i++) scanf("%d", &v[i]);

    int atual[MAXN], prox[MAXN];
    int qa = 0, qp;
    int nivel = 0;
    int primeiro = 1;

    if (n > 0 && v[0] != -1) atual[qa++] = 0;

    while (qa > 0) {
        if (nivel % 2 == 0) {
            for (int i = 0; i < qa; i++) {
                if (!primeiro) printf(" ");
                printf("%d", v[atual[i]]);
                primeiro = 0;
            }
        } else {
            for (int i = qa - 1; i >= 0; i--) {
                if (!primeiro) printf(" ");
                printf("%d", v[atual[i]]);
                primeiro = 0;
            }
        }

        qp = 0;
        for (int i = 0; i < qa; i++) {
            int e = 2 * atual[i] + 1;
            int d = 2 * atual[i] + 2;
            if (e < n && v[e] != -1) prox[qp++] = e;
            if (d < n && v[d] != -1) prox[qp++] = d;
        }
        for (int i = 0; i < qp; i++) atual[i] = prox[i];
        qa = qp;
        nivel++;
    }
    printf("\n");

    return 0;
}