#include "redBlack.h"
#include <stdlib.h>
#include <stdio.h>


bool isEmpty(const Tree *redBlack)
{
	return redBlack->root? false : true; 
}

bool isFull(const node *root)
{
	return root? false : true; 
}

void initialize(Tree *redBlack)
{
	redBlack->size = 0; 
	redBlack->root = redBlack->minimum = redBlack->maximum = NULL; 
}

node *search(const Tree *redBlack, int key)
{
	node *root = redBlack->root; 
	while(root)
	{
		if(root->key == key)
			break; 
		else if(key < root->key)
			root = root->left; 
		else 	root = root->right; 
	}

	return root;
}
node *minimum(const node *root)
{
	while(root && root->left)
		   root = root->left; 
	
	return (node *)root;
}

node *maximum(const node *root)
{
	while(root && root->right)
		   root = root->right; 

	return (node *)root; 
}

node *successor(const Tree *redBlack, node *root)
{ 
	if(root == NULL) 
	       return root; 	
	else if(root->right)	
	       return minimum(root->right); 
	
	node *parent = root->parent; 
	while(parent && parent->right == root)
	{
		root = parent; 
		parent = parent->parent; 
	}

	return parent; 
}

node *predecessor(const Tree *redBlack, node *root)
{
	if(root == NULL)
	       return NULL; 	
	else if(root->left)	
	       return minimum(root->left); 
	
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

void transplant(Tree *redBlack, const node *parent, node *child)
{
	node *grandparent = parent->parent; 

	if(grandparent == NULL)
		redBlack->root = child; 
	else if(grandparent->left == parent)
		grandparent->left = child; 
	else grandparent->right = child; 

	if(child)
		child->parent = grandparent; 
}


bool insert(Tree *redBlack, int key)
{
	node *parent = NULL; 
	node *temp = calloc(1, sizeof(node)); 
	if(isFull(temp))
		   return false;

    node **root = &redBlack->root; 
    while(*root)
    {
		parent = *root; 
		if((*root)->key == key)
			   return false; 
		else if(key < (*root)->key)
			   root = &(*root)->left; 
		else root = &(*root)->right; 
    }

    temp->parent = parent; 
    temp->color = RED; 
    temp->key = key; 
    *root = temp; 
    redBlack->size++;
    updateMinMax(redBlack, *root); 
    maintenance(redBlack, *root);
    return true;   
}

void maintenance(Tree *redBlack, node *root)
{
	node *parent;// parent of root
	node *grandparent; //grandparent of root 
	node *parentSibling; //parent's sibling
      
	/*The while test to see if the newly inserted node's parent is red. If red it corrects the situation
       ,else it does nothing since there is no property of the red black tree violated. 
       */ 
	    while(root->parent && root->parent->color == RED) 
	    { 
    		parent = root->parent; //root's parent
	       	grandparent = parent->parent;// grandparent of root

		//checks to see if parent is a left cild of grandparent to do corrective measures
		if(grandparent->left == parent)
		{
			parentSibling = grandparent->right; 
			if(parentSibling && parentSibling->color == RED)
			{
				changeColor(parent, parentSibling, BLACK);   
				grandparent->color = RED; 
				root = grandparent;
			}
			else
			{
				if(parent->left == root)
				{	
				 	rightRotation(redBlack, parent);
					parent->color = BLACK; 
					changeColor(parent->left, parent->right, RED); 
				}
				else 
				{ 
					leftRotation(redBlack, root); 
				    rightRotation(redBlack, root);
					root->color = BLACK; 
					changeColor(root->left, root->right, RED); 			
				} 	
			}
		
		}
		else 
		{
			parentSibling = grandparent->left; 
			if(parentSibling && parentSibling->color == RED)
			{
				changeColor(parent, parentSibling, BLACK);  
			        grandparent->color = RED; 
				root = grandparent; 	
			}
			else
			{ 
				if(parent->right == root)
				{	
					leftRotation(redBlack, parent);
					parent->color = BLACK; 
					changeColor(parent->left, parent->right, RED);
				}
					
				else 
				{
					rightRotation(redBlack, root); 
					leftRotation(redBlack, root); 
					root->color = BLACK; 
					changeColor(root->left, root->right, RED);
				}	
			}
		}
	    } 
	    redBlack->root->color = BLACK; 
}

bool removeNode(Tree *redBlack, int key)
{
	node *root;
        if((root = search(redBlack, key)) == NULL && isEmpty(redBlack))			
		return false;

	node *child;//child of node to be removed
	int color; //color of the node to be removed
	color = root->color; //color of the root to know if we need to run maintenance on the tree
	updateMinMax(redBlack, root); //updates the nodes that point to the minimum and maximum node
	redBlack->size--; 
	if(root->left == NULL)
	{
		child = root->right; 
		transplant(redBlack, root, root->right); 
	}
	else if(root->right == NULL)
	{
		child = root->left; 
		transplant(redBlack, root, root->left); 
	}
	else 
	{
		node *rootSuccessor = successor(redBlack, root);
		child = rootSuccessor->right; 
		color = rootSuccessor->color;
		if(rootSuccessor->parent != root)
		{
	      	transplant(redBlack, rootSuccessor, rootSuccessor->right); 	
			rootSuccessor->right = root->right; 
			root->right->parent = rootSuccessor; 
		}

		rootSuccessor->left = root->left; 
		root->left->parent = rootSuccessor;
		transplant(redBlack, root, rootSuccessor); 		
	}
	
	free(root); 

    if(color == BLACK)
       deleteMaintenance(redBlack, child);  
	return true; 	
}	

void deleteMaintenance(Tree *redBlack, node *root)
{
    node *parent; //parent of root 
    node *sibling; //sibling of root
    while(redBlack->root != root && root->color == BLACK)
    {
        parent  = root->parent; 
        if(parent->left == root)
        {
            sibling = parent->right;
            if(sibling)
            { 
                if(sibling && sibling->color == RED) //case 1
                {
                    parent->color = RED; 
                    sibling->color = BLACK; 
                    leftRotation(redBlack, sibling); 
                    sibling = parent->right;
                }
                 //case 2
                if(sibling->right && sibling->left && sibling->right->color == BLACK && sibling->left->color == BLACK)
                {
                    sibling->color = RED; 
                    root = parent;       
                }
                else 
                {
                    if(sibling->right && sibling->right->color == BLACK)
                    {
                        sibling->color = RED; 
                        if(sibling->left)
                        {
                            sibling->left->color = BLACK; 
                            rightRotation(redBlack, sibling->left); 
                            sibling = parent->right; 
                        }
                        sibling->color = parent->color; 
                        parent->color = BLACK; 
                        sibling->right->color = BLACK; 
                        leftRotation(redBlack, parent->left); 
                        root = redBlack->root; 
                    }
                }
            }
        }
        else
        {
            sibling = parent->left;
            if(sibling)
            { 
                if(sibling && sibling->color == RED) //case 1
                {
                    parent->color = RED; 
                    sibling->color = BLACK; 
                    leftRotation(redBlack, sibling); 
                    sibling = parent->left;
                }
                 //case 2
                if(sibling->right && sibling->left && sibling->right->color == BLACK && sibling->left->color == BLACK)
                {
                    sibling->color = RED; 
                    root = parent;       
                }
                else 
                {
                    if(sibling->left && sibling->left->color == BLACK)
                    {
                        sibling->color = RED; 
                        if(sibling->right)
                        {
                            sibling->right->color = BLACK; 
                            rightRotation(redBlack, sibling->right); 
                            sibling = parent->left; 
                        }
                        sibling->color = parent->color; 
                        parent->color = BLACK; 
                        sibling->right->color = BLACK; 
                        leftRotation(redBlack, parent->right); 
                        root = redBlack->root; 
                    }
                }
            }
        }
    }
    
    if(root)
        root->color = BLACK; 
}

void leftRotation(Tree *redBlack, node*root)
{
	node *grandparent = root->parent; 
	transplant(redBlack, root, root->left);  
    root->left = grandparent; 	
	transplant(redBlack, grandparent, root);
    grandparent->parent = root; 	
}

void rightRotation(Tree *redBlack, node *root)
{
	node *grandparent = root->parent; 
	transplant(redBlack, root, root->right);  
	root->right = grandparent; 
	transplant(redBlack, grandparent, root); 
	grandparent->parent = root; 
}

void inOrder(const node *root)
{
	if(root == NULL)
		return; 
	
	inOrder(root->left); 
	printf(" %d",root->key); 
	inOrder(root->right); 
}

void postOrder(const node*root)
{
	if(root == NULL)
		return; 

	postOrder(root->left); 
	postOrder(root->right); 
	printf(" %d",root->key);
}

void preOrder(const node *root)
{
	if(root == NULL); 
		return; 

	printf(" %d",root->key); 
	preOrder(root->left); 
	preOrder(root->right);
}

void changeColor(node *left, node *right, int color)
{
	if(left == NULL && right == NULL)
		return; 

	if(color == BLACK) 
		left->color = right->color = BLACK; // changes left and right child color
	else left->color = right->color = RED; 
}
