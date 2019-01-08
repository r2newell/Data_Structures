#include "arraylist.h"
#include <stdlib.h> 
#include <stdio.h> 
#include "utility.h"


bool isFull(const arraylist *list)
{
	return list->tail == list->size && list->front == 0?  true :  false; //test to see whether the array list is full
}

bool isEmpty(const arraylist *list)
{
	return list->tail == list->front? true : false; //test to see whether the array list is full 
}

void display(const arraylist *list)
{
	
	   for(int index = list->front; index < list->tail; index++)
		printf(" %d",list->seq[index]); 
		
		printf("\n"); 
}

void insertAtFront(arraylist *list, int element)
{
	if(isFull(list))
	{
		printf("\nOverflow error!!!\n"); 
		return; 
	}

	if(isEmpty(list))
		list->tail++; 

	if(list->front != 0)
		list->seq[--list->front] = element; //insert's element
	else 
		   printf("\nWe can't insert any thing at the front\n");
}

void insertAtBack(arraylist *list, int element)
{
	if(isFull(list))
	{
		printf("\nOverflow error!!!\n"); 
		return; 
	}
	
	list->seq[list->tail++] = element;  //insert's element

	if(list->size == list->tail)
		   list->tail = 0; 
}

void removeFromBack(arraylist *list, int *element)
{
	if(isEmpty(list))
	{
		printf("\nUndeflow error\n");
		return; 
	}
	
	*element = list->seq[--list->tail]; //delete's element
}

void removeFromFront(arraylist *list, int *element)
{
	if(isEmpty(list))
	{
		printf("\nUnderflow error\n"); 
		return; 
	}

	*element = list->seq[list->front++]; //delete's element
}

int initializeList(arraylist *list, int size)
{
	list->front = list->tail = 0 ; 
	list->size = size; 
	list->seq = (int *)malloc(size * sizeof(int)); 

	return list->seq? 0 : -1; //returns -1 if list couldn't be initialized
}

void freeList(arraylist *list)
{
	if(list->seq)
		   free(list->seq); 
	
	list->seq = NULL; 
	list->front = list->tail = 0; 
	list->size = -1; 
}
