//Created by Romario Newell
//Simple array implementation of a queue

#ifndef QUEUE_H_
#define QUEUE_H_ 
#include <stdbool.h> 

typedef struct queue
{
	int size; //size of queue for array implementation  
	int front; //index of the first element in queue
	int tail; //index of last element inserted
	int *seq; //stores the address of the array
}queue; 

bool isEmpty(const queue*); 
bool isFull(const queue*); 
void enqueue(queue *, int); 
void dequeue(queue *, int *);
int initializeQueue(queue*, int);//initialize queue to a specified size and returns zero if successful
void freeQueue(queue*);// free memory used by queue
#endif
