#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NoMenu {
    int id;
    char titulo[50];
    struct NoMenu *primeiro_filho;
    struct NoMenu *proximo_irmao;
} NoMenu;

NoMenu* criar_no(int id, const char *titulo) {
    NoMenu *novo = (NoMenu*) malloc(sizeof(NoMenu));
    novo->id = id;
    strcpy(novo->titulo, titulo);
    novo->primeiro_filho = NULL;
    novo->proximo_irmao = NULL;
    return novo;
}

void adicionar_filho(NoMenu *pai, NoMenu *filho) {
    if (pai->primeiro_filho == NULL) {
        pai->primeiro_filho = filho;
    } else {
        NoMenu *atual = pai->primeiro_filho;
        while (atual->proximo_irmao != NULL) {
            atual = atual->proximo_irmao;
        }
        atual->proximo_irmao = filho;
    }
}

void exibir_menu(NoMenu *atual, int eh_raiz) {
    printf("=== %s ===\n", atual->titulo);
    NoMenu *filho = atual->primeiro_filho;
    int indice = 1;
    while (filho != NULL) {
        printf("%d. %s\n", indice++, filho->titulo);
        filho = filho->proximo_irmao;
    }
    if (!eh_raiz) {
        printf("0. Voltar\n");
    }
    printf("Escolha: ");
}

void liberar_arvore(NoMenu *no) {
    if (no == NULL) return;
    NoMenu *filho = no->primeiro_filho;
    while (filho != NULL) {
        NoMenu *proximo = filho->proximo_irmao;
        liberar_arvore(filho);
        filho = proximo;
    }
    free(no);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    NoMenu *nos[1005];
    int total_nos = 0;
    NoMenu *raiz = NULL;

    for (int i = 0; i < n; i++) {
        int id_pai, id_filho;
        char titulo[50];
        scanf("%d %d %[^\r\n]", &id_pai, &id_filho, titulo);

        NoMenu *novo = criar_no(id_filho, titulo);
        nos[total_nos++] = novo;

        if (id_pai == -1) {
            raiz = novo;
        } else {
            NoMenu *pai = NULL;
            for (int j = 0; j < total_nos; j++) {
                if (nos[j]->id == id_pai) {
                    pai = nos[j];
                    break;
                }
            }
            if (pai != NULL) adicionar_filho(pai, novo);
        }
    }

    if (raiz == NULL) return 0;

    NoMenu *historico[1005];
    int topo = 0;
    historico[topo] = raiz;

    char comando[20];
    while (1) {
        NoMenu *atual = historico[topo];
        exibir_menu(atual, topo == 0);

        if (scanf("%s", comando) != 1) break;
        printf("%s\n", comando);

        if (comando[0] == 'S' || comando[0] == 's') {
            printf("Saindo...\n");
            break;
        }

        int opcao = atoi(comando);
        if (opcao == 0) {
            if (topo == 0) {
                printf("Saindo...\n");
                break;
            } else {
                topo--;
            }
        } else if (opcao > 0) {
            // 1. Tenta encontrar pela posição na lista (1, 2, ...)
            NoMenu *filho = atual->primeiro_filho;
            int indice = 1;
            while (filho != NULL && indice < opcao) {
                filho = filho->proximo_irmao;
                indice++;
            }

            // 2. Se não encontrou pela posição, tenta encontrar pelo ID do nó
            if (filho == NULL) {
                filho = atual->primeiro_filho;
                while (filho != NULL && filho->id != opcao) {
                    filho = filho->proximo_irmao;
                }
            }

            if (filho != NULL) {
                historico[++topo] = filho;
            }
        }
    }

    liberar_arvore(raiz);
    return 0;
}