#include <iostream> 
#define MAX 1000
using namespace std; 

struct Work{
    int id;
    int paginas;
}; 

struct Queue{
    Work dados[MAX]; 
    int front;
    int back; 
    int size; 
}; 

void inicializar(Queue *fila){
    int front = 0; 
    int back = -1;
    int size = 0; 
}

void enqueue(Queue *fila, Work trabalho){
    if(fila -> size = MAX){
        return; 
    }
    fila -> back++ % MAX; 
    fila -> dados[fila -> back + 1] = trabalho;
    fila -> size++ % MAX; 

}

Work endqueue(Queue *fila){
    Work removido = fila -> dados[fila -> front]; 
    fila -> front++ %MAX;
    fila -> size-- %MAX;
    return removido; 
}

int main(){


    return 0; 
}