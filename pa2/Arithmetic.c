/*
Name: Moises Perez
CruzID: mperez86
Assignment: pa2

*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"BigInteger.h"

#define MAX_LEN 10000

int main(int argc, char* argv[]) {

    FILE* in, * out;
    int line_count = 0;
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
    //We need to fget the lines but only every other line
    //We need big integers for our testing and then at then end of the file we need to free them
    BigInteger A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R;
    int counter = 0;
    //Allows us to get the lines we want
    while (fgets(strLine, MAX_LEN, in) != NULL) {
        if (counter == 1)
            A = stringToBigInteger(strLine);
        else if (counter == 3)
            B = stringToBigInteger(strLine);
        counter++;
    }
    //printing to see if they have values A, B
    printBigInteger(out, A);
    fprintf(out, "\n");
    printBigInteger(out, B);
    fprintf(out, "\n");

    //A + B
    C = sum(A, B);
    printBigInteger(out, C);
    fprintf(out, "\n");

    // A - B, A - A
    D = diff(A, B);
    printBigInteger(out, C);
    fprintf(out, "\n");
    E = diff(A, A);
    printBigInteger(out, C);
    fprintf(out, "\n");

    //3A - 2B
    F = stringToBigInteger("3");
    G = prod(A, F);
    H = stringToBigInteger("2");
    I = prod(B, H);
    J = diff(G, I);
    printBigInteger(out, J);
    fprintf(out, "\n");

    //AB, A^2, B^2
    E = prod(A, B);
    printBigInteger(out, E);
    fprintf(out, "\n");
    D = prod(B, B);
    printBigInteger(out, D);
    fprintf(out, "\n");
    C = prod(A, A);
    printBigInteger(out, C);
    fprintf(out, "\n");


    //9A^4 + 16B^5 klmnopqr
    L = stringToBigInteger("9");
    M = stringToBigInteger("16");
    K = prod(C, C);
    N = prod(L, K);
    O = prod(D, D);
    P = prod(O, B);
    Q = prod(M, P);
    R = sum(N, Q);
    printBigInteger(out, R);
    fprintf(out, "\n");

    //Free the Bigintegers
    freeBigInteger(&A);
    freeBigInteger(&B);
    freeBigInteger(&C);
    freeBigInteger(&D);
    freeBigInteger(&E);
    freeBigInteger(&F);
    freeBigInteger(&G);
    freeBigInteger(&H);
    freeBigInteger(&I);
    freeBigInteger(&J);
    freeBigInteger(&K);
    freeBigInteger(&L);
    freeBigInteger(&M);
    freeBigInteger(&N);
    freeBigInteger(&O);
    freeBigInteger(&P);
    freeBigInteger(&Q);
    freeBigInteger(&R);

    //Close both the in and out for the file
    fclose(in);
    fclose(out);

    return(0);
}

