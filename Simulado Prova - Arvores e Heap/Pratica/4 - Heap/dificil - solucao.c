#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[50];
    int prioridade;
    int chegada;
} Paciente;

Paciente heap[100005];
int tamanho = 0;
int contador_chegada = 0;

int menor(Paciente a, Paciente b) {
    if (a.prioridade != b.prioridade)
        return a.prioridade < b.prioridade;
    return a.chegada < b.chegada;
}

void troca(int i, int j) {
    Paciente temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

void subir(int i) {
    while (i > 0) {
        int pai = (i - 1) / 2;

        if (!menor(heap[i], heap[pai])) break;

        troca(i, pai);
        i = pai;
    }
}

void descer(int i) {
    while (1) {
        int esq = 2 * i + 1;
        int dir = 2 * i + 2;
        int melhor = i;

        if (esq < tamanho && menor(heap[esq], heap[melhor]))
            melhor = esq;

        if (dir < tamanho && menor(heap[dir], heap[melhor]))
            melhor = dir;

        if (melhor == i) break;

        troca(i, melhor);
        i = melhor;
    }
}

void chegar(char *nome, int prioridade) {
    strcpy(heap[tamanho].nome, nome);
    heap[tamanho].prioridade = prioridade;
    heap[tamanho].chegada = contador_chegada++;

    tamanho++;
    subir(tamanho - 1);
}

Paciente atender(void) {
    Paciente topo = heap[0];

    tamanho--;
    heap[0] = heap[tamanho];
    descer(0);

    return topo;
}

int main(void) {
    char linha[200];

    while (fgets(linha, sizeof(linha), stdin) != NULL) {
        char comando[30];

        if (sscanf(linha, "%29s", comando) != 1)
            continue;

        if (strcmp(comando, "FIM") == 0)
            break;

        if (strcmp(comando, "CHEGAR") == 0) {

            char nome[50];
            int prioridade;

            if (sscanf(linha, "%*s %49s %d", nome, &prioridade) == 2)
                chegar(nome, prioridade);

        } else if (strcmp(comando, "ATENDER") == 0) {

            if (tamanho == 0) {
                printf("VAZIO\n");
            } else {
                Paciente p = atender();
                printf("%s %d\n", p.nome, p.prioridade);
            }

        } else if (strcmp(comando, "TOTAL") == 0) {

            printf("%d\n", tamanho);
        }
    }

    return 0;
}
