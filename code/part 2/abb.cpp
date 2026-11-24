#include <stdio.h>
#include <stdlib.h>

struct no{
    int valor;
    no* esq, *dir;
};

no* criar_no(int valor)
{
    no* novo = (no*) malloc(sizeof(no));
    novo->valor = valor;
    novo->esq = novo->dir = NULL;
    return novo;
}

no* inserir_abb(no* raiz, int valor)
{
    if(raiz == NULL)
        return criar_no(valor);
    else if(valor < raiz->valor)
        raiz->esq = inserir_abb(raiz->esq, valor);
    else
        raiz->dir = inserir_abb(raiz->dir, valor);
    return raiz;
}

no* menor(no* raiz)
{
    no* aux = raiz;
    while (aux->esq != NULL)
        aux = aux->esq;
    
    return aux;
}

no* maior(no* raiz)
{
    no* aux = raiz;
    while (aux->dir != NULL)
        aux = aux->dir;
    
    return aux;
}

void em_ordem(no* raiz)
{
    if (raiz != NULL)
    {
        em_ordem(raiz->esq);
        printf("%d ", raiz->valor);
        em_ordem(raiz->dir);
    }
}

int main(){

    int valores[] = {50, 30, 70, 20, 40, 60, 80};
    // int valores[] = {80, 30, 20, 40, 60, 70, 50};
    int n = sizeof(valores) / sizeof(int);

    no* raiz = NULL;
    for(int i = 0; i < n; i++)
    {
        raiz = inserir_abb(raiz, valores[i]);
    }

    printf("ABB em ordem: ");
    em_ordem(raiz);
    printf("\n");

    printf("Maior: %d | Menor: %d\n", maior(raiz)->valor, menor(raiz)->valor);

    return 0;
}