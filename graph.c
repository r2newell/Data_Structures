#include "graph.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <math.h> 



bool vertex_Empty(const vertex *origin)
{
   return origin->head == NULL? true : false; 
}

bool edge_insertAtFront(vertex *origin, edge *temp)
{
    if(origin == NULL)
            return false; 

    if(vertex_Empty(origin))
            origin->head = origin->tail = temp; 
    else
    {
        temp->next = origin->head; 
        origin->head->prev = temp; 
        origin->head = temp; 
    }

    return true; 
}

bool edge_insertAtBack(vertex *origin, edge *temp)
{
    if(origin == NULL)
            return false; 

    if(vertex_Empty(origin))
            origin->head = origin->tail = temp; 
    else
    {
        origin->tail->next = temp; 
        temp->prev = origin->tail; 
        origin->tail = temp; 
    }

    return true; 
}

edge *find_Edge(const vertex *origin, int key)
{
    if(origin == NULL)
            return NULL; 

    edge *head = origin->head; 
    while(head != NULL)
    {
        if(head->destination == key)
                break ;

        head = head->next; 
    }

    return head; 
}

void remove_Edge_From_Front(vertex *origin)
{
    if(origin->head == origin->tail)
            origin->head = origin->tail = NULL; 
    else
    {
        origin->head = origin->head->next; 
        origin->head->prev = NULL; 
    }
}

void remove_Edge_From_Back(vertex *origin)
{
    origin->tail = origin->tail->prev; 
    origin->tail->next = NULL; 
}

void remove_Edge(vertex *origin, edge *key)
{
    if(origin->head == key)
            remove_Edge_From_Front(origin); 
    else if(origin->tail == key)
            remove_Edge_From_Back(origin); 
    else
    {
        key->prev->next = key->next; 
        key->next->prev = key->prev; 
    }
    free(key); 
}

void display_Vertex(const graph *mixed_graph, const vertex *origin)
{
    if(origin == NULL || mixed_graph == NULL)
            return; 

    edge *head = origin->head; 
    while(head != NULL)
    {
        printf("\n%s\t\t%s\t\t$%.2lf",mixed_graph->name[head->origin], mixed_graph->name[head->destination], head->weight); 
        head = head->next; 
    }
}

void clear_Vertex(vertex *origin)
{
    if(origin == NULL)
            return; 

    while(origin->head != NULL)
            remove_Edge(origin, origin->head); 
}

void min_heapify(heap_item *seq, int parent, int size)
{
    int left = LEFT(parent); 
    int right = RIGHT(parent); 
    int location = parent;//stores location of the smallest child
    heap_item temp;

    if(left <= size && *(seq[left].distance) < *(seq[parent].distance))
            location = left; 
    if(right <= size && *(seq[right].distance) < *(seq[location].distance))
            location = right; 
    
    while(location != parent)
    {
        temp = seq[parent]; 
        seq[parent] = seq[location];
        seq[location] = temp; 
        parent = location; 
        left = LEFT(parent);
        right = RIGHT(parent); 
        
        if(left <= size && *(seq[left].distance) < *(seq[parent].distance))
            location = left; 
        if(right <= size && *(seq[right].distance) < *(seq[location].distance))
            location = right; 
    }
}

void max_heapify(heap_item *seq, int parent, int size)
{
    
    int left = LEFT(parent); 
    int right = RIGHT(parent); 
    int location = parent;//stores location of the smallest child
    heap_item temp;
    if(left <= size && *(seq[left].distance) > *(seq[parent].distance))
            location = left; 
    
    if(right <= size && *(seq[right].distance) > *(seq[location].distance))
            location = right; 
    
    while(location != parent)
    {
        temp = seq[parent]; 
        seq[parent] = seq[location];
        seq[location] = temp; 
        parent = location; 
        left = LEFT(parent);
        right = RIGHT(parent); 
        
        if(left <= size && *(seq[left].distance) > *(seq[parent].distance))
            location = left; 
        if(right <= size && *(seq[right].distance) > *(seq[location].distance))
            location = right; 
    }
}

void build_min_heap(Heap *heap)
{
    for(int counter = heap->current / 2; counter >= 0; --counter)
            min_heapify(heap->seq, counter, heap->current -1);
}

