#include "avlTree.h"
#include <stdlib.h>
#include <stdio.h>
#include "utility.h"


void initializeAvl(Tree *avl)
{
	avl->height = -1;
	avl->root = avl->minimum = avl->maximum = NULL; 
	avl->size = 0;
}

bool isEmpty(const Tree *avl)
{
	return avl->root? false : true; 
}

bool isFull(const node *root)
{
	return root? false : true; 
}

bool insert(Tree *avl, int key)
{
	node *temp = (node *)calloc(1, sizeof(node)); 
	if(isFull(temp))
		   return false; 

	node **root = &avl->root;
	node *parent = NULL;  

	while(*root)
	{
		parent = *root;
		if((*root)->key == key)
			return false; 
		else if(key < (*root)->key)
			   root = &(*root)->left; 
		else 
		    root = &(*root)->right; 	   
	}
	
	temp->key = key;
	temp->parent = parent;
	*root = temp; 	
	avl->size++; 
	updateMinMax(avl, *root); 
	rebalance(avl, *root);	
	return true;
}

bool removeNode(Tree *avl, int key)
{
	   node *position; 
	   if(isEmpty(avl) || (position = search(avl, key)) == NULL)
			 return false; 

	   updateMinMax(avl, position);  
	   node *positionSuccessor;
	   avl->size--; 

	   if(position->left == NULL)
			 transplant(avl, position, position->right);

	   else if(position->right == NULL)	 
			 transplant(avl, position, position->left);
	   else
	   {
			positionSuccessor = succesor(position); 
			position->key = positionSuccessor->key; 
			transplant(avl, positionSuccessor, positionSuccessor->right); 
		     position = positionSuccessor; 	
	   }
	   node *parent = position->parent; 
	   free(position); 
	   rebalance(avl, parent);
}

node *search(const Tree *avl, int key)
{
	node *root = avl->root; 
	
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


void updateMinMax(Tree *avl, const node *root)
{
	   if(avl->minimum == NULL &&  avl->maximum == NULL)
			 avl->maximum = avl->minimum = (node *)root;
	   else if(root->key < avl->minimum->key)
			 avl->minimum = (node *)root; 
	   else if(root->key > avl->maximum->key)
			 avl->maximum = (node *)root;
	   else if(avl->minimum == root)
			 avl->minimum = avl->minimum->right? avl->minimum->right : avl->minimum->parent; 
	   else if(avl->maximum == root)
			 avl->maximum = avl->maximum->left? avl->maximum->left : avl->maximum->parent; 
}


int max(const node *left, const node *right)
{
	if(left == right)
		   return -1; 
	else if(left == NULL)
		   return right->height; 
	else if(right == NULL)
		   return left->height;

	return left->height > right->height? left->height : right->height;
}

int balanceFactor(const node *root)
{	
	if(root->left == root->right)
		return 0; 
	else if(root->right == NULL)
		return root->left->height + 1;
	else if(root->left == NULL)
		return -(root->right->height + 1); 

		return (root->left->height + 1) - (root->right->height + 1);	
}

int height(const node *root)
{
	if(root == NULL)
		   return -1; 

	int left = height(root->left) + 1;
     int right = height(root->right) + 1; 	
	
	return left > right? left : right;  
}

int depth(const node *root, int key)
{	
	int ancestors = -1; 
	while(root)
	{
		ancestors++; 
		if(root->key == key)
			   break; 
		else if(key < root->key)
			   root = root->left; 
		else 
			   root = root->right; 
	}

	return root? ancestors : -1; 
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

node *succesor(const node *root)
{
	if(root == NULL)
		   return (node *)root; 

	if(root->right)
		   return minimum(root->right); 

	node *parent  = root->parent; 

	while(parent && parent->right == root)
	{
		root = parent; 
		parent = parent->parent; 
	
	}

	return parent; 
}

node *predecessor(const node *root)
{
	if(root == NULL)
		   return (node *)root; 

	node *parent = root->parent; 
	while(parent && parent->left == root)
	{
		root = parent; 
		parent = parent->parent; 
	}
return (node *)parent; 
}

void transplant(Tree *avl, const node *parent, node *child)
{
	node *grandparent = parent->parent; 

	if(grandparent == NULL)
		avl->root = child;
	else if(grandparent->right == parent)
		grandparent->right = child; 
	else	grandparent->left = child; 	   
	
	if(child)
	   child->parent = grandparent;	   
	
	if(grandparent)
		grandparent->height = max(grandparent->left, grandparent->right) + 1;
	else avl->height = child? child->height: -1;	   
}

bool isExternal(const node *root)
{
	return root->left == root->right? true : false; 
}

bool isInternal(const node *root)
{
	return root->left && root->right? true : false; 
}

bool isRoot(const Tree *avl, const node *root)
{
	return avl->root == root? true : false;
}

void leftRotation(Tree *avl, node *grandparent, node *parent)
{
	   transplant(avl, parent, parent->left);
	   parent->left = grandparent; 
	   transplant(avl, grandparent, parent); 
	   grandparent->parent = parent;   
	   parent->height = max(parent->left, parent->right) + 1; 
}

void rightRotation(Tree *avl, node *grandparent, node *parent)
{
	transplant(avl, parent, parent->right); 	
	parent->right = grandparent; 
	transplant(avl, grandparent, parent); 
	grandparent->parent = parent;
	parent->height = max(parent->left, parent->right) + 1; 
}

void rebalance(Tree *avl, node *root)
{
	int key = root->key; 

	while(root)
	{
		root->height = max(root->left, root->right) + 1; 
		if(balanceFactor(root) <= -2)
		{
			if(balanceFactor(root->right) >= 1)
				   rightRotation(avl, root->right, root->right->left); 
			leftRotation(avl, root, root->right); 	
		}
		else if(balanceFactor(root) >= 2)
		{
			if(balanceFactor(root->left) <= -1)
				   leftRotation(avl, root->left, root->left->right);
			rightRotation(avl, root, root->left); 
		}
		root = root->parent;
	}

	avl->height  = avl->root->height;
}

void inOrder(const node *root)
{
	if(root ==  NULL) 
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
	printf(" %d", root->key); 
}
