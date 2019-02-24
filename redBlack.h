#ifndef REDBLACK_H_
#define REDBLACK_H_ 
#include <stdbool.h> 
#define RED 0
#define BLACK 1

typedef struct node
{
	int key; 
	int color: 1; 
	struct node *parent; 
	struct node *left; 
	struct node *right; 
}node; 

typedef struct Tree
{
	int size; 
	node *root; 
	node *maximum; 
	node *minimum; 
}Tree; 

bool isEmpty(const Tree *); 
bool isFull(const node *); 
void initialize(Tree *); 
node *minimum(const node *); 
node *maximum(const node *); 
node *successor(const Tree *, node *); 
node *predecessor(const Tree*, node *); 
void updateMinMax(Tree*, const node *);
void transplant(Tree *, const node *, node *); 
bool insert(Tree *, int); //inserts a node. Takes redblack tree and key to insert 
bool removeNode(Tree *, int); //removes a node. Takes redblack tree and key to remove
node *search(const Tree *, int);
void maintenance(Tree *, node *); //maintains the properties after insertion. NB Don't call this function. 
void deleteMaintenance(Tree *, node *);//maintains the properties after deletion. NB Don't call this function
void inOrder(const node *); 
void postOrder(const node *); 
void preOrder(const node *); 
void leftRotation(Tree *, node*); 
void rightRotation(Tree *, node *);
void changeColor(node *, node *, int); 
#endif