void build_max_heap(Heap *heap)
{
    for(int counter = heap->current / 2; counter >= 0; --counter)
            max_heapify(heap->seq, counter, heap->current-1); 
}

void remove_min(Heap *heap)
{
    heap->seq[0] = heap->seq[--heap->current];
    min_heapify(heap->seq, 0, heap->current -1); 
}

void remove_max(Heap *heap)
{
    heap->seq[0] = heap->seq[--heap->current];
    max_heapify(heap->seq, 0, heap->current -1); 
}


void min_insert(Heap *heap, const heap_item *item)
{
    heap->seq[heap->current] =  *item;
    int parent = PARENT(heap->current); 
    int child = heap->current++; 
    heap_item temp; 
    
   while(*(heap->seq[child].distance) < *(heap->seq[parent].distance))
   {
        temp = heap->seq[parent]; 
        heap->seq[parent] = heap->seq[child];
        heap->seq[child] = temp; 
        child = parent; 
        parent = PARENT(parent); 
   } 
}

void max_insert(Heap *heap, const heap_item *item)
{
    heap->seq[heap->current] = *item;
    int parent = PARENT(heap->current); 
    int child = heap->current++; 
    heap_item temp; 
    
   while(*(heap->seq[child].distance) > *(heap->seq[parent].distance))
   {
        temp = heap->seq[parent]; 
        heap->seq[parent] = heap->seq[child];
        heap->seq[child] = temp; 
        child = parent; 
        parent = PARENT(parent); 
   }
}

void create_heap(Heap *heap, int size)
{
    heap->current = size; 
    heap->size = size;
    heap->seq = calloc(size, sizeof(heap_item)); 
    int counter;

    for(counter = 0; counter < size; counter++)
    {
        heap->seq[counter].origin = counter; 
        heap->seq[counter].distance = (distance + counter);
    }
}

heap_item *getMin(Heap *heap)
{
    return heap->seq; 
}

heap_item *getMax(Heap *heap)
{
    return heap->seq;
}

void clear_heap(Heap *heap)
{
    free(heap->seq); 
}

bool is_Deque_Empty(const deque *list)
{
    return list->head == NULL? true : false; 
}

bool deque_InsertAtFront(deque *list, int origin, edge *location)
{
        if(list == NULL)
                return false;
        
        node *temp = calloc(1, sizeof(node)); 
        temp->origin = origin; 
        temp->current = location; 

        if(is_Deque_Empty(list)) 
                list->head = list->tail = temp; 
        else
        {
            temp->next = list->head; 
            list->head->prev = temp; 
            list->head = temp; 
        }
        return true; 
}

bool deque_InsertAtBack(deque *list, int origin, edge *location)
{
    if(list == NULL)
            return false; 
        
    node *temp = calloc(1, sizeof(node)); 
    temp->origin = origin; 
    temp->current = location; 

     if(is_Deque_Empty(list)) 
         list->head = list->tail = temp; 
     else
    {
            list->tail->next = temp; 
            temp->prev = list->tail; 
            list->tail = temp;
    }
    return true; 
}

void deque_removeFront(deque *list, node *temp)
{
    if(list == NULL)
            return; 

     node *tempHead = list->head;  
    *temp = *list->head; 
    if(list->head == list->tail)
            list->head = list->tail = NULL; 
    else
    {
        list->head = list->head->next; 
        list->head->prev = NULL; 
    }

    free(tempHead); 
}

void deque_removeBack(deque *list, node *temp)
{

    if(list == NULL)
            return; 

    node *tempTail = list->tail;  
    *temp = *list->tail; 
    if(list->head == list->tail)
            list->head = list->tail = NULL; 
    else
    {
        list->tail = list->tail->prev; 
        list->tail->next = NULL; 
    }

    free(tempTail); 
}

void deque_clear(deque *list)
{
    node temp; 
    while(list && list->head)
            deque_removeFront(list, &temp); 
}

void deque_initialize(deque *list)
{
    list->head = list->tail = NULL; 
}
/*Graph Operations*/

