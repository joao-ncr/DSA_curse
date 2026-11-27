/*
Use uma árvore genérica para representar uma taxonomia biológica (Reino → Filo → Classe → Ordem → Família → Gênero → Espécie). Cada nó armazena o nome do táxon e seu nível.

typedef struct NoTaxonomia {
    char nome[50];
    int nivel;   // 0=Reino, 1=Filo, ..., 6=Espécie
    struct NoTaxonomia *primeiro_filho;
    struct NoTaxonomia *proximo_irmao;
} NoTaxonomia;
Implemente:

a) void exibir_taxonomia(NoTaxonomia *no, int nivel): exibe a taxonomia hierarquicamente

b) int contar_especies(NoTaxonomia *no): conta quantas espécies existem na árvore (nós com nível 6)

c) void listar_especies(NoTaxonomia *no): lista todas as espécies precedidas pelo caminho taxonômico

Entrada:

Primeira linha: N (número de nós)

Próximas N linhas: nome_pai nome_filho nivel

Saída:

Primeira linha: "Taxonomia:"

Próximas linhas: a árvore exibida hierarquicamente

Linha em branco

"Total de especies: <n>"

"Especies:"

Lista de espécies com caminho

Por exemplo:

Input	Resultado
7
Animalia Chordata 1
Chordata Mammalia 2
Mammalia Carnivora 3
Carnivora Canidae 4
Canidae Canis 5
Canis lupus 6
Animalia Arthropoda 1
Taxonomia:
|-- Animalia
    |-- Arthropoda
    |-- Chordata
        |-- Mammalia
            |-- Carnivora
                |-- Canidae
                    |-- Canis
                        |-- lupus

Total de especies: 1
Especies:
Animalia/Chordata/Mammalia/Carnivora/Canidae/Canis/lupus

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NoTaxonomia {
    char nome[50];
    int nivel;   // 0=Reino, 1=Filo, ..., 6=Especie
    struct NoTaxonomia *primeiro_filho;
    struct NoTaxonomia *proximo_irmao;
} NoTaxonomia;

NoTaxonomia* criar_no(const char *nome, int nivel) {
    NoTaxonomia *novo = (NoTaxonomia*) malloc(sizeof(NoTaxonomia));
    strcpy(novo->nome, nome);
    novo->nivel = nivel;
    novo->primeiro_filho = NULL;
    novo->proximo_irmao = NULL;
    return novo;
}

void adicionar_filho(NoTaxonomia *pai, NoTaxonomia *filho) {
    filho->proximo_irmao = pai->primeiro_filho;
    pai->primeiro_filho = filho;
}

NoTaxonomia* buscar(NoTaxonomia *no, const char *nome) {
    if (no == NULL) return NULL;
    if (strcmp(no->nome, nome) == 0) return no;

    NoTaxonomia *retorno = NULL;
    NoTaxonomia *filho = no->primeiro_filho;
    while (filho != NULL && retorno == NULL) {
        retorno = buscar(filho, nome);
        filho = filho->proximo_irmao;
    }
    return retorno;
}

// a) Exibe a taxonomia hierarquicamente
void exibir_taxonomia(NoTaxonomia *no, int nivel) {
    if (no == NULL) return;

    for (int i = 0; i < nivel; i++) printf("    ");
    printf("|-- %s\n", no->nome);

    NoTaxonomia *filho = no->primeiro_filho;
    while (filho != NULL) {
        exibir_taxonomia(filho, nivel + 1);
        filho = filho->proximo_irmao;
    }
}

// b) Conta quantas espécies existem na árvore (nós com nivel 6)
int contar_especies(NoTaxonomia *no) {
    if (no == NULL) return 0;

    int total = (no->nivel == 6) ? 1 : 0;

    NoTaxonomia *filho = no->primeiro_filho;
    while (filho != NULL) {
        total += contar_especies(filho);
        filho = filho->proximo_irmao;
    }
    return total;
}

// c) Lista todas as espécies precedidas pelo caminho taxonômico
void listar_especies_aux(NoTaxonomia *no, char *caminho) {
    if (no == NULL) return;

    int tam_anterior = strlen(caminho);
    if (tam_anterior > 0) strcat(caminho, "/");
    strcat(caminho, no->nome);

    if (no->nivel == 6) {
        printf("%s\n", caminho);
    }

    NoTaxonomia *filho = no->primeiro_filho;
    while (filho != NULL) {
        listar_especies_aux(filho, caminho);
        filho = filho->proximo_irmao;
    }

    caminho[tam_anterior] = '\0';
}

void listar_especies(NoTaxonomia *no) {
    char caminho[2000] = "";
    listar_especies_aux(no, caminho);
}

void liberar_arvore(NoTaxonomia *no) {
    if (no == NULL) return;
    NoTaxonomia *filho = no->primeiro_filho;
    while (filho != NULL) {
        NoTaxonomia *proximo = filho->proximo_irmao;
        liberar_arvore(filho);
        filho = proximo;
    }
    free(no);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    NoTaxonomia *raiz = NULL;

    for (int i = 0; i < n; i++) {
        char nome_pai[50], nome_filho[50];
        int nivel;
        if (scanf("%s %s %d", nome_pai, nome_filho, &nivel) != 3) break;

        NoTaxonomia *pai = buscar(raiz, nome_pai);
        if (pai == NULL) {
            pai = criar_no(nome_pai, nivel - 1);
            raiz = pai;
        }

        NoTaxonomia *filho = buscar(raiz, nome_filho);
        if (filho == NULL) {
            filho = criar_no(nome_filho, nivel);
            adicionar_filho(pai, filho);
        }
    }

    printf("Taxonomia:\n");
    exibir_taxonomia(raiz, 0);

    printf("\n");
    printf("Total de especies: %d\n", contar_especies(raiz));
    printf("Especies:\n");
    listar_especies(raiz);

    liberar_arvore(raiz);
    return 0;
}
