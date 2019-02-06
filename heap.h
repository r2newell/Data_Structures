#ifndef HEAP_H_ 
#define HEAP_H_ 
#include <stdbool.h> 

#define PARENT(n) (n / 2)
#define LEFT(n) (2 * (n) + 1)
#define RIGHT(n) (2 *(n) + 2)

typedef struct heap
{
	int size; //size of heap
	int *elements; //points to the array that will store the heap
	int currentSize; //stores current number of elements in the heap
}heap; 

bool initializeHeap(heap *, int size);// returns true upon successful initialization 
bool isFull(const heap*);
bool isEmpty(const heap *);
void maxHeapify(int *, int, int);//construct a subtree which is maximum heap
void minHeapify(int *, int, int);//construct a subtree which is minimum heap
void buildMaxHeap(int *, int); //construct a maximum heap from an array
void buildMinHeap(int *, int);//construct a minimum heap from an array
void insertMaxHeap(heap *, int);//insert into a maximum heap
void insertMinHeap(heap *, int);//insert into a minimum heap
int extractMax(heap *);//extract maximum element
int extractMin(heap *);//extract minimum element
int getMax(const heap*);//return maximum element
int getMin(const heap *);//retrun minimum element 
void display(const heap*); //display heap
void displayArray(const int *, int);
void destroy(heap *);
#endif
