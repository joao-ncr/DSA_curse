#include <iostream> 
using namespace std;
#define MAX 1000
#include <string>

struct Stack{
    char dados[MAX]; 
    int size; 
}; 


void inicializar(Stack *pilha){
    pilha -> size = 0; 
}

void push(Stack *pilha, char valor){
    if(pilha-> size == MAX){
        cout << "Operação inválida"; 
    }
    pilha -> dados[pilha -> size] = valor; 
    pilha -> size++; 
}

char pop(Stack *pilha){
    if(pilha -> size == 0){
        cout << "Operação inválida"; 
        return -1; 
    }
    
    int valorRemovido = pilha -> dados[pilha -> size - 1];
    pilha -> size--;
    return valorRemovido; 
}

char top(Stack *pilha){
    if(pilha -> size == 0){
        cout << "Operação inválida"; 
        return -1; 
    }
    
    int valorTopo = pilha -> dados[pilha -> size - 1];
    return valorTopo; 
}


int main(){
 
    Stack pilha; 
    string entrada; 
    inicializar(&pilha); 
    bool balanceada = true;

    while(cin >> entrada){ 

    for(int i = 0; i < (int)entrada.size(); i++){

    if(entrada[i] == '(' || entrada[i] == '[' || entrada[i] == '{'){

        push(&pilha, entrada[i]);

    } else {

        if(pilha.size == 0){
            balanceada = false;
            break;
        }

        char topo = top(&pilha);

        if((entrada[i] == ')' && topo != '(') ||
           (entrada[i] == ']' && topo != '[') ||
           (entrada[i] == '}' && topo != '{')){

            balanceada = false;
            break;
        }

        top(&pilha);
    }
} 

    return 0; 
} 