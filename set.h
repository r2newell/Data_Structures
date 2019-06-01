#ifndef SET_H_
#define SET_H_
#include <stdbool.h> 

/*A simple implementation of the union find data structure using integers. This implementation uses the two well-known heuristic
 * of path compression and union by weight.*/

typedef struct set
{
    int *components; //array for the different connected components
    int *size;//size of each components  
}set; 

void initializeSet(set *, int);//initializes the set  
int find(set *,int);//finds the component where an element is located in 
void set_union(set *, int, int);//unions two different components into one 
bool connected(set *,int, int);//tells whether to elements are in the same component hence connected 
void destroy_set(set *);//destroys the components created
#endif
