/*
Name: Moises Perez
CruzID: mperez86
Assignment: pa7
*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"Dictionary.h"

int main(int argc, char* argv[]) {


    Dictionary A = newDictionary(1);
    Dictionary B = newDictionary(0);

    char* word[] = { "n","z","w","k","i","c","l","d","t","a",
                    "e","y","b","h","v","f","s","m","x","r",
                    "o","u","p","g","j","q" };

    VAL_TYPE x;
    VAL_TYPE y;
    int i, n = 26;
    // add pairs to A --------------------------------------
    for (i = 0; i < n; i++) {
        insert(A, word[i], NULL);
    }

    // print Dictionary A after insertions
    printf("Dictionary A (%sunique keys):\n", (getUnique(A) ? "" : "non-"));
    printf("after insertions:\n");
    printf("******************************************************\n");
    printf("IN-ORDER:\n");
    printf("******************************************************\n");
    printDictionary(stdout, A, "in");
    printf("******************************************************\n");
    printf("PRE-ORDER:\n");
    printf("******************************************************\n");
    printDictionary(stdout, A, "pre");
    printf("******************************************************\n");
    printf("POST-ORDER:\n");
    printf("******************************************************\n");
    printDictionary(stdout, A, "post");
    printf("\n");

    printf("reverse A:\n");
    for (y = beginReverse(A); currentVal(A) != VAL_UNDEF; y = prev(A)) {
        printf("key: "KEY_FORMAT" value: "VAL_FORMAT"\n", currentKey(A), y);
    }
    printf("\n\n");

    // add pairs to B
    for (i = n - 1; i >= 0; i--) {
        insert(B, word[i], NULL);
    }

    // print Dictionary A after insertions
    printf("Dictionary B (%sunique keys):\n", (getUnique(B) ? "" : "non-"));
    printf("after insertions:\n");
    printf("******************************************************\n");
    printf("IN-ORDER:\n");
    printf("******************************************************\n");
    printDictionary(stdout, B, "in");
    printf("******************************************************\n");
    printf("PRE-ORDER:\n");
    printf("******************************************************\n");
    printDictionary(stdout, A, "pre");
    printf("******************************************************\n");
    printf("POST-ORDER:\n");
    printf("******************************************************\n");
    printDictionary(stdout, A, "post");
    printf("\n");

    // forward iteration over B ----------------------------
    printf("forward B:\n");
    for (x = beginForward(B); currentVal(B) != VAL_UNDEF; x = next(B)) {
        printf("key: "KEY_FORMAT" value: "VAL_FORMAT"\n", currentKey(B), x);
    }
    printf("\n\n");

    // delete keys from B ----------------------------------
    for (i = 1; i < n; i += 2) {
        delete(B, word[i]);
    }

    // print Dictionary B after deletions
    printf("Dictionary B (%sunique keys):\n", (getUnique(B) ? "" : "non-"));
    printf("after deletions:\n");
    printf("******************************************************\n");
    printf("IN-ORDER:\n");
    printf("******************************************************\n");
    printDictionary(stdout, B, "in");
    printf("******************************************************\n");
    printf("PRE-ORDER:\n");
    printf("******************************************************\n");
    printDictionary(stdout, A, "pre");
    printf("******************************************************\n");
    printf("POST-ORDER:\n");
    printf("******************************************************\n");
    printDictionary(stdout, A, "post");
    printf("\n");

    // delete keys from A ----------------------------------
    for (i = 0; i < n; i += 2) {
        delete(A, word[i]);
    }

    // print Dictionary A after deletions
    printf("Dictionary A (%sunique keys):\n", (getUnique(A) ? "" : "non-"));
    printf("after deletions:\n");
    printf("******************************************************\n");
    printf("IN-ORDER:\n");
    printf("******************************************************\n");
    printDictionary(stdout, A,"in");
    printf("******************************************************\n");
    printf("PRE-ORDER:\n");
    printf("******************************************************\n");
    printDictionary(stdout, A, "pre");
    printf("******************************************************\n");
    printf("POST-ORDER:\n");
    printf("******************************************************\n");
    printDictionary(stdout, A, "post");
    printf("\n");



    freeDictionary(&A);
    freeDictionary(&B);
    return(0);
}