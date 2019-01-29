#ifndef AVLTREE_H_
#define AVLTREE_H_ 
#include <stdbool.h>

typedef struct node
{
	int key;
	int height; 
	struct node *parent;
	struct node *left; 
	struct node *right; 
}node; 

typedef struct Tree
{
	int height; 
	int size;
	node *root; 
	node *maximum; 
	node *minimum; 
}Tree; 

void initializeAvl(Tree *avl);
bool isEmpty(const Tree *avl);
bool isFull(const node *root);
bool insert(Tree *avl, int key);
bool removeNode(Tree *avl, int key);
node *search(const Tree *avl, int key);
void updateMinMax(Tree *avl, const node *root); 
int	max(const node *left, const node *right); 
int	balanceFactor(const node *root);
int	height(const node *root); 
int  depth(const node *root, int key);
node *minimum(const node *root);
node *maximum(const node *root);
node *succesor(const node *root);
node *predecessor(const node *root);
void transplant(Tree *avl, const node *parent, node *child);
bool isExternal(const node *root);
bool isInternal(const node *root);
bool isRoot(const Tree *avl, const node *root); 
void leftRotation(Tree *avl, node *grandparent, node *parent); 
void rightRotation(Tree *avl, node *grandparent, node *parent);
void rebalance(Tree *avl, node *root);
void inOrder(const node *root); 
void preOrder(const node *root); 
void postOrder(const node *root);
#endif
