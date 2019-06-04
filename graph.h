#ifndef GRAPHS_H_
#define GRAPHS_H_ 
#define MAX 1000
#define PARENT(x) ((x)/2)
#define LEFT(x) ((((x)) * 2) + 1)
#define RIGHT(x) (((x) * 2) + 2)
#include <stdbool.h> 


/*Edge declaration*/
typedef struct edge
{
    int origin;//origin vertex
    int destination;//destination vertex 
    double weight;//weight for the particular edge 
    struct edge *next;//points to the next edge of the current vertex 
    struct edge *prev;//points to the previous edge of the current of vertex 
}edge; 


/*Vertex Declaration*/
typedef struct vertex
{
    edge *head;//head of the list
    edge *tail;//tail of the list 
}vertex; 


/*Vertex Operations*/
bool edge_insertAtBack(vertex *, edge*);//inserts an edge in the back of the list
bool edge_insertAtFront(vertex *, edge *);//inserts an edge at the front of the list
edge *find_Edge(const vertex *, int);//finds an edge
bool vertex_Empty(const vertex *);//tells whether that vertex has any other vertex adjacent to it
void remove_Edge_From_Front(vertex *);//removes an edge from the front of a list 
void remove_Edge_From_Back(vertex *);//removes an edge from the back of a list
void remove_Edge(vertex *, edge *);//removes an edge
void clear_Vertex(vertex *);//returns memory allocated

/*Miscellaneous Operations*/
typedef struct node 
{
    int origin;//origin of an edge 
    edge *current;//stores the current location of where we are in the list 
    struct node *next;//points to the next location 
    struct node *prev;//points to the previous location 
}node; 

typedef struct deque
{
    node *head; 
    node *tail; 
}deque; 

/*Heap*/

typedef struct heap_item
{
    int origin;//points to the index at where the vertex is located 
    double *distance;//points to index in the distance array of where the appropriate distance for the vertex is 
}heap_item; 

typedef struct Heap
{
    heap_item *seq;//sequence of heap items 
    int current;//stores the current amount of heap_items in the heap
    int size;//stores the size of the heap 
}Heap;

/*Heap Operations*/
void min_heapify(heap_item *, int, int);//creates a min heap
void max_heapify(heap_item *, int, int);//creates a max heap
void build_min_heap(Heap *);//builds a min heap
void build_max_heap(Heap *);//builds a max heap
void remove_min(Heap *);//removes minimum heap_item in the heap
void remove_max(Heap *);//removes a maximum heap_item in the heap
void min_insert(Heap *, const heap_item *);//inserts into a min heap 
void max_insert(Heap *, const heap_item *);//inserts into a max heap 
void create_heap(Heap *, int);//creates a heap
void clear_heap(Heap *);//release the memory held by heap
heap_item *getMin(Heap *);//gets the maximum heap_item 
heap_item *getMax(Heap *);//gets the minimum heap_item

/*Deque Operations*/
bool is_Deque_Empty(const deque *);//checks to see whether a deque is empty
bool deque_InsertAtFront(deque *, int, edge *);//inserts into the deque
bool deque_InsertAtBack(deque *, int, edge *);//inserts at back into the deque
void deque_removeFront(deque *, node *);//removes from front
void deque_removeBack(deque *, node *);//removes from back
void deque_clear(deque *);//removes deque
void deque_initialize(deque *);//initializes deque

/*Graph representation*/
enum STATES{WHITE = 0, GREY, BLACK}; 

typedef struct graph
{
    vertex *list[MAX];//adjacency list
    char *name[MAX];//names of vertex 
    int current;//current number of vertices
}graph;

int parent[MAX];//parent during breadth first, depth first and many other graph algorithms
int discovered[MAX];//tells whether a vertex is discovered 
int start[MAX];//tells the first time the vertex was encountered on dfs 
int end[MAX];//tells when the vertex was finished on dfs 
double distance[MAX];//tells the distance during bfs and other shortest path algorithms
int components[MAX];//identifies the components
int indegree[MAX];//in degree of a vertex
int outDegree[MAX];//out degree of a vertex 
int clockTime;//keeps a clock for dfs

void   calculateDegree(graph *);//calculates degree as the name says
void   calculateDegree_helper(graph *, int);//helper method for calculateDegree
bool   addEdge(graph *, const char *, const char *, double);//adds edge
void   initializeGraph(graph *);//initializes graph
graph  *copy_Graph(graph *);//copies graph 
graph  *transpose_Graph(graph *);//transpose of a graph
void   display_Vertex(const graph *, const vertex *);//display vertices adjacent to the current vertex
vertex *find_Vertex(graph *, const char *);//returns a vertex
void   initializeDFS();//initializes elements used in dfs
int    get_Vertex(graph *, const char *);//returns index to a vertex
void   clear_Graph(graph *);//returns memory the graph occupies
void   display_Graph(const graph *); 
deque  *acyclic(graph *);//returns whether a graph contains a cycle
deque  *acyclic_Visit(graph *, int, bool *);//acyclic helper method 
deque  *topologicalSort(graph *);//returns topolgical order of graph , otherwise null
void   topological_Visit(graph *, int, deque *);//topological sort helper method
deque  *topologicalSort2(graph *);//uses an alternative algorithm for topological order
void   breadth_First(graph *, int);//breadth first search
void   depth_First(graph *);//depth first search
void   dfs_Initialize(graph *);//initialize for depth first or breadth first search 
void   depth_First_Visit(graph *, int);//depth first search 
bool   bipartite(graph *);//checks if the graph is bipartite
void   bipartite_helper(graph *, int, int *, bool *);//helper function for bipartite function 
void   connectedComponents(graph *);//outputs the connected components
void   connectedComponents_helper(graph *, int, int);//connected components helper 
bool   connected(graph *);//outputs true upon connected graph, otherwise false
int    connected_helper(graph *, int);//helper function for connected
void   strongly_Connected(graph *);//outputs the strongly connected components
deque  *findsPath(graph *, const char *, const char *);//finds a path from source to destination
deque  *getPath(int, int);//to be called after a breadth first search or shortest path algorithm such as dijkstra or bellman ford
void   dijsktra(graph *, const char *);//outputs the shortest path in the graph
void   bellman_Ford(graph *, const char *);//outputs the shortest path
void   relax(int, int, double);//relaxation
void   initializeShortest(graph *, int);//initializes graph for shortest path 
void   longest_Path(graph *, const char *);//longest path
deque  *cpm(graph *);//finds the critical path
#endif
