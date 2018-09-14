//Robert Trew - 15315527
//01-12-2017
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Tree_Node {
    char val;
    struct Tree_Node *left, *right;
} Tree_Node;

void tree_insert (Tree_Node** root, char data);
Tree_Node* tree_search (Tree_Node* root, char data);
void tree_print_sorted (Tree_Node* root);
void tree_delete (Tree_Node* root);

int main ( int argc, char *argv[] ) {
    Tree_Node *root = NULL;
    char buff;
    char ins[] = "FLOCCINAUCINIHILIPILIFICATION";
    int len = strlen(ins);
    int i;
    printf("ADDING: ");
    for (i = 0; i < len; i++) {printf("%c ", ins[i]);}
    puts("");
    for (i = 0; i < len; i++) {tree_insert(&root, ins[i]);}
    printf("SORTED: ");
    tree_print_sorted(root);
    puts("");
    buff = '\n';
    /*do {
        printf("Please enter a letter to search for: ");
        do {
            buff = getchar();
        }while (buff == '\n');
        if (buff != ' ') {
            if (tree_search(root, buff)) {
                printf("%c in tree\n", buff);
            }
            else {printf("%c not in tree\n", buff);}
        }
    }while (buff != ' ');*/
    for (i = 0; i < 2; i++) {
        buff = 'A' + (rand() % 26);
        if(tree_search(root, buff)) {printf("%c in tree\n", buff);}
        else {printf("%c not in tree\n", buff);}
    }
    tree_delete(root);
    printf("Tree deleted\n");
    return 0;
}

void tree_insert (Tree_Node** root, char data) {
    if (!(*root)) {
        Tree_Node *new_node = (Tree_Node*)malloc(sizeof(Tree_Node));
        new_node->val = data;
        *root = new_node;
        (*root)->left = NULL;
        (*root)->right = NULL;
        return;
    }
    if (data < (*root)->val) {
        tree_insert(&(*root)->left, data);
    }
    else {
        tree_insert(&(*root)->right, data);
    }
}

Tree_Node* tree_search (Tree_Node* root, char data) {
    if ((!root) || (root->val == data)) {return root;}
    if (data > root->val) {return (tree_search(root->right, data));}
    return (tree_search(root->left, data));
}

void tree_print_sorted (Tree_Node* root) {
    if (root) {
        tree_print_sorted(root->left);
        printf("%c ", root->val);
        tree_print_sorted(root->right);
    }
}

void tree_delete (Tree_Node* root) {
    if (root) {
        tree_delete(root->left);
        tree_delete(root->right);
        free(root);
    }
}