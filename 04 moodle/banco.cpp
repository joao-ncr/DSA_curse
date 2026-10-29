#include <iostream>
using namespace std; 
#define MAX 1000 


struct Queue{

    int dados[MAX]; 


    int front; // posição do próximo elemento que deve sair
    int back; // onde está o último elemento que entrou 
    int size; // tamanho da fia

};

void inicializar(Queue *fila){

    fila -> size = 0; 
    fila -> front = 0; 
    fila -> back = -1;

}


void enqueue(Queue *fila, int valor){

    if(fila -> size == MAX ){
        cout << "Operação inválida. Fila lotada" << endl; 
    return;
    }
    
    fila -> dados[fila -> back + 1] = valor; 
    fila -> back += 1 %MAX; // atualiza o novo back 
    fila -> size++; 
     

}



int dequeue(Queue *fila){

    if(fila -> size == 0 ){
        cout << "Operação inválida. Fila vazia" << endl; 
    return -1;
    }

    int valorRemovido = fila -> dados[fila -> front];
    fila -> front++ %MAX;
    fila -> size--; 
    return valorRemovido; 

}

int main(){

    Queue filaN, filaP; 
    inicializar(&filaN);
    inicializar(&filaP);

    int nClientes;
    cin >> nClientes; 
    char tipo;
    int senha; 

    for(int i = 0; i < nClientes; i++)
    {
        cin >> tipo >> senha; 
        if(tipo == 'P'){
            enqueue(&filaP, senha);
        }
        else{
            enqueue(&filaN, senha); 
        }
    }

    while(filaN.size > 0 || filaP.size  > 0)
    {

        if(filaP.size > 0){
            cout << dequeue(&filaP) << endl; 
        }
        if(filaP.size > 0){
            cout << dequeue(&filaP) << endl ; 
        }
        if(filaN.size > 0){
            cout << dequeue(&filaN) << endl; 
        }

    }


    return 0; 
}