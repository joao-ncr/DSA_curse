
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Use uma árvore genérica para representar uma árvore de decisão simples. Cada nó interno representa uma pergunta (com múltiplas respostas possíveis), e cada folha representa uma decisão final.

*/

struct NoDecisao {
    char texto[100];       // pergunta ou decisão
    int eh_folha;          // 1 se for folha, 0 caso contrário
    struct NoDecisao *primeiro_filho;
    struct NoDecisao *proximo_irmao;
};

NoDecisao* criar_no(const char *texto, int eh_folha) {
    NoDecisao *novo = (NoDecisao*) malloc(sizeof(NoDecisao));
    strcpy(novo->texto, texto);
    novo->eh_folha = eh_folha;
    novo->primeiro_filho = NULL;
    novo->proximo_irmao = NULL;
    return novo;
}

// Insere no final da lista de irmãos para manter a ordem 1, 2, 3...
void adicionar_filho(NoDecisao *pai, NoDecisao *filho) {
    if (pai->primeiro_filho == NULL) {
        pai->primeiro_filho = filho;
    } else {
        NoDecisao *atual = pai->primeiro_filho;
        while (atual->proximo_irmao != NULL) {
            atual = atual->proximo_irmao;
        }
        atual->proximo_irmao = filho;
    }
}

// Retorna o k-ésimo filho (1-indexado) do nó atual
NoDecisao* obter_filho_por_opcao(NoDecisao *pai, int opcao) {
    NoDecisao *filho = pai->primeiro_filho;
    int indice = 1;

    while (filho != NULL && indice < opcao) {
        filho = filho->proximo_irmao;
        indice++;
    }
    return filho;
}

void jogar(NoDecisao *raiz) {
    NoDecisao *atual = raiz;
    int escolha;

    while (atual != NULL && atual->eh_folha == 0) {
        printf("%s\n", atual->texto);

        if (scanf("%d", &escolha) != 1) {
            return;
        }

        NoDecisao *proximo = obter_filho_por_opcao(atual, escolha);
        if (proximo == NULL) {
            printf("Opcao invalida!\n");
            return;
        }
        atual = proximo;
    }

    if (atual != NULL && atual->eh_folha == 1) {
        printf("Resultado: %s\n", atual->texto);
    }
}

void liberar_arvore(NoDecisao *no) {
    if (no == NULL) return;

    NoDecisao *filho = no->primeiro_filho;
    while (filho != NULL) {
        NoDecisao *proximo = filho->proximo_irmao;
        liberar_arvore(filho);
        filho = proximo;
    }
    free(no);
}

int main() {
    // Construção manual da árvore do exemplo
    NoDecisao *raiz = criar_no("É um animal? (1-Sim, 2-Não)", 0);

    // Ramo 1: Sim (É um animal)
    NoDecisao *q_pelo = criar_no("Tem pelo? (1-Sim, 2-Não)", 0);
    NoDecisao *f_cachorro = criar_no("É um cachorro", 1);
    NoDecisao *f_galinha = criar_no("É uma galinha", 1);

    adicionar_filho(q_pelo, f_cachorro); // Opção 1
    adicionar_filho(q_pelo, f_galinha);  // Opção 2

    // Ramo 2: Não (Não é um animal)
    NoDecisao *q_objeto = criar_no("É um objeto? (1-Sim, 2-Não)", 0);
    NoDecisao *f_computador = criar_no("É um computador", 1);
    NoDecisao *f_planta = criar_no("É uma planta", 1);

    adicionar_filho(q_objeto, f_computador); // Opção 1
    adicionar_filho(q_objeto, f_planta);     // Opção 2

    // Liga os dois ramos principais à raiz
    adicionar_filho(raiz, q_pelo);   // Opção 1
    adicionar_filho(raiz, q_objeto); // Opção 2

    // Executa o jogo interativo
    jogar(raiz);

    liberar_arvore(raiz);
    return 0;
}