void calculateDegree_helper(graph *mixed_graph, int source)
{
    deque Stack; 
    deque_initialize(&Stack); 
    edge *currentPosition = mixed_graph->list[source]->head;//current position of where we are in the list
    vertex *dest;//destination vertex 
    node top;//top of stack
    int next;//next vertex in dfs search 
    discovered[source] = GREY; 
    start[source] = ++clockTime;  
    deque_InsertAtFront(&Stack, source, currentPosition);
    outDegree[source]++;  
    while(!is_Deque_Empty(&Stack))
    {
        while(currentPosition != NULL)
        {   
            next = currentPosition->destination; 
            dest = mixed_graph->list[next]; 
            indegree[next]++; 
            outDegree[source]++;  
            
            if(discovered[next] == WHITE)
            {
                discovered[next] = GREY; 
                parent[next] = source; 
                start[next] =  ++clockTime; 
                deque_InsertAtFront(&Stack, next, currentPosition); 
                source = next;
                currentPosition  = dest->head;  
                continue; 
            }

            currentPosition = currentPosition->next; 
        }
        
        deque_removeFront(&Stack, &top);
        if(top.current != NULL)
        {
            currentPosition = top.current->next;
        }

        discovered[top.origin] = BLACK; 
        end[top.origin] = ++clockTime;

        if(Stack.head != NULL)
               source = Stack.head->origin;  
    } 
    deque_clear(&Stack);  
}

void calculateDegree(graph *mixed_graph)
{
    clockTime = 0; 
    int counter; 
    dfs_Initialize(mixed_graph); 

    for(counter = 0; counter < mixed_graph->current; counter++)
    {
        if(discovered[counter] == WHITE)
                calculateDegree_helper(mixed_graph, counter); 
    }
}

graph *copy_Graph(graph *mixed_graph)
{
    if(mixed_graph == NULL)
            return NULL; 

    graph *temp = calloc(1, sizeof(graph)); 
    edge *head; 
    int counter; 
    for(counter = 0; counter != mixed_graph->current; ++counter)
    {
        head = mixed_graph->list[counter]->head;
        while(head != NULL)
        {
            addEdge(temp, mixed_graph->name[head->origin], mixed_graph->name[head->destination], head->weight); 
            head = head->next; 
        } 
    }
    return temp; 
}

graph *transpose_Graph(graph *mixed_graph)
{
    if(mixed_graph == NULL)
            return NULL; 

    graph *temp = calloc(1, sizeof(graph)); 
    initializeGraph(temp);

    edge *head; 
    int counter; 
    for(counter = 0; counter != mixed_graph->current; ++counter)
    {
        head = mixed_graph->list[counter]->head;
        while(head != NULL)
        {
            addEdge(temp, mixed_graph->name[head->destination], mixed_graph->name[head->origin], head->weight); 
            head = head->next; 
        } 
    }

     return temp; 
}

vertex *find_Vertex(graph *mixed_graph, const char *key)
{
    int counter; 
    for(counter = 0; counter < mixed_graph->current; ++counter)
        if(strcmp(mixed_graph->name[counter], key) == 0)
                break; 

    return mixed_graph->list[counter]; 
    
}

int get_Vertex(graph *mixed_graph, const char *key)
{
    int counter; 
    for(counter = 0; counter < mixed_graph->current; ++counter)
        if(strcmp(mixed_graph->name[counter], key) == 0)
                return counter; 

    return -1; 

}

void initializeGraph(graph *mixed_graph)
{
    if(mixed_graph == NULL)
            return; 

    int counter; 
    for(counter = 0; counter < MAX; counter++)
            mixed_graph->list[counter] = mixed_graph->name[counter] = NULL; 
   
    mixed_graph->current = 0; 
}
void clear_Graph(graph *mixed_graph)
{
    int counter; 
    for(counter = 0; counter != mixed_graph->current; ++counter)
        if(mixed_graph->list[counter] != NULL)
        {
            clear_Vertex(mixed_graph->list[counter]);
            free(mixed_graph->list[counter]); 
            free(mixed_graph->name[counter]); 
        }
}

