/*
Name: Moises Perez
CruzID: mperez86
Assignment: pa4

FindComponents.c will do the following:
• Read the input file.
• Assemble a graph object 𝐺 using newGraph() and addArc().
• Print the adjacency list representation of G to the output file.
• Run DFS on 𝐺 and 𝐺 of 𝑇, processing the vertices in the second call by decreasing finish times from the first call.
• Determine the strong components of 𝐺.
• Print the strong components of 𝐺 to the output file in topologically sorted order.


*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[]) {

    FILE* in, * out;

    //Check that there are two command line arguments (other than the program name Lex)
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    // open files for reading and writing 
    in = fopen(argv[1], "r");
    if (in == NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    out = fopen(argv[2], "w");
    if (out == NULL) {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }
    //The first part will begin with a line consisting of a single integer n
    //giving the number of vertices in the graph.
    int sizeOfGraph = 0;
    fscanf(in, "%d", &sizeOfGraph);

    Graph G = newGraph(sizeOfGraph);

    //• Assemble a graph object 𝐺 using newGraph() and addArc().

    List temp = newList();
    for (int i = 1; i <= getOrder(G); i++) {
        append(temp, i);
    }


    int num1;
    int num2;
    fscanf(in, "%d", &num1);
    fscanf(in, "%d", &num2);


    while (num1 != 0 && num2 != 0) {
        addArc(G, num1, num2);
        fscanf(in, "%d", &num1);
        fscanf(in, "%d", &num2);
    }
    //• Print the adjacency list representation of G to the output file.

    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);

    //• Run DFS on 𝐺 and 𝐺 of 𝑇, processing the vertices in the second call by decreasing finish times from the first call.

    DFS(G, temp);
    Graph GTrans = transpose(G);
    DFS(GTrans, temp);

    //• Determine the strong components of 𝐺.

    int StrongCC = 0;
    moveFront(temp);
    while (index(temp) != -1) {
        if (getParent(GTrans, get(temp)) == NIL)
            StrongCC++;
        moveNext(temp);
    }

    fprintf(out, "G contains %d strongly connected components:", StrongCC);

    //• Print the strong components of 𝐺 to the output file in topologically sorted order.

    moveBack(temp);
    int count = 1;
    while (count != getOrder(G)) {
        List Components = newList();
        while (getParent(GTrans, get(temp)) != NIL) {
            prepend(Components, get(temp));
            movePrev(temp);
        }
        prepend(Components, get(temp));

        fprintf(out, "\nComponent %d: ", count);
        printList(out, Components);
        freeList(&Components);
        movePrev(temp);
        count++;
    }
    //Free everything
    freeList(&temp);
    freeGraph(&G);
    freeGraph(&GTrans);
    fclose(in);
    fclose(out);
    return 0;
}


