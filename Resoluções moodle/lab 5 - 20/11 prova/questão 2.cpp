#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    int id;
    int alteracoes;
    struct No *pai;
    struct No *primeiro_filho;
    struct No *proximo_irmao;
} No;

No *criar_no(int id, int alteracoes, No *pai) {
    No *novo = (No *)malloc(sizeof(No));

    if (novo == NULL) exit(1);

    novo->id = id;
    novo->alteracoes = alteracoes;
    novo->pai = pai;
    novo->primeiro_filho = NULL;
    novo->proximo_irmao = NULL;

    return novo;
}

No *buscar(No *nos[], int quantidade, int id) {
    int i;

    for (i = 0; i < quantidade; i++) {
        if (nos[i]->id == id)
            return nos[i];
    }

    return NULL;
}

void adicionar_filho(No *pai, No *filho) {
    if (pai->primeiro_filho == NULL) {
        pai->primeiro_filho = filho;
    } else {
        No *atual = pai->primeiro_filho;

        while (atual->proximo_irmao != NULL)
            atual = atual->proximo_irmao;

        atual->proximo_irmao = filho;
    }
}

int total_alteracoes(No *no) {
    if (no == NULL) return 0;

    int total = no->alteracoes;
    No *filho = no->primeiro_filho;

    while (filho != NULL) {
        total += total_alteracoes(filho);
        filho = filho->proximo_irmao;
    }

    return total;
}

void listar_bfs(No *raiz, int capacidade) {
    if (raiz == NULL) return;

    No **fila = (No **)malloc(capacidade * sizeof(No *));

    if (fila == NULL) exit(1);

    int inicio = 0;
    int fim = 0;
    int primeiro = 1;

    fila[fim++] = raiz;

    while (inicio < fim) {
        No *atual = fila[inicio++];

        if (!primeiro) printf(" ");

        printf("%d", atual->id);
        primeiro = 0;

        No *filho = atual->primeiro_filho;

        while (filho != NULL) {
            fila[fim++] = filho;
            filho = filho->proximo_irmao;
        }
    }

    printf("\n");
    free(fila);
}

void liberar(No *no) {
    if (no == NULL) return;

    No *filho = no->primeiro_filho;

    while (filho != NULL) {
        No *proximo = filho->proximo_irmao;
        liberar(filho);
        filho = proximo;
    }

    free(no);
}

int main(void) {
    No *nos[10005];
    int quantidade = 0;

    No *raiz = NULL;

    char linha[200];

    while (fgets(linha, sizeof(linha), stdin) != NULL) {
        char comando[30];
        int pai_id, id, alteracoes;

        if (sscanf(linha, "%29s", comando) != 1)
            continue;

        if (strcmp(comando, "FIM") == 0)
            break;

        if (strcmp(comando, "COMMIT") == 0) {

            if (sscanf(linha, "%*s %d %d %d",
                       &pai_id, &id, &alteracoes) == 3) {

                No *pai = NULL;

                if (pai_id != -1)
                    pai = buscar(nos, quantidade, pai_id);

                No *novo = criar_no(id, alteracoes, pai);

                nos[quantidade++] = novo;

                if (pai == NULL)
                    raiz = novo;
                else
                    adicionar_filho(pai, novo);
            }

        } else if (strcmp(comando, "TOTAL") == 0) {

            if (sscanf(linha, "%*s %d", &id) == 1) {
                No *no = buscar(nos, quantidade, id);

                if (no != NULL)
                    printf("%d\n", total_alteracoes(no));
            }

        } else if (strcmp(comando, "PROFUNDIDADE") == 0) {

            if (sscanf(linha, "%*s %d", &id) == 1) {
                No *no = buscar(nos, quantidade, id);

                if (no != NULL) {
                    int profundidade = 0;

                    while (no->pai != NULL) {
                        profundidade++;
                        no = no->pai;
                    }

                    printf("%d\n", profundidade);
                }
            }

        } else if (strcmp(comando, "CAMINHO") == 0) {

            if (sscanf(linha, "%*s %d", &id) == 1) {
                No *no = buscar(nos, quantidade, id);

                if (no != NULL) {
                    int caminho[10005];
                    int tamanho = 0;

                    while (no != NULL) {
                        caminho[tamanho++] = no->id;
                        no = no->pai;
                    }

                    while (tamanho > 0) {
                        printf("%d", caminho[--tamanho]);

                        if (tamanho > 0)
                            printf(" ");
                    }

                    printf("\n");
                }
            }

        } else if (strcmp(comando, "LISTAR") == 0) {

            listar_bfs(raiz, quantidade + 1);
        }
    }

    liberar(raiz);

    return 0;
}