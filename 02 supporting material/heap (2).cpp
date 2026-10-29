#define MAX 100

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct Heap {
    int dados[MAX];
    int tamanho;
};

void inicializar(Heap *heap) {
    heap->tamanho = 0;
}

int pai(int i) { return (i - 1) / 2; }
int filho_esq(int i) { return 2 * i + 1; }
int filho_dir(int i) { return 2 * i + 2; }

bool esta_vazia(Heap *heap) {
    return heap->tamanho == 0;
}

int peek(Heap *heap) {
    if (esta_vazia(heap)) return -1;
    return heap->dados[0];  // Raiz = maximo
}

void heapify_up(Heap *heap, int indice) {
    while (indice > 0 && heap->dados[pai(indice)] < heap->dados[indice]) {
        // Troca com o pai
        int temp = heap->dados[pai(indice)];
        heap->dados[pai(indice)] = heap->dados[indice];
        heap->dados[indice] = temp;
        indice = pai(indice);
    }
}

void heapify_down(Heap *heap, int indice) {
    int maior = indice;
    int esq = filho_esq(indice);
    int dir = filho_dir(indice);
    
    if (esq < heap->tamanho && 
        heap->dados[esq] > heap->dados[maior]) {
        maior = esq;
    }
    if (dir < heap->tamanho && 
        heap->dados[dir] > heap->dados[maior]) {
        maior = dir;
    }
    
    if (maior != indice) {
        // Troca com o maior filho
        int temp = heap->dados[indice];
        heap->dados[indice] = heap->dados[maior];
        heap->dados[maior] = temp;
        heapify_down(heap, maior);
    }
}

void inserir(Heap *heap, int valor) {
    if (heap->tamanho >= MAX) return;
    
    heap->dados[heap->tamanho] = valor;
    heapify_up(heap, heap->tamanho);
    heap->tamanho++;
}

int remover_maior(Heap *heap) {
    if (esta_vazia(heap)) return -1;
    
    int maximo = heap->dados[0];
    heap->dados[0] = heap->dados[heap->tamanho - 1];
    heap->tamanho--;
    heapify_down(heap, 0);
    return maximo;
}

void heap_sort(int* vetor, int n)
{
    Heap fila_prioridade;
    inicializar(&fila_prioridade);
    for (int i = 0; i < n; i++)
    {
        inserir(&fila_prioridade, vetor[i]);
    }

    for (int i = 0; i < n; i++)
    {
        vetor[n - i - 1] = remover_maior(&fila_prioridade);
    }
}

int main(){

    int vetor[MAX];

    srand(time(NULL));
    
    printf("Array aleatório:");
    for (int i = 0; i < 20; i++)
    {
        vetor[i] = rand() % 100;
        printf("%4d", vetor[i]);
    }
    printf("\n");

    heap_sort(vetor, 20);

    printf("Array ordenado:");
    for (int i = 0; i < 20; i++)
    {
        printf("%4d", vetor[i]);
    }
    printf("\n");

    return 0;
}