#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>

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

no* remover_abb(no *raiz, int valor, bool dir = true) {
    // Caso base: arvore vazia ou valor nao encontrado
    if (raiz == NULL) return NULL;
    
    // Procura o no a ser removido
    if (valor < raiz->valor) {
        raiz->esq = remover_abb(raiz->esq, valor);
    } else if (valor > raiz->valor) {
        raiz->dir = remover_abb(raiz->dir, valor);
    } else {// Encontrou o no! Tratar casos...
        // Caso 1: no folha
        if (raiz->esq == NULL && raiz->dir == NULL) {
            printf("Caso 1: Remove folha!\n");
            free(raiz);
            return NULL;
        }
        
        // Caso 2: no com um filho
        if (raiz->esq == NULL) {
            printf("Caso 2: Remove filho único direito!\n");
            no *temp = raiz->dir;
            free(raiz);
            return temp;
        }
        if (raiz->dir == NULL) {
            printf("Caso 2: Remove filho único esquerdo!\n");
            no *temp = raiz->esq;
            free(raiz);
            return temp;
        }
        
        // Caso 3: no com dois filhos
        // Encontra o sucessor em-ordem, copia valor e remove da sub-dir
        if (dir == true)
        {
            no *sucessor = menor(raiz->dir);
            raiz->valor = sucessor->valor;
            printf("Caso 3: Trocando por sucessor %d!\n", raiz->valor);
            raiz->dir = remover_abb(raiz->dir, sucessor->valor);
        }
        else
        {
            no *sucessor = maior(raiz->esq);
            raiz->valor = sucessor->valor;
            printf("Caso 3: Trocando por antecessor %d!\n", raiz->valor);
            raiz->esq = remover_abb(raiz->esq, sucessor->valor);
        }
    }
    return raiz;
}

void exibir(no *raiz, int nivel) {
    if (raiz == NULL) return;
    
    // Indentacao proporcional ao nivel
    for (int i = 0; i < nivel; i++) {
        printf("    ");
    }
    printf("|-- %d\n", raiz->valor);
    
    // Recursivamente exibe todos os filhos
    exibir(raiz->esq, nivel + 1);
    exibir(raiz->dir, nivel + 1);
}

int main(){

    srand(time(NULL));

    int n = 1e6;

    int* valores = (int*) malloc(sizeof(int) * n);

    no* raiz = NULL;
    for(int i = 0; i < n; i++)
    {
        valores[i] = rand() % 1000000;
        raiz = inserir_abb(raiz, valores[i]);
    }

    // std::sort(valores, valores + n);
    // no* raiz2 = NULL;
    // for(int i = 0; i < n; i++)
    // {
    //     raiz2 = inserir_abb(raiz2, valores[i]);
    // }

    // printf("ABB em ordem: ");
    // em_ordem(raiz);
    // printf("\n");

    // exibir(raiz, 0);

    printf("Maior: %d | Menor: %d\n", maior(raiz)->valor, menor(raiz)->valor);

    // raiz = remover_abb(raiz, 50);
    // printf("ABB em ordem: ");
    // em_ordem(raiz);
    // printf("\n");
    // exibir(raiz, 0);

    // raiz = remover_abb(raiz, 60, false);
    // printf("ABB em ordem: ");
    // em_ordem(raiz);
    // printf("\n");
    // exibir(raiz, 0);

    return 0;
}