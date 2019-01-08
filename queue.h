#ifndef QUEUE_H_
#define QUEUE_H_ 
#include <stdbool.h> 

typedef struct queue
{
	int size; 
	int front; 
	int tail; 
	int *seq; 
}queue; 

bool isEmpty(const queue*); 
bool isFull(const queue*); 
void enqueue(queue *, int); 
void dequeue(queue *, int *);
int	initializeQueue(queue*, int);//initialize queue to a specified size and returns zero if successful
void freeQueue(queue*);// free memory used by queue
void display(const queue*); 
#endif
