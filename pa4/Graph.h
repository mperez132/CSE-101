/*
Name: Moises Perez
CruzID: mperez86
Assignment: pa4
*/

#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_
#include "List.h"

#define UNDEF -2
#define INF -1
#define NIL 0

typedef struct GraphObj* Graph;
/*** Constructors-Destructors ***/
//Function newGraph() will return a reference to a new graph object containing n vertices and no edges.
Graph newGraph(int n);
//freeGraph() frees all heap memory associated with a graph and sets its Graph argument to NULL.
void freeGraph(Graph* pG);

/*** Access functions ***/
//Function getOrder() returns the number of vertices in �
int getOrder(Graph G);
//Functions getOrder() and getSize() return the corresponding field values,
int getSize(Graph G);
//getSource() returns the source vertex most recently used in function BFS(), or NIL if
//BFS() has not yet been called.
int getSource(Graph G);

//while functions getParent(), getDiscover(), and getFinish() return the appropriate field values for the given vertex.
//Note that the parent of a vertex may be NIL.
//The discover and finish times of vertices will be undefined before DFS is called.
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);
//Function getDist() returns the distance from the most recent BFS 
//source to vertex u, or INF if BFS() has not yet been called.
int getDist(Graph G, int u);
//Function getPath() appends to the List L the vertices of a shortest path 
//in G from source to u, or appends to L the value NIL if no such path exists.
void getPath(List L, Graph G, int u);


/*** Manipulation procedures ***/
//Function makeNull() deletes all edges of G, restoring it to its original 
//(no edge) state. (This is called a null graph in graph theory literature).
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
//Function BFS() runs the BFS algorithm on the Graph G with source s,
//setting the color, distance, parent,and source fields of G accordingly.
void BFS(Graph G, int s);
void DFS(Graph G, List s);

/*** Other operations ***/
//Finally, function printGraph() prints the adjacency list representation 
//of G to the file pointed to by out.The format of this representation should match the above examples, so all that is required by the client is a single call to printGraph().
void printGraph(FILE* out, Graph G);
/*
Function transpose() returns a reference to a new graph object representing the transpose of G, and
copyGraph() returns a reference to a new graph that is a copy of G. Both transpose() and copyGraph()
could be considered constructors since they create new graph objects.
*/
Graph transpose(Graph G);
Graph copyGraph(Graph G);

#endif