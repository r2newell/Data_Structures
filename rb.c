#include "rb.h"
#include <stdlib.h>
#include <stdio.h> 

/*An efficient implementation of a red and black tree that uses bottom up insertion and top down deletion.*/
bool isTreeEmpty(const Tree *rb)
{
    return rb->root? false : true; 
}

int insert(Tree *rb, int key)
{
        if(rb == NULL)
                return -1; //returns negative one if the user passed a null value
        
        node **root = &rb->root; 
        node *parent = NULL; 
        bool duplicate = false; 
        while(*root)
        {
            parent = *root; 
            (*root)->size++;

            if(key < (*root)->key)
                    root = &(*root)->left; 
            else if(key > (*root)->key)
                    root = &(*root)->right; 
            else   { duplicate = true; break; }
        }
        
        if(duplicate == true)
        {
            reverse(*root);//reverses the changes that were made to the tree such as increasing tree size 
            return -2; 
        }
        *root = calloc(1, sizeof(node)); 
        (*root)->key = key; 
        (*root)->parent = parent; 
        (*root)->color = RED; 
        (*root)->size = 0; 
        insert_rebalance(rb, *root); 
        return 0;
}

int removeKey(Tree *rb, int key)
{
        bool found = false; 
        node *parent; 
        node *sibling;
        node *root = rb->root;
        if(search(rb, key) == NULL)
                return -1;

        while(!found && root != NULL)
        {
            root->size--;
            if(key < root->key)
                    root = root->left; 
            else if(key > root->key)
                    root = root->right;
            else    found = true;
            
            if( (root == NULL) || root->color == RED)
                    continue;
        
            parent = root->parent; 
            if(parent != NULL)//a null parent is useless so we continue down the tree when a null parent has occured
            {      if(parent->right == root)
                          sibling = parent->left;
                   else
                          sibling = parent->right;  
            }else continue;

            if(color_compare(root) != 3)
                    continue;

            if(color_compare(sibling) == 3 && sibling->color == BLACK)
                    delete_rebalance(rb, root, 1); 
            else if(color_compare(sibling) != 3 && sibling->color == BLACK) 
                    delete_rebalance(rb, root, 2);
            else 
            {
                    delete_rebalance(rb, root, 3);
                    delete_rebalance(rb, root, 1);
            }
        }
        
        if(found == true)
        {
            if(root->right == NULL)
                transplant(rb, root, root->left);
            else if(root->left == NULL)
                transplant(rb, root, root->right);
            else
            {
                node *key_successor = successor(root); 
                if(key_successor->parent != root) 
                {
                    transplant(rb, key_successor, key_successor->right);
                    key_successor->right = root->right; 
                    key_successor->right->parent = key_successor; 
                } 

                transplant(rb, root, key_successor); 
                key_successor->left = root->left; 
                key_successor->left->parent = key_successor;
                treesize(key_successor);
            }
        
                
                 free(root);
        }
}

node *search(Tree *rb, int key)
{
    node *root = rb->root; 
    while(root != NULL)
        if(key < root->key)
                root = root->left; 
        else if(key > root->key)
                root = root->right; 
        else    break; 

    return root;
}

void insert_rebalance(Tree *rb, node *root)
{
    node *parent = root->parent; 
    node *grandparent; 
    node *sibling; 
    while(parent && parent->color == RED && root->color == RED)
    {
         grandparent = parent->parent; 
         if(grandparent && grandparent->right == parent)
         { 
            sibling = grandparent->left; 
            if(sibling && sibling->color == RED)
            {
                    flipColor(grandparent, RED, BLACK); 
                    root = grandparent; 
                    parent = root->parent; 
            }
            else
            {
                if(parent->right == root)
                {
                    leftRotation(rb, parent); 
                    flipColor(parent, BLACK, RED); 
                    root = parent; 
                    parent = parent->parent; 
                }
                else
                {
                    rightRotation(rb, root); 
                    leftRotation(rb, root); 
                    flipColor(root, BLACK, RED);
                    parent = root->parent; 
                }
            }
         }else
         {
            sibling = grandparent->right; 
            if(sibling && sibling->color == RED)
            {
                    flipColor(grandparent, RED, BLACK); 
                    root = grandparent; 
                    parent = root->parent; 
            }
            else
            {
                if(parent->left == root)
                {
                    rightRotation(rb, parent); 
                    flipColor(parent, BLACK, RED); 
                    root = parent; 
                    parent = parent->parent; 
                }
                else
                {
                    leftRotation(rb, root); 
                    rightRotation(rb, root); 
                    flipColor(root, BLACK, RED);
                    parent = root->parent; 
                }
            }

         }
        
    }

    rb->root->color = BLACK; 
}

