#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

struct NoArvore {
    char nome[50];
    int valor;
    NoArvore *primeiro_filho;
    NoArvore *proximo_irmao;
};

int soma_valores(NoArvore *no)
{
    if (no == NULL) return 0;
    
    // Recursivamente conta todos os filhos
    int soma = no->valor;
    NoArvore *filho = no->primeiro_filho;
    while (filho != NULL) {
        soma += soma_valores(filho);
        filho = filho->proximo_irmao;
    }
    return soma;
}

int maior_valor(NoArvore *no)
{
    if (no == NULL) return INT_MIN;
    
    // Recursivamente pegar o maior de todos os filhos
    int maior = no->valor;
    NoArvore *filho = no->primeiro_filho;
    while (filho != NULL) {
        int maior_filho = maior_valor(filho);
        maior = (maior < maior_filho) ? maior_filho : maior;
        filho = filho->proximo_irmao;
    }
    return maior;
}

int menor_valor(NoArvore *no)
{
    if (no == NULL) return INT_MAX;
    
    // Recursivamente pegar o maior de todos os filhos
    int menor = no->valor;
    NoArvore *filho = no->primeiro_filho;
    while (filho != NULL) {
        int menor_filho = menor_valor(filho);
        menor = (menor > menor_filho) ? menor_filho : menor;
        filho = filho->proximo_irmao;
    }
    return menor;
}

// Criar novo no
NoArvore* criar_no(const char *nome, int valor) {
    NoArvore *novo = (NoArvore*) malloc(sizeof(NoArvore));
    strcpy(novo->nome, nome);
    novo->valor = valor;
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

int main()
{
    int n;
    char pai[50], filho[50];

    scanf("%d", &n);

    NoArvore *raiz = NULL;
    for(int i = 0; i < n; i++)
    {
        int valor;
        scanf("%s %s %d", pai, filho, &valor);

        auto no_pai = buscar(raiz, pai);
        if (no_pai == NULL)
        {
            raiz = criar_no(pai, 0);
            no_pai = raiz;
        }
        auto no_filho = criar_no(filho, valor);
        adicionar_filho(no_pai, no_filho);
    }
    
    // Itera pelos filhos de raiz
    int menor = INT_MAX;
    NoArvore* aux = raiz->primeiro_filho;
    while (aux != NULL) {
        int menor_filho = menor_valor(aux);
        menor = (menor > menor_filho) ? menor_filho : menor;
        aux = aux->proximo_irmao;
    }
    int maior = INT_MIN;
    aux = raiz->primeiro_filho;
    while (aux != NULL) {
        int maior_filho = maior_valor(aux);
        maior = (maior < maior_filho) ? maior_filho : maior;
        aux = aux->proximo_irmao;
    }

    // exibir(raiz, 0);
    // printf("\n");
    printf("Soma: %d\n", soma_valores(raiz));
    printf("Maior(raiz): %d\n", maior_valor(raiz));
    printf("Menor(raiz): %d\n", menor_valor(raiz));
    printf("Maior: %d\n", maior);
    printf("Menor: %d\n", menor);

    return 0;
}
