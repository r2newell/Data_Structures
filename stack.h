#ifndef STACK_H_
#define STACK_H_ 
#include <stdbool.h> 

typedef struct stack 
{
	int top; 
	int size; 
	int *seq; 
}stack; 

bool isEmpty(const stack *); 
bool isFull(const stack *); 
void push(stack *, int); 
void pop(stack*, int *);
void display(const stack*);
int initializeStack(stack *, int);//initializes size of stack to specific size and returns zero if successful
void freeStack(stack *);//free memory used by stack
#endif
