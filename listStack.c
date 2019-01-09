#include "listStack.h"
#include <stdlib.h> 
#include <stdio.h>
#include "utility.h"

bool isEmpty(const stack *items)
{
	return items->top? false : true;   
}

bool isFull(void)
{
	node *temp = (node *)malloc(sizeof(node)); 
	
	if(temp)
	{
		free(temp); 
		return false; 
	}
return true; 
}

bool push(stack *items, int element)
{
	if(isFull())
		return false; 

	node *temp = (node *)malloc(sizeof(node)); 
	temp->data = element; 
	temp->next = items->top; 
	items->top = temp; 

	return true; 
}

bool pop(stack *items, int *element)
{
	if(isEmpty(items))
		   return false; 

	*element = items->top->data; 
	node *tempTop = items->top; 
	items->top = items->top->next; 
	free(tempTop); 

	return true; 	
}

void destroy(stack *items)
{
	int element; 
	while(pop(items, &element)); 
}

bool initializeStack(stack *items)
{
	items->top = NULL; 
	return true;
}

void display(const stack *items)
{
	node *tempTop = items->top; 
	while(tempTop)
	{
		printf(" %d",tempTop->data); 
		tempTop = tempTop->next;
	}
	printf("\n");
}
