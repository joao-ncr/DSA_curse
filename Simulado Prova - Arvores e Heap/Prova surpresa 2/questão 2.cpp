/*
Um servidor de arquivos organiza seus dados em uma árvore genérica de diretórios. Cada diretório pode conter subdiretórios e arquivos. Cada arquivo tem um tamanho em MB, e cada diretório tem uma cota máxima de armazenamento (em MB) que deve ser respeitada considerando todos os arquivos em sua subárvore.

Implemente um sistema que:

Constrói a árvore de diretórios a partir da entrada

Calcula o tamanho total de cada diretório (soma recursiva de todos os arquivos em sua subárvore)

Verifica quais diretórios excedem sua cota

Encontra o diretório mais profundo que excede a cota

Lista os arquivos maiores que um limite X, precedidos pelo caminho completo

Entrada:

Primeira linha: N (número de entradas, 1 ≤ N ≤ 1000)

Próximas N linhas: caminho_pai nome tipo tamanho cota onde:

caminho_pai: caminho do diretório pai (/ para a raiz)

nome: nome do diretório ou arquivo

tipo: D para diretório ou A para arquivo

tamanho: tamanho em MB (0 para diretórios)

cota: cota em MB (apenas para diretórios, 0 para arquivos)

Última linha: X (limite para listar arquivos grandes, 1 ≤ X ≤ 10^6)

Saída:

Primeira linha: TAMANHOS: seguida pelos diretórios e seus tamanhos totais, ordenados alfabeticamente, no formato caminho:tamanho

Segunda linha: EXCEDEM: seguida pelos diretórios que excedem a cota, no formato caminho:tamanho/cota, ordenados alfabeticamente (ou NENHUM se nenhum exceder)

Terceira linha: MAIS PROFUNDO: <caminho> (ou NENHUM se nenhum exceder)

Quarta linha: ARQUIVOS > X: seguida pelos caminhos completos dos arquivos maiores que X, ordenados alfabeticamente (ou NENHUM)

Por exemplo:

Input	Resultado
1
/ docs D 0 100
50
TAMANHOS: /:0 /docs:0
EXCEDEM: NENHUM
MAIS PROFUNDO: NENHUM
ARQUIVOS > 50: NENHUM

*/

#include <stdio.h>  
#include <stdlib.h>
#include <string.h>

typedef struct No {
    int valor;
    struct No *esq;
    struct No *dir;
} No;

No* criar_no(int valor) {
    No *novo = (No*) malloc(sizeof(No));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

No* inserir(No *raiz, int valor) {
    if (raiz == NULL) return criar_no(valor);
    if (valor < raiz->valor) {
        raiz->esq = inserir(raiz->esq, valor);
    } else if (valor > raiz->valor) {
        raiz->dir = inserir(raiz->dir, valor);
    }
    return raiz;
}

No* minimo(No *no) {
    while (no != NULL && no->esq != NULL) {
        no = no->esq;
    }
    return no;
}

No* remover(No *raiz, int valor) {
    if (raiz == NULL) return NULL;
    if (valor < raiz->valor) {
        raiz->esq = remover(raiz->esq, valor);
    } else if (valor > raiz->valor) {
        raiz->dir = remover(raiz->dir, valor);
    } else {
        if (raiz->esq == NULL) {
            No *temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            No *temp = raiz->esq;
            free(raiz);
            return temp;
        }
        No *sucessor = minimo(raiz->dir);
        raiz->valor = sucessor->valor;
        raiz->dir = remover(raiz->dir, sucessor->valor);
    }
    return raiz;
}

// Preenche o vetor em ordem crescente (in-ordem)
void coletar_crescente(No *raiz, int v[], int *tam) {
    if (raiz == NULL) return;
    coletar_crescente(raiz->esq, v, tam);
    v[(*tam)++] = raiz->valor;
    coletar_crescente(raiz->dir, v, tam);
}

void liberar_arvore(No *raiz) {
    if (raiz == NULL) return;
    liberar_arvore(raiz->esq);
    liberar_arvore(raiz->dir);
    free(raiz);
}

int main() {
    No *raiz = NULL;
    char cmd[30];
    int arr[10005];

    while (scanf("%s", cmd) == 1) {
        if (strcmp(cmd, "FIM") == 0) {
            break;
        } else if (strcmp(cmd, "ENTRAR") == 0 || strcmp(cmd, "REATIVAR") == 0) {
            int p;
            scanf("%d", &p);
            raiz = inserir(raiz, p);
        } else if (strcmp(cmd, "BANIR") == 0) {
            int p;
            scanf("%d", &p);
            raiz = remover(raiz, p);
        } else if (strcmp(cmd, "TOP") == 0) {
            int k;
            scanf("%d", &k);
            int tam = 0;
            coletar_crescente(raiz, arr, &tam);

            if (tam < k || k <= 0) {
                printf("VAZIO\n");
            } else {
                for (int i = 0; i < k; i++) {
                    if (i > 0) printf(" ");
                    printf("%d", arr[tam - 1 - i]);
                }
                printf("\n");
            }
        } else if (strcmp(cmd, "BOTTOM") == 0) {
            int k;
            scanf("%d", &k);
            int tam = 0;
            coletar_crescente(raiz, arr, &tam);

            if (tam < k || k <= 0) {
                printf("VAZIO\n");
            } else {
                for (int i = 0; i < k; i++) {
                    if (i > 0) printf(" ");
                    printf("%d", arr[i]);
                }
                printf("\n");
            }
        } else if (strcmp(cmd, "MEDIANA") == 0) {
            int tam = 0;
            coletar_crescente(raiz, arr, &tam);

            if (tam == 0) {
                printf("VAZIO\n");
            } else if (tam % 2 == 1) {
                printf("%.1f\n", (double)arr[tam / 2]);
            } else {
                double med = (arr[tam / 2 - 1] + arr[tam / 2]) / 2.0;
                printf("%.1f\n", med);
            }
        } else if (strcmp(cmd, "POSICAO") == 0) {
            int p;
            scanf("%d", &p);
            int tam = 0;
            coletar_crescente(raiz, arr, &tam);

            int pos = -1;
            for (int i = 0; i < tam; i++) {
                if (arr[tam - 1 - i] == p) {
                    pos = i + 1;
                    break;
                }
            }

            if (pos == -1) {
                printf("NAO ENCONTRADO\n");
            } else {
                printf("%d\n", pos);
            }
        }
    }

    liberar_arvore(raiz);
    return 0;
}