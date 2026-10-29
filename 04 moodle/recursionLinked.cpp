#include <iostream>
using namespace std; 

struct No{
    int valor;
    No *prox; 
}; 

// função recursiva de soma
int somar(No *atual){
    if(atual == NULL){
        return 0;
    }
    return atual -> valor + somar(atual -> prox); 
}

// função recursiva de contadores
int contarMaiores(No *atual, int x){ // x é o valor comparado
    if(atual == NULL){
        return 0;
    }
    if(atual -> valor > x){
        return 1+contarMaiores(atual -> prox, x);
        return contarMaiores(atual -> prox, x);  
    }
}

int main(){

    int n; 
    cin >> n; 
    No *inicio = NULL;
    No *fim = NULL;

    for(int i = 0; i < n; i++){

        int valor;
        cin >> valor; 
        No *novo = new No;

        novo -> valor = valor;
        novo -> prox = NULL;  
        // primeiro nó 
        if(inicio == NULL){
            inicio = novo;
            fim = novo; 
        }
        else{
            fim -> prox = novo;
            fim = novo;
        }

    }

    int x;
    cin >> x; 

    cout << somar(inicio) << endl; 
    cout << contarMaiores(inicio, x) << endl; 
        
    return 0; 
}