bool addEdge(graph *mixed_graph, const char *origin, const char *destination, double weight)
{
    if(mixed_graph == NULL || origin == NULL || destination == NULL)
            return false; 
    
    if(strcmp(origin, destination) == 0)//protects against self loops 
            return false; 

    int position[2];//identifies where in the array the adjancency list for each vertex exist 
    bool exist[2] = {false, false};//tells whether any of the vertices exists
    int counter; 

    for(counter = 0; counter < mixed_graph->current; ++counter)
    {
        if(strcmp(mixed_graph->name[counter], origin) == 0)
        {
            position[0] = counter; 
            exist[0] = true; 
        }

        if(strcmp(mixed_graph->name[counter], destination) == 0)
        {
            position[1] = counter; 
            exist[1] = true; 
        }
        
        if(exist[0] == true && exist[1] == true)
                break; 
    }
    
    if(exist[0] == true && exist[1] == true && find_Edge(mixed_graph->list[position[0]], position[1]))
            return false; 

    edge *temp = calloc(1, sizeof(edge)); 
    temp->weight = weight; 
    if(exist[0] == false)
    {
        position[0] = counter; 
        mixed_graph->list[position[0]] = calloc(1, sizeof(vertex)); 
        mixed_graph->name[position[0]] = calloc(strlen(origin) + 1, sizeof(char)); 
        strcpy(mixed_graph->name[position[0]], origin); 
        mixed_graph->current++; 
        counter++; 
    }

    if(exist[1] == false)
    {
        position[1] = counter; 
        mixed_graph->list[position[1]] = calloc(1, sizeof(vertex)); 
        mixed_graph->name[position[1]] = calloc(strlen(destination)+ 1, sizeof(char)); 
        strcpy(mixed_graph->name[position[1]], destination); 
        mixed_graph->current++; 
        counter++; 
    }

        temp->origin = position[0]; 
        temp->destination = position[1]; 
        edge_insertAtBack(mixed_graph->list[position[0]], temp);
    
    return true; 
}

void display_Graph(const graph *mixed_graph)
{
    int counter = 0; 
    printf("\nOrigin\t\tDestination\t\tCost"); 
    for(counter = 0; counter < mixed_graph->current; ++counter)
        display_Vertex(mixed_graph, mixed_graph->list[counter]);
}

void dfs_Initialize(graph *mixed_graph)
{
        int counter; 
        for(counter = 0; counter < mixed_graph->current; counter++)
        {
            parent[counter] = counter; 
            start[counter] = end[counter] = 0; 
            distance[counter] = -1; 
            discovered[counter] = WHITE; 
        }
}
void depth_First(graph *mixed_graph)
{
    clockTime = 0; 
    int counter; 
    dfs_Initialize(mixed_graph); 
    
    for(counter = 0; counter < mixed_graph->current; counter++)
    {
        if(discovered[counter] == WHITE)
                depth_First_Visit(mixed_graph, counter); 
    }
}
void depth_First_Visit(graph *mixed_graph, int source)
{
    deque Stack; 
    deque_initialize(&Stack); 
    edge *currentPosition = mixed_graph->list[source]->head;//current position of where we are in the list
    vertex *dest;//destination vertex 
    node top;//top of stack
    int next;//next vertex in dfs search 
    discovered[source] = GREY; 
    start[source] = ++clockTime;  
    deque_InsertAtFront(&Stack, source, currentPosition); 
    while(!is_Deque_Empty(&Stack))
    {
        while(currentPosition != NULL)
        {
            next = currentPosition->destination; 
            dest = mixed_graph->list[next]; 
            if(discovered[next] == WHITE)
            {
                discovered[next] = GREY; 
                parent[next] = source; 
                start[next] =  ++clockTime; 
                deque_InsertAtFront(&Stack, next, currentPosition); 
                source = next;
                currentPosition  = dest->head;  
                continue; 
            }

            currentPosition = currentPosition->next; 
        }
        
        deque_removeFront(&Stack, &top);
        if(top.current != NULL)
        {
            currentPosition = top.current->next;
        }

        discovered[top.origin] = BLACK; 
        end[top.origin] = ++clockTime;

        if(Stack.head != NULL)
               source = Stack.head->origin;  
    } 

    deque_clear(&Stack); 
}

