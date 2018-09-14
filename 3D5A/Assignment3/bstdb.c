//Robert Trew - 15315527
//01-12-2017
//AVL Tree method, inspired by http://www.geeksforgeeks.org/avl-tree-set-1-insertion/
//check_bal method (for balanced tree), from http://www.geeksforgeeks.org/avl-tree-set-1-insertion/
#include "bstdb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

// Write your submission in this file
//
// A main function and some profiling tools have already been set up to test
// your code in the task2.c file. All you need to do is fill out this file
// with an appropriate Binary Search Tree implementation.
//
// The input data will be books. A book is comprised of a title and a word
// count. You should store both these values in the tree along with a unique
// integer ID which you will generate.
//
// We are aiming for speed here. A BST based database should be orders of
// magnitude faster than a linked list implementation if the BST is written
// correctly.
//
// We have provided an example implementation of what a linked list based
// solution to this problem might look like in the db/listdb.c file. If you
// are struggling to understand the problem or what one of the functions
// below ought to do, consider looking at that file to see if it helps your
// understanding.
//
// There are 6 functions you need to look at. Each is provided with a comment
// which explains how it should behave. The functions are:
//
//  + bstdb_init
//  + bstdb_add
//  + bstdb_get_word_count
//  + bstdb_get_name
//  + bstdb_stat
//  + bstdb_quit
//
// Do not rename these functions or change their arguments/return types.
// Otherwise the profiler will not be able to find them. If you think you
// need more functionality than what is provided by these 6 functions, you
// may write additional functions in this file.

#define TRUE 1
#define FALSE 0

typedef struct tree_node {
	int doc_id;
	char *name;
	int word_count;
	struct tree_node *left;
	struct tree_node *right;
	int height;
} tree_node;

char choice;
int b_added_elements;
tree_node *root;

int b_num_comps;
static int b_num_searches;

int
bstdb_init ( void ) {
	// This function will run once (and only once) when the database first
	// starts. Use it to allocate any memory you want to use or initialize 
	// some globals if you need to. Function should return 1 if initialization
	// was successful and 0 if something went wrong.
	root = NULL;
	b_added_elements = 0;
	b_num_comps = 0;
	b_num_searches = 0;
	choice = 'A';
	if (choice == 'B') {srand(time(NULL));}
	//Make sure everything is as expected
	if (root && b_added_elements != 0 && b_num_comps != 0 && b_num_searches != 0) {return 0;}
	return 1;
}

int get_height (tree_node* tn) {
	if (!tn) {return 0;}

	return tn->height;
}

int max(int a, int b) {
	return ((a > b)? a : b);
}

static void free_tree_node(tree_node *node) {
	if (node) {
		free_tree_node(node->left);
		free_tree_node(node->right);
		if (node->name) {free(node->name);}
		free(node);
	}
}

static tree_node* create_tree_node(int doc_id, char *name, int word_count) {
	tree_node *tn = (tree_node*)malloc(sizeof(tree_node));
	size_t len_name;
	if (tn) {
		tn->doc_id = doc_id;
		tn->word_count = word_count;
		tn->left = NULL;
		tn->right = NULL;
		tn->height = 1;

		len_name = strlen(name)+1;
		tn->name = calloc(len_name, sizeof(char));
		if (tn->name) {strcpy(tn->name, name);}
		else { //calloc failed
			free_tree_node(tn);
			tn = NULL;
		}
	}
	return tn;
}

tree_node* r_rot (tree_node *tn) {
	tree_node *x = tn->left;
	tree_node *y = x->right;
	//Perform rotation
	x->right = tn;
	tn->left = y;
	//Update heights
	tn->height = max(get_height(tn->left), get_height(tn->right)) + 1;
	x->height = max(get_height(x->left), get_height(x->right)) + 1;
	return x;
}

tree_node* l_rot (tree_node *tn) {
	tree_node *y = tn->right;
	tree_node *x = y->left;
	//Perform rotation
	y->left = tn;
	tn->right = x;
	//Update heights
	tn->height = max(get_height(tn->left), get_height(tn->right)) + 1;
	y->height = max(get_height(y->left), get_height(y->right)) + 1;
	return y;
}

