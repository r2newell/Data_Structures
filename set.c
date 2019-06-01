#include "set.h"
#include <stdlib.h> 
#include <time.h>
#include <stdio.h>



void initializeSet(set * connectedComponents, int size)
{
    connectedComponents->components = calloc(size, sizeof(int)); 
    connectedComponents->size = calloc(size, sizeof(int)); 
    int counter; 
    for(counter = 0; counter < size; counter++)
    {
            connectedComponents->size[counter] = 1;
            connectedComponents->components[counter] = counter; 
    }
}

int find(set *connectedComponents, int element)
{
    int child, root; 
    root = connectedComponents->components[element]; 
    child = element; 
    while(root != child)
    {
        child = root; 
        root = connectedComponents->components[root]; 
    }
   
   /*path compression*/ 
    child = connectedComponents->components[element]; 
    while(element != child)
    {
        connectedComponents->components[element] = root; 
        element = child;
        child = connectedComponents->components[child]; 
    }

    return root;
}

void set_union(set *connectedComponents, int origin, int destintation)
{
    /*Uses union by rank heuristics*/
     int root[2] = {find(connectedComponents, origin), find(connectedComponents, destintation)}; 
     if(root[0] == root[1])
        return;     

    if(connectedComponents->size[root[0]] < connectedComponents->size[root[1]])
    {
             connectedComponents->components[root[0]] = root[1];  
             connectedComponents->size[root[1]] += connectedComponents->size[root[0]]; 
    }
    else
    {
            connectedComponents->components[root[1]] = root[0]; 
            connectedComponents->size[root[0]] += connectedComponents->size[root[0]]; 
    }
}

bool connected(set *connectedComponents, int origin, int destination)
{
    return find(connectedComponents, origin) == find(connectedComponents, destination)? true : false; 
}

void destroy_set(set *connectedComponents)
{
    free(connectedComponents->size); 
    free(connectedComponents->components); 
}