void breadth_First(graph *mixed_graph, int source)
{
    deque Queue; 
    edge *currentPosition; 
    dfs_Initialize(mixed_graph);  
    deque_initialize(&Queue); 
    deque_InsertAtBack(&Queue, source, NULL); 
    node front; 
    distance[source] = 0; 

    while(!is_Deque_Empty(&Queue))
    {
        deque_removeFront(&Queue, &front);  
        discovered[front.origin] = GREY; 
        source = front.origin;
        currentPosition = mixed_graph->list[source]->head;
       
        while(currentPosition != NULL)
        {
            if(discovered[currentPosition->destination] == WHITE)
            {
                discovered[currentPosition->destination] = GREY; 
                distance[currentPosition->destination] = distance[currentPosition->origin] + 1; 
                parent[currentPosition->destination] = currentPosition->origin; 
                deque_InsertAtBack(&Queue, currentPosition->destination, NULL); 
                
            }
            currentPosition = currentPosition->next;
        }
        discovered[source] = BLACK; 
    }

    deque_clear(&Queue); 
}

deque *acyclic(graph *mixed_graph)
{
    clockTime = 0; 
    deque *Queue = NULL;
    dfs_Initialize(mixed_graph); 
    int counter; 
    bool cycle = false; 
    for(counter = 0; counter < mixed_graph->current; counter++) 
    {
        if(discovered[counter] == WHITE)
            Queue = acyclic_Visit(mixed_graph, counter, &cycle); 
        if(cycle == true)
                return Queue; 
    }
   return Queue;
} 

deque *acyclic_Visit(graph *mixed_graph, int source, bool *cycle)
{

    deque Stack; 
    deque *Queue = calloc(1, sizeof(deque)); 
    deque_initialize(&Stack);
    edge *currentPosition = mixed_graph->list[source]->head;//current position of where we are in the list
    vertex *dest;//destination vertex 
    node top;//top of stack
    int next;//next vertex in dfs search 
    discovered[source] = GREY; 
    start[source] = ++clockTime;  
    deque_InsertAtFront(&Stack, source, currentPosition);
    deque_InsertAtBack(Queue, source, NULL);  
    while(!is_Deque_Empty(&Stack))
    {
        while(currentPosition != NULL)
        {
            next = currentPosition->destination; 
            dest = mixed_graph->list[next]; 
            if(discovered[next] == WHITE)
            {
                discovered[next] = GREY; 
                parent[next] = source; 
                start[next] =  ++clockTime; 
                deque_InsertAtFront(&Stack, next, currentPosition); 
                deque_InsertAtBack(Queue, next, NULL);  
                source = next;
                currentPosition  = dest->head;  
                continue; 
            }else if(discovered[next] == GREY)
            {
                    deque_InsertAtBack(Queue, next, NULL); 
                    *cycle = true;  
                    deque_clear(&Stack); 
                    return Queue;
            }

            currentPosition = currentPosition->next; 
        }
        
        deque_removeFront(&Stack, &top);
        if(top.current != NULL)
        {
            currentPosition = top.current->next;
        }

        discovered[top.origin] = BLACK; 
        end[top.origin] = ++clockTime;

        if(Stack.head != NULL)
               source = Stack.head->origin;  
    } 
   
    deque_clear(&Stack);  
    deque_clear(Queue); 
    free(Queue); 
    return NULL; 
}


void bipartite_helper(graph *mixed_graph, int source, int *color, bool *status)
{
    
    enum COLORS{RED = 0, BLUE};
    deque Stack; 
    deque_initialize(&Stack); 
    edge *currentPosition = mixed_graph->list[source]->head;//current position of where we are in the list
    vertex *dest;//destination vertex 
    node top;//top of stack
    int next;//next vertex in dfs search 
    discovered[source] = GREY; 
    color[source] = RED; 
    start[source] = ++clockTime;  
    deque_InsertAtFront(&Stack, source, currentPosition); 
    
    while(!is_Deque_Empty(&Stack))
    {
        while(currentPosition != NULL)
        {
            next = currentPosition->destination; 
            dest = mixed_graph->list[next]; 
            if(discovered[next] == WHITE)
            {
                if(color[source]  == RED)
                        color[next] = BLUE; 
                else
                        color[next] = RED; 
                discovered[next] = GREY; 
                parent[next] = source; 
                start[next] =  ++clockTime; 
                deque_InsertAtFront(&Stack, next, currentPosition); 
                source = next;
                currentPosition  = dest->head; 
                continue; 
            }else if(color[source] == color[next])
            {
                    *status = false;
                    deque_clear(&Stack);
                    return;  
            }

            currentPosition = currentPosition->next; 
        }
        
        deque_removeFront(&Stack, &top);
        if(top.current != NULL)
        {
            currentPosition = top.current->next;
        }

        discovered[top.origin] = BLACK; 
        end[top.origin] = ++clockTime;

        if(Stack.head != NULL)
               source = Stack.head->origin;  
    } 

    deque_clear(&Stack);      
}

