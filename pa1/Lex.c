/*
Name: Moises Perez
CruzID: mperez86
Assignment: pa1


Our goal in this project is to build an Integer List ADT in C and use it to alphabetize the lines in a file. This ADT
module will also be used (with some modifications) in future programming assignments, so you should test it
thoroughly, even though not all of its features will be used here. Begin by reading the handout ADT.pdf posted
on the class webpage for a thorough explanation of the programming practices and conventions required in this
class for implementing ADTs in C.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"

#define MAX_LEN 200

int main(int argc, char* argv[]) {

    int line_count = 0;
    int counter = 0;
    FILE* in, * out;
    char strLine[MAX_LEN];

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

    //Count the number of lines n in the input file
    while (fgets(strLine, MAX_LEN, in) != NULL) {
        line_count++;
    }

    //fclose(in);
    //in = fopen(argv[1], "r");
    rewind(in);
    char* strArray[line_count];
    List strList = newList();

    //Dynamically allocate array
    //begin with an initially empty List, then insert the indices of
    //the array one by one into the appropriate positions of the List.
    for (int i = 0; i < line_count; i++) {
        fgets(strLine, MAX_LEN, in);
        strArray[i] = (char*)malloc(sizeof(strLine));
        strcpy(strArray[i], strLine);
    }
    //You may use only the List ADT operations defined below to manipulate the List. 
    //Note that the C standard library string.h provides a function called strcmp() that 
    //determines the lexicographic ordering of two Strings
    /*
     If s1 and s2 are strings then :
    strcmp(s1, s2) < 0 is true ifand only if s1 comes before s2
    strcmp(s1, s2) > 0 is true ifand only if s1 comes after s2
    strcmp(s1, s2) == 0 is true ifand only if s1 is identical to s2

    Note that at no time is the array ever sorted.
    Instead you are indirectly sorting the array by building a List of indices in a certain order.
    */

    //Sort for lexicographic 
    append(strList, 0);
    for (int i = 1; i < line_count; i++) {
        moveFront(strList);
        while (index(strList) != -1) {
            if (strcmp(strArray[i], strArray[get(strList)]) < 0) {
                insertBefore(strList, i);
                break;
            }
            else if (strcmp(strArray[i], strArray[get(strList)]) > 0)
                moveNext(strList);
        }
        if (index(strList) == -1)
            append(strList, i);
    }
    //Use the List constructed in (3) to print the array in alphabetical order to the output file
    moveFront(strList);
    while (index(strList) != -1) {

        fprintf(out, "%s", strArray[get(strList)]);
        moveNext(strList);
    }
    //Free array before exiting
    for (int i = 0; i < line_count; i++) {
        free(strArray[i]);
    }

    //Free list and close both our files
    freeList(&strList);
    fclose(in);
    fclose(out);

    return(0);
}