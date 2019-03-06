#include "redBlackTree.h"
#include <stdlib.h> 
#include <stdio.h> 



void initialize(Tree *rbTree)
{
    rbTree->size = 0; 
    rbTree->root = rbTree->minimum = rbTree->maximum = NULL; 
} 

bool isEmpty(const Tree *rbTree)
{
    return rbTree->root? false : true; 
}

bool isFull(const node *root)
{
    return root? false : true;  
}

node *search(Tree *rbTree, int key)
{
    node *root = rbTree->root;  
    while(root)
    {
        if(root->key == key)
            break; 
        else if(key < root->key)
            root = root->left; 
        else root = root->right; 
    }
    
 return root; 
}

node *minimum(const node *root)
{
    while(root && root->left)//test to see whether root is null and root left child is null
    root = root->left;//keeps on traversing left to find the smallest node

    return (node *) root; 
}

node *maximum(const node *root)
{
    while(root && root->right)//test to see whether root is null and root right child is null
        root = root->right;//keeps on traversing right to find the largest node
    
    return (node *) root; 
}

node *sucessor(const node *root)
{
    if(root->right)
        return minimum(root->right); 

    node *parent = root->parent; 
    while(parent && parent->right == root)
    {
        root = parent;
        parent = parent->parent; 
    }

    return parent;
}

node *predecessor(const node *root)
{
    if(root->left)
        return maximum(root->left); 

    node *parent = root->parent; 
    while(parent && parent->left == root)
    {
        root = parent; 
        parent = parent->parent;
    }

    return parent;
}

void updateMinMax(Tree *rbTree, const node *root)
{
    if(rbTree->minimum == NULL && rbTree->maximum == NULL)
        rbTree->minimum = rbTree->maximum = (node *)root; 
    else if(root->key < rbTree->minimum->key)
       rbTree->minimum = (node *)root; 
    else if(root->key > rbTree->maximum->key)
        rbTree->maximum = (node *)root;
    else if(rbTree->minimum == rbTree->maximum)
        rbTree->minimum =rbTree->maximum = NULL;
    else if(root == rbTree->minimum)
    {
        if(rbTree->minimum->right == NULL)
            rbTree->minimum = rbTree->minimum->parent; 
        else 
            rbTree->minimum = rbTree->minimum->right; 
    }
    else 
    {
        if(rbTree->maximum->left == NULL)
            rbTree->maximum = rbTree->maximum->parent; 
        else 
            rbTree->maximum = rbTree->maximum->left; 
    }
}

bool insert(Tree *rbTree, int key)
{
    node *temp = calloc(1,sizeof(node));
    if(isFull(temp))
        return false;

    node *parent = NULL; 
    node **root = &rbTree->root; 
    while(*root)
    {
        parent = *root; 
        if((*root)->key == key)
            return false; 
        else if(key < (*root)->key)
            root = &(*root)->left; 
        else root = &(*root)->right; 
    }

    rbTree->size++; 
    temp->key = key; 
    temp->parent = parent;
    temp->color = RED; 
    *root = temp;  
    insertionMaintenance(rbTree, *root); 
    return true; 
}

bool deletion(Tree *rbTree, int key)
{
    node *found;//node to be deleted from the tree
    if((found = search(rbTree, key)) == NULL || isEmpty(rbTree))
        return false; 
    rbTree->size--;
    node *child; //child of node deleted
    int color = found->color;  
    updateMinMax(rbTree, found); 

    if(found->left == NULL)
    {
        child = found->right; 
        transplant(rbTree, found, found->right); 
    }
    else if(found->right == NULL)
    {   
        child = found->left; 
        transplant(rbTree, found, found->left); 
    }
    else
    {
       
        node *foundSuccessor = sucessor(found);
        transplant(rbTree, foundSuccessor, foundSuccessor->right); 
        color = foundSuccessor->color;
        child = foundSuccessor->right;  
        if(foundSuccessor->parent != found)
        {
            foundSuccessor->right = found->right; 
            if(foundSuccessor->right != NULL)
                foundSuccessor->right->parent = foundSuccessor; 
        }
        foundSuccessor->left = found->left; 
        foundSuccessor->left->parent = foundSuccessor; 
        transplant(rbTree, found, foundSuccessor); 
    }
    if(color == BLACK)
        deletionMaintenance(rbTree, child);
    free(found);
    return true; 
}

