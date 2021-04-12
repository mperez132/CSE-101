    /*
    Name: Moises Perez
    CruzID: mperez86
    Assignment: pa3
    */

    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    #include"Graph.h"
    #include"List.h"
    /*
    The input file will be in two parts. The first part will begin with a line consisting of a single integer
    n
    giving the number of vertices in the graph. Each subsequent line will represent an edge by a pair of distinct
    numbers in the range 1 to n, separated by a space. These numbers are the end vertices of the corresponding
    edge. The first part of the input file defines the graph, and will be terminated by a dummy line containing
    “0 0”. After these lines are read your program will print the adjacency list representation of the graph to
    the output file.


    The second part of the input file will consist of a number of lines, each consisting of a pair of integers in
    the range 1 to n, separated by a space. Each line specifies a pair of vertices in the graph; a starting point
    (source) and a destination. The second part of the input will also be terminated by the dummy line “0 0”.


    Your program’s operation can be broken down into two basic steps, corresponding to the two groups of
    input data.
    1. Read and store the graph and print out its adjacency list representation.
    2. Enter a loop that processes the second part of the input. Each iteration of the loop should read in one
    pair of vertices (source, destination), run BFS on the source vertex, print the distance to the destination
    vertex, then find and print the resulting shortest path, if it exists, or print a message if no path from
    source to destination exists

    */
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
    //giving the number of vertices in the graph.Each subsequent line will represent an edge by a pair of distinct
    //numbers in the range 1 to n, separated by a space.

    int sizeOfGraph = 0;
    fscanf(in, "%d", &sizeOfGraph);

    Graph G = newGraph(sizeOfGraph);

    int num1;
    int num2; 
    fscanf(in, "%d", &num1);
    fscanf(in, "%d", &num2);

    
    while (num1 != 0 && num2 != 0) {
        addEdge(G, num1, num2);
        fscanf(in, "%d", &num1);
        fscanf(in, "%d", &num2);
    }
    //Print
    printGraph(out, G);
    /*
    The second part of the input file will consist of a number of lines, each consisting of a pair of integers in
    the range 1 to n, separated by a space. Each line specifies a pair of vertices in the graph; a starting point
    (source) and a destination. The second part of the input will also be terminated by the dummy line “0 0”.
    */
    num1 = 0;
    num2 = 0;

    fscanf(in, "%d", &num1);
    fscanf(in, "%d", &num2);

    while (num1 != 0 && num2 != 0) {
        BFS(G, num1);
        List foundPath = newList();
        getPath(foundPath, G, num2);
        if (getDist(G, num2) != INF) {
            fprintf(out, "The distance from %d to %d is %d\n", num1, num2, getDist(G, num2));
            fprintf(out, "A shortest %d-%d path is:", num1, num2);
            printList(out, foundPath);
            fprintf(out, "\n");
        }
        else {
            fprintf(out, "The distance from %d to %d is infinity\n", num1, num2);
            fprintf(out, "No %d-%d path exists\n", num1, num2);
            fprintf(out, "\n");
        }
        fscanf(in, "%d", &num1);
        fscanf(in, "%d", &num2);
        freeList(&foundPath);
    }
    freeGraph(&G);
    fclose(in);
    fclose(out);

    return 0;
    }