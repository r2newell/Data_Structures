#include "heap.h"
#include <stdio.h> 
#include <stdlib.h> 



bool isFull(const heap *genericHeap)
{
	return genericHeap->currentSize == genericHeap->size? true : false; 
}

bool isEmpty(const heap *genericHeap)
{
	return genericHeap->currentSize? false : true; 
}

void maxHeapify(int *seq, int parent, int size)
{
	int largest = parent; 
	int left = LEFT(parent); 
	int right = RIGHT(parent); 
	int temp; 

	if(left <= size && seq[left] > seq[largest])
		   largest = left; 

	if(right <= size && seq[right] > seq[largest])
		   largest = right;

	while(largest != parent)
	{
		temp = seq[parent]; 
		seq[parent] = seq[largest]; 
		seq[largest] = temp; 
		parent = largest; 
		left = LEFT(parent); 
		right = RIGHT(parent); 

		if(left <= size && seq[left] > seq[largest])
		   largest = left; 

		if(right <= size && seq[right] > seq[largest])
		   largest = right;
	}
}

void minHeapify(int *seq, int parent, int size)
{
	int smallest = parent; 
	int left = LEFT(parent); 
	int right = RIGHT(parent); 
	int temp; 

	if(left <= size && seq[left] < seq[smallest])
		   smallest = left; 

	if(right <= size && seq[right] < seq[smallest])
		   smallest = right;

	while(smallest != parent)
	{
		temp = seq[parent]; 
		seq[parent] = seq[smallest]; 
		seq[smallest] = temp; 
		parent = smallest; 
		left = LEFT(parent); 
		right = RIGHT(parent); 

		if(left <= size && seq[left] > seq[smallest])
		   smallest = left; 

		if(right <= size && seq[right] > seq[smallest])
		   smallest = right;
	}
}

void insertMaxHeap(heap *genericHeap, int key)
{
	   if(isFull(genericHeap))
	   {
			 printf("\nOverflow error!\n"); 
			 return; 
	   }
	   int index = genericHeap->currentSize; 
	   int parent = PARENT(index); 
	   int temp; 
	   genericHeap->elements[index] = key; 
	   genericHeap->currentSize++;

	   while(genericHeap->elements[parent] < genericHeap->elements[index])
	   {
			temp = genericHeap->elements[index]; 
			genericHeap->elements[index] = genericHeap->elements[parent]; 
			genericHeap->elements[parent] = temp; 
			index = parent; 
			parent = PARENT(parent);
	   }
}

void insertMinHeap(heap *genericHeap, int key)
{

	  if(isFull(genericHeap))
	   {
			 printf("\nOverflow error!\n"); 
			 return; 
	   }
	   int index = genericHeap->currentSize; 
	   int parent = PARENT(index); 
	   int temp; 
	   genericHeap->elements[index] = key; 
	   genericHeap->currentSize++; 

	   while(genericHeap->elements[parent] > genericHeap->elements[index])
	   {
			temp = genericHeap->elements[index]; 
			genericHeap->elements[index] = genericHeap->elements[parent]; 
			genericHeap->elements[parent] = temp; 
			index = parent; 
			parent = PARENT(parent);
	   }
}

void buildMaxHeap(int *seq, int size)
{
	size--; 

	for(int index = size / 2; index >= 0; index--)
		   maxHeapify(seq, index, size);
}

void buildMinHeap(int *seq, int size)
{
	size--;

	for(int index = size / 2; index >= 0; index--)
		minHeapify(seq, index, size); 
}

int extractMax(heap *genericHeap)
{
	int temp = genericHeap->elements[0]; 
	genericHeap->elements[0] = genericHeap->elements[--genericHeap->currentSize];
	maxHeapify(genericHeap->elements, 0, genericHeap->size - 1);

	return temp; 
}

int extractMin(heap *genericHeap)
{
	int temp = genericHeap->elements[0]; 
	genericHeap->elements[0] = genericHeap->elements[--genericHeap->currentSize]; 
	minHeapify(genericHeap->elements, 0, genericHeap->size - 1);

	return temp; 
}

int getMax(const heap *genericHeap)
{
	return *genericHeap->elements; 
}

int getMin(const heap *genericHeap)
{
	return *genericHeap->elements; 
}

void display(const heap*genericHeap)
{
	for(int index = 0, end = genericHeap->currentSize; index < end; index++)
		   printf(" %d", genericHeap->elements[index]); 
	
	printf("\n"); 
}

bool initializeHeap(heap *genericHeap, int size)
{
	if(genericHeap == NULL)
		   return false; 
	genericHeap->elements = (int *)malloc(size * sizeof(int));
	genericHeap->size = size; 
	genericHeap->currentSize = 0; 
	
	if(genericHeap->elements)
		   return true; 
	else 
		   return false;
}

void destroy(heap *genericHeap)
{	
	   free(genericHeap->elements); 
	   genericHeap->elements = NULL; 
	   genericHeap->size = genericHeap->currentSize = 0; 
}

void displayArray(const int *seq, int size)
{
	for(int index = 0; index < size; index++)
		   printf(" %d",seq[index]); 
	
	printf("\n"); 

}
