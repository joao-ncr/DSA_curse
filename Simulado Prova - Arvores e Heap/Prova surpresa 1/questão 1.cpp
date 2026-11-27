/*
Em um curso de graduação em computação, as disciplinas possuem pré-requisitos que formam uma estrutura hierárquica. Cada disciplina pode ter várias disciplinas dependentes (que só podem ser cursadas após ela), formando uma árvore genérica.

Dada a lista de pré-requisitos, determine:

A ordem topológica de conclusão das disciplinas (da raiz até as folhas)

A altura da árvore de dependências (quantos semestres no mínimo são necessários)

O caminho mais longo da raiz até uma folha

A árvore começa na disciplina "CALCULO1" (raiz), e cada linha indica que uma disciplina é pré-requisito de outra.

Entrada:

Primeira linha: N (número de relações de pré-requisito, 1 ≤ N ≤ 1000)

Próximas N linhas: pre_requisito disciplina

A primeira disciplina que aparece como pré-requisito mas nunca como dependente é a raiz.

Saída:

Primeira linha: ORDEM: <disciplinas em BFS separadas por espaço>

Segunda linha: ALTURA: <n>

Terceira linha: CAMINHO: <disciplinas do caminho mais longo separadas por espaço>

Por exemplo:

Input	Resultado
3
CALCULO1 PROG1
PROG1 ESTRUTURA
ESTRUTURA ALGORITMOS
ORDEM: CALCULO1 PROG1 ESTRUTURA ALGORITMOS
ALTURA: 4
CAMINHO: CALCULO1 PROG1 ESTRUTURA ALGORITMOS

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NoDisciplina {
    char nome[50];
    struct NoDisciplina *primeiro_filho;
    struct NoDisciplina *proximo_irmao;
    struct NoDisciplina *pai;
    int tem_pai;
} NoDisciplina;

NoDisciplina *nos[2005];
int total_nos = 0;

NoDisciplina* obter_ou_criar(const char *nome) {
    for (int i = 0; i < total_nos; i++) {
        if (strcmp(nos[i]->nome, nome) == 0) {
            return nos[i];
        }
    }
    NoDisciplina *novo = (NoDisciplina*) malloc(sizeof(NoDisciplina));
    strcpy(novo->nome, nome);
    novo->primeiro_filho = NULL;
    novo->proximo_irmao = NULL;
    novo->pai = NULL;
    novo->tem_pai = 0;
    nos[total_nos++] = novo;
    return novo;
}

// Insere o novo filho no INÍCIO da lista de irmãos
void adicionar_filho(NoDisciplina *pai, NoDisciplina *filho) {
    filho->pai = pai;
    filho->tem_pai = 1;
    filho->proximo_irmao = pai->primeiro_filho;
    pai->primeiro_filho = filho;
}

void liberar_memoria() {
    for (int i = 0; i < total_nos; i++) {
        free(nos[i]);
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    for (int i = 0; i < n; i++) {
        char pre[50], disc[50];
        scanf("%s %s", pre, disc);

        NoDisciplina *no_pre = obter_ou_criar(pre);
        NoDisciplina *no_disc = obter_ou_criar(disc);
        adicionar_filho(no_pre, no_disc);
    }

    NoDisciplina *raiz = NULL;
    for (int i = 0; i < total_nos; i++) {
        if (!nos[i]->tem_pai) {
            raiz = nos[i];
            break;
        }
    }

    if (raiz == NULL) return 0;

    NoDisciplina *fila[2005];
    int nivel_fila[2005];
    int inicio = 0, fim = 0;

    fila[fim] = raiz;
    nivel_fila[fim] = 1;
    fim++;

    int altura_max = 0;
    NoDisciplina *no_mais_profundo = raiz;

    printf("ORDEM:");
    while (inicio < fim) {
        NoDisciplina *atual = fila[inicio];
        int nivel = nivel_fila[inicio];
        inicio++;

        printf(" %s", atual->nome);

        if (nivel > altura_max) {
            altura_max = nivel;
            no_mais_profundo = atual;
        }

        NoDisciplina *filho = atual->primeiro_filho;
        while (filho != NULL) {
            fila[fim] = filho;
            nivel_fila[fim] = nivel + 1;
            fim++;
            filho = filho->proximo_irmao;
        }
    }
    printf("\n");

    printf("ALTURA: %d\n", altura_max);

    NoDisciplina *caminho[2005];
    int tam_caminho = 0;
    NoDisciplina *curr = no_mais_profundo;
    while (curr != NULL) {
        caminho[tam_caminho++] = curr;
        curr = curr->pai;
    }

    printf("CAMINHO:");
    for (int i = tam_caminho - 1; i >= 0; i--) {
        printf(" %s", caminho[i]->nome);
    }
    printf("\n");

    liberar_memoria();
    return 0;
}