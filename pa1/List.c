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
#include <stdio.h>
#include <stdlib.h>
#include "List.h"

//Structs
//contain a private (non - exported) struct called NodeObj and a pointer to that struct called Node.
//The struct NodeObj should contain fields for an int(the data), and two Node references(the previous and next Nodes, respectively.)
typedef struct NodeObj {
    int data;

    struct NodeObj* next;
    struct NodeObj* prev;

}NodeObj;

//private node type
typedef NodeObj* Node;

//The private (non-exported) struct ListObj should contain fields of type Node referring to the front, backand cursor elements, respectively.
typedef struct ListObj {
    int Length;
    int position;
    Node front;
    Node back;
    Node cursor;

}ListObj;

// Constructors-Destructors ---------------------------------------------------
//Creates and returns a new empty List.
List newList(void)
{
    List L;
    L = malloc(sizeof(ListObj));
    L->front = NULL;
    L->back = NULL;
    L->Length = 0;
    L->position = -1;
    L->cursor = NULL;
    return (L);
}
// Frees all heap memory associated with *pL, and sets *pL to NULL.
void freeList(List* pL)
{
    if (pL != NULL && *pL != NULL) {
        while (!(length(*pL) == 0)) {
            deleteFront(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
}
// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(int data) {
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->next = NULL;
    N->prev = NULL;
    return(N);
}
// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN) {
    if (pN != NULL && *pN != NULL) {
        free(*pN);
        *pN = NULL;
    }
}

// Access functions -----------------------------------------------------------
// Returns the number of elements in L.
int length(List L)
{
    if (L == NULL) {
        printf("List Error: calling length() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return(L->Length);
}
// Returns index of cursor element if defined, -1 otherwise.
int index(List L)
{
    if (L == NULL) {
        return -1;
    }
    if (L->Length < 0) {
        return -1;
    }
    return(L->position);
}
// Returns front element of L. Pre: length()>0
int front(List L)
{
    if (L == NULL) {
        printf("List Error: calling front() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->Length == 0) {
        printf("List Error: calling front() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    return(L->front->data);
}
// Returns back element of L. Pre: length()>0
int back(List L)
{
    if (L == NULL) {
        printf("List Error: calling back() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->Length == 0) {
        printf("List Error: calling back() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    return(L->back->data);
}
// Returns cursor element of L. Pre: length()>0, index()>=0
int get(List L)
{
    if (L == NULL) {
        printf("List Error: calling get() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor == NULL) {
        printf("List Error: calling get() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    return(L->cursor->data);
}
// Returns true (1) iff Lists A and B are in same state, and returns false (0) otherwise.
int equals(List A, List B)
{

    if (A == NULL || B == NULL) {
        printf("List Error: calling equals() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    int eq = 0;
    Node N = NULL;
    Node M = NULL;

    eq = (A->Length == B->Length);
    N = A->front;
    M = B->front;

    while (eq && N != NULL) {
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}

// Manipulation procedures ----------------------------------------------------
// Resets L to its original empty state.
void clear(List L)
{
    if (L == NULL) {
        printf("List Error: calling clear() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    while (L->Length > 0) {
        deleteFront(L);
    }
    L->cursor = NULL;
    L->position = -1;
}
// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L)
{
    if (L == NULL) {
        printf("List Error: calling moveFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->Length > 0) {
        L->cursor = L->front;
        L->position = 0;
    }
}
// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L)
{
    if (L == NULL) {
        printf("List Error: calling moveBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    L->cursor = L->back;
    //adust index
    L->position = L->Length - 1;
}
// If cursor is defined and not at front, move cursor one step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined do nothing
void movePrev(List L)
{
    if (L == NULL) {
        printf("List Error: calling movePrev() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL) {
        if (L->cursor != L->front) {
            //adjust index
            L->cursor = L->cursor->prev;
            L->position--;
        }
        else if ((L->cursor) == (L->front)) {
            L->position = -1;
            L->cursor = NULL;
        }
    }
}
// If cursor is defined and not at back, move cursor one step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined do nothing
void moveNext(List L)
{
    if (L == NULL) {
        printf("List Error: calling moveNext() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL) {
        if (L->cursor != L->back) {
            L->cursor = L->cursor->next;
            L->position++;
        }
        else if (L->cursor == L->back) {
            //adjust index
            L->position = -1;
            L->cursor = NULL;
        }
    }

}
// Insert new element into L. If L is non-empty, insertion takes place before front element.
void prepend(List L, int data)
{
    //inserting the node before the front element so we chack to see if there is even a front node
    //else adjust nodes for the insert
    Node nodeInsert = newNode(data);
    if (L == NULL) {
        printf("List Error: calling prepend() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->Length > 0) {
        nodeInsert->next = L->front;
        L->front->prev = nodeInsert;
        L->front = nodeInsert;
        if (L->cursor != NULL)
            L->position++;
        L->Length++;
    }
    else if (L->Length == 0) {
        L->front = L->back = nodeInsert;
        L->Length++;
    }
}
// Insert new element into L. If L is non-empty, insertion takes place after back element.
void append(List L, int data)
{
    //inserting into L after the back so we check if there is even a length and then set the node to the back. 
    Node nodeInsert = newNode(data);
    if (L == NULL) {
        printf("List Error: calling append() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->Length > 0) {
        nodeInsert->prev = L->back;
        L->back->next = nodeInsert;
        L->back = nodeInsert;
        L->Length++;
    }
    else if (L->Length == 0) {
        L->front = L->back = nodeInsert;
        L->Length++;
    }
}
// Insert new element before cursor. Pre: length()>0, index()>=0
void insertBefore(List L, int data)
{
    Node nodeInsert = newNode(data);
    if (L == NULL) {
        printf("List Error: calling insertBefore() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor == NULL) {
        printf("List Error: calling insertBefore() where the cursor is NULL\n");
        exit(EXIT_FAILURE);
    }
    if (L->position == -1) {
        printf("List Error: calling insertBefore() where the cursor is NULL\n");
        exit(EXIT_FAILURE);
    }
    if (L->Length <= 0) {
        printf("List Error: calling insertBefore() failing pre condition\n");
        exit(EXIT_FAILURE);
    }
    //Check if the node is in the front so we can just add to front but if not we adjust nodes
    else if (L->cursor == L->front) {
        nodeInsert->next = L->front;
        L->front->prev = nodeInsert;
        L->front = nodeInsert;
        L->position++;
        L->Length++;
    }
    else {
        nodeInsert->prev = L->cursor->prev;
        nodeInsert->next = L->cursor;
        L->cursor->prev->next = nodeInsert;
        L->cursor->prev = nodeInsert;
        L->position++;
        L->Length++;
    }
}
// Insert new element after cursor. Pre: length()>0, index()>=0
void insertAfter(List L, int data)
{
    Node nodeInsert = newNode(data);
    if (L == NULL) {
        printf("List Error: calling insertAfter() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor == NULL) {
        printf("List Error: calling insertAfter() where the cursor is NULL\n");
        exit(EXIT_FAILURE);
    }
    if (L->position == -1) {
        printf("List Error: calling insertAfter() where the cursor is NULL\n");
        exit(EXIT_FAILURE);
    }
    if (L->Length <= 0) {
        printf("List Error: calling insertAfter() failing pre condition\n");
        exit(EXIT_FAILURE);
    }
    // check to see of the cursor is back then we just add to back but if it isn't we set the new node
    // to adjust the other nodes to insert the new one. 
    else if (L->cursor == L->back) {
        nodeInsert->prev = L->back;
        L->back->next = nodeInsert;
        L->back = nodeInsert;
        L->Length++;
    }
    else {
        nodeInsert->next = L->cursor->next;
        nodeInsert->prev = L->cursor;
        L->cursor->next->prev = nodeInsert;
        L->cursor->next = nodeInsert;
        L->Length++;
    }
}
/// Delete the front element. Pre: length()>0
void deleteFront(List L)
{
    if (L == NULL) {
        printf("List Error: calling deleteFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->front == NULL) {
        printf("List Error: calling deleteFront() on empty lisT\n");
        exit(EXIT_FAILURE);
    }
    if (L->Length <= 0) {
        printf("List Error: calling deleteFront() failing pre condition\n");
        exit(EXIT_FAILURE);
    }
    //deleting front and we already know it's not null so we see if there is onyl one node
    //else free front node but check if the position is 0 so we can set cursor to null and 
    //decremtn the pos and length
    if (L->Length == 1) {
        freeNode(&L->front);
        L->front = NULL;
        L->back = NULL;
        L->position = -1;
        L->Length = 0;
    }
    else {
        Node tempNode = L->front;
        L->front = L->front->next;
        freeNode(&tempNode);
        L->front->prev = NULL;
        //check
        if (L->position == 0)
            L->cursor = NULL;
        L->position--;
        L->Length--;
    }
}
// Delete the back element. Pre: length()>0
void deleteBack(List L)
{
    if (L == NULL) {
        printf("List Error: calling deleteBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->back == NULL) {
        printf("List Error: calling deleteBack() on empty list\n");
        exit(EXIT_FAILURE);
    }
    if (L->Length <= 0) {
        printf("List Error: calling deleteBack() failing pre condition\n");
        exit(EXIT_FAILURE);
    }
    //checkif 1 node and we already know it's not null so just else statement
    //where we check to see if the cursor is at the back if not free
    if (L->Length == 1) {
        freeNode(&L->front);
        L->front = NULL;
        L->back = NULL;
        L->position = -1;
        L->Length = 0;
    }
    else {
        Node tempNode = L->back;
        if (L->cursor == tempNode) {
            L->cursor = NULL;
            L->position = -1;
        }
        L->back = L->back->prev;
        freeNode(&tempNode);
        L->back->next = NULL;
        L->Length--;
    }
}
// Delete cursor element, making cursor undefined. Pre: length()>0, index()>=0
void delete(List L)
{
    if (L == NULL) {
        printf("List Error: calling deleteBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor == NULL) {
        printf("List Error: calling delete() on NULL cursor\n");
        exit(EXIT_FAILURE);
    }
    if (L->position < 0) {
        printf("List Error: calling delete() on position -1\n");
        exit(EXIT_FAILURE);
    }
    if (L->position == -1) {
        printf("List Error: calling delete() where the cursor is NULL\n");
        exit(EXIT_FAILURE);
    }
    if (L->Length <= 0) {
        printf("List Error: calling delete() failing pre condition\n");
        exit(EXIT_FAILURE);
    }
    Node tempNode = L->cursor;
    L->cursor = NULL;
    //check if cursor is front
    if (L->front == tempNode) {
        tempNode = L->front;
        L->front = L->front->next;
        freeNode(&tempNode);
        L->front->prev = NULL;
    }
    //check if cursor is back
    else if (L->back == tempNode) {
        tempNode = L->back;
        L->back = L->back->prev;
        freeNode(&tempNode);
        L->back->next = NULL;
    }
    //else then delete element that cursor was pointing to
    else {
        //check if it's only 1 
        if (L->Length == 1) {
            freeNode(&L->front);
            L->front = L->back = NULL;
            L->Length--;
            L->position = -1;
            return;
        }
        tempNode->prev->next = tempNode->next;
        tempNode->next->prev = tempNode->prev;
        freeNode(&tempNode);
    }
    L->Length--;
    L->position = -1;
}

// Other operations -----------------------------------------------------------
// Prints to the file pointed to by out, a string representation of L consisting
// of a space separated sequence of integers, with front on left.
void printList(FILE* out, List L)
{
    if (L == NULL) {
        printf("List Error: calling printList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    for (moveFront(L); index(L) >= 0; moveNext(L)) {
        fprintf(out, "%d ", get(L));
    }
}
// Returns a new List representing the same integer sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state of L is unchanged.
List copyList(List L)
{
    if (L == NULL) {
        printf("List Error: calling copyList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    List newCopy = newList();
    Node N = L->back;
    while (N != NULL) {

        prepend(newCopy, N->data);
        N = N->prev;
    }

    return (newCopy);
}