bool bipartite(graph *mixed_graph)
{
    clockTime = 0; 
    bool status = true;
    int color[mixed_graph->current]; 
    dfs_Initialize(mixed_graph); 
    int counter; 
    
    for(counter = 0; counter < mixed_graph->current; counter++)
    {
        if(discovered[counter] == WHITE)
                bipartite_helper(mixed_graph, counter, color, &status); 
        if(status == false)
                return status; 
    }

    return status; 
}


void connectedComponents_helper(graph *mixed_graph, int source, int count)
{
    deque Stack; 
    deque_initialize(&Stack); 
    edge *currentPosition = mixed_graph->list[source]->head;//current position of where we are in the list
    vertex *dest;//destination vertex 
    node top;//top of stack
    int next;//next vertex in dfs search 
    discovered[source] = GREY; 
    start[source] = ++clockTime;  
    components[source] = count; 
    deque_InsertAtFront(&Stack, source, currentPosition); 
    while(!is_Deque_Empty(&Stack))
    {
        while(currentPosition != NULL)
        {
            next = currentPosition->destination; 
            dest = mixed_graph->list[next]; 
            if(discovered[next] == WHITE)
            {
                discovered[next] = GREY; 
                parent[next] = source; 
                start[next] =  ++clockTime; 
                deque_InsertAtFront(&Stack, next, currentPosition); 
                source = next;
                currentPosition  = dest->head;  
                components[next] = count; 
                continue; 
            }

            currentPosition = currentPosition->next; 
        }
        
        deque_removeFront(&Stack, &top);
        if(top.current != NULL)
        {
            currentPosition = top.current->next;
        }

        discovered[top.origin] = BLACK; 
        end[top.origin] = ++clockTime;

        if(Stack.head != NULL)
               source = Stack.head->origin;  
    } 

    deque_clear(&Stack); 
}

void connectedComponents(graph *mixed_graph)
{
    int counter, numComponents = 0; 
    clockTime = 0 ; 
    dfs_Initialize(mixed_graph); 

    for(counter = 0; counter < mixed_graph->current; counter++)
    {
       if(discovered[counter] == WHITE)
       {
            connectedComponents_helper(mixed_graph, counter, numComponents); 
            numComponents++; 
       } 
    
    }

    printf("\nThe number of components is: %d\n", numComponents); 
    counter = 0; 
    while(counter < mixed_graph->current)
    {
        printf("\nComponent Number %d: %s", components[counter], mixed_graph->name[counter]);
        counter++;
    }
}

deque *findsPath(graph *mixed_graph, const char *origin, const char *destination)
{
    int source = get_Vertex(mixed_graph, origin); 
    int dest = get_Vertex(mixed_graph, destination); 
    if(source != -1 && dest != -1)
        breadth_First(mixed_graph, source);
    else
           return NULL; 

    return getPath(source, dest); 
}

deque *getPath(int source, int destination)
{
   deque *Queue = calloc(1, sizeof(Queue));  
   deque_initialize(Queue); 

   int path = parent[destination]; 
   while(path != source)
    {
        deque_InsertAtFront(Queue, path, NULL); 
        path = parent[path]; 
    }
    
    if(is_Deque_Empty(Queue))
    {
        free(Queue); 
        Queue = NULL;
    }else
    {
        deque_InsertAtFront(Queue, source, NULL);
        deque_InsertAtBack(Queue, destination, NULL); 
    }
    return Queue;
}

