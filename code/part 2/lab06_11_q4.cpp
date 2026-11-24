#include <stdio.h>
#include <stdlib.h>

int eh_espelho(int heap[], int n, int esq, int dir) {
    int val_esq = (esq < n) ? heap[esq] : -1;
    int val_dir = (dir < n) ? heap[dir] : -1;

    if (val_esq == -1 && val_dir == -1) {
        return 1;
    }

    if (val_esq != val_dir) {
        return 0;
    }

    return eh_espelho(heap, n, 2 * esq + 1, 2 * dir + 2) &&
           eh_espelho(heap, n, 2 * esq + 2, 2 * dir + 1);
}

int main() {
    int n;
    
    if (scanf("%d", &n) != 1) {
        return 1;
    }

    if (n <= 0) {
        return 0;
    }

    int *heap = (int*) malloc(n * sizeof(int));
    if (heap == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &heap[i]);
    }

    if (eh_espelho(heap, n, 1, 2)) {
        printf("SIMETRICA\n");
    } else {
        printf("NAO SIMETRICA\n");
    }

    free(heap);
    
    return 0;
}