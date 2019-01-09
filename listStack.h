#ifndef LISTSTACK_H_ 
#define LISTSTACK_H_
#include <stdbool.h>

//A linked list representation of a stack is used here. 

typedef struct node
{
	int data; 
	struct node *next; 
}node; 

typedef struct stack
{
	node *top; 
}stack; 

bool isEmpty(const stack *);  
bool isFull(void);
bool push(stack *, int); 
bool pop(stack *, int *); 
bool initializeStack(stack *);//call right before using the stack for the first time. Returns true upon proper initialization 
void destroy(stack *); 
void display(const stack *); //only for debugging purposes. It is illegal to traverse a stack

#endif