int connected_helper(graph *mixed_graph, int source)
{
    deque Queue; 
    edge *currentPosition; 
    dfs_Initialize(mixed_graph);  
    deque_initialize(&Queue); 
    deque_InsertAtBack(&Queue, source, NULL); 
    node front; 
    distance[source] = 0; 
    int counter = 0; 
    while(!is_Deque_Empty(&Queue))
    {
        counter++; 
        deque_removeFront(&Queue, &front);  
        discovered[front.origin] = GREY; 
        source = front.origin;
        currentPosition = mixed_graph->list[source]->head;
       
        while(currentPosition != NULL)
        {
            if(discovered[currentPosition->destination] == WHITE)
            {
                discovered[currentPosition->destination] = GREY; 
                distance[currentPosition->destination] = distance[currentPosition->origin] + 1; 
                parent[currentPosition->destination] = currentPosition->origin; 
                deque_InsertAtBack(&Queue, currentPosition->destination, NULL); 
                
            }
            currentPosition = currentPosition->next;
        }
        discovered[source] = BLACK; 
    }

    deque_clear(&Queue); 
    return counter; 
}

bool connected(graph *mixed_graph)
{
    int source = rand() % mixed_graph->current;  
    
    int numVertices = connected_helper(mixed_graph, source); 
    if(numVertices != mixed_graph->current)
            return false; 
    
    graph *rev = transpose_Graph(mixed_graph); 
    numVertices = connected_helper(rev, get_Vertex(mixed_graph, mixed_graph->name[source]));
    clear_Graph(rev); 
    free(rev);  

    return numVertices == mixed_graph->current? true : false;
}

void topological_Visit(graph *mixed_graph, int source, deque *topological)
{
    deque Stack; 
    deque_initialize(&Stack);
    edge *currentPosition = mixed_graph->list[source]->head;//current position of where we are in the list
    vertex *dest;//destination vertex 
    node top;//top of stack
    int next;//next vertex in dfs search 
    discovered[source] = GREY; 
    start[source] = ++clockTime;  
    deque_InsertAtFront(&Stack, source, currentPosition); 
    while(!is_Deque_Empty(&Stack))
    {
        while(currentPosition != NULL)
        {
            next = currentPosition->destination; 
            dest = mixed_graph->list[next]; 
            if(discovered[next] == WHITE)
            {
                discovered[next] = GREY; 
                parent[next] = source; 
                start[next] =  ++clockTime; 
                deque_InsertAtFront(&Stack, next, currentPosition); 
                source = next;
                currentPosition  = dest->head;  
                continue; 
            }

            currentPosition = currentPosition->next; 
        }
        
        deque_removeFront(&Stack, &top);
        deque_InsertAtFront(topological, top.origin, NULL); 
        if(top.current != NULL)
        {
            currentPosition = top.current->next;
        }

        discovered[top.origin] = BLACK; 
        end[top.origin] = ++clockTime;
    
        if(Stack.head != NULL)
               source = Stack.head->origin;  
    } 

    deque_clear(&Stack); 
}

deque *topologicalSort(graph *mixed_graph)
{
    clockTime = 0; 
    int counter; 
    deque *topological = calloc(1,  sizeof(deque)); 
    deque_initialize(topological); 
    dfs_Initialize(mixed_graph); 

    for(counter = 0; counter < mixed_graph->current; counter++)
    {
        if(discovered[counter] == WHITE)
             topological_Visit(mixed_graph, counter, topological); 
    }
    return topological; 
}


