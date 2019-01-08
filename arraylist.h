#ifndef ARRAYLIST_H_ 
#define ARRAYLIST_H_ 
#include <stdbool.h> 


typedef struct arraylist
{
	int size; 
	int front; 
	int tail; 
	int *seq; 
}arraylist; 

bool isFull(const arraylist *); 
bool isEmpty(const arraylist*); 
void display(const arraylist*); 
void insertAtFront(arraylist *, int); 
void insertAtBack(arraylist *, int); 
void removeFromBack(arraylist *, int *); 
void removeFromFront(arraylist *, int *); 
int initializeList(arraylist *, int); //initializes the list
void freeList(arraylist *); 
#endif
