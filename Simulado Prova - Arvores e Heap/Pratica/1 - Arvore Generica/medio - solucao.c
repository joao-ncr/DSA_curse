#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NoArvore {
    char nome[50];
    int limite;
    struct NoArvore *primeiro_filho;
    struct NoArvore *proximo_irmao;
} NoArvore;

NoArvore *nos[205];
int eh_filho[205];
int quantidade = 0;

NoArvore *criar_no(char *nome, int limite) {
    NoArvore *novo = (NoArvore *)malloc(sizeof(NoArvore));
    if (novo == NULL) exit(1);

    strcpy(novo->nome, nome);
    novo->limite = limite;
    novo->primeiro_filho = NULL;
    novo->proximo_irmao = NULL;

    return novo;
}

int buscar_indice(char *nome) {
    int i;
    for (i = 0; i < quantidade; i++)
        if (strcmp(nos[i]->nome, nome) == 0)
            return i;
    return -1;
}

void adicionar_filho(NoArvore *pai, NoArvore *filho) {
    if (pai->primeiro_filho == NULL) {
        pai->primeiro_filho = filho;
    } else {
        NoArvore *atual = pai->primeiro_filho;

        while (atual->proximo_irmao != NULL)
            atual = atual->proximo_irmao;

        atual->proximo_irmao = filho;
    }
}

int caminho_aprovacao(NoArvore *no, char *nome, char *resultado) {
    if (no == NULL) return 0;

    char acumulado[2000];
    strcpy(acumulado, resultado);

    if (strlen(acumulado) > 0)
        strcat(acumulado, "/");
    strcat(acumulado, no->nome);

    if (strcmp(no->nome, nome) == 0) {
        strcpy(resultado, acumulado);
        return 1;
    }

    NoArvore *filho = no->primeiro_filho;
    while (filho != NULL) {
        if (caminho_aprovacao(filho, nome, acumulado)) {
            strcpy(resultado, acumulado);
            return 1;
        }
        filho = filho->proximo_irmao;
    }

    return 0;
}

void listar_por_nivel(NoArvore *raiz) {
    NoArvore *fila[205];
    int nivel_fila[205];
    int inicio = 0, fim = 0;

    fila[fim] = raiz;
    nivel_fila[fim] = 0;
    fim++;

    int nivel_atual = -1;
    int primeiro_no_nivel = 1;

    while (inicio < fim) {
        NoArvore *atual = fila[inicio];
        int nivel = nivel_fila[inicio];
        inicio++;

        if (nivel != nivel_atual) {
            if (nivel_atual != -1) printf(" | ");
            nivel_atual = nivel;
            primeiro_no_nivel = 1;
        }

        if (!primeiro_no_nivel) printf(" ");
        printf("%s", atual->nome);
        primeiro_no_nivel = 0;

        NoArvore *filho = atual->primeiro_filho;
        while (filho != NULL) {
            fila[fim] = filho;
            nivel_fila[fim] = nivel + 1;
            fim++;
            filho = filho->proximo_irmao;
        }
    }

    printf("\n");
}

NoArvore *encontrar(NoArvore *no, char *nome) {
    if (no == NULL) return NULL;
    if (strcmp(no->nome, nome) == 0) return no;

    NoArvore *filho = no->primeiro_filho;
    while (filho != NULL) {
        NoArvore *achado = encontrar(filho, nome);
        if (achado != NULL) return achado;
        filho = filho->proximo_irmao;
    }

    return NULL;
}

int soma_limites(NoArvore *no) {
    if (no == NULL) return 0;

    int total = no->limite;
    NoArvore *filho = no->primeiro_filho;

    while (filho != NULL) {
        total += soma_limites(filho);
        filho = filho->proximo_irmao;
    }

    return total;
}

void liberar(NoArvore *no) {
    if (no == NULL) return;

    NoArvore *filho = no->primeiro_filho;
    while (filho != NULL) {
        NoArvore *proximo = filho->proximo_irmao;
        liberar(filho);
        filho = proximo;
    }

    free(no);
}

int main(void) {
    int n, i;

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        char nome[50];
        int limite;
        scanf("%s %d", nome, &limite);

        nos[quantidade] = criar_no(nome, limite);
        eh_filho[quantidade] = 0;
        quantidade++;
    }

    int m;
    scanf("%d", &m);

    for (i = 0; i < m; i++) {
        char nome_pai[50], nome_filho[50];
        scanf("%s %s", nome_pai, nome_filho);

        int idx_pai = buscar_indice(nome_pai);
        int idx_filho = buscar_indice(nome_filho);

        eh_filho[idx_filho] = 1;
        adicionar_filho(nos[idx_pai], nos[idx_filho]);
    }

    char consulta[50];
    scanf("%s", consulta);

    NoArvore *raiz = NULL;
    for (i = 0; i < quantidade; i++) {
        if (!eh_filho[i]) {
            raiz = nos[i];
            break;
        }
    }

    char caminho[2000] = "";
    caminho_aprovacao(raiz, consulta, caminho);
    printf("Caminho: %s\n", caminho);

    printf("Por nivel: ");
    listar_por_nivel(raiz);

    NoArvore *alvo = encontrar(raiz, consulta);
    printf("Soma de limites de %s: %d\n", consulta, soma_limites(alvo));

    liberar(raiz);

    return 0;
}
