//Created by Romario Newell 
//Simple Implementation of a circular queue 
//Note when declaring the size of the queue it should be N + 1 if you had a size of N in mind.

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
	return (list->size - list->front + list->tail) % list->size == list->size -1? true : false; 
}

void enqueue(queue *list, int element)
{
	if(isFull(list))
	{
		printf("\nOverflow error!");
		return;
	}

	list->seq[list->tail] = element; 
	list->tail = (list->tail + 1) % list->size;	
}

void dequeue(queue *list, int *element)
{
	if(isEmpty(list))
	{
		printf("\nUnderflow error!!!"); 
		return; 
	}

	*element = list->seq[list->front];
	list->front = (list->front + 1) % list->size; 
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
