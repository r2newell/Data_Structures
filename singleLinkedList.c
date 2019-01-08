#include "singlelinkList.h"
#include <stdlib.h> 
#include <stdio.h> 
#include "utility.h"



bool isEmpty(const list *items)
{
	return items->head == items->tail? true : false;
}

bool isFull(void)
{
	node *temp = (node *)calloc(1, sizeof(node)); 

	if(temp)
	{
		free(temp); 
		return false; 
	}

	return true; 
}


bool insertAtFront(list *items, int element)
{
	if(isFull()) 
		   return false; 
		
	node *temp = (node *)calloc(1, sizeof(node)); 
	temp->data = element; 
	temp->next = items->head; 
	items->head = temp;

	if(items->tail == NULL)
		   items->tail = items->head; 
	return true; 
}

bool insertAtBack(list *items, int element)
{
	if(isFull())
		   return false; 

	node *temp = (node *)calloc(1, sizeof(node)); 
	temp->data = element;

	if(isEmpty(items))	
	{
		   items->head = items->tail = temp; 
		   return true; 
	}

	items->tail->next = temp; 
	items->tail = temp; 

	return true; 
}

bool insertBefore(list * items, const node *position, int element)
{ 	   
		if(isEmpty(items) || position == items->head)
			   return insertAtFront(items, element);//test whether it is really an insertAtfront  


		if(isFull() || position == NULL)
			   return false; 

		node **tempHead = &items->head; 

		while((*tempHead)->next != position)
			tempHead = &(*tempHead)->next;
		

		node *temp = (node *)calloc(1, sizeof(node));
		temp->data = element; 
		(*tempHead)->next = temp; 
		temp->next = (node *)position; //type casting 
		    
	    	return true; 	
		   
}

bool insertAfter(list *items, node *position, int element)
{
	if(isEmpty(items))
		return insertAtFront(items, element); 
		
	if(isFull() || position == NULL)
		return false; 

	if(items->tail == position) 
		return insertAtBack(items, element); //test whether it is just an insert at the back

		node *temp = (node *)calloc(1, sizeof(node));
		temp->data = element; 
		temp->next = position->next; 
		position->next = temp; 

	return true; 	
}

node *first(const list *items)
{
	return items->head; 
}

node *last(const list *items)
{
	return items->tail; 
}

node *search(const list *items, int key)
{
	node *tempHead = items->head; 

	while(tempHead)
		if(tempHead->data == key)
			   break; 
		else 
			   tempHead = tempHead->next;
	return tempHead; 
}

bool remove(list *items, node *key)
{
	if(isEmpty(items))
	   return false; 
	
	if(items->head == items->tail && key == items->head) //test to see if only one element exist
	{
		free(key); 
		items->head = items->tail = NULL; 
	}
	else	if(key == items->head) //test to see if the first element is being removed
	{
		items->head = items->head->next;
		free(key); 
	}
	else
	{
		node **prev = predecessor(items, key); 
		
		if((*prev)->next == items->tail) //update the tail to the previous node if the tail is being removed
			items->tail = *prev; 

		(*prev)->next = key->next; 
		free(key); 
	}
return true; 
}

node **predecessor(const list *items, const node *key)
{
	
	node **tempHead = (node **) &items->head; //type cast done here 

	while(*tempHead && (*tempHead)->next!= key)
		   tempHead = &(*tempHead)->next;

	return tempHead; 
}

void display(const list *items)
{
	node *tempHead = items->head; 
	while(tempHead)
	{
		printf(" %d",tempHead->data);
		tempHead = tempHead->next; 	
	}

	printf("\n");
}

void destroy(list *items)
{ 
	while(items->head)
	{
		items->tail = items->head; 
		items->head = items->head->next; 
		free(items->tail);		
	}
	items->tail = items->head;
}

void initializeList(list *items)
{
	items->head = items->tail = NULL;
}
