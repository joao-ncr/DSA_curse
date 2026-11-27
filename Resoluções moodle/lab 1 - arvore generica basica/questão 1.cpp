#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
/*
implementações que a questão pede: altura, profundidade (nível), grau máximo 
Saídas esperadas 
Altura:
Profundidade de <nome>:
Grau máximo: 
*/


/*
Em árvore genéricas o primeiro filho desce um nível hierárquico 
próximo irmão anda para o lado no mesmo nível 
*/

struct NoArvore{
    char nome[50]; 
    NoArvore* primeiro_filho;
    NoArvore* proximo_irmao; 
}; 

NoArvore* criar_no(const char* nome){
    NoArvore *novo = (NoArvore*) malloc(sizeof(NoArvore)); 
    strcpy(novo-> nome, nome); // copia o nome
    novo -> primeiro_filho = NULL; // nó vazio 
    novo -> proximo_irmao = NULL; // nó vazio
    return novo;
}

void add_filho(NoArvore* pai, NoArvore* filho){
    filho -> proximo_irmao = pai -> primeiro_filho; // B recebe o primeiro filho de A (nulo)
    pai -> primeiro_filho = filho; // Agora A aponta para B = são conectados
}

void exibir(NoArvore *no, int nivel){ 
    // pense: se eu só preciso exibir algo, acesso o nó diretamente ou ele depende dos filhos
    if(no == NULL) return; // caso basee

    // trabalho no nó atual (pré ordem)
    for(int i = 0; i < nivel; i++){
        printf("  "); 
    }
    printf(" -- %s\n", no-> nome);

    // --- visita aos filhos --- laço
    NoArvore *filho = no->primeiro_filho; 
    while(filho!= NULL){
        exibir(filho, nivel + 1);
        filho = filho->proximo_irmao; 
    }
}


NoArvore* buscar(NoArvore *no, const char* nome){
    if(no == NULL) return NULL; // caso base 
    if(strcmp(no->nome, nome) == 0) return no; // pré ordem: testa o nó atual antes de descer
        
    NoArvore *retorno = NULL; 
    NoArvore *filho = no->primeiro_filho; 
    while(filho != NULL && retorno == NULL){ // enquanto houver filhos e não tiver achado
        retorno = buscar(filho, nome); // procura na subárvore inteira deste filho 
        filho = filho -> proximo_irmao; // se não achou, tenta o próximo irmão 
    }
    return retorno; // devolve o endereço encontrado ou null
}

// Operações obrigatórias: altura, profundidade, grau


int altura(NoArvore *no){ // altura depende dos filhos > pós-ordem

    if(no == NULL) return 0;

    int altura_max = 1; // conta o próprio nó atual
    NoArvore *filho = no-> primeiro_filho; 
    while(filho != NULL){
        int altura_filho = altura(filho); // descobre a altura de cada filho
        if(altura_filho + 1 > altura_max){ // compara
            altura_max = altura_filho + 1; 
        }
        filho = filho->proximo_irmao;
    }

    return altura_max; // só retorna após consultar todos os filhos

}

int profundidade(NoArvore *no, char *nome, int nivel_atual){
    if(no == NULL) return -1;
    else if(strcmp(no-> nome, nome) == 0) return nivel_atual; // verifica se achou antes de descer (pré-ordem)
    NoArvore *filho = no-> primeiro_filho;
    while(filho!= NULL){
        int profundidade_filho = profundidade(filho, nome, nivel_atual +1);
        if(profundidade_filho != -1) return profundidade_filho; // se achar um filho diferente de -1, repassa
        filho = filho-> proximo_irmao;
    }
    return -1; 
}

int grau_maximo(NoArvore *no) {
    if (no == NULL) return -1;

    int grau_no = 0;                            // Conta os filhos DIRETOS deste nó
    int grau_max = 0;                           // Guarda o maior grau encontrado nas subárvores
    NoArvore *filho = no->primeiro_filho;
    while (filho != NULL) {
        grau_no++;                              // Achou mais um irmão na lista = +1 filho direto
        int grau_filho = grau_maximo(filho);    // Pergunta qual o recorde dentro da subárvore desse filho
        if (grau_filho > grau_max)
            grau_max = grau_filho;
        filho = filho->proximo_irmao;
    }
    return grau_max > grau_no ? grau_max : grau_no;
}



int main() {
    int n;
    char pai[50], filho[50], nome[50];

    scanf("%d", &n);

    NoArvore *raiz = NULL;
    for(int i = 0; i < n; i++) {
        scanf("%s %s", pai, filho);

        NoArvore *no_pai = buscar(raiz, pai); // Trocado 'auto' por 'NoArvore*'
        if (no_pai == NULL) {
            raiz = criar_no(pai);
            no_pai = raiz;
        }
        NoArvore *no_filho = criar_no(filho); // Trocado 'auto' por 'NoArvore*'
        add_filho(no_pai, no_filho);
    }
    scanf("%s", nome);

    exibir(raiz, 0);
    printf("\n");
    printf("Altura: %d\n", altura(raiz));
    printf("Profundidade de %s: %d\n", nome, profundidade(raiz, nome, 0));
    printf("Grau maximo: %d\n", grau_maximo(raiz));

    return 0;
}