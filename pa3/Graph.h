/*
Name: Moises Perez
CruzID: mperez86
Assignment: pa3
*/

#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_
#include "List.h"

#define INF -1
#define NIL 0

typedef struct GraphObj* Graph;
/*** Constructors-Destructors ***/
//Function newGraph() returns a Graph pointing to a newly created GraphObj 
//representing a graph having n vertices and no edges
Graph newGraph(int n);
//Function freeGraph() frees all dynamic memory associated with the Graph
//* pG, then sets the handle* pG to NULL.
void freeGraph(Graph* pG);

/*** Access functions ***/
//Functions getOrder() and getSize() return the corresponding field values,
int getOrder(Graph G);
//Functions getOrder() and getSize() return the corresponding field values,
int getSize(Graph G);
//getSource() returns the source vertex most recently used in function BFS(), or NIL if
//BFS() has not yet been called.
int getSource(Graph G);
//Function getParent() will return the parent of vertex u in the BreadthFirst tree 
//created by BFS(), or NIL if BFS() has not yet been called.
int getParent(Graph G, int u);
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
//addEdge() inserts a new edge joining u to v, i.e.u is added to the adjacency 
//List of v, and v to the adjacency List of u.
void addEdge(Graph G, int u, int v);
//addArc() inserts a new directed edge from u to v, i.e.v is added to the adjacency 
//List of u(but not u to the adjacency List of v).Both addEdge() and addArc() have 
//the precondition that their two int arguments must lie in the range 1 to getOrder(G)
void addArc(Graph G, int u, int v);
//Function BFS() runs the BFS algorithm on the Graph G with source s,
//setting the color, distance, parent,and source fields of G accordingly.
void BFS(Graph G, int s);

/*** Other operations ***/
//Finally, function printGraph() prints the adjacency list representation 
//of G to the file pointed to by out.The format of this representation should match the above examples, so all that is required by the client is a single call to printGraph().
void printGraph(FILE* out, Graph G);

#endif