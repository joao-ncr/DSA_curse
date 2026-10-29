#include <iostream>
#include <string>
#include <vector>
#include <cassert>
using namespace std;

// ---- mini-framework de teste (nao precisa mexer) ----
static int falhas = 0;
#define CHECK(cond) do { if (cond) cout << "  [OK]     " << #cond << "\n"; \
    else { cout << "  [FALHOU] " << #cond << "   (linha " << __LINE__ << ")\n"; falhas++; } } while (0)

// =====================================================================
// D02 - LISTA 1, Exercicios 1 e 2   (nivel 2-3)   Tempo: ~60 min
// Compile:  g++ -std=c++17 -Wall -Wextra -g D02_lista1_ex1_ex2.cpp -o d02
// Fonte: lista1.pdf, Ex.1 (arrays dinamicos) e Ex.2 (structs e ponteiros)
// ---------------------------------------------------------------------
// Antes de codar, DESENHE no papel: o array antigo [20,10] (tam=2) e o novo
// de tamanho 3. Qual indice do antigo vai para qual indice do novo?
// =====================================================================

// ---------- EX.1 ----------
// Cria novo array de tam+1, valor na posicao 0, copia o antigo deslocado
// uma casa a direita, libera o antigo (delete[]) e retorna o novo.
// Caso especial: arr == nullptr (tam == 0) NAO pode dar delete[] problematico
// (delete[] nullptr e permitido em C++, mas pense por que nem precisa testar).
int* inserir_inicio(int* arr, int tam, int valor) {
    // TODO
    return nullptr;
}

// ---------- EX.2 ----------
struct Produto {
    int codigo;
    string nome;
    float preco;
    int quantidade;
};

// (a) indice do produto MAIS CARO (empate: o primeiro encontrado).
// (c) comece com: assert(produtos != nullptr && tam > 0);
int indice_mais_caro(Produto* produtos, int tam) {
    // TODO
    return -1;
}

// (b) ponteiro para o produto com esse codigo, ou nullptr se nao existir.
Produto* buscar_por_codigo(Produto* produtos, int tam, int codigo) {
    // TODO
    return nullptr;
}

int main() {
    cout << "EX.1 - inserir_inicio (exemplo do enunciado)\n";
    int tam = 0;
    int* arr = nullptr;
    arr = inserir_inicio(arr, tam++, 10);
    CHECK(arr != nullptr && arr[0] == 10);
    arr = inserir_inicio(arr, tam++, 20);
    CHECK(arr != nullptr && tam == 2 && arr[0] == 20 && arr[1] == 10);
    arr = inserir_inicio(arr, tam++, 30);
    CHECK(arr != nullptr && tam == 3 && arr[0] == 30 && arr[1] == 20 && arr[2] == 10);
    delete[] arr;

    cout << "EX.1 - muitas insercoes\n";
    int t2 = 0;
    int* b = nullptr;
    for (int i = 0; i < 1000; i++) b = inserir_inicio(b, t2++, i);
    CHECK(b != nullptr && b[0] == 999 && b[999] == 0 && b[500] == 499);
    delete[] b;

    cout << "EX.2 - indice_mais_caro / buscar_por_codigo\n";
    Produto* ps = new Produto[4]{
        {101, "caneta",   2.50f, 10},
        {102, "caderno", 19.90f,  3},
        {103, "mochila", 19.90f,  1},   // empata com o caderno
        {104, "lapis",    1.20f, 50}
    };
    CHECK(indice_mais_caro(ps, 4) == 1);    // primeiro do empate
    CHECK(indice_mais_caro(ps, 1) == 0);
    CHECK(buscar_por_codigo(ps, 4, 103) == &ps[2]);
    CHECK(buscar_por_codigo(ps, 4, 104) == &ps[3]);
    CHECK(buscar_por_codigo(ps, 4, 999) == nullptr);
    Produto* achado = buscar_por_codigo(ps, 4, 101);
    if (achado) achado->quantidade = 99;     // alterar via ponteiro altera o array
    CHECK(ps[0].quantidade == 99);
    delete[] ps;

    cout << "\n" << (falhas == 0 ? "TUDO OK!" : "Ainda ha testes falhando.") << "\n";
    return falhas;
}

// ====================== PERGUNTAS DE REFLEXAO ===========================
// R1. Esta funcao e O(n) por chamada. Inserir N elementos no inicio desse jeito
//     custa quanto no total? Compare com 'insere_inicio(LLigada*)' do
//     experimento.cpp do professor (Lista 1 -> Lista 2 Ex.10 usa isso).
// R2. Por que retornamos o ponteiro novo em vez de alterar 'arr' dentro da
//     funcao? (Dica: 'arr' dentro da funcao e uma COPIA do ponteiro.)
// R3. Em indice_mais_caro, por que o enunciado pede assert e nao um 'return -1'?