int get_balance (tree_node *tn) {
	if (!tn) {return 0;}
	return (get_height(tn->left) - get_height(tn->right));
}

tree_node* insert_bst(tree_node* node, tree_node* tn) {
	if (!node) {return tn;}
	if (tn->doc_id < node->doc_id) {node->left = insert_bst(node->left, tn);}
	else if (tn->doc_id > node->doc_id) {node->right = insert_bst(node->right, tn);}
	else {
		if(tn->doc_id + 5 <= 0) {tn->doc_id = tn->doc_id - 1;}
		else {tn->doc_id++;}
		node = insert_bst(node, tn);
	}
	return node;
}

tree_node* insert_avl(tree_node *node, tree_node *tn) {
	if (!node) {return tn;}
	if (tn->doc_id < node->doc_id) {node->left = insert_avl(node->left, tn);}
	else if (tn->doc_id > node->doc_id) {node->right = insert_avl(node->right, tn);}
	else {tn->doc_id++; node = insert_avl(node, tn);}
	int bal = get_balance(node);
	if (bal > 1) { //Left greater
		if (get_height(node->left->left) >= get_height(node->left->right)) {
			return r_rot(node); //LL
		}
		else {
			node->left = l_rot(node->left);
			return r_rot(node); //LR
		}
	}
	if (bal < -1) { //Right greater
		if (get_height(node->right->right) >= get_height(node->right->left)) {
			return l_rot(node); //RR
		}
		else {
			node->right = r_rot(node->right);
			return l_rot(node); //RL
		}
	}
	node->height = 1 + max(get_height(node->left), get_height(node->right));
	return node;
}

tree_node* search(tree_node* tn, int doc_id) {
	if (!tn || tn->doc_id == doc_id) {b_num_comps++; return tn;}
	if (tn->doc_id < doc_id) {b_num_comps+=2; return search(tn->right, doc_id);}
	return search(tn->left, doc_id);
}

int count_nodes (tree_node *tn) {
	int count = 1;
	if (!tn) {return 0;}
	else {
		count += count_nodes(tn->left);
		count += count_nodes(tn->right);
		return count;
	}
}

int hash (char *c) {
	int x = 0;
	while(*c){
		x = 31 * x + *c;
		if (x < 0) {
			x = abs(x % (INT_MAX/7));}
		c++;
	}
	return x;
}

int
bstdb_add ( char *name, int word_count ) {
	// This function should create a new node in the binary search tree, 
	// populate it with the name and word_count of the arguments and store
	// the result in the tree.
	//
	// This function should also generate and return an identifier that is
	// unique to this document. A user can find the stored data by passing
	// this ID to one of the two search functions below.
	//
	// How you generate this ID is up to you, but it must be an integer. Note
	// that this ID should also form the keys of the nodes in your BST, so
	// try to generate them in a way that will result in a balanced tree.
	//
	// If something goes wrong and the data cannot be stored, this function
	// should return -1. Otherwise it should return the ID of the new node
	tree_node* tmp = NULL;
	if (choice == 'A') {tmp = create_tree_node(b_added_elements + 1, name, word_count);}
	else {
		//tmp = create_tree_node((hash(name)), name, word_count);
		tmp = create_tree_node(rand(), name, word_count);
	}
	if (!tmp) {return -1;}
	if (choice == 'B') {
		if (!root) {root = insert_bst(root, tmp);}
		else {insert_bst(root, tmp);}
	}
	else {root = insert_avl(root, tmp);}
	b_added_elements++;
	//In case something went wrong in insertion
	return (tmp && root)? tmp->doc_id : -1;
}

int
bstdb_get_word_count ( int doc_id ) {
	// This is a search function. It should traverse the binary search tree
	// and return the word_count of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return -1
	tree_node *tn = search(root, doc_id);
	b_num_searches++;
	return (tn)? tn->word_count : -1;
}

char*
bstdb_get_name ( int doc_id ) {
	// This is a search function. It should traverse the binary search tree
	// and return the name of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return NULL or 0
	tree_node *tn = search(root, doc_id);
	b_num_searches++;
	return (tn)? tn->name : NULL;
}

