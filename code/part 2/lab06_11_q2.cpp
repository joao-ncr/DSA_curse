#include <cstdio>
#include <climits>

#define MAX 1005

int arv[MAX];
int n;

int eh_abb(int i, long long minimo, long long maximo) {
    if (i >= n || arv[i] == -1) return 1;
    if (arv[i] <= minimo || arv[i] >= maximo) return 0;
    return eh_abb(2 * i + 1, minimo, arv[i]) && eh_abb(2 * i + 2, arv[i], maximo);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &arv[i]);

    if (eh_abb(0, LLONG_MIN, LLONG_MAX)) printf("ABB\n");
    else printf("NAO ABB\n");
    return 0;
}