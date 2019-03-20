#include "linearProbe.h"
#include <stdlib.h>
#include <stdio.h> 
#include <string.h> 

int main()
{
    hashTable dictionary; 
    initialize(&dictionary, SIZE_1);
    FILE *fp; 

    if((fp = fopen("words.txt","r"))== NULL)
    {
        fprintf(stderr,"\nFile couldn't be opened.\n");
        exit(1); 
    }
   
    node *item = calloc(1, sizeof(node));
    if(item == NULL)
    {
        printf("\nHash Table Full.\n");
        exit(1); 
    }
    while(fscanf(fp, "%s", item->key) == 1)
    {
	   item->status = 0;
        insert(&dictionary, item, SIZE_1);
        item = calloc(1, sizeof(node));
        if(item == NULL)
          {
              printf("\nHash Table Full.\n");
              break;
          }
    }

    int option; 
    char key[KEYSIZE + 1]; 
    printf("\n1) Enter -1 to quit.");
    printf("\n2) Enter 0 to search: ");
    printf("\n3) Enter 1 to insert: "); 
    printf("\n4) Enter 2 to delete: "); 
    printf("\n5) Enter 3 to display dictionary: ");
    printf("\nEnter option: ");  
    while(scanf("%d", &option)&& option != -1)
    {
        switch(option)
        {
            case -1:
               break; 
            case 0: 
              printf("\nEnter the key you would like to search for: "); 
		    scanf(" %s", key);
              item = search(&dictionary, key, SIZE_1); 
		    if(item != NULL)
                 printf("\nWe found %s in the dictionary.", item->key); 
              else 
                printf("\nAre you sure that key exist?");
            break; 
            case 1: 
                item = calloc(1, sizeof(node));
			 item->status = 0; 
                printf("\nPlease enter the key to insert: "); 
			 scanf(" %s", item->key);
                if(insert(&dictionary, item, SIZE_1) == false)
                   printf("\nWe couldn't insert that key for some reason."); 
               else 
                  printf("\nInserted succesfully"); 
              break; 
            case 2:               
               printf("\nEnter the key you would like to search for: ");  
			scanf(" %s", key); 
               if(removeNode(&dictionary, key, SIZE_1) == false)
                   printf("\nThe key doesn't exist within the dictionary."); 
               else
                   printf("\nSuccessfully removed."); 
               break; 
            case 3: 
               display(&dictionary, SIZE_1);
               break; 
            default: 
               break; 
                
        }
    printf("\n1) Enter -1 to quit.");
    printf("\n2) Enter 0 to search: ");
    printf("\n3) Enter 1 to insert: "); 
    printf("\n4) Enter 2 to delete: "); 
    printf("\n5) Enter 3 to display dictionary: ");
    printf("\nEnter option: ");  

    }
    fclose(fp);
    return 0; 
}

unsigned long long hash(const char *key, unsigned long long size)
{
    const int alpha = 33; 
    unsigned long long sum = 0; 

    while(*key)
    {
        sum = ((sum * alpha) + (unsigned long long) (*key)) % size; 
        key++; 
    }

    return sum % size; 
}

bool insert(hashTable *dictionary, node *item, unsigned long long size)
{
    unsigned long long index = hash(item->key, size); 
    int counter = 1; 
    while((dictionary->table[index]) != NULL && (dictionary->table[index]->status) == 0)
    {
        index = (index + counter) % size;
        if(counter == size)
           break;  
        counter++;  
    }

    if(counter != size)
        dictionary->table[index] = item; 
    return counter == size ? false : true; 
}

node *search(hashTable *dictionary, const char *key, unsigned long long size)
{
    unsigned long long index = hash(key, size); 
    int counter = 1; 
    while((dictionary->table[index]) != NULL)
    {
        if(counter == size)
            break; 
        if(strcmp(key, dictionary->table[index]->key) == 0 && (dictionary->table[index]->status) == 0)
            break; 
        index = (index + counter) % size;
	   counter++; 
    }

    if(counter != size)
            return dictionary->table[index]; 
    else 
            return NULL;
}

bool removeNode(hashTable *dictionary, const char *key, unsigned long long size)
{
    node *item = search(dictionary, key, size); 
    if(item == NULL)
        return false; 

    item->status = 1; 
    return true; 
}

void initialize(hashTable *dictionary, int size)
{
    if(dictionary == NULL)
        return; 

    int counter; 
    dictionary->table = calloc(size, sizeof(node *));
    for(counter = 0; counter < size; counter++)
       dictionary->table[counter] = NULL; 
}

void display(hashTable *dictionary, int size)
{
    int counter; 
    for(counter = 0; counter < size; counter++)
    { 
         if(dictionary->table[counter] != NULL && dictionary->table[counter]->status == 0)
            printf("\n%d)Key: %s", counter,dictionary->table[counter]->key);
    }
}
