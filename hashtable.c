#include "hashtable.h" 
#include <stdlib.h> 
#include <stdio.h>
#include <string.h> 


int main()
{
   FILE *fp; 
   Queue *hashTable = calloc(SIZE, sizeof(Queue)); 
   initialize(hashTable, SIZE); 
   char key[KEYSIZE + 1];
   unsigned long long position; 
   item *element = NULL;
   long long lineNumber = 1; 
   if((fp = fopen("words.txt","r")) == NULL)
   {
        printf("\nCould not open your file");
        exit(1);  
   }

    
   element  = calloc(1, sizeof(item)); 
   while(fscanf(fp, "%s",element->key) == 1)
   { 
     if(isFull(element))
     {
        printf("\nCouldn't insert anything else into the hash table good bye.\n");
        exit(1); 
     }
     element->lineNumber = lineNumber;  
     position = hash(element->key, SIZE); 
     insert(hashTable, position, element);   
     element  = calloc(1, sizeof(item));
     lineNumber++; 
   }
   int option; 
   printf("\nPlease enter -1 to exit search: "); 
   while(true)
   {
        scanf(" %d", &option); 
        if(option == -1)
            break; 
        option = getchar();  
        printf("\nPlease enter a word to search for: "); 
        scanf(" %s", key); 
        position = hash(key, SIZE); 
        element = search(hashTable, key, SIZE); 
        
        if(element)
           printf("\nWe found %s at %d", element->key, element->lineNumber);
        else
           printf("\nWe couldn't find the string.\n"); 

        printf("\nPlease enter -1 to exit search: "); 
   }
   destroy(hashTable, SIZE); 
   printf("\nHead: %p",hashTable[0].head); 
   fclose(fp);
}



bool isFull(const item *element)
{
    return element? false : true; 
}

bool isEmpty(const Queue *buffer)
{
    return buffer->head? false : true; 
}

void initializeQueue(Queue *buffer)
{
    buffer->head = NULL;
    buffer->size = 0; 
}

void destroyQueue(Queue *buffer)
{
    item *prev;
    while(buffer->head)
    {
        prev = buffer->head;
        buffer->head = buffer->head->next; 
        free(prev);
    }
    initializeQueue(buffer); 
}

bool insertQueue(Queue *buffer, item *element)
{
        buffer->size++; //increments the size of the bucket
        if(!isEmpty(buffer))
        {
            element->next = buffer->head; 
            buffer->head->prev = element; 
        }
        buffer->head = element;
        return true; 
}

bool deleteQueue(Queue *buffer, item *element)
{
    if(element == NULL)
    {
        fprintf(stderr, "\nYou passed a null value.\n");
        return false;
    } 
    buffer->size--; //decrements the size of the bucket
    if(buffer->head == element)
    {
        buffer->head = element->next; 
        buffer->head->prev = NULL; 
    }else if(element->next)
    {
        element->next->prev = element->prev; 
        element->prev->next = element->next; 
    }
    else element->prev->next = NULL; 
    
    free(element); 
    return true; 
}

item *searchQueue(Queue *buffer, const char *key)
{

    item *found = buffer->head; 
    while(found)
    {
        if((strcmp(found->key, key)) == 0)
            break; 
        found = found->next; 
    }

    return found; 
}

void initialize(Queue *hashTable, int size)
{
    int counter; 
    for(counter = 0; counter < size; hashTable++, counter++)
        initializeQueue(hashTable); 
}

unsigned long long hash(const char *key, unsigned long long size)
{
    const int scalar  = 33;
    unsigned long long sum = 0; 
    
    while(*key)
    {
        sum = ((sum * scalar) + (unsigned long long) (*key)) % size; 
        key++; 
    }
    return sum % size;
}

bool insert(Queue *hashTable, unsigned long long position, item *element)
{
    insertQueue(&hashTable[position], element); 
    return true; 
}

item *search(Queue *hashTable, const char *key, unsigned long long size)
{
    unsigned long long position = hash(key, size); 
    return searchQueue(&hashTable[position], key); 
}

bool removes(Queue *hashTable, const char *key, unsigned long long size)
{
    unsigned long long position = hash(key, size); 
    return deleteQueue(&hashTable[position], searchQueue(&hashTable[position], key));  
}

void destroy(Queue *hashTable, unsigned long long size)
{
    int counter; 
    for(counter = 0; counter < size; counter++)
        destroyQueue(&hashTable[counter]);    
}
