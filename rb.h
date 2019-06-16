#ifndef RB_H_
#define RB_H_
#include <stdbool.h> 

enum COLOR{RED, BLACK}; 

typedef struct node
{
    int key; 
    int color; 
    int size; 
    struct node *parent; 
    struct node *left; 
    struct node *right; 
}node;

typedef struct Tree
{
    node *root;  
}Tree; 

bool isTreeEmpty(const Tree *);//returns true is the tree is empty otherwise false
int insert(Tree *, int);//inserts a key
int removeKey(Tree *, int );//removes a node with specified key
node *search(Tree *, int);//searches for a specific key
node *minimum(node *);//returns the minimum key in a tree
node *maximum(node *);//returns the maximum key in a tree
node *successor(node *);//finds the sucessor of a node  
node *predecessor(node *);//finds the predecessor of a node 
node *select_node(const node *, int);//select the kth smallest node in the tree
void insert_rebalance(Tree *, node *);//rebalances the tree after an insertion
void delete_rebalance(Tree *, node *, int);//rebalances the tree after an deletion
void leftRotation(Tree *, node *);//makes a left rotation 
void rightRotation(Tree *, node *);//makes a right rotation 
void flipColor(node *, int, int);//flips the color of a root and its child
void inorder(const node *);//inorder traversal
void postorder(const node *);//post order traversal 
void preorder(const node *);//preorder traversal
void initializeTree(Tree *);//initializes tree
void treesize(node *);//calculate the size of a tree
void clear_tree(node *);//deletes all node in the subtree
void reverse(node *);//reverses all changes made when trying to insert duplicate key
void transplant(Tree *, node *, node *);//transplants a node and by this we mean we connect the child to its grandparent
int  color_compare(const node*);//compares the color of two node and return 1 if the two node are black, 0 if both are red or different 
#endif
