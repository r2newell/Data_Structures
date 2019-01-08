#include "queue.h"
#include "utility.h"
#include <stdlib.h>
#include <stdio.h>

bool isEmpty(const queue*list)
{
	return list->front == list->tail? true : false; 
}

bool isFull(const queue *list)
{
	return list->front == 0 && list->tail == list->size? true : false; 
}

void enqueue(queue *list, int element)
{
	if(isFull(list))
	{
		printf("\nOverflow error!!!\n"); 
		return; 
	}

	   list->seq[list->tail++] = element; 
	
	   if(list->tail == list->size)
			 list->tail == 0; 
}

void dequeue(queue *list, int *element)
{
	if(isEmpty(list))
	{ 
		   printf("\nUndeflow error!!!\n");
		   return; 
	}

	*element = list->seq[list->front++]; 

	if(list->front == list->size)
		   list->front = 0; 
}

void freeQueue(queue *list)
{
	if(list->seq)
		   free(list->seq);
		   
	list->front = list->tail = 0;  
}

void display(const queue *list)
{
	for(int start = list->front, end = list->tail;start < end; start++)
		   printf(" %d",list->seq[start]);
	printf("\n");
}

int initializeQueue(queue*list, int size)
{
	   list->size = size; 
	   list->seq = (int *)malloc(size * sizeof(int)); //allocating memory for queue
	   list->front = list->tail = 0; 
		
	   return list->seq? 0 : -1; 
}
