#ifndef LINEARPROBE_H_
#define LINEARPROBE_H_
#define KEYSIZE 30
#define SIZE_1 393241
#include <stdbool.h>
/*This is a hash table implemented by that Romario Newell that uses linear probing as a method of resolving collisions. In this example we hash strings to array indices. We allocate a very large array from beginning but this is only a demonstration of the hash table concepts.*/


typedef struct node
{
    int status : 1;//represents whether the object is deleted or not
    char key[KEYSIZE + 1];//represents the key
}node;

typedef struct hashTable
{
    node **table;//stores the key. This right here is practically the hash table.
}hashTable;

unsigned long long hash(const char *, unsigned long long);//returns an hash
bool insert(hashTable *, node *, unsigned long long);//inserts into the hash table and returns true success and false otherwise
node *search(hashTable *, const char *, unsigned long long);//searches for a key
bool removeNode(hashTable *, const char *, unsigned long long);//removes a key from the hash table
void display(hashTable *, int);//display hash table elements
void initialize(hashTable *, int);//initializes hash table

#endif
