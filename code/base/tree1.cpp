#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct NoArvore {
    char nome[50];
    NoArvore *primeiro_filho;
    NoArvore *proximo_irmao;
};

// Criar novo no
NoArvore* criar_no(const char *nome) {
    NoArvore *novo = (NoArvore*) malloc(sizeof(NoArvore));
    strcpy(novo->nome, nome);
    novo->primeiro_filho = NULL;
    novo->proximo_irmao = NULL;
    return novo;
}

// Adicionar filho (insere no inicio da lista de filhos)
void adicionar_filho(NoArvore *pai, NoArvore *filho) {
    filho->proximo_irmao = pai->primeiro_filho;
    pai->primeiro_filho = filho;
}

NoArvore* buscar(NoArvore *no, const char* nome) {
    if (no == NULL) return NULL;
    if (strcmp(no->nome, nome) == 0) return no;
    
    // Recursivamente busca nome em todos os filhos
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
    
    // Indentacao proporcional ao nivel
    for (int i = 0; i < nivel; i++) {
        printf("    ");
    }
    printf("|-- %s\n", no->nome);
    
    // Recursivamente exibe todos os filhos
    NoArvore *filho = no->primeiro_filho;
    while (filho != NULL) {
        exibir(filho, nivel + 1);
        filho = filho->proximo_irmao;
    }
}

int altura(NoArvore *no)
{
    if (no == NULL) return 0;

    int altura_max = 1;
    NoArvore *filho = no->primeiro_filho;
    while (filho != NULL) {
        int altura_filho = altura(filho);
        if (altura_filho + 1 > altura_max)
            altura_max = altura_filho + 1;
        filho = filho->proximo_irmao;
    }
    return altura_max;
}

int profundidade(NoArvore *no, char *nome, int nivel_atual)
{
    if (no == NULL) return -1;

    else if (strcmp(no->nome, nome) == 0)
        return nivel_atual;

    NoArvore *filho = no->primeiro_filho;
    while (filho != NULL) {
        int profundidade_filho = profundidade(filho, nome, nivel_atual + 1);
        if (profundidade_filho != -1)
            return profundidade_filho;
        filho = filho->proximo_irmao;
    }
    return -1;
}

int grau_maximo(NoArvore *no)
{
    if (no == NULL) return -1;

    int grau_no = 0;
    int grau_max = 0;
    NoArvore *filho = no->primeiro_filho;
    while (filho != NULL) {
        grau_no++;
        int grau_filho = grau_maximo(filho);
        if (grau_filho > grau_max)
            grau_max = grau_filho;
        filho = filho->proximo_irmao;
    }
    return grau_max > grau_no ? grau_max : grau_no;
}

int main()
{
    int n;
    char pai[50], filho[50], nome[50];

    scanf("%d", &n);

    NoArvore *raiz = NULL;
    for(int i = 0; i < n; i++)
    {
        scanf("%s %s", pai, filho);

        auto no_pai = buscar(raiz, pai);
        if (no_pai == NULL)
        {
            raiz = criar_no(pai);
            no_pai = raiz;
        }
        auto no_filho = criar_no(filho);
        adicionar_filho(no_pai, no_filho);
    }
    scanf("%s", nome);

    exibir(raiz, 0);
    printf("\n");
    printf("Altura: %d\n", altura(raiz));
    printf("Profundidade de %s: %d\n", nome, profundidade(raiz, nome, 0));
    printf("Grau maximo: %d\n", grau_maximo(raiz));

    return 0;
}