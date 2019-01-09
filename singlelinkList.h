#ifndef SINGLE_LINKED_LIST_H_
#define SINGLE_LINKED_LIST_H_ 
#include <stdbool.h> 

typedef struct node
{
	   int data; 
	   struct node *next; 
}node; 

typedef struct list
{
	node *head; 
	node *tail; 
}list; 

bool isEmpty(const list *); //test to see whether the linked list is empty. Returns true upon empty  
bool isFull(void); //test see whether we can insert a next node. Returns true upon full
bool insertAtFront(list *, int); 
bool insertAtBack(list *, int); 
bool insertBefore(list *, const node *, int);// insert a node before node p
node *first(const list *); //returns the first node within the linked list
node *last(const list *); //returns the last node within the linked list
bool insertAfter(list *, node*, int); //insert a node after a node p
node *search(const list *, int); //search for a node
node **predecessor(const list*, const node *); //finds the predecessor of a node
bool remove(list *, node *); //removes a node. Returns true upon successful removal
void initializeList(list *); // initialize list. Call after creation of list 
void display(const list *); 
void destroy(list *); 
#endif
