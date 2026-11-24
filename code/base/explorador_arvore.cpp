#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack>
#include <queue>

struct NoArvore {
    int id;
    char nome[50];
    struct NoArvore *primeiro_filho;
    struct NoArvore *proximo_irmao;
};

NoArvore* buscar(NoArvore *no, int id) {
    if (no == NULL) return NULL;
    if (no->id == id) return no;
    
    // Recursivamente busca nome em todos os filhos
    NoArvore *retorno = NULL;
    NoArvore *filho = no->primeiro_filho;
    while (filho != NULL && retorno == NULL) {
        retorno = buscar(filho, id);
        filho = filho->proximo_irmao;
    }
    return retorno;
}

void explorar_dfs(NoArvore *raiz)
{
    std::stack<int> pilha;
    // std::stack<NoArvore*> pilha;
    pilha.push(raiz->id);

    while(!pilha.empty())
    {
        printf("%d ", pilha.top());
        NoArvore* aux = buscar(raiz, pilha.top());
        pilha.pop();
        aux = aux->primeiro_filho;
        while(aux != NULL)
        {
            pilha.push(aux->id);
            if (aux->proximo_irmao == NULL)
                break;
            aux = aux->proximo_irmao;
        }
    }
}

void explorar_bfs(NoArvore *raiz)
{
    std::queue<int> fila;
    fila.push(raiz->id);

    while(!fila.empty())
    {
        printf("%d ", fila.front());
        NoArvore* aux = buscar(raiz, fila.front());
        fila.pop();
        aux = aux->primeiro_filho;
        while(aux != NULL)
        {
            fila.push(aux->id);
            if (aux->proximo_irmao == NULL)
                break;
            aux = aux->proximo_irmao;
        }
    }
}

// Criar novo no
NoArvore* criar_no(const char *nome, int id) {
    NoArvore *novo = (NoArvore*) malloc(sizeof(NoArvore));
    strcpy(novo->nome, nome);
    novo->id = id;
    novo->primeiro_filho = NULL;
    novo->proximo_irmao = NULL;
    return novo;
}

// Adicionar filho (insere no inicio da lista de filhos)
void adicionar_filho(NoArvore *pai, NoArvore *filho) {
    filho->proximo_irmao = pai->primeiro_filho;
    pai->primeiro_filho = filho;
}

void exibir(NoArvore *no, int nivel) {
    if (no == NULL) return;
    
    // Indentacao proporcional ao nivel
    for (int i = 0; i < nivel; i++) {
        printf("    ");
    }
    printf("|-- %d: %s\n", no->id, no->nome);
    
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
    char filho[50];
    int id_pai, id_filho;

    scanf("%d", &n);

    NoArvore *raiz = NULL;
    for(int i = 0; i < n; i++)
    {
        scanf("%d %d %s", &id_pai, &id_filho, filho);

        if (id_pai == -1)
        {
            raiz = criar_no(filho, id_filho);
        }
        else
        {
            auto no_pai = buscar(raiz, id_pai);
            auto no_filho = criar_no(filho, id_filho);
            adicionar_filho(no_pai, no_filho);
        }
    }

    exibir(raiz, 0);
    printf("\n");

    printf("DFS: ");
    explorar_dfs(raiz);
    printf("\n");

    printf("BFS: ");
    explorar_bfs(raiz);
    printf("\n");

    return 0;
}