void delete_rebalance(Tree *rb, node *root, int option)
{
    node *parent; 
    node *sibling; 
    node *temp; 

    parent = root->parent; 
    if(parent->right == root)
            sibling = parent->left; 
    else    sibling = parent->right;
    
    switch(option)
    {
        /*When root and it's sibling are both black and have black children*/
        case 1:
                parent->color = BLACK;
                root->color = RED; 
                if(sibling != NULL)
                       sibling->color = RED;  
               break; 
       /*When the sibling has at least one red node*/
        case 2:
                if(parent->left == sibling) 
                {    
                        if(sibling->left != NULL && sibling->left->color == RED)
                        {   
                            rightRotation(rb, sibling); 
                            flipColor(sibling, RED, BLACK);
                        }
                        else
                        {
                            temp = sibling->right;                       
                            leftRotation(rb, temp);
                            rightRotation(rb, temp);
                            flipColor(temp, RED, BLACK);
                        }
                }
                else 
                {
                    if(sibling->right != NULL && sibling->right->color == RED)
                        {
                            leftRotation(rb, sibling); 
                            flipColor(sibling, RED, BLACK);
                        }else
                        {
                            temp = sibling->left;                       
                            rightRotation(rb, temp);
                            leftRotation(rb, temp);
                            flipColor(temp, RED, BLACK);
                        }
                } 
                root->color = RED;
                break; 
        /*When sibling is red we rotate around parent around sibling*/
        case 3:
                sibling->color = BLACK; 
                parent->color = RED;
                if(parent->left == sibling)
                        rightRotation(rb, sibling); 
                else    leftRotation(rb, sibling); 
                break;     
    }

}

node *minimum(node *root)
{ 
    while(root && root->left)
            root = root->left; 
    return root; 
}

node *maximum(node *root)
{
    while(root && root->right)
            root = root->right; 
    return root;
}

node *successor(node *root)
{
    if(root == NULL)
            return root; 

    if(root->right != NULL)
            return minimum(root->right); 
    
    node *parent = root->parent; 
    while(parent && parent->right == root)
    {
        root = parent; 
        parent = parent->parent; 
    }

    return parent; 
}

node *predecessor(node *root)
{
    if(root == NULL)
            return root; 

    if(root->left != NULL)
            return maximum(root->left); 
    
    node *parent = root->parent; 
    while(parent && parent->left == root)
    {
        root = parent; 
        parent = parent->parent; 
    }

    return parent; 


}


void leftRotation(Tree *rb, node *root)
{
    node *parent = root->parent; 
    
    parent->right = root->left; 
    if(parent->right != NULL)
           parent->right->parent = parent;
    
    node *grandparent = parent->parent;  //grandparent of root
    if(grandparent != NULL)
    {
            if(grandparent->right == parent)
                   grandparent->right = root;  
            else
                    grandparent->left = root; 
    }else rb->root = root;

    root->left = parent; 
    parent->parent = root; 
    root->parent = grandparent;
    treesize(parent); 
    treesize(root); 
}

void rightRotation(Tree *rb, node *root)
{
 node *parent = root->parent; 
    
    parent->left = root->right; 
    if(parent->left != NULL)
           parent->left->parent = parent;
    
    node *grandparent = parent->parent;  //grandparent of root
    if(grandparent != NULL)
    {
            if(grandparent->right == parent)
                   grandparent->right = root;  
            else
                    grandparent->left = root; 
    }else rb->root = root;

    root->right = parent; 
    parent->parent = root; 
    root->parent = grandparent; 
    treesize(parent); 
    treesize(root); 

}

void flipColor(node *root, int root_color, int child_color)
{
    root->color = root_color; 
    root->left->color = child_color;
    root->right->color = child_color; 
}

void inorder(const node *root)
{
    if(root == NULL)
            return; 
    inorder(root->left); 
    printf(" %d", root->key); 
    inorder(root->right);
}

void preorder(const node *root)
{
    if(root == NULL)
            return; 
    printf(" %d", root->key); 
    preorder(root->left); 
    preorder(root->right); 
}

void postorder(const node *root)
{
    if(root == NULL)
            return;

    postorder(root->left); 
    postorder(root->right);
    printf(" %d", root->key); 
}
void initializeTree(Tree *rb)
{
    rb->root = NULL;
}

void treesize(node *root)
{
    if(root == NULL)
            return;

    root->size = 0;
    if(root->right != NULL && root->left != NULL)
    {
            root->size = root->right->size + root->left->size + 2;
            return; 
    } 
    
    if(root->left != NULL)
            root->size = root->left->size + 1;
    if(root->right != NULL) 
            root->size = root->right->size + 1; 
}

void reverse(node *root)
{
    while(root != NULL)
    {
        root->size--;
        root = root->parent; 
    }
}


void transplant(Tree *rb, node *parent, node *child)
{
    node *grandparent = parent->parent;
    if(grandparent == NULL)
            rb->root = child; 
    else if(grandparent->right == parent)
        grandparent->right = child; 
    else    
        grandparent->left  = child;
       
    treesize(grandparent); 
    if(child != NULL)
    {
            child->color = parent->color; 
            child->parent = grandparent; 
    }
    
}

int color_compare(const node *root)
{
    if(root == NULL)
            return 3;
    
    if(root->left != NULL && root->left->color == RED)
            return 1; 
    else if(root->right != NULL && root->right->color == RED)
            return 2; 
    else    return 3;             
}

void clear_tree(node *root)
{
    if(root == NULL)
            return; 
    clear_tree(root->left); 
    clear_tree(root->right); 
    free(root);
}
