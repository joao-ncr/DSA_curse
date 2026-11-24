#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

struct NoArvore {
    char texto[100];
    int eh_folha;
    NoArvore *primeiro_filho;
    NoArvore *proximo_irmao;
};

// Criar novo no
NoArvore* criar_no(const char *nome, int valor) {
    NoArvore *novo = (NoArvore*) malloc(sizeof(NoArvore));
    strcpy(novo->texto, nome);
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
    if (strcmp(no->texto, nome) == 0) return no;
    
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
    printf("|-- %s\n", no->texto);
    
    // Recursivamente exibe todos os filhos
    NoArvore *filho = no->primeiro_filho;
    while (filho != NULL) {
        exibir(filho, nivel + 1);
        filho = filho->proximo_irmao;
    }
}

int main()
{
    NoArvore *raiz =  criar_no("É um animal? (1-Sim, 2-Não)", 0);

    // 1º filho
    {
        NoArvore *p_filho = criar_no("É um objeto? (1-Sim, 2-Não)", 0);
        adicionar_filho(raiz, p_filho);
        adicionar_filho(p_filho, criar_no("É uma planta", 1));
        adicionar_filho(p_filho, criar_no("É um computador", 1));
    }

    // 2º filho
    {
        NoArvore *s_filho = criar_no("Tem pelo? (1-Sim, 2-Não)", 0);
        adicionar_filho(raiz, s_filho);
        adicionar_filho(s_filho, criar_no("É uma galinha", 1));
        adicionar_filho(s_filho, criar_no("É um cachorro", 1));
    }

    // exibir(raiz, 0);
    // printf("\n");
    
    int d1, d2;
    scanf("%d %d", &d1, &d2);

    // Primeiro nivel
    printf("%s\n", raiz->texto);
    NoArvore* aux = raiz->primeiro_filho;
    while(d1 > 1)
    {
        aux = aux->proximo_irmao;
        d1--;
    }
    printf("%s\n", aux->texto);

    // Segundo nivel
    aux = aux->primeiro_filho;
    while(d2 > 1)
    {
        aux = aux->proximo_irmao;
        d2--;
    }
    printf("Resultado: %s\n", aux->texto);

    return 0;
}
