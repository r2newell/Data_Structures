#include "listQueue.h"
#include <stdlib.h> 
#include <stdio.h> 
#include "utility.h"

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

bool isEmpty(const queue *items)
{
	return items->front? false : true; 
}

bool enqueue(queue *items, int element)
{
	   if(isFull())
			 return false;
	   
	   node *temp = (node *)calloc(1, sizeof(node));
	   temp->data = element; 

	   if(isEmpty(items))
	   {
		items->front = items->rear = temp; 
		return true; 
	   }

	   items->rear = items->rear->next = temp; //adds and updates the rear of the list at the same time
}

bool dequeue(queue *items, int *element)
{
	if(isEmpty(items))
		   return false; 
	
	*element = items->front->data; 

	if(items->front == items->rear)
	{
		free(items->front); 
		items->front = items->rear = NULL;
		return true; 
	}
	
	node *temp = items->front; 
	items->front = items->front->next; 

	return true; 
}

bool initializeQueue(queue *items)
{
	if(!items)
		   return false; 

	items->front = items->rear = NULL; 
	return true; 
}

void display(const queue *items)
{
	node *tempFront = items->front; 	
	while(tempFront)
	{
		printf(" %d",tempFront->data); 
		tempFront = tempFront->next;
	}

	printf("\n");
}

void destroy(queue *items)
{
	while(items->front)
	{
		items->rear = items->front; 
		items->front = items->front->next; 
		free(items->rear); 	
	}

	items->front = items->rear = NULL; 
}
