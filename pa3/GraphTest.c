/*
Name: Moises Perez
CruzID: mperez86
Assignment: pa3
*/
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]) {

    //Tester for our functions 
    int size = 5;
    Graph A = newGraph(size);
    printf("TEST GRAPH A FOR getSize() and addEdge()------------------------\n");

    addEdge(A, 1, 5);
    addEdge(A, 1, 2);
    addEdge(A, 1, 4);
    addEdge(A, 4, 5);
    addEdge(A, 5, 3);

    printf("Graph A getSize(): \n");
    printf("Expecting 5\n");
    printf("getSize(): %d\n\n", getSize(A));
    printf("addEdge expected output: \n");
    printf("1: 2 4 5\n");
    printf("2: 1\n");
    printf("3: 5\n");
    printf("4: 1 5\n");
    printf("5: 1 3 4\n\n");
    printf("REAL OUPUT\n");
    printGraph(stdout, A);
    printf("\n\n");


    Graph B = newGraph(size);
    printf("TEST GRAPH B FOR getSize() and addArc()------------------------\n");
    addArc(B, 2, 5);
    addArc(B, 2, 2);
    addArc(B, 2, 4);
    addArc(B, 4, 5);
    addArc(B, 5, 3);
    printf("Graph A getSize(): \n");
    printf("Expecting 5\n");
    printf("getSize(): %d\n\n", getSize(B));
    printGraph(stdout, B);
    printf("\n\n");


    printf("TEST for makeNull() on graph B------------------------\n");
    printf("Order of B: %d\n", getOrder(B));
    printf("getSize(): %d\n\n", getSize(B));
    makeNull(B);
    printf("Order of B: %d\n", getOrder(B));
    printf("getSize(): %d\n\n", getSize(B));
    printGraph(stdout, B);
    printf("\n\n");


    printf("TEST findPath() on graph A------------------------\n");
    printf("Graph A getSize(): \n");
    printf("getSize(): %d\n\n", getSize(A));

    BFS(A, 1);
    List temp = newList();
    getPath(temp, A, 3);
    printf("Path Expected: 1 5 3\n");
    printf("Path: ");
    printList(stdout, temp);
    printf("\n\n");

    freeList(&temp);
    freeGraph(&A);
    freeGraph(&B);

    return(0);
}