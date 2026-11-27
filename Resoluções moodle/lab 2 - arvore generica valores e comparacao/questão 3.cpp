/*
Implemente funções recursivas para comparar duas árvores genéricas:

a) int sao_iguais(NoArvore *a, NoArvore *b): verifica se duas árvores têm a mesma estrutura e os mesmos valores

b) int sao_espelhadas(NoArvore *a, NoArvore *b): verifica se uma árvore é o espelho da outra (mesma estrutura, mas filhos em ordem reversa)

c) int eh_subarvore(NoArvore *a, NoArvore *b): verifica se a árvore B é uma subárvore de A

Entrada:

Primeira linha: N e M (tamanhos das árvores A e B)

Próximas N linhas: descrição da árvore A (nome_pai nome_filho)

Próximas M linhas: descrição da árvore B (nome_pai nome_filho)

Saída:

Primeira linha: "Iguais: Sim" ou "Iguais: Nao"

Segunda linha: "Espelhadas: Sim" ou "Espelhadas: Nao"

Terceira linha: "B e subarvore de A: Sim" ou "B e subarvore de A: Nao"

Por exemplo:

Input	Resultado
4 2
raiz a
raiz b
a c
a d
raiz a
a c
Iguais: Nao
Espelhadas: Nao
B e subarvore de A: Sim
*/