deque *topologicalSort2(graph *mixed_graph)
{
    calculateDegree(mixed_graph); 
    int counter;  
    deque Stack;
    deque *Queue = calloc(1, sizeof(deque)); 
    deque_initialize(&Stack);
    deque_initialize(Queue);  
    dfs_Initialize(mixed_graph);  
    
    for(counter = 0; counter < mixed_graph->current; counter++)
        if(indegree[counter] == 0 && discovered[counter] ==  WHITE)
        {
            deque_InsertAtFront(&Stack, counter, NULL); 
            discovered[counter] = GREY; 
        }

    edge *currentPosition; 
    node top;
    counter = 0;
    
    while(!is_Deque_Empty(&Stack))
    {
        counter++;
        deque_removeFront(&Stack, &top); 
        deque_InsertAtBack(Queue, top.origin, NULL); 
        currentPosition = mixed_graph->list[top.origin]->head;

        while(currentPosition != NULL)
        {
            indegree[currentPosition->destination]--;
            if(indegree[currentPosition->destination] == 0 && discovered[currentPosition->destination] == WHITE)
            {
                    deque_InsertAtFront(&Stack, currentPosition->destination, NULL); 
                    discovered[currentPosition->destination] = GREY; 
            }
            currentPosition = currentPosition->next; 
        } 
    }

    
    deque_clear(&Stack); 
    if(counter == mixed_graph->current)
            return Queue; 
    deque_clear(Queue); 
    free(Queue); 
    return NULL; 
}


void strongly_Connected(graph *mixed_graph)
{
    graph *graphTranspose = transpose_Graph(mixed_graph); 
    deque *topological = topologicalSort(mixed_graph);
    dfs_Initialize(graphTranspose); 
    clockTime = 0; 
    int numComponents = 0;  
    int counter; 
    node top;  

    while(!is_Deque_Empty(topological))
    {
        deque_removeFront(topological, &top);
        if(discovered[top.origin] == WHITE)
        {
          connectedComponents_helper(graphTranspose, top.origin, numComponents);
          numComponents++;   
        } 
    }
    
    printf("\nThe number of components is: %d\n", numComponents); 
    counter = 0; 
    while(counter < mixed_graph->current)
    {
        printf("\nComponent Number %d: %s", components[counter], mixed_graph->name[counter]);
        counter++;
    }

    clear_Graph(graphTranspose); 
    deque_clear(topological); 
    free(graphTranspose); 
    free(topological); 
}

void initializeShortest(graph *mixed_graph, int source)
{
    int counter; 
    for(counter = 0; counter < mixed_graph->current; ++counter)
    { 
        if(counter != source)
        {
            parent[counter] = counter; 
            distance[counter] = INFINITY; 
        }
        else 
            parent[counter] = counter;
    }
    distance[source] = 0;

}

void relax(int dest, int origin, double weight)
{

    if(distance[dest] > distance[origin] + weight)
    {
            distance[dest] = distance[origin] + weight;
            parent[dest] = origin;
    }
}

void bellman_Ford(graph *mixed_graph, const char *source)
{
        int origin = get_Vertex(mixed_graph, source);
        if(origin == -1)
                return; 
        
        initializeShortest(mixed_graph, origin); 
        int vertices; 
        int counter; 
        edge *currentPosition;

        for(counter = 0; counter < mixed_graph->current; counter++)
        {
            for(vertices = 0; vertices < mixed_graph->current; vertices++)
            {
                currentPosition = mixed_graph->list[vertices]->head;
                while(currentPosition != NULL)
                {
                    relax(currentPosition->destination, currentPosition->origin, currentPosition->weight); 
                    currentPosition = currentPosition->next; 
                } 
            }
        }
        
        for(vertices = 0; vertices < mixed_graph->current; vertices++)
        {
            currentPosition = mixed_graph->list[vertices]->head;
            while(currentPosition != NULL)
            {
                if(distance[currentPosition->destination] > distance[currentPosition->origin] + currentPosition->weight)
                {
                    printf("\nThe graph contains a negative cycle.");
                    return;
                }
                currentPosition = currentPosition->next; 
            } 
        }
}

void dijsktra(graph *mixed_graph, const char *source)
{
    int origin = get_Vertex(mixed_graph, source); 
    if(origin == -1)
            return;
    
    initializeShortest(mixed_graph, origin); 
    Heap minHeap; 
    create_heap(&minHeap, mixed_graph->current);
    build_min_heap(&minHeap);
    edge *currentPosition;  
    heap_item *minimum; 
    
    while(minHeap.current)
    {
        minimum = getMin(&minHeap);
        currentPosition = mixed_graph->list[minimum->origin]->head;
        remove_min(&minHeap);
        while(currentPosition != NULL)
        {
            relax(currentPosition->destination, currentPosition->origin, currentPosition->weight);
            currentPosition = currentPosition->next;  
        }
    }

    clear_heap(&minHeap);
}
