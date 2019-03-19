#ifndef HASHTABLE_H_
#define HASHTABLE_H_ 
#include <stdbool.h>
#define KEYSIZE 30
#define SIZE 196613 

typedef struct item
{
    int lineNumber; 
    char key[KEYSIZE + 1];//key  
    struct item *next;//points to the next node 
    struct item *prev;//points to the previous node
}item; 

typedef struct Queue
{
    item *head;//head of the queue
    int size;//size of the queue
}Queue;

bool isFull(const item *);//check if an item can be inserted into the queue
bool isEmpty(const Queue *);//check if the queue is full
void initializeQueue(Queue *);//initializes queue
void destroyQueue(Queue *);//destroy memory for queue
bool insertQueue(Queue *, item *);//inserts into the front of the queue and return true if successful
bool deleteQueue(Queue *, item *);//deletes the item from the queue
item *searchQueue(Queue *, const char *);//searches queue for item and returns the item and null if not found
unsigned long long  hash(const char *, unsigned long long);//hash function for string
void initialize(Queue *, int);//initializes hash table
bool insert(Queue *, unsigned long long, item *);//inserts into the hash table and returns true, false otherwise
item *search(Queue *, const char *, unsigned long long);//searches the hash table for value and returns the item else null unsuccesful
bool removes(Queue *, const char *, unsigned long long);//removes an item from the hash table
void destroy(Queue *, unsigned long long);//destroys hash table
#endif
