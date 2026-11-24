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

int contar(NoArvore *no) {
    if (no == NULL) return 0;
    
    // Recursivamente conta todos os filhos
    int n_nos = 1;
    NoArvore *filho = no->primeiro_filho;
    while (filho != NULL) {
        n_nos += contar(filho);
        filho = filho->proximo_irmao;
    }
    return n_nos;
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

int main() {
    // Construindo a arvore de diretorios
    NoArvore *raiz = criar_no("raiz");
    
    NoArvore *documentos = criar_no("documentos");
    NoArvore *imagens = criar_no("imagens");
    NoArvore *musicas = criar_no("musicas");
    
    adicionar_filho(raiz, documentos);
    adicionar_filho(raiz, imagens);
    adicionar_filho(raiz, musicas);

    NoArvore *tese = criar_no("tese");
    adicionar_filho(documentos, tese);
    adicionar_filho(tese, criar_no("tese.pdf"));
    
    adicionar_filho(documentos, criar_no("trabalho.txt"));
    adicionar_filho(imagens, criar_no("foto.jpg"));
    
    // Exibindo a arvore
    exibir(raiz, 0);

    printf("# de nos de raiz: %d\n", contar(raiz));
    printf("# de nos de documentos: %d\n", contar(documentos));

    const char* nome = "trabalho.txt";
    auto no_buscado = buscar(raiz, nome);
    if (no_buscado != NULL)
        printf("Buscando %s: %p -> %s (1o filho)\n",
            nome, no_buscado, no_buscado->primeiro_filho ? no_buscado->primeiro_filho->nome : "nao tem");
    else
        printf("Nao encontrado %s\n", nome);
    
    return 0;
}