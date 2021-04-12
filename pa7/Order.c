/*
Name: Moises Perez
CruzID: mperez86
Assignment: pa7
*/
//Code take from pa6 for re use. 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dictionary.h"

#define MAX_LEN 200

int main(int argc, char* argv[]) {

    int line_count = 0;
    int counter = 0;
    FILE* in, * out;
    char strLine[MAX_LEN];
    char** key;
    Dictionary D = newDictionary(0);

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

    key = (char**)malloc(sizeof(char*) * line_count);

    while (counter < line_count) {
        fgets(strLine, MAX_LEN, in);
        key[counter] = (char*)malloc(sizeof(char) * MAX_LEN);
        strcat(strLine, "\0");
        strcpy(key[counter], strLine);
        insert(D, &key[counter][0], VAL_UNDEF);
        counter++;
    }

    fprintf(out, "******************************************************\n");
    fprintf(out, "PRE-ORDER:\n");
    fprintf(out, "******************************************************\n");
    printDictionary(out, D, "pre");

    fprintf(out, "******************************************************\n");
    fprintf(out, "IN-ORDER:\n");
    fprintf(out, "******************************************************\n");
    printDictionary(out, D, "in");

    fprintf(out, "******************************************************\n");
    fprintf(out, "POST-ORDER:\n");
    fprintf(out, "******************************************************\n");
    printDictionary(out, D, "post");

    freeDictionary(&D);
    for (int i = 0; i < line_count; i++) {
        free(key[i]);
    }
    //freeDictionary(&D);
    free(key);
    fclose(in);
    fclose(out);
    return 0;
}

