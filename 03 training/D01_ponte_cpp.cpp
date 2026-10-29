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
// D01 - PONTE C -> C++   (nivel 1-2)   Tempo: ~40 min
// Compile:  g++ -std=c++17 -Wall -Wextra -g D01_ponte_cpp.cpp -o d01
// Rode:     ./d01   (Windows: d01.exe)
// Objetivo: seis habilidades de C++ que o professor usa nos .cpp dele.
// Complete os TODO. NAO mexa na main. Tente sozinho antes de consultar
// o material de apoio (indicado em cada drill).
// =====================================================================

// ---------- DRILL 1: string, to_string, const& ----------
// Retorne exatamente: "Ola, <nome>! Voce tem <idade> anos."
// Dicas: std::string aceita '+'; to_string(int) converte numero em string.
// 'const string&' = passa sem copiar e sem permitir alterar.
string saudacao(const string& nome, int idade) {
    // TODO
    return "";
}

// ---------- DRILL 2: referencia (&) ----------
// Em C voce faria trocar(int* a, int* b) e chamaria trocar(&x,&y).
// Em C++ a referencia faz o '*' e o '&' sumirem na chamada: trocar(x,y).
// Material de apoio: nada usa isso ainda; a Lista 1 usa &permissoes (Ex.3).
void trocar(int& a, int& b) {
    // TODO
}
// Deixe a <= b (reaproveite trocar).
void ordenar2(int& a, int& b) {
    // TODO
}

// ---------- DRILL 3: new[] / delete[] ----------
// Aloque um array de n inteiros com new int[n], onde v[i] = i*i, e retorne.
// Quem CHAMA e responsavel por delete[] (veja a main).
// Compare com malloc em '02 supporting material/exercicio5.cpp' (create_list).
int* criar_quadrados(int n) {
    // TODO
    return nullptr;
}

// ---------- DRILL 4: nullptr e ponteiro como retorno ----------
// Retorne o ENDERECO do primeiro elemento == x, ou nullptr se nao existir.
// Modelo: buscabinaria()/buscalinear() em '02 supporting material/binaria.c'
int* encontrar(int* v, int n, int x) {
    // TODO
    return nullptr;
}

// ---------- DRILL 5: struct com string + std::vector + range-for ----------
struct Aluno {
    string nome;
    double nota;
};
// Media das notas (vetor vazio -> 0.0). Use: for (const Aluno& a : v) { ... }
double media(const vector<Aluno>& v) {
    // TODO
    return -1;
}
// Nome do aluno com maior nota (empate: o primeiro). Vetor vazio -> "".
string melhor(const vector<Aluno>& v) {
    // TODO
    return "?";
}

// ---------- DRILL 6: sobrecarga e argumento padrao ----------
// O professor usa os dois: buscar(lista, msg = NULL, autor = NULL) em
// chat_uol.cpp e duas insere_inicio(...) em experimento.cpp.
// (a) somar(a,b,c=0): soma de inteiros, c opcional.
int somar(int a, int b, int c = 0) {
    // TODO
    return 0;
}
// (b) sobrecarga: versao para double (apenas dois argumentos).
double somar(double a, double b) {
    // TODO
    return 0;
}

int main() {
    cout << "DRILL 1 - saudacao\n";
    CHECK(saudacao("Ana", 20) == "Ola, Ana! Voce tem 20 anos.");
    CHECK(saudacao("", 0) == "Ola, ! Voce tem 0 anos.");

    cout << "DRILL 2 - referencias\n";
    int x = 1, y = 2;
    trocar(x, y);
    CHECK(x == 2 && y == 1);
    int p = 9, q = 4;
    ordenar2(p, q);
    CHECK(p == 4 && q == 9);
    ordenar2(p, q);               // ja ordenado: nao muda
    CHECK(p == 4 && q == 9);

    cout << "DRILL 3 - new/delete\n";
    int* sq = criar_quadrados(5);
    CHECK(sq != nullptr && sq[0] == 0 && sq[3] == 9 && sq[4] == 16);
    delete[] sq;                  // delete[] porque veio de new[]

    cout << "DRILL 4 - encontrar\n";
    int v[] = {7, 3, 9, 3};
    int* r = encontrar(v, 4, 3);
    CHECK(r == &v[1]);            // primeira ocorrencia, mesmo endereco
    CHECK(r != nullptr && *r == 3);
    CHECK(encontrar(v, 4, 100) == nullptr);
    CHECK(encontrar(v, 0, 7) == nullptr);   // n = 0

    cout << "DRILL 5 - vector<Aluno>\n";
    vector<Aluno> turma = { {"Bia", 7.0}, {"Caio", 9.0}, {"Davi", 9.0}, {"Eva", 5.0} };
    CHECK(media(turma) == 7.5);
    CHECK(melhor(turma) == "Caio");
    vector<Aluno> vazio;
    CHECK(media(vazio) == 0.0);
    CHECK(melhor(vazio) == "");

    cout << "DRILL 6 - sobrecarga\n";
    CHECK(somar(1, 2) == 3);
    CHECK(somar(1, 2, 3) == 6);
    CHECK(somar(1.5, 2.5) == 4.0);

    cout << "\n" << (falhas == 0 ? "TUDO OK! Passe para o D02." : "Ainda ha testes falhando.") << "\n";
    return falhas;
}

// ====================== PERGUNTAS DE LEITURA (responda por escrito) =====
// Abra '02 supporting material/experimento.cpp' e responda aqui nos comentarios:
// P1. Por que existem DUAS funcoes chamadas insere_inicio? O que o compilador
//     usa para escolher qual chamar?
// P2. Neste arquivo ele usa malloc/free E std::vector/std::list. Em C++ puro,
//     qual seria o equivalente de malloc(sizeof(No)) e de free(p)?
// P3. 'LArray' tem 'int data[1000000]'. Por que declarar 'LArray lista;' dentro
//     da main pode estourar a pilha de execucao (stack overflow)?
