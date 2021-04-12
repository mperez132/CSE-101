/*
Name: Moises Perez
CruzID: mperez86
Assignment: pa2

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "List.h"
#include "BigInteger.h"

//It is recommended that BigInteger.c contain either global
//constants or #define constant macros for both BASE and POWER satisfying BASE = 10POWER.
//During your testing phase, you may have any value 0 ≤ POWER ≤ 9, but when you submit your project, be sure
//to set POWER = 9 and BASE = 1000000000, for proper grading.
#define POWER 9
#define BASE 1000000000

//Following our standard practice BigInteger.c will contain a typedef 
//for BigIntegerObjand BigInteger.h will define the reference type BigInteger as a pointer to BigIntegerObj.
//The BigIntegerObj should have at least two components : an int(1, -1 or 0) specifying the sign, and 
//a normalized List of longs specifying the magnitude. (Here "normalized" means each List element x is in the range 0 <= x < BASE.)

typedef struct BigIntegerObj {
    int sign;
    List LL;
}BigIntegerObj;

// Constructors-Destructors ---------------------------------------------------
// newBigInteger()
// Returns a reference to a new BigInteger object in the zero state.
BigInteger newBigInteger()
{
    BigInteger BI = malloc(sizeof(BigIntegerObj));
    BI->LL = newList();
    BI->sign = 0;
    return BI;
}
// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger* pN)
{
    if (pN != NULL && *pN != NULL) {
        BigInteger N = *pN;
        freeList(&N->LL);
        free(*pN);
        *pN = NULL;
    }
}

// Access functions -----------------------------------------------------------
// sign()
// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero
// state.
int sign(BigInteger N)
{
    if (N == NULL) {
        printf("BigInteger Error: calling sign() on NULL BigInteger\n");
        exit(EXIT_FAILURE);
    }
    return N->sign;
}
// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
//If we're to compare the 2 lists we need to check all 3 signs (neg, pos, and zero state)
//Another thing we have to check is if they're the same sign. If they're the same sign then we need to check length
int compare(BigInteger A, BigInteger B)
{
    if (A == NULL || B == NULL) {
        printf("BigInteger Error: calling compare() on NULL BigInteger\n");
        exit(EXIT_FAILURE);
    }
    if (A == B) {
        return 0;
    }
    else if (A->sign > B->sign) {
        return 1;
    }
    else if (A->sign < B->sign) {
        return -1;
    }
    if (A->sign == B->sign) {

        if (A->sign == 1) {
            if (length(A->LL) > length(B->LL)) {
                return 1;
            }
            if (length(A->LL) < length(B->LL)) {
                return -1;
            }
            if (equalsList(A->LL, B->LL) == 1) {
                return 0;
            }
            else {
                moveFront(A->LL);
                moveFront(B->LL);
                for (int i = 0; i < length(A->LL); i++) {
                    if (get(A->LL) > get(B->LL)) {
                        return 1;
                    }
                    if (get(A->LL) < get(B->LL)) {
                        return -1;
                    }
                    else {
                        moveNext(A->LL);
                        moveNext(B->LL);
                    }

                }
            }

        }
        if (A->sign == -1) {
            if (length(A->LL) > length(B->LL)) {
                return -1;
            }
            if (length(A->LL) < length(B->LL)) {
                return 1;
            }
            if (equalsList(A->LL, B->LL) == 1) {
                return 0;
            }
            else {
                moveFront(A->LL);
                moveFront(B->LL);
                for (int i = 0; i < length(A->LL); i++) {
                    if (get(A->LL) > get(B->LL)) {
                        return -1;
                    }
                    if (get(A->LL) < get(B->LL)) {
                        return 1;
                    }
                    else {
                        moveNext(A->LL);
                        moveNext(B->LL);
                    }

                }
            }
        }
        if (A->sign == 0) {
            return 0;
        }
    }
    return 0;
}


// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B)
{
    if (A == NULL || B == NULL) {
        printf("BigInteger Error: calling equals() on a NULL BigInteger reference\n");
        exit(EXIT_FAILURE);
    }
    if (compare(A, B) == 0) {
        return 1;
    }
    else
        return 0;
}

// Manipulation procedures ----------------------------------------------------
// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N)
{
    if (N == NULL) {
        printf("BigInteger Error: calling makeZero() on a NULL BigInteger reference\n");
        exit(EXIT_FAILURE);
    }
    /* if (length(N->LL) == 0) {
         printf("BigInteger Error: calling negate() on an empty BigInteger\n");
         exit(EXIT_FAILURE);
     }*/
    clear(N->LL);
    N->sign = 0;
}
// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger N)
{
    if (N == NULL) {
        printf("BigInteger Error: calling negate() on a NULL BigInteger reference\n");
        exit(EXIT_FAILURE);
    }
    /*if (length(N->LL) == 0) {
        printf("BigInteger Error: calling negate() on an empty BigInteger\n");
        exit(EXIT_FAILURE);
    }*/
    //Just flipping the sign after checking if theres a list and it's not empty. 
    if (N->sign == 1) {
        N->sign = -1;
    }
    else if (N->sign == -1) {
        N->sign = 1;
    }
}
//Helper function for the pow function in math.h since the makefile doesn't work with it.
//I also didn't know "how" to get it to work, which I knew it could.
int powerHelper(int power, int base)
{
    if (base == 0)
        return 1;
    else if (base % 2 == 0)
        return powerHelper(power, base / 2) * powerHelper(power, base / 2);
    else
        return power * powerHelper(power, base / 2) * powerHelper(power, base / 2);
}
// BigInteger Arithmetic operations -----------------------------------------------
// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}
// and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char* s)
{
    if (s == NULL) {
        printf("BigInteger Error: calling stringToBigInteger() on a NULL char* reference\n");
        exit(EXIT_FAILURE);
    }
    if (s[0] == '\0') {
        printf("BigInteger Error: calling stringToBigInteger() on an empty char* reference\n");
        exit(EXIT_FAILURE);
    }
    BigInteger stringToBI = newBigInteger();
    //Check for sign since it's the firt thing the s can have so we can move to big int
    int position = 0;
    if (s[position] == '-') {
        stringToBI->sign = -1;
        ++position;
    }
    if (s[position] == '+') {
        stringToBI->sign = 1;
        ++position;
    }
    else
        stringToBI->sign = 1;
    //This will put us where there are no leading zeros
    while (s[position] == '0') {
        ++position;
    }
    int count = 0;
    int tenPlace = 1;
    long value, strl = 0;
    //Preconditions set and now we can 
    while (position != '\n') {
        if (s[position] > 48 || s[position] < 57) {
            strl = (s[position] - 48);
            value = value + (strl * tenPlace);
            count++;
            //Don't know why the macro does'nt work here so had to use 9
            if (count == POWER) {
                prepend(stringToBI->LL, value);
                movePrev(stringToBI->LL);
                tenPlace = 1;
                count = 0;
                value = 0;
            }
            else {
                tenPlace = (tenPlace * 10);
            }
        }
        else {
            printf("BigInteger Error: calling stringToBigInteger() on an invalid char* reference\n");
            exit(EXIT_FAILURE);
        }
        position++;
    }
    if (value != 0) {
        append(stringToBI->LL, value);
    }
    return stringToBI;

}
// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N)
{
    if (N == NULL) {
        printf("BigInteger Error: calling add() on a NULL BigInteger reference\n");
        exit(EXIT_FAILURE);
    }
    BigInteger newCopy = newBigInteger();
    newCopy->sign = N->sign;
    newCopy->LL = copyList(N->LL);
    return (newCopy);
}
// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B)
{
    if (S == NULL || A == NULL || B == NULL) {
        printf("BigInteger Error: calling add() on a NULL BigInteger reference\n");
        exit(EXIT_FAILURE);
    }
    BigInteger newCopy = sum(A, B);
    freeList(&S->LL);
    S->LL = copyList(newCopy->LL);
    S->sign = newCopy->sign;
    freeBigInteger(&newCopy);

}
// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B)
{
    if (A == NULL || B == NULL) {
        printf("BigInteger Error: calling sum() on a NULL BigInteger reference\n");
        exit(EXIT_FAILURE);
    }
    if (A->sign == 0) {
        return copy(B);
    }
    if (B->sign == 0) {
        return copy(A);
    }
    long carry = 0;
    long value = 0;
    BigInteger newBI = newBigInteger();
    //Check the cases for sum. 
    //We already checked if the sign is zero
    //Now we need to check if there is a negative on one of the numbers
    if (A->sign == -1 || B->sign == -1) {
        if (A->sign == 1 && B->sign == -1) {
            //Call the differnce of the two
            B->sign = 1;
            newBI = diff(A, B);
            B->sign = -1;
            return (newBI);
        }
        if (A->sign == -1 && B->sign == 1) {
            //Call the difference of the two
            A->sign = 1;
            newBI = diff(B, A);
            A->sign = -1;
            return (newBI);
        }
        //If they're both negative we just do the addition but flip the sign at the end. 
        else {
            A->sign = B->sign = 1;
            newBI = sum(A, B);
            A->sign = B->sign = -1;
            newBI->sign = -1;
            return (newBI);
        }
    }
    //Now that we've checked the conditions we need to actually do the sum of 2 positive numbers
    newBI = newBigInteger();
    //It's going to be positive. 
    newBI->sign = A->sign;
    moveBack(A->LL);
    moveBack(B->LL);
    while (index(A->LL) > -1 && index(B->LL) > -1) {
        //Haven't accounted for base yet.
        value = get(A->LL) + get(B->LL) + carry;
        prepend(newBI->LL, value);
        movePrev(A->LL);
        movePrev(B->LL);
    }
    //Haven't accounted for base yet.
    while (index(A->LL) > -1) {

        value = get(A->LL) + carry;
        prepend(newBI->LL, value);
        movePrev(A->LL);
    }
    //Haven't accounted for base yet.
    while (index(B->LL) > -1) {

        value = get(B->LL) + carry;
        prepend(newBI->LL, value);
        movePrev(B->LL);
    }
    if (carry != 0)
        prepend(newBI->LL, carry);

    return(newBI);
}
// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state: D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B)
{
    if (A == NULL || B == NULL || D == NULL) {
        printf("BigInteger Error: calling subtract() on a NULL BigInteger reference\n");
        exit(EXIT_FAILURE);
    }
    BigInteger newCopy = diff(A, B);
    freeList(&D->LL);
    D->LL = copyList(newCopy->LL);
    D->sign = newCopy->sign;
    freeBigInteger(&newCopy);

}
//Helper function for diff called subtraction
BigInteger subtraction(BigInteger A, BigInteger B) {

    /*BigInteger newBI = newBigInteger();
    long value = 0;
    long carry = 0;
    moveBack(newBI->LL);
    moveBack(A->LL);
    moveBack(B->LL);
    while (index(A->LL) > -1 && index(B->LL) > -1) {

        value = get(A->LL) - get(B->LL) + carry;
        prepend(newBI->LL, value);
        movePrev(A->LL);
        movePrev(B->LL);
    }
    while (index(A->LL) > -1) {

        value = get(A->LL) + carry;
        prepend(newBI->LL, value);
        movePrev(A->LL);
    }
    return newBI;
    */
}
// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B)
{
   /* if (A == NULL || B == NULL) {
        printf("BigInteger Error: calling diff() on a NULL BigInteger reference\n");
        exit(EXIT_FAILURE);
    }
    if (A->sign == 0) {
        return copy(B);
    }
    if (B->sign == 0) {
        return copy(A);
    }
    BigInteger newBI;
    //Check if they're equal so we can just return our constructed newBI
    if (equals(A, B) == 1) {
        return(newBI);
    }
    if (A->sign == -1 || B->sign == -1) {
        if (A->sign == 1 && B->sign == -1) {
            //Call the sum of the two
            B->sign = 1;
            newBI = sum(A, B);
            B->sign = -1;
            return (newBI);
        }
        if (A->sign == -1 && B->sign == 1) {
            //Call the sum of the two
            B->sign = -1;
            newBI = sum(A, B);
            B->sign = 1;
            return (newBI);
        }
        else {
            //they're both negative and we just flip sign of b and subtract.
            B->sign = 1;
            newBI = diff(A, B);
            return (newBI);
        }
    }
    //Now we just do it for 2 positive numbers and do subtraction
    newBI = newBigInteger();
    //It's going to be positive. 
    newBI->sign = A->sign;
    newBI = subtraction(A, B);
    return(newBI);*/
}
// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B)
{
    if (P == NULL || A == NULL || B == NULL) {
        printf("BigInteger Error: calling multiply() on a NULL BigInteger reference\n");
        exit(EXIT_FAILURE);
    }
    BigInteger newCopy = prod(A, B);
    freeList(&P->LL);
    P->LL = copyList(newCopy->LL);
    P->sign = newCopy->sign;
    freeBigInteger(&newCopy);
}
// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B)
{
    if (A == NULL || B == NULL) {
        printf("BigInteger Error: calling prod() on a NULL BigInteger reference\n");
        exit(EXIT_FAILURE);
    }
    return A;
}

// Other operations -----------------------------------------------------------
// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N)
{
    if (N == NULL) {
        printf("BigInteger List Error: calling printBigInteger() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(N->LL) == 0) {
        printf("BigInteger List Error: calling printBigInteger() on emptyList reference\n");
        exit(EXIT_FAILURE);
    }
    if (N->sign != 0) {
        if (N->sign == -1) {
            fprintf(out, "-");
        }
        for (moveFront(N->LL); index(N->LL) >= 0; moveNext(N->LL)) {
            fprintf(out, "%0*ld ", POWER, get(N->LL));
        }
    }
    else {
        fprintf(out, "\n");
    }
}
