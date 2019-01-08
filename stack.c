#include "stack.h"
#include "utility.h"
#include <stdio.h>
#include <stdlib.h> 


bool isEmpty(const stack *top)
{
	return top->top == -1? true : false;  
}

bool isFull(const stack *top)
{
	return top->top ==  top->size? true : false; 
}

void push(stack *top, int element)
{
	if(isFull(top))
	{
		printf("\nOverflow error!!!\n");
		return;	
	}
	
	top->seq[++top->top] = element;  
}

void pop(stack *top, int *element)
{
	
	if(isEmpty(top))
	{
		printf("\nUnder flow error!!!\n"); 
		return; 
	}

	top->top--; 
	*element = top->seq[top->top + 1]; 
}

int initializeStack(stack *top, int size) 
{
	top->top = -1;
	top->size = size; 	
	top->seq = (int *)malloc(size * sizeof(int));//allocates the memory that will be used for stack

	return top->seq? 0 : -1; // test to see whether the stack is empty
}

void freeStack(stack *top)
{
	if(top->seq)
		free(top->seq);

	top->seq = NULL; 
	top->size = top->top = -1; 

}

void display(const stack *top)
{
	for(int index = top->top; index >= 0; index--)
		printf(" %d",top->seq[index]); 
	
	printf("\n");
}
