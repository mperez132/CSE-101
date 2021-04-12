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

int main(int argc, char* argv[]) {

    //We need to create out BigInteger to test our functions from the .c
    BigInteger A, B, C, D, E;

    //Give the BigIntegers values
    //Test our function stringToBiginter(char* s)
    A = stringToBigInteger("0098342");
    B = stringToBigInteger("-098342");
    C = stringToBigInteger("0");
    D = stringToBigInteger("+123456789");
    E = stringToBigInteger("-1234");

    //Test that they have values
    printBigInteger(stdout, A);
    printBigInteger(stdout, B);
    printBigInteger(stdout, C);
    printBigInteger(stdout, D);
    printBigInteger(stdout, E);

    //Test our function compare()
    //Create integer to hold the value of our compare function so we know our result
    int valueOfCompare = compare(A, B);
    if (valueOfCompare == 1) {
        printf("A > B\n");
    }
    else if (valueOfCompare == -1) {
        printf("A < B\n");
    }
    else
        printf("A = B\n");

    //Test our function copy(Biginteger N)
    printf("------------------------------------------\n");
    C = copy(E);
    printBigInteger(stdout, C);

    //Test our function add/sum
    printf("------------------------------------------\n");
    C = sum(A, B);
    printBigInteger(stdout, C);
    printf("\n");
    D = sum(A, B);
    printBigInteger(stdout, D);
    printf("\n");
    add(D, B, A);
    printBigInteger(stdout, D);
    printf("\n");

    //Test our function subtract/diff
    printf("------------------------------------------\n");
    C = diff(A, B);
    printBigInteger(stdout, C);
    printf("\n");
    D = diff(B, A);
    printBigInteger(stdout, D);
    printf("\n");
    subtract(D, A, B);
    printBigInteger(stdout, D);
    printf("\n");

    //Test our function multiply/prod
    printf("------------------------------------------\n");
    C = prod(A, B);
    printBigInteger(stdout, C);
    printf("\n");
    D = prod(E, B);
    printBigInteger(stdout, D);
    printf("\n");
    multiply(C, E, B);
    printBigInteger(stdout, C);
    printf("\n");

    //Free our BigInteger functions 
    freeBigInteger(&A);
    freeBigInteger(&B);
    freeBigInteger(&C);
    freeBigInteger(&D);
    freeBigInteger(&E);

    return 0;
}