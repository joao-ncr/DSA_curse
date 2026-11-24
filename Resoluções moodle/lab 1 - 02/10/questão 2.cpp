#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct NoArvore {
    char nome[50];
    NoArvore *primeiro_filho;
    NoArvore *proximo_irmao;
};

NoArvore* criar_no(const char *nome) {
    NoArvore *novo = (NoArvore*) malloc(sizeof(NoArvore));
    strcpy(novo->nome, nome);
    novo->primeiro_filho = NULL;
    novo->proximo_irmao = NULL;
    return novo;
}

void adicionar_filho(NoArvore *pai, NoArvore *filho) {
    filho->proximo_irmao = pai->primeiro_filho;
    pai->primeiro_filho = filho;
}

NoArvore* buscar(NoArvore *no, const char *nome) {
    if (no == NULL) return NULL;
    if (strcmp(no->nome, nome) == 0) return no;

    NoArvore *retorno = NULL;
    NoArvore *filho = no->primeiro_filho;
    while (filho != NULL && retorno == NULL) {
        retorno = buscar(filho, nome);
        filho = filho->proximo_irmao;
    }
    return retorno;
}

void exibir(NoArvore *no, int nivel) {
    if (no == NULL) return;

    for (int i = 0; i < nivel; i++) {
        printf("    ");
    }
    printf("|-- %s\n", no->nome);

    NoArvore *filho = no->primeiro_filho;
    while (filho != NULL) {
        exibir(filho, nivel + 1);
        filho = filho->proximo_irmao;
    }
}

// ============================================================================
// a) CAMINHO DA RAIZ ATÉ O ALVO (Pré-ordem com Backtracking)
// ============================================================================

int caminho(NoArvore *no, char *nome, char *resultado) {
    if (no == NULL) return 0;

    // Guarda o tamanho da string antes de adicionar este nó (para desfazer se falhar)
    int tam_anterior = strlen(resultado);

    if (tam_anterior > 0) {
        strcat(resultado, "/");
    }
    strcat(resultado, no->nome);

    // Achou o destino: mantém o caminho montado e retorna 1
    if (strcmp(no->nome, nome) == 0) {
        return 1;
    }

    // Procura nos filhos
    NoArvore *filho = no->primeiro_filho;
    while (filho != NULL) {
        if (caminho(filho, nome, resultado) == 1) {
            return 1; // Propaga o sucesso sem desfazer a string
        }
        filho = filho->proximo_irmao;
    }

    // Backtracking: nenhum filho levou ao destino, apaga este nó do resultado
    resultado[tam_anterior] = '\0';
    return 0;
}

// ============================================================================
// b) IMPRIMIR POR NÍVEL (BFS usando Fila)
// ============================================================================
void imprimir_por_nivel(NoArvore *no) {
    if (no == NULL) return;

    NoArvore* fila[1000];
    int inicio = 0;
    int fim = 0;

    fila[fim++] = no;

    int nivel = 0;
    while (inicio < fim) {
        int qtd_no_nivel = fim - inicio;

        if (nivel > 0) printf(" | ");

        for (int i = 0; i < qtd_no_nivel; i++) {
            NoArvore *atual = fila[inicio++];
            printf("%s", atual->nome);
            if (i < qtd_no_nivel - 1) printf(" "); // Apenas espaço, sem vírgula

            NoArvore *filho = atual->primeiro_filho;
            while (filho != NULL) {
                fila[fim++] = filho;
                filho = filho->proximo_irmao;
            }
        }
        nivel++;
    }
    printf("\n");
}

// ============================================================================
// c) REMOVER NÓ E SUBÁRVORE (Liberação em Pós-ordem)
// ============================================================================
void liberar_subarvore(NoArvore *no) {
    if (no == NULL) return;

    // Pós-ordem: primeiro libera todos os filhos
    NoArvore *filho = no->primeiro_filho;
    while (filho != NULL) {
        NoArvore *proximo = filho->proximo_irmao; // Salva antes de dar free!
        liberar_subarvore(filho);
        filho = proximo;
    }

    // Por último, libera o próprio nó
    free(no);
}

NoArvore* remover(NoArvore *no, char *nome) {
    if (no == NULL) return NULL;

    // Caso especial: o nó a ser removido é a própria raiz passada
    if (strcmp(no->nome, nome) == 0) {
        liberar_subarvore(no);
        return NULL;
    }

    // Procura o alvo na lista encadeada de filhos diretos de 'no'
    NoArvore *anterior = NULL;
    NoArvore *atual = no->primeiro_filho;

    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            // 1. Desconecta 'atual' da lista de irmãos
            if (anterior == NULL) {
                no->primeiro_filho = atual->proximo_irmao;
            } else {
                anterior->proximo_irmao = atual->proximo_irmao;
            }

            // 2. Isola o ponteiro de irmão para não apagar os irmãos junto
            atual->proximo_irmao = NULL;

            // 3. Libera o nó e toda sua subárvore
            liberar_subarvore(atual);
            return no;
        }
        anterior = atual;
        atual = atual->proximo_irmao;
    }

    // Se não estava nos filhos diretos, continua procurando nas subárvores
    NoArvore *filho = no->primeiro_filho;
    while (filho != NULL) {
        remover(filho, nome);
        filho = filho->proximo_irmao;
    }

    return no;
}


int main() {
    int n;
    char pai[50], filho[50], nome_alvo[50];

    scanf("%d", &n);

    NoArvore *raiz = NULL;
    for (int i = 0; i < n; i++) {
        scanf("%s %s", pai, filho);

        NoArvore *no_pai = buscar(raiz, pai);
        if (no_pai == NULL) {
            raiz = criar_no(pai);
            no_pai = raiz;
        }
        NoArvore *no_filho = criar_no(filho);
        adicionar_filho(no_pai, no_filho);
    }
    scanf("%s", nome_alvo);

    // 1. Caminho
    char resultado[1000] = "";
    if (caminho(raiz, nome_alvo, resultado)) {
        printf("Caminho: %s\n", resultado);
    } else {
        printf("Caminho: nao encontrado\n");
    }

    // 2. Por nível
    printf("Por nivel: ");
    imprimir_por_nivel(raiz);

    // 3. Remoção e exibição
    raiz = remover(raiz, nome_alvo);
    printf("Apos remover %s:\n", nome_alvo);
    exibir(raiz, 0);

    return 0;
}

