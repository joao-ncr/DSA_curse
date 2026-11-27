/*
Dados os percursos em-ordem e pré-ordem de uma árvore binária, reconstrua a árvore e imprima seu percurso pós-ordem.

Entrada:

Primeira linha: N (número de nós, 1 ≤ N ≤ 1000)

Segunda linha: N inteiros representando o percurso em pré-ordem

Terceira linha: N inteiros representando o percurso em-ordem

Saída:

N inteiros representando o percurso pós-ordem da árvore reconstruída

Por exemplo:

Input	Resultado
7
1 2 4 5 3 6 7
4 2 5 1 6 3 7
4 5 2 6 7 3 1


*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

Node* build_tree(int pre_order[], int in_order[], int in_start, int in_end, int* pre_idx) {
    if (in_start > in_end) {
        return NULL;
    }

    int root_val = pre_order[*pre_idx];
    (*pre_idx)++;
    
    Node* root = create_node(root_val);

    if (in_start == in_end) {
        return root;
    }

    int root_idx_in = -1;
    for (int i = in_start; i <= in_end; i++) {
        if (in_order[i] == root_val) {
            root_idx_in = i;
            break;
        }
    }

    root->left = build_tree(pre_order, in_order, in_start, root_idx_in - 1, pre_idx);
    root->right = build_tree(pre_order, in_order, root_idx_in + 1, in_end, pre_idx);

    return root;
}

void print_post_order(Node* root, int* is_first) {
    if (root == NULL) return;

    print_post_order(root->left, is_first);
    print_post_order(root->right, is_first);

    if (*is_first) {
        printf("%d", root->data);
        *is_first = 0; 
    } else {
        printf(" %d", root->data);
    }
}

void free_tree(Node* root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    int* pre_order = (int*)malloc(n * sizeof(int));
    int* in_order = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d", &pre_order[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &in_order[i]);
    }

    int pre_idx = 0;
    Node* root = build_tree(pre_order, in_order, 0, n - 1, &pre_idx);

    int is_first = 1;
    print_post_order(root, &is_first);
    printf("\n");

    free_tree(root);
    free(pre_order);
    free(in_order);

    return 0;
}
