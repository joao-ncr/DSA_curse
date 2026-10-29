#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct nome{
    char nome[20];
};

struct queue{
    nome data[MAX];
    int front, back;
    int size;
};

void inicializa(queue* q)
{
    q->size = q->front = 0;
    q->back = -1;
}

void enqueue(queue* q, const char* nome)
{
    if (q->size == MAX)
    {
        printf("Fila lotada!\n");
        return;
    }

    int pos = (q->back + 1) % MAX;
    strcpy(q->data[pos].nome, nome);
    q->back = pos;
    q->size++;
}

char* dequeue(queue* q)
{
    if (q->size == 0)
    {
        printf("Fila vazia!\n");
        return NULL;
    }
    
    char* nome = (char*) malloc(sizeof(char) * 20);
    strcpy(nome, q->data[q->front].nome);
    q->front = (q->front + 1) % MAX;
    q->size--;
    return nome;
}

int main()
{
    queue q;
    inicializa(&q);

    // int caixas[] = { 1, 3, 5 };
    int caixas[] = { 1, 1, 1 };

    char nome[20];
    // enqueue(&q, "Pessoa a");
    // enqueue(&q, "Pessoa b");
    // enqueue(&q, "Pessoa c");

    int cont_p = 1;
    // for (int i = 0; i < 6 * 3600; i++)
    for (int i = 1; i < 100; ++i)
    {
        if (i % 2 == 0)
        {
            sprintf(nome, "Pessoa %d", cont_p++);
            enqueue(&q, nome);
        }
        for (int j = 0; j < 3; ++j)
        {
            if (caixas[j] % 5 == 0)
            {
                auto atendido = dequeue(&q);
                if (atendido != NULL)
                    printf("[%ds]Caixa %d Atendimento %s\n", i, j, atendido);
                else
                    printf("[%ds]Caixa %d ocioso. Ngm para atender.\n",i , j);
            }
            caixas[j]++;
        }
    }

    return 0;
}