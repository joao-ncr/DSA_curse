# Progresso de estudo

- Última atualização: 2026-10-29
- Disciplina: Algoritmos e Programação I (STCO01) — Prof. Sávio S. Dias, UNIFEI
- Sessões registradas: 1
- Prazo: 2 semanas (até 11–12/11/2026). Contexto: turma já em Árvores.

## Perfil declarado (diagnóstico inicial)
- Sólido: C padrão (matriz, laços, alocação dinâmica, teoria). Em melhora: funções.
- Lacuna: C++ (referência, new/delete, string, STL), listas/pilhas/filas/heap.

## Tópicos
| Tópico | Origem | Nível-alvo | Nível atual | Status | Última revisão |
|---|---|---|---|---|---|
| Ponte C→C++ | D01 / Lista 1 | 3 | 1 (declarado) | não iniciado | — |
| Array dinâmico (new/delete) | Lista 1 Ex1,4 | 3 | — | não iniciado | — |
| Struct + ponteiros | Lista 1 Ex2 | 3 | — | não iniciado | — |
| Recursão | Lista 1 Ex5–10, Lista 2 Ex1–2 | 4 | — | não iniciado | — |
| Lista sequencial | Lista 2 Ex6–7 | 3 | — | não iniciado | — |
| Lista encadeada / dupla | Lista 2 Ex8–9, Aula 7 | 4 | — | não iniciado | — |
| Pilha | Aula 8 | 3 | — | não iniciado | — |
| Fila / fila circular | Aula 9 | 3 | — | não iniciado | — |
| Fila de prioridade / Heap | Aula 10 | 3 | — | não iniciado | — |

Status "dominado" só com desafio do nível-alvo aprovado.

## Histórico de desafios
| Data | Tópico | Tipo | Nível | Resultado | Dicas usadas |
|---|---|---|---|---|---|

## Padrões de erro observados (nos seus envios ao Moodle, `04 moodle/`)
- Precedência/operador: `fila->back += 1 % MAX` (o `%` só age sobre o 1) e `fila->front++ % MAX` (resultado descartado) em `banco.cpp`.
- `=` no lugar de `==`: `if (fila->size = MAX)` em `impressora.cpp`.
- Variáveis locais sombreando campos: `int front = 0;` dentro de `inicializar` não inicializa a fila.
- Caminhos sem `return` / `main` sem fechar o laço (balanceamento.cpp).
→ Meu foco: revisar fila circular com módulo e comparação vs atribuição.

## Lacunas na matéria
- Aulas 8–10 têm exercícios sem material de apoio equivalente (pilha mínima, ordenar pilha, k-ésimo maior).

## Próximos passos
1. Fazer D01 e D02 (`03 training/`).
2. Responder as perguntas de leitura no fim de cada arquivo.
3. Voltar aqui com o resultado dos testes para eu avaliar e subir o nível.
