/*
Use uma árvore genérica para representar expressões aritméticas. Cada nó armazena um operador (+, -, *, /) ou um operando (número inteiro). Os filhos de um operador são seus operandos (ou subexpressões).

typedef struct NoExpr {
    char operador; // '+', '-', '*', '/' ou '\0' para números
    int valor;     // usado apenas se operador == '\0'
    struct NoExpr *primeiro_filho;
    struct NoExpr *proximo_irmao;
} NoExpr;
Implemente:

a) int avaliar(NoExpr *no): avalia a expressão recursivamente

b) void imprimir_infixa(NoExpr *no): imprime a expressão em notação infixa com parênteses

Entrada:

A entrada descreve uma árvore de expressão no formato: cada linha contém o nó e seus filhos

Formato: operador filho1 filho2 ... (para operadores) ou numero (para operandos)

A primeira linha é a raiz

Saída:

Primeira linha: "Resultado: <valor>"

Segunda linha: "Infixa: <expressao>"

Por exemplo:

Input	Resultado
+ 3 *
3
* 4 5
4
5
Resultado: 23
Infixa: (3 + (4 * 5))

*/