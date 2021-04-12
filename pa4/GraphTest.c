/*
Name: Moises Perez
CruzID: mperez86
Assignment: pa4
*/
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[]) {

   //Create new graph G
    Graph G = newGraph(10);
    printf("Order of G: %d\n", getOrder(G));
    addArc(G, 8, 8);
    addArc(G, 7, 4);
    addArc(G, 1, 2);
    addArc(G, 2, 3);
    addArc(G, 2, 6);
    addArc(G, 4, 3);
    addArc(G, 5, 1);
    addArc(G, 3, 7);
    addArc(G, 6, 7);
    addArc(G, 3, 4);

    Graph A = transpose(G);
    printf("Order of G: %d\n", getOrder(G));

    List temp1 = newList();
    List temp2 = newList();
    for (int i = 1; i <= getOrder(A); i++) {
        append(temp1, i);
        append(temp2, i);
    }

    DFS(G, temp1);
    DFS(A, temp2);
    printList(stdout, temp1);
    printf("\n\n");
    printList(stdout, temp2);
    printf("\n\n");

    return 0;
}