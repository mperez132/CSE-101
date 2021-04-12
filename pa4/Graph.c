/*
Name: Moises Perez
CruzID: mperez86
Assignment: pa4
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "List.h"

typedef struct GraphObj {

    int Order; //Vertices call the "order" of the graph
    int Size; //Edges called the "size" of the graph
    int Source; //The label of the vertex that was most recently used as "source" for BFS.


    int* Parent;
    int* Color;
    int* Discover;
    int* Distance;
    int* Finish;

    List* GraphList;
}GraphObj;

//Function newGraph() returns a Graph pointing to a newly created GraphObj 
//representing a graph having n vertices and no edges
Graph newGraph(int n)
{
    Graph GraphArray = malloc(sizeof(GraphObj));

    GraphArray->Order = n; //where n is the number of vertices in the graph
    GraphArray->Size = 0; //
    GraphArray->Source = NIL; //An undefined vertex label


    //It is recommended that all arrays be of length 𝑛 + 1, where 𝑛 is 
    //the number of vertices in the graph, and that only indices 1 through n be used.
    GraphArray->Parent = malloc((n + 1) * sizeof(int));
    GraphArray->Distance = malloc((n + 1) * sizeof(int));
    GraphArray->Color = malloc((n + 1) * sizeof(int));
    GraphArray->Discover = malloc((n + 1) * sizeof(int));
    GraphArray->Finish = malloc((n + 1) * sizeof(int));
    GraphArray->GraphList = malloc((n + 1) * sizeof(List*));

    //By defualt, colors need to be set to white
    //Parents needs to be set to NIL
    //Distance needs to be set to INF
    //and create a new list for the size of n
    for (int i = 1; i <= n; i++) {
        GraphArray->GraphList[i] = newList();
        //COLORS: white = 0, grey = 1, and black = 2
        GraphArray->Color[i] = 0;
        GraphArray->Parent[i] = NIL;
        GraphArray->Distance[i] = INF;
        GraphArray->Discover[i] = UNDEF;
        GraphArray->Finish[i] = UNDEF;
    }
    return GraphArray;
}
//Function freeGraph() frees all dynamic memory associated with the Graph
//* pG, then sets the handle* pG to NULL.
void freeGraph(Graph* pG)
{
    if (pG != NULL && *pG != NULL) {
        for (int i = 1; i <= getOrder(*pG); i++) {
            freeList(&((*pG)->GraphList[i]));
        }
        free((*pG)->GraphList);
        free((*pG)->Color);
        free((*pG)->Parent);
        free((*pG)->Discover);
        free((*pG)->Finish);
        free((*pG)->Distance);
        free(*pG);
        *pG = NULL;
    }
}

int getOrder(Graph G)
{
    if (G == NULL) {
        printf("Graph Error: calling getOrder() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return (G->Order);
}

int getSize(Graph G)
{
    if (G == NULL) {
        printf("Graph Error: calling getSize() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return (G->Size);
}
//getSource() returns the source vertex most recently used in function BFS(), or NIL if
//BFS() has not yet been called.
int getSource(Graph G)
{
    if (G == NULL) {
        printf("Graph Error: calling getSource() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return (G->Source);
}

int getParent(Graph G, int u)
{
    if (G == NULL) {
        printf("Graph Error: calling getParent() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (1 > u || u > getOrder(G)) {
        printf("Graph Error: calling getParent() failing precondition 1 <= u <= getParent(G). \n");
        exit(EXIT_FAILURE);
    }
    return (G->Parent[u]);
}
//Function getDist() returns the distance from the most recent BFS 
//source to vertex u, or INF if BFS() has not yet been called.
//the precondition 1 <= u <= getOrder(G).
int getDist(Graph G, int u)
{
    if (G == NULL) {
        printf("Graph Error: calling getDist() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (1 > u || u > getOrder(G)) {
        printf("Graph Error: calling getDist() failing precondition 1 <= u <= getDist(G). \n");
        exit(EXIT_FAILURE);
    }
    if (G->Source == NIL) {
        return INF;
    }
    return (G->Distance[u]);
}
int getDiscover(Graph G, int u)
{
    if (G == NULL) {
        printf("Graph Error: calling getDiscover() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (1 > u || u > getOrder(G)) {
        printf("Graph Error: calling getDiscover() failing precondition 1 <= u <= getParent(G). \n");
        exit(EXIT_FAILURE);
    }
    return (G->Discover[u]);
}
int getFinish(Graph G, int u)
{
    if (G == NULL) {
        printf("Graph Error: calling getFinish() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (1 > u || u > getOrder(G)) {
        printf("Graph Error: calling getFinish() failing precondition 1 <= u <= getParent(G). \n");
        exit(EXIT_FAILURE);
    }

    return (G->Finish[u]);
}
//Function getPath() appends to the List L the vertices of a shortest path 
//in G from source to u, or appends to L the value NIL if no such path exists.
//the precondition 1 <= u <= getOrder(G).
void getPath(List L, Graph G, int u)
{
    if (G == NULL) {
        printf("Graph Error: calling getPath() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (L == NULL) {
        printf("List Error: calling getPath() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (1 > u || u > getOrder(G)) {
        printf("Graph Error: calling getPath() failing precondition 1 <= u <= getOrder(G). \n");
        exit(EXIT_FAILURE);
    }
    if (getSource(G) == 0) {
        printf("Graph Error: calling getPath() on NIL source. \n");
        exit(EXIT_FAILURE);
    }
    //Given from the example algorithm
    if (u == G->Source) {
        append(L, u);
    }
    else if (G->Distance[u] < 0) {
        append(L, NIL);
    }
    else {
        getPath(L, G, getParent(G, u));
        append(L, u);
    }

}
//Function makeNull() deletes all edges of G, restoring it to its original 
//(no edge) state. (This is called a null graph in graph theory literature).
void makeNull(Graph G)
{
    if (G == NULL) {
        printf("Graph Error: calling makeNull() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= getOrder(G); i++) {
        G->Color[i] = 0;
        G->Parent[i] = NIL;
        G->Distance[i] = INF;
        clear(G->GraphList[i]);
    }
    G->Size = 0;
    G->Source = NIL;
}

//addEdge() inserts a new edge joining u to v, i.e.u is added to the adjacency 
//List of v, and v to the adjacency List of u.
void addEdge(Graph G, int u, int v)
{
    if (G == NULL) {
        printf("Graph Error: calling addEdge() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (1 > u || u > getOrder(G)) {
        printf("Graph Error: calling addEdge() failing precondition 1 <= u <= addOrder(G). \n");
        exit(EXIT_FAILURE);
    }
    if (1 > v || v > getOrder(G)) {
        printf("Graph Error: calling addEdge() failing precondition 1 <= v <= addOrder(G). \n");
        exit(EXIT_FAILURE);
    }
    //joining u to v, i.e.u is added to the adjacency List of v, and v to the adjacency List of u.

    addArc(G, u, v);

    moveFront(G->GraphList[v]);
    if (index(G->GraphList[v]) != -1) {
        while (index(G->GraphList[v]) != -1 && get(G->GraphList[v]) < u) {
            moveNext(G->GraphList[v]);
        }
        if (index(G->GraphList[v]) == -1) {
            append(G->GraphList[v], u);
            //G->Size++;
        }
        else if (get(G->GraphList[v]) > u) {
            insertBefore(G->GraphList[v], u);
            //G->Size++;
        }
    }
    else {
        append(G->GraphList[v], u);
        //G->Size++;
    }
}

//addArc() inserts a new directed edge from u to v, i.e.v is added to the adjacency 
//List of u(but not u to the adjacency List of v).Both addEdge() and addArc() have 
//the precondition that their two int arguments must lie in the range 1 to getOrder(G)
void addArc(Graph G, int u, int v)
{
    if (G == NULL) {
        printf("Graph Error: calling addArc() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (1 > u || u > getOrder(G)) {
        printf("Graph Error: calling addArc() failing precondition 1 <= u <= addOrder(G). \n");
        exit(EXIT_FAILURE);
    }
    if (1 > v || v > getOrder(G)) {
        printf("Graph Error: calling addArc() failing precondition 1 <= v <= addOrder(G). \n");
        exit(EXIT_FAILURE);
    }
    moveFront(G->GraphList[u]);
    if (index(G->GraphList[u]) != -1) {
        while (index(G->GraphList[u]) != -1 && get(G->GraphList[u]) < v) {
            moveNext(G->GraphList[u]);
        }
        if (index(G->GraphList[u]) == -1) {
            append(G->GraphList[u], v);
            G->Size++;
        }
        else if (get(G->GraphList[u]) > v){
            insertBefore(G->GraphList[u], v);
            G->Size++;
        }
    }
    else {
        append(G->GraphList[u], v);
        G->Size++;
    }
}
//Function BFS() runs the BFS algorithm on the Graph G with source s,
//setting the color, distance, parent,and source fields of G accordingly.
//BFS(𝐺, 𝑠)
//1. for 𝑥 ∈ V(G) − { s }
//2. color[𝑥] = white
//3. 𝑑[𝑥] = ∞
//4. 𝑝[𝑥] = nil
//5. color[𝑠] = gray // discover the source 𝑠
//6. 𝑑[𝑠] = 0
//7. 𝑝[𝑠] = nil
//8. 𝑄 = ∅ // construct a new empty queue
//9. Enqueue(𝑄, 𝑠)
//10. while 𝑄 ≠ ∅
//11. 𝑥 = Dequeue(𝑄)
//12. for 𝑦 ∈ adj[𝑥]
//13. if color[𝑦] == white // 𝑦 is undiscovered
//14. color[𝑦] = gray // discover 𝑦
//15. 𝑑[𝑦] = 𝑑[𝑥] + 1
//16. 𝑝[𝑦] = 𝑥
//17. Enqueue(𝑄, 𝑦)
//18. color[𝑥] = black // finish �
void BFS(Graph G, int s)
{
    if (G == NULL) {
        printf("Graph Error: calling BFS() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (1 > s || s > getOrder(G)) {
        printf("Graph Error: calling BFS() failing precondition 1 <= u <= addOrder(G). \n");
        exit(EXIT_FAILURE);
    }
    G->Source = s;
    for (int i = 1; i <= getOrder(G); i++) {
        //COLORS: white = 0, grey = 1, and black = 2
        G->Color[i] = 0;
        G->Parent[i] = NIL;
        G->Distance[i] = INF;
    }
    G->Color[s] = 1;
    G->Distance[s] = 0;
    G->Parent[s] = NIL;

    List Q = newList();
    append(Q, s);
    moveFront(Q);

    while (length(Q) != 0) {
        int x = front(Q);
        moveFront(G->GraphList[x]);
        while (index(G->GraphList[x]) != -1) {

            int y = get(G->GraphList[x]);
            if (G->Color[y] == 0) {
                G->Color[y] = 1;
                G->Distance[y] = G->Distance[x] + 1;
                G->Parent[y] = x;
                append(Q, y);
            }
            moveNext(G->GraphList[x]);
        }
        G->Color[x] = 2;
        deleteFront(Q);
    }
    freeList(&Q);
}

/*
Visit(𝑥)
1. 𝑑[𝑥] = (+ + time) // discover 𝑥
2. color[𝑥] = gray
3. for all 𝑦 ∈ adj[𝑥]
4. if color[𝑦] == white
5. 𝑝[𝑦] = 𝑥
6. Visit(𝑦)
7. color[𝑥] = black
8. 𝑓[𝑥] = (+ + time) // finish �
*/
void Visit(Graph G, int u, int* time, List s) {
    if (G == NULL) {
        printf("Graph Error: calling Visit() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (s == NULL) {
        printf("List Error: calling Visit() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    G->Discover[u] = ++(*time);
    G->Color[u] = 1; //gray

    moveFront(G->GraphList[u]);

    while (index(G->GraphList[u]) != -1) {

        if (G->Color[get(G->GraphList[u])] == 0) {
            G->Parent[get(G->GraphList[u])] = u;
            Visit(G, get(G->GraphList[u]), time, s);
        }
        moveNext(G->GraphList[u]);
    }
    G->Color[u] = 2;
    G->Finish[u] = ++(*time);
    prepend(s, u);
}
/*
DFS(𝐺)
1. for all 𝑥 ∈ 𝑉(𝐺)
2. color[𝑥] = white
3. 𝑝[𝑥] = nil
4. time = 0
5. for all 𝑥 ∈ 𝑉(𝐺)
6. if color[𝑥] == white
7. Visit(𝑥)
*/
void DFS(Graph G, List s)
{
    if (G == NULL) {
        printf("Graph Error: calling DFS() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (s == NULL) {
        printf("List Error: calling DFS() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(s) != getOrder(G))
    {
        printf("DFS Error: calling DFS() with a failing precondiiton\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= getOrder(G); i++) {
        G->Color[i] = 0;
        G->Parent[i] = NIL;
        G->Discover[i] = UNDEF;
        G->Finish[i] = UNDEF;
    }

    int time = 0;
    List copy = copyList(s);
    clear(s);

    moveFront(copy);
    while (index(copy) != -1) {
        if (G->Color[get(copy)] == 0) {
            Visit(G, get(copy), &time, s);
        }
        moveNext(copy);
    }
    freeList(&copy);
}

//Finally, function printGraph() prints the adjacency list representation 
//of G to the file pointed to by out.The format of this representation should match the above examples, so all that is required by the client is a single call to printGraph().
void printGraph(FILE* out, Graph G)
{
    if (G == NULL) {
        printf("Graph Error: calling printGraph() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= getOrder(G); i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->GraphList[i]);
        fprintf(out, "\n");
    }
}

Graph transpose(Graph G)
{
    if (G == NULL) {
        printf("Graph Error: calling transpose() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    Graph GTrans = newGraph(getOrder(G));
    for (int i = 1; i <= getOrder(G); i++) {
        moveFront(G->GraphList[i]);
        while (index(G->GraphList[i]) != -1) {
            addArc(GTrans, get(G->GraphList[i]), i);
            moveNext(G->GraphList[i]);
        }
    }
    GTrans->Order = getOrder(G);
    return GTrans;
}

Graph copyGraph(Graph G)
{
    if (G == NULL) {
        printf("Graph Error: calling copyGraph() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    Graph GCopy = newGraph(getOrder(G));
    for (int i = 1; i <= getOrder(G); i++) {
        moveFront(G->GraphList[i]);
        while (index(G->GraphList[i]) != -1) {
            addArc(GCopy, i, get(G->GraphList[i]));
            moveNext(G->GraphList[i]);
        }
    }
    GCopy->Order = getOrder(G);
    return GCopy;
}

