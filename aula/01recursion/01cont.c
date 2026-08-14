// Implemente de forma recursiva (sem usar laços for, while ou goto):a) Uma func ̧  ̃ao que imprime todos os n  ́umeros de 1 at  ́e n em ordem crescente.

#include <stdio.h>

int contagem(n){
    if(n == 0) printf("(%d)Fogo!", n );

    else{
        printf("%d...", n);

        contagem(n-1);
    }
}

/*
Explicação:
O caso base define n = 0
Caso não seja satisfeita, será executada a função recursiva que, por sua vez, ficará empilhada, crescentemente, esperando que o caso base seja atingido, formando frames na stack
obs: n-1 garante que não haja stack overflow
printf imprime e depois a próxima função será empilhada
em memória:
n = 5
n == 0 ? False
5... (imprime)
5 - 1 = 4
4 == 0 ? False
4... (imprime)
0 == 0? True (caso base)
0...Fogo! (imprime)
= 5...4...3...2..1..0...Fogo!
*/