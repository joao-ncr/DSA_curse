#include <stdio.h>
#include <string.h>

int heap[100005];
int tamanho = 0;

void troca(int i, int j) {
    int temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

void subir(int i) {
    while (i > 0) {
        int pai = (i - 1) / 2;

        if (heap[i] >= heap[pai]) break;

        troca(i, pai);
        i = pai;
    }
}

void descer(int i) {
    while (1) {
        int esq = 2 * i + 1;
        int dir = 2 * i + 2;
        int menor = i;

        if (esq < tamanho && heap[esq] < heap[menor])
            menor = esq;

        if (dir < tamanho && heap[dir] < heap[menor])
            menor = dir;

        if (menor == i) break;

        troca(i, menor);
        i = menor;
    }
}

void inserir(int v) {
    heap[tamanho] = v;
    tamanho++;
    subir(tamanho - 1);
}

int remover_min(void) {
    int minimo = heap[0];

    tamanho--;
    heap[0] = heap[tamanho];
    descer(0);

    return minimo;
}

int main(void) {
    char linha[200];

    while (fgets(linha, sizeof(linha), stdin) != NULL) {
        char comando[30];
        int valor;

        if (sscanf(linha, "%29s", comando) != 1)
            continue;

        if (strcmp(comando, "FIM") == 0)
            break;

        if (strcmp(comando, "INSERIR") == 0) {

            if (sscanf(linha, "%*s %d", &valor) == 1)
                inserir(valor);

        } else if (strcmp(comando, "REMOVER_MIN") == 0) {

            if (tamanho == 0)
                printf("VAZIO\n");
            else
                printf("%d\n", remover_min());

        } else if (strcmp(comando, "TOPO") == 0) {

            if (tamanho == 0)
                printf("VAZIO\n");
            else
                printf("%d\n", heap[0]);

        } else if (strcmp(comando, "IMPRIMIR") == 0) {

            if (tamanho == 0) {
                printf("VAZIO\n");
            } else {
                int i;
                for (i = 0; i < tamanho; i++) {
                    if (i > 0) printf(" ");
                    printf("%d", heap[i]);
                }
                printf("\n");
            }
        }
    }

    return 0;
}
