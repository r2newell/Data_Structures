#ifndef REBLACKTREE_H_ 
#define REDBLACKTREE_H_ 
#include <stdbool.h> 
#define RED 0
#define BLACK 1

typedef struct node
{
    int color: 1;//uses 1 bit to store the color
    int key;
    struct node *parent;//points to the parent of the node  
    struct node *left;//points to the left child of the node
    struct node *right;//points to the right child of the node
}node;

typedef struct Tree
{
    int size; 
    node *root;
    node *minimum; //points to the node with smallest key
    node *maximum;//points to the node with the largest key
}Tree; 


bool isEmpty(const Tree *);  //test to see whether the tree is empty
bool isFull(const node *); //test to see whether the tree is full
void initialize(Tree *);//initializes red and black tree for use
void destroy(Tree *, node *);//destroy red and black tree. This function accepts the tree and its root.
bool insert(Tree *, int); //inserts a node and returns true if successfully inserted
void insertionMaintenance(Tree *, node *); //maintain's properties of the red and black tree after insertion
void deletionMaintenance(Tree *, node *);//maintain's properties of the red and black tree after deletion
void updateMinMax(Tree *, const node *); //updates the pointers for minimum and maximum nodes in the tree
node *minimum(const node *);//finds minimum node within a subtree
node *maximum(const node *);//finds maximum node within a subtree
node *sucessor(const node *);//locates the node that would follow the node passed in an inorder display
node *predecessor(const node *);//locates the node that would be before the node passed inorder display
bool deletion(Tree *, int); //removes a node and returns true if successfully removed
node *search(Tree *, int); //searches for a node and returns it if found, else otherwise returns null
void leftRotation(Tree *, node *);//applies a left rotation to a node 
void rightRotation(Tree *, node *);//applies a right rotation to a tree
void inOrder(const node *);//displays tree inorder 
void preOrder(const node *);//displays tree in preoder
void postOrder(const node *);//displays tree postorder
void transplant(Tree *, const node *, node *);//transplants a node
#endif
