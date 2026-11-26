#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct NoExpr {
    char operador;   // '+', '-', '*', '/' ou '\0' para números
    int valor;       // usado apenas se operador == '\0'
    struct NoExpr *primeiro_filho;
    struct NoExpr *proximo_irmao;
} NoExpr;

NoExpr* criar_no_expr(char operador, int valor) {
    NoExpr *novo = (NoExpr*) malloc(sizeof(NoExpr));
    novo->operador = operador;
    novo->valor = valor;
    novo->primeiro_filho = NULL;
    novo->proximo_irmao = NULL;
    return novo;
}

void adicionar_filho_expr(NoExpr *pai, NoExpr *filho) {
    if (pai->primeiro_filho == NULL) {
        pai->primeiro_filho = filho;
    } else {
        NoExpr *atual = pai->primeiro_filho;
        while (atual->proximo_irmao != NULL) {
            atual = atual->proximo_irmao;
        }
        atual->proximo_irmao = filho;
    }
}

// a) Avalia a expressão recursivamente
int avaliar(NoExpr *no) {
    if (no == NULL) return 0;

    if (no->operador == '\0') {
        return no->valor;
    }

    NoExpr *filho = no->primeiro_filho;
    if (filho == NULL) return 0;

    int resultado = avaliar(filho);
    filho = filho->proximo_irmao;

    while (filho != NULL) {
        int val_filho = avaliar(filho);
        switch (no->operador) {
            case '+': resultado += val_filho; break;
            case '-': resultado -= val_filho; break;
            case '*': resultado *= val_filho; break;
            case '/': 
                if (val_filho != 0) resultado /= val_filho; 
                break;
        }
        filho = filho->proximo_irmao;
    }

    return resultado;
}

// b) Imprime a expressão em notação infixa com parênteses
void imprimir_infixa(NoExpr *no) {
    if (no == NULL) return;

    if (no->operador == '\0') {
        printf("%d", no->valor);
        return;
    }

    printf("(");
    NoExpr *filho = no->primeiro_filho;
    while (filho != NULL) {
        imprimir_infixa(filho);
        if (filho->proximo_irmao != NULL) {
            printf(" %c ", no->operador);
        }
        filho = filho->proximo_irmao;
    }
    printf(")");
}

void liberar_expr(NoExpr *no) {
    if (no == NULL) return;
    NoExpr *filho = no->primeiro_filho;
    while (filho != NULL) {
        NoExpr *prox = filho->proximo_irmao;
        liberar_expr(filho);
        filho = prox;
    }
    free(no);
}

NoExpr* ler_arvore_expr() {
    char linha[256];
    while (fgets(linha, sizeof(linha), stdin) != NULL) {
        linha[strcspn(linha, "\r\n")] = '\0';
        if (strlen(linha) == 0) continue;

        char *token = strtok(linha, " \t");
        if (token == NULL) continue;

        if (strlen(token) == 1 && !isdigit((unsigned char)token[0])) {
            char op = token[0];
            NoExpr *no = criar_no_expr(op, 0);

            int qtd_filhos = 0;
            while (strtok(NULL, " \t") != NULL) {
                qtd_filhos++;
            }

            for (int i = 0; i < qtd_filhos; i++) {
                NoExpr *filho = ler_arvore_expr();
                if (filho != NULL) {
                    adicionar_filho_expr(no, filho);
                }
            }
            return no;
        } else {
            return criar_no_expr('\0', atoi(token));
        }
    }
    return NULL;
}

int main() {
    NoExpr *raiz = ler_arvore_expr();
    if (raiz != NULL) {
        printf("Resultado: %d\n", avaliar(raiz));
        printf("Infixa: ");
        imprimir_infixa(raiz);
        printf("\n");
        liberar_expr(raiz);
    }
    return 0;
}