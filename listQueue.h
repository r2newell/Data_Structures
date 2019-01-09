#ifndef LISTQUEUE_H_ 
#define LISTQUEUE_H_
#include <stdbool.h> 
typedef struct node 
{
	int data; 
	struct node *next; 
}node; 

typedef struct queue
{
	node *front; 
	node *rear; 
}queue; 

bool isFull(void); 
bool isEmpty(const queue *); 
bool enqueue(queue *, int); //returns true upon successful insertion 
bool dequeue(queue *, int *);//returns true upon successful deletion
bool initializeQueue(queue *);//returns true upon succesful initialization 
void destroy(queue *); 
#endif
