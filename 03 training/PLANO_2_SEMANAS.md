# Plano de 2 semanas — Listas lineares até Filas de Prioridade (Algoritmos e Programação I)

Início: qui 29/10/2026 · Fim: qua 11/11 (qui 12/11 = folga) · Meta: ~90 exercícios, todos com teste ou verificação.

**Regra de ouro:** o que importa para ÁRVORES vem primeiro — ponteiros/nó, recursão, lista encadeada, pilha/fila (DFS/BFS) e heap (árvore em array).

## Prioridade do conteúdo
| Prioridade | Conteúdo | Por quê |
|---|---|---|
| A (indispensável) | L1 Ex1,2,4 · Recursão (L1 Ex5,6,7,9,10) · L2 Ex6,7 (lista sequencial) · L2 Ex8,9 (encadeada) · Aula 8 (pilha) · Aula 9 (fila) | base direta de árvores + provável prova |
| B (importante) | L2 Ex1 (busca binária), Ex2a (backtracking) · Aula 7 (inserção ordenada, merge, lista dupla) · Aula 10 (heap, heapsort, std::priority_queue) | recursão com ramificação / árvore em array |
| C (só se sobrar tempo) | L1 Ex3 (bitwise) e Ex8c (tabela empírica) · L2 Ex3–5 (TADs Complexo/Vetor3D/Data) · L2 Ex10 e Aula 7 Ex1 (benchmark) · XOR list · k listas / mediana | treino de sintaxe, não de ideias novas |

## Calendário
| Dia | Foco | Exercícios (aprox.) |
|---|---|---|
| 1 · qui 29/10 | **Ponte C→C++** + tour do material de apoio + L1 Ex1–2 | D01 (6 drills) + L1 Ex1, Ex2a/b/c |
| 2 · sex 30 | L1 Ex4 + recursão base (Ex5, Ex6) | 6 |
| 3 · sáb 31 | L1 Ex7, Ex9, Ex10, Ex8a/b | 7 |
| 4 · dom 01/11 | L2 Ex1 (busca binária), Ex2a (labirinto), TAD mínimo (ponto2d → Complexo parcial) | 5 |
| 5 · seg 02 | L2 Ex6, Ex7 (lista sequencial) | 7 |
| 6 · ter 03 | L2 Ex8 (lista encadeada completa) | 8 |
| 7 · qua 04 | L2 Ex9 (inverter, ordenado, meio, ciclo) + Aula 7 Ex4–5 | 8 |
| 8 · qui 05 | Aula 7: lista dupla (Ex2), std::list; **revisão espaçada** do que errou nos dias 1–7 | 5 |
| 9 · sex 06 | Aula 8: pilha (array + lista), balanceamento, decimal→binário | 7 |
| 10 · sáb 07 | Aula 8: pilha mínima, remover do meio (recursivo), ordenar pilha, RPN | 6 |
| 11 · dom 08 | Aula 9: fila circular, fila com lista, inverter fila, banco | 7 |
| 12 · seg 09 | Aula 9: fila de impressão, 1º não repetido · Aula 10: PQ ingênua + heap | 7 |
| 13 · ter 10 | Aula 10: heapsort, k-ésimo maior, std::priority_queue | 5 |
| 14 · qua 11 | **Simulado** estilo prova (sem consultar) + ponte para árvores | 5 |
| folga · qui 12 | refazer o que ainda falha | — |

O plano se ajusta ao seu desempenho: se um dia render menos, os itens C caem primeiro.

## Como usar `02 supporting material` (consulta em prova)
| Precisa de... | Abra | Atenção |
|---|---|---|
| recursão com rastro na tela | `exemplo1.cpp`, `exerc2.c`, `hanoi.c` (Hanoi + permutações) | — |
| busca binária (recursiva, contador) | `binaria.c` | — |
| lista sequencial (inserir/remover/buscar) | `exerc1.cpp` | op. 3 imprime `p1[pos]` mesmo com `pos == -1` |
| lista sequencial dinâmica | `exercicio5.cpp` | `insert_list` desloca a partir de `capacity` (deveria ser `size`); `remove_list` é TODO |
| TAD (struct + funções) | `ponto2d.cpp` | — |
| lista encadeada simples (cabeça/cauda) | `questao4.c` | `inserir_ordenado` quebra com lista vazia e insere errado após a cabeça (testei: [1,5] + 3 → `3 1 5`) |
| lista dupla | `lista_dupla (2).cpp`, `chat_uol (1).cpp` | `lista_dupla` **não compila** (`criar_no_duplo` duplicada); `remover` quebra com 1 único nó |
| pilha | `balanceamento (2).cpp`, `questao2.cpp` | — |
| fila circular | `banco (1).cpp` | modelo correto do `% MAX` |
| heap / heapsort | `heap (2).cpp`, `questao1.c` | — |
| benchmark de estruturas | `experimento.cpp` | — |

Use como **ponto de partida de prova**, não como verdade: leia e teste antes de copiar.

## Compilar
`g++ -std=c++17 -Wall -Wextra -g arquivo.cpp -o arquivo`
> Seu `.vscode/tasks.json` usa `gcc.exe`: para `.cpp` com `iostream`/`string` isso falha no link. Use `g++.exe` (mesma pasta `C:\MinGW\bin`).
