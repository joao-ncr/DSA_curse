#include <stdio.h>
#include <stdlib.h>

struct Pilha{
    char *dados;
    int topo, cap;
};

void inicializar(Pilha* p)
{
    p->dados = (char*) malloc (sizeof(char) * 100);
    p->cap = 100;
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

void push(Pilha* p, char valor)
{
    if (p->topo + 1 == p->cap)
    {
        p->dados = (char*) realloc(p->dados, p->cap * 2);
        p->cap *= 2;
    }

    // p->dados[++p->topo] = valor;
    // p->topo++;
    ++p->topo;
    p->dados[p->topo] = valor;
    // p->dados[p->topo++] = valor;
}

char pop(Pilha* p)
{
    if (eh_vazia(p))
    {
        printf("[ERRO] Pilha vazia!\n");
        return '\0';
    }

    char temp = p->dados[p->topo];
    p->topo--;
    return temp;
}

int verificar_balanceamento(char* expressao)
{
    Pilha p;
    inicializar(&p);

    for(int i = 0; expressao[i] != '\0'; i++)
    {
        char c = expressao[i];
        if (c == '(' || c == '[' || c == '{')
        {
            push(&p, c);
        }
        if (c == ')' || c == ']' || c == '}')
        {
            char r = pop(&p);
            if (r == '\0')
                return 0; // Pilha vazia

            if ((r != '(' && c == ')') ||
                (r != '[' && c == ']') ||
                (r != '{' && c == '}'))
            {
                return 0; // Mismatch de caracteres
            }
        }
    }

    return eh_vazia(&p); // balanceamento correto
}

int main()
{
    char expressao[100];

    printf("Expressao: ");
    scanf("%s", expressao);

    printf("%s\n", expressao);

    printf("Balanceamento %s!\n",
        (verificar_balanceamento(expressao)) ? "correto" : "incorreto");

    return 0;
}