int is_bal (tree_node *tn) {
	if (!tn) {return 0;}

	int lh = is_bal(tn->left);
	if (lh == -1) return -1;

	int rh = is_bal(tn->right);
	if (rh == -1) return -1;

	if (abs(lh - rh) > 1) {return -1;}

	return (max(lh, rh) + 1);
}

int check_is_bal(tree_node *tn) {
	if (is_bal(tn) == -1) {return FALSE;}

	return TRUE;
}

int check_bal (tree_node *tn, int *h) {
	int lh = 0, rh = 0;
	int l = 0, r = 0;;
	if (!tn) {return 1;}

	l = check_bal(tn->left, &lh);
	r = check_bal(tn->right, &rh);

	*h = (lh > rh? lh : rh) + 1;

	if ((lh - rh >=2) || (rh - lh >=2)) {
		return 0;}

	return l&&r;
}

int add_to_array(tree_node *tn, int a[], int i) {
	if (!tn) {return i;}
	
	a[i] = tn->doc_id;
	i++;
	if (tn->left) {i = add_to_array(tn->left, a, i);}
	if (tn->right) {i = add_to_array(tn->right, a, i);}

	return i;
}

int check_dup(int c) {
	int *a;
	int i, j, x;
	a = calloc(c, sizeof(int));
	if (!a) { //calloc failed
		puts("Calloc Failed!");
		free(a);
		return TRUE;
	}
	add_to_array(root, a, 0);
	x = 0;
	for (i = 0; i < c; i++) {
		for (j = i+1; j < c; j++) {
			if (a[i] == a[j]) {
				printf("a[i]: %d, i: %d\n", a[i], i);
				printf("a[j]: %d, j: %d\n", a[j], j);
				free(a);
				return TRUE;
			}
		}
	}
	free(a);
	return FALSE; //desired outcome
}

void
bstdb_stat ( void ) {
	// Use this function to show off! It will be called once after the 
	// profiler ends. The profiler checks for execution time and simple errors,
	// but you should use this function to demonstrate your own innovation.
	//
	// Suggestions for things you might want to demonstrate are given below,
	// but in general what you choose to show here is up to you. This function
	// counts for marks so make sure it does something interesting or useful.
	//
	//  + Check if your tree is balanced and print the result
	//
	//  + Does the number of nodes in the tree match the number you expect
	//    based on the number of insertions you performed?
	//
	//  + How many nodes on average did you need to traverse in order to find
	//    a search result? 
	//
	//  + Can you prove that there are no accidental duplicate document IDs
	//    in the tree?
	printf("STAT\n");
	printf("Avg comparisons per search\t-> %lf\n", (double)b_num_comps/b_num_searches);
	int added = count_nodes(root);
	int h = 0;
	printf("Tree nodes matches expected?\t-> %c\n\n", ((b_added_elements == added)? 'Y' : 'N'));
	printf("Tree balanced?\t\t\t-> %c\n", (check_bal(root, &h))? 'Y' : 'N');
	printf("Tree balanced?\t\t\t-> %c\n\n", (check_is_bal(root))? 'Y' : 'N');
	printf("Height of tree?\t\t\t-> %d\n\n", h);
	if (choice == 'B') {
		h = 0;
		check_bal(root->right, &h);
		printf("Height of right subtree?\t-> %d\n", h);
	}
	else {printf("Height of right subtree?\t-> %d\n", get_height(root->right));}
	printf("Nodes in right subtree?\t\t-> %d\n\n", count_nodes(root->right));
	if (choice == 'B') {
		h = 0;
		check_bal(root->left, &h);
		printf("Height of left subtree?\t\t-> %d\n", h);
	}
	else {printf("Height of left subtree?\t\t-> %d\n", get_height(root->left));}
	printf("Nodes in left subtree?\t\t-> %d\n\n", count_nodes(root->left));
	printf("Duplicate IDs?\t\t\t-> %c\n\n", (check_dup(added))? 'Y' : 'N'); //do last, takes most time
}

void
bstdb_quit ( void ) {
	// This function will run once (and only once) when the program ends. Use
	// it to free any memory you allocated in the course of operating the
	// database.
	free_tree_node(root);
}
