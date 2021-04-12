/*
Name: Moises Perez
CruzID: mperez86
Assignment: pa5

*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <string>
#include "List.h"


using namespace std;
/*
* 
Function shuffle() will alter its List& (List reference) argument D by performing one shuffle operation,
as described above. Function main() will read a single command line argument, which will be a positive
integer specifying the maximum number of cards in a deck. For each 𝑛 in the range 1 up to this maximum,
your program will perform shuffles until the list (0, 1, 2, … , 𝑛 − 1) is brought back to its original order,
2
counting the number of shuffles as it goes. It will print a table to standard output giving this count, for each
value of 𝑛.


As usual, the $ sign represents the Unix prompt. If you re-direct your program output to a file, then you
can verify your formatting and results by comparing to the files out10, out35 and out75 respectively, all
posted on the webpage. For instance Shuffle 35 > myout35 and then diff myout35 out35 will
verify your results up to a deck size of 35.

*/
void shuffle(List& deck) {
    List A;
    List B;
    int i = 0;
    deck.moveFront();
    for (i = 0; i < deck.size() / 2; i++) {
        A.insertBefore(deck.peekNext());
        deck.moveNext();
    }
    for (int y = deck.size() / 2; y < deck.size(); y++) {
        B.insertBefore(deck.peekNext());
        deck.moveNext();
    }
    deck.clear();
    A.moveFront();
    B.moveFront();
    while (A.position() != A.size() || B.position() != B.size()) {
        //check
        if (B.position() != B.size()) {
            deck.insertBefore(B.peekNext());
            B.moveNext();

        }
        if (A.position() != A.size()) {
            deck.insertBefore(A.peekNext());
            A.moveNext();

        }
    }
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <number>" << endl;
        return (EXIT_FAILURE);
    }
    //Need number in deck
    //Function main() will read a single command line argument, which will be a positive
    //integer specifying the maximum number of cards in a deck.
    int numOfDeck = atoi(argv[1]);
    List D, F;

    cout << "deck size       shuffle count" << endl;
    cout << "------------------------------" << endl;
    //while loop for number in deck
    //Shuffle needs to be function -easier
    int shuffles = 0;
    int i = 0;
    int j = 0;
    /*
    For each 𝑛 in the range 1 up to this maximum,
    your program will perform shuffles until the list (0, 1, 2, … , 𝑛 − 1) is brought back to its original order, 2
    counting the number of shuffles as it goes. It will print a table to standard output giving this count, for each
    value of 𝑛.
    */
    while (i < numOfDeck) {
        shuffles = 0;
        while (j < (i + 1)) {
            D.insertBefore(j);
            F.insertBefore(j);
            j++;
        }
        shuffle(D);
        shuffles++;
        while (!(D.equals(F))) {
            shuffle(D);
            shuffles++;
        }
        cout << " " << i + 1 << "               " << shuffles << endl;
        D.clear();
        F.clear();
        j = 0;
        i++;
    }
    return (0);
}