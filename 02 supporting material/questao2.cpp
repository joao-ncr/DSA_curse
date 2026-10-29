#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pilha{
    char dados[100][200];
    int topo;
};

void inicializar(Pilha* p)
{
    p->topo = -1;
}

int tamanho(Pilha* p)
{
    return p->topo + 1;
}

int eh_vazia(Pilha* p)
{
    return p->topo == -1;
}

void push(Pilha* p, char* valor)
{
    ++p->topo;
    strcpy(p->dados[p->topo], valor);
}

char* pop(Pilha* p)
{
    char* temp = (char*) malloc (sizeof(char) * 200);
    strcpy(temp, p->dados[p->topo]);
    p->topo--;
    return temp;
}

int main()
{
    char pagina[200];
    char comando[10];

    Pilha p_historico, p_avancar;
    inicializar(&p_historico);
    inicializar(&p_avancar);

    while(true)
    {
        scanf("%s", comando);
        if (strcmp(comando, "FIM") == 0)
            break;

        if (strcmp(comando, "VISITAR") == 0)
        {
            scanf("%s", pagina);
            push(&p_historico, pagina);
            printf("%s\n", p_historico.dados[p_historico.topo]);
            inicializar(&p_avancar);
        }

        if (strcmp(comando, "VOLTAR") == 0)
        {
            // printf("HISTORICO:");
            // for (int i = 0; i <= p_historico.topo; i++)
            //     printf("%s\t", p_historico.dados[i]);
            // printf("\nAVANCAR:");
            // for (int i = 0; i <= p_avancar.topo; i++)
            //     printf("%s\t", p_avancar.dados[i]);
            // printf("\n");

            char* pagina_anterior;
            if (!eh_vazia(&p_historico))
            {
                pagina_anterior = pop(&p_historico);
                push(&p_avancar, pagina_anterior);
                if (!eh_vazia(&p_historico))
                {
                    printf("%s\n", p_historico.dados[p_historico.topo]);
                }
                else
                {
                    push(&p_historico, pagina_anterior);
                    pop(&p_avancar);
                    printf("NAO FOI POSSIVEL\n");
                }
            }
            else
            {
                printf("NAO FOI POSSIVEL\n");
            }
        }

        if (strcmp(comando, "AVANCAR") == 0)
        {
            // printf("HISTORICO:");
            // for (int i = 0; i <= p_historico.topo; i++)
            //     printf("%s\t", p_historico.dados[i]);
            // printf("\nAVANCAR:");
            // for (int i = 0; i <= p_avancar.topo; i++)
            //     printf("%s\t", p_avancar.dados[i]);
            // printf("\n");
            char* proxima_pagina;
            if (!eh_vazia(&p_avancar))
            {
                proxima_pagina = pop(&p_avancar);
                push(&p_historico, proxima_pagina);
                printf("%s\n", proxima_pagina);
            }
            else
            {
                printf("NAO FOI POSSIVEL\n");
            }
        }
    }

    return 0;
}