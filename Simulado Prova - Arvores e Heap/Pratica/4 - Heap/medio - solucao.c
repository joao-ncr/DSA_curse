#include <stdio.h>
#include <string.h>

int heap[1005];
int tamanho = 0;

void troca(int i, int j) {
    int temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

int subir_pos(int i) {
    while (i > 0) {
        int pai = (i - 1) / 2;

        if (heap[i] >= heap[pai]) break;

        troca(i, pai);
        i = pai;
    }

    return i;
}

int descer_pos(int i) {
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

    return i;
}

int main(void) {
    int n, i;

    scanf("%d", &n);

    for (i = 0; i < n; i++)
        scanf("%d", &heap[i]);

    tamanho = n;

    for (i = n / 2 - 1; i >= 0; i--)
        descer_pos(i);

    char linha[200];

    while (fgets(linha, sizeof(linha), stdin) != NULL) {
        char comando[30];
        int pos, novo_valor;

        if (sscanf(linha, "%29s", comando) != 1)
            continue;

        if (strcmp(comando, "FIM") == 0)
            break;

        if (strcmp(comando, "ATUALIZAR") == 0) {

            if (sscanf(linha, "%*s %d %d", &pos, &novo_valor) == 2) {
                if (pos < 0 || pos >= tamanho) {
                    printf("POSICAO INVALIDA\n");
                } else {
                    int antigo = heap[pos];
                    heap[pos] = novo_valor;

                    int nova_pos;
                    if (novo_valor < antigo)
                        nova_pos = subir_pos(pos);
                    else if (novo_valor > antigo)
                        nova_pos = descer_pos(pos);
                    else
                        nova_pos = pos;

                    printf("%d\n", nova_pos);
                }
            }

        } else if (strcmp(comando, "TOPO") == 0) {

            printf("%d\n", heap[0]);

        } else if (strcmp(comando, "IMPRIMIR") == 0) {

            for (i = 0; i < tamanho; i++) {
                if (i > 0) printf(" ");
                printf("%d", heap[i]);
            }
            printf("\n");
        }
    }

    return 0;
}