void deletionMaintenance(Tree *rbTree, node *root)
{
    node *parent; 
    node *sibling; 
    while(root && rbTree->root != root && root->color == BLACK)
    {
        parent = root->parent; 
        if(parent && parent->left == root)
        {
            sibling = parent->right; 
            if(sibling && sibling->color == RED)
            {
                parent->color = RED; 
                sibling->color = BLACK;
                leftRotation(rbTree, sibling); 
                sibling = parent->right;  
            }

            if(sibling && sibling->color == BLACK && sibling->right && sibling->left && sibling->left->color == BLACK && sibling->right->color == BLACK)
            { 
                sibling->color = RED;
                root = parent; 
            }
            else if(sibling && sibling->right && sibling->right->color == BLACK)
            {
            
                sibling->color =  RED;   
                if(sibling->left)
                {   
                    sibling->left->color = BLACK; 
                    rightRotation(rbTree, sibling->left);
                    sibling = parent->right; 
                }

                sibling->color = parent->color; 
                parent->color = BLACK; 
                sibling->right->color = BLACK; 
                leftRotation(rbTree, parent->left); 
                root = rbTree->root; 
            }
        }
        else
        {
            sibling = parent->left; 
            if(sibling && sibling->color == RED)
            {
                parent->color = RED; 
                sibling->color = BLACK;
                leftRotation(rbTree, sibling); 
                sibling = parent->left;  
            }

            if(sibling && sibling->color == BLACK && sibling->right && sibling->left && sibling->left->color == BLACK && sibling->right->color == BLACK)
            {
                sibling->color = RED;
                root = parent; 
            }
            else if(sibling && sibling->left && sibling->left->color == BLACK)
            {
            
                sibling->color =  RED;   
                if(sibling->right)
                {   
                    sibling->right->color = BLACK; 
                    rightRotation(rbTree, sibling->right);
                    sibling = parent->left; 
                }

                sibling->color = parent->color; 
                parent->color = BLACK; 
                sibling->left->color = BLACK; 
                leftRotation(rbTree, parent->left); 
                root = rbTree->root; 
            }
 
        }
    }
    if(root)
        root->color = BLACK;
}

void insertionMaintenance(Tree *rbTree, node *root)
{
    node *parent; //parent of root
    node *grandparent; //grandparent of root
    node *parentSibling; //sibling of parent
    
    while(root->parent && root->parent->color == RED)
    {
        parent = root->parent; 
        grandparent = parent->parent; 
        if(grandparent && grandparent->left == parent)
        {
            parentSibling = grandparent->right; 
            if(parentSibling && parentSibling->color == RED) //performs case 1
            {
                parent->color = parentSibling->color = BLACK; 
                grandparent->color = RED; 
                root = grandparent; 
            }
            else if(parent->left == root) //performs case 2
            {
                rightRotation(rbTree, parent); 
                parent->color = BLACK; 
                parent->left->color = parent->right->color = RED;  
            }
            else //performs case 3
            {
                leftRotation(rbTree, root);
                rightRotation(rbTree, root); 
                root->color = BLACK; 
                root->left->color = root->right->color = RED;  
            }
        }
        else if(grandparent) //test to see if grandparent is null. 
        {
            parentSibling = grandparent->left; 
            if(parentSibling && parentSibling->color == RED) //performs case 1
            {
                parent->color = parentSibling->color = BLACK; 
                grandparent->color = RED; 
                root = grandparent; 
            }
            else if(parent->right == root) //performs case 2
            {

                leftRotation(rbTree, parent);  
                parent->color = BLACK; 
                parent->left->color = parent->right->color = RED;
            }
            else //performs case 3
            {
                rightRotation(rbTree, root);
                leftRotation(rbTree, root); 
                root->color = BLACK; 
                root->left->color = root->right->color = RED;  
            }
        }
    }
    rbTree->root->color = BLACK; 
}

void transplant(Tree *rbTree, const node *parent, node *child)
{
    node *grandparent = parent->parent; 
    if(grandparent) 
    { 
        if(grandparent->left == parent)
            grandparent->left = child; 
        else 
            grandparent->right = child;
    }
    else rbTree->root = child; 

    if(child)
        child->parent = grandparent; 
}
void leftRotation(Tree *rbTree, node *parent)
{
    node *grandparent = parent ->parent; //parent of parent a.k.a grandparent of the newly inserted node
    grandparent->right = parent->left; //moves parent right subtree to grandparent right subtree
    parent->parent = grandparent->parent; //points parent's parent to grandparent's parent
    if(parent->left) //points parent right subtree to grandparent
        parent->left->parent = grandparent; 
    if(grandparent->parent)
    {
        if(grandparent->parent->right == grandparent) //connects grandparent's parent to parent subtree
            grandparent->parent->right = parent; 
        else 
            grandparent->parent->left = parent; 
    }
    else rbTree->root = parent; 
    parent->left = grandparent; 
    grandparent->parent = parent;  
}

void rightRotation(Tree *rbTree, node *parent)
{
    node *grandparent = parent ->parent; //parent of parent a.k.a grandparent of the newly inserted node
    grandparent->left = parent->right; //moves parent right subtree to grandparent right subtree
    parent->parent = grandparent->parent; //points parent's parent to grandparent's parent
    if(parent->right) //points parent right subtree to grandparent
        parent->right->parent = grandparent; 
    if(grandparent->parent)
    {
        if(grandparent->parent->right == grandparent) //connects grandparent's parent to parent subtree
            grandparent->parent->right = parent; 
        else 
            grandparent->parent->left = parent; 
    }
    else rbTree->root = parent; 
    parent->right = grandparent; 
    grandparent->parent = parent; 
}


void inOrder(const node *root)
{
    if(root == NULL)
        return; 

    inOrder(root->left); 
    printf(" %d", root->key); 
    inOrder(root->right);
}

void preOrder(const node *root)
{
    if(root == NULL)
        return; 

    printf(" %d", root->key); 
    preOrder(root->left); 
    preOrder(root->right); 
}

void postOrder(const node *root)
{
    if(root == NULL)
        return; 

    postOrder(root->left); 
    postOrder(root->right); 
    printf(" %d",root->key);
}

void destroy(Tree *rbTree, node *root)
{
    if(root == NULL)
        return; 
    destroy(rbTree, root->left);
    destroy(rbTree, root->right);//maintain's properties of the red and black tree after deletion 
    free(root);  
}
