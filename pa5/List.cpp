/*
Name: Moises Perez
CruzID: mperez86
Assignment: pa5

The underlying data structure for this incarnation of the List ADT will be a doubly linked list of Node
objects, with two dummy nodes at the front and the back. The empty List state will be represented by these
two sentinel nodes, pointing to each other as next and prev, respectively. The value stored in the data fields
of the dummy nodes can by anything you like, and will not be read from or written to. As you may be
aware, dummy nodes are useful for resolving special cases of insertion and deletion.

A key difference between this List ADT and the one you created in previous assignments is the cursor.
Instead of a horizontal bar lying under a list element, the cursor will be a vertical bar standing between two
elements, or standing to the left or to the right of all elements (in the client view). In fact, the elements
themselves are not indexed, but instead the spaces between the elements are. The cursor will always stand
in one of these in-between positions, and cannot become undefined. A List containing 𝑛 elements will
therefore have exactly 𝑛 + 1 possible cursor positions, namely 0, signifying the front of the List, through 𝑛
at the back. For instance, if 𝑛 = 7 the List has 8 available cursor positions.
0 1 2 3 4 5 6 7
| a | b | c | d | e | f | g |
3
To represent the cursor within the ADT, we will use two Node pointers, which are called beforeCursor
and afterCusor in the .h file. These pointers will always straddle the vertical cursor, pointing to the Node
objects immediately before and after the cursor position. If the cursor is at the front of the List (position 0),
then beforeCursor will point to frontDummy. Likewise if the cursor is at the back of the List (position
𝑛), then afterCursor will point to backDummy.
*/

#include <iostream>
#include <iomanip>
#include "List.h"

using namespace std;
// Private Constructor --------------------------------------------------------
//Node Constructor
List::Node::Node(int x) {
    data = x;
    next = nullptr;
    prev = nullptr;
}

// Class Constructors & Destructors -------------------------------------------
//NewList() basically in an empty state
List::List()
{
    frontDummy = new Node(0);
    backDummy = new Node(1);

    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;

    beforeCursor = frontDummy;
    afterCursor = backDummy;

    pos_cursor = 0;
    num_elements = 0;

}
//Copy Constructor
List::List(const List& L)
{
    frontDummy = new Node(0);
    backDummy = new Node(1);

    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;

    beforeCursor = frontDummy;
    afterCursor = backDummy;

    pos_cursor = 0;
    num_elements = 0;

    Node* N = L.frontDummy->next;
    while (N != L.backDummy) {
        this->insertBefore(N->data);
        N = N->next;
    }
    this->moveFront();

}
//Destructor
List::~List()
{
    if (!isEmpty()) {
        this->clear();
    }
    delete(frontDummy);
    delete(backDummy);
}
// Access functions --------------------------------------------------------

// isEmpty()
// Returns true if this List is empty, false otherwise.

bool List::isEmpty()
{
    if (num_elements == 0)
        return true;
    else
        return false;
}
// size()
// Returns the size of this List.

int List::size()
{
    return num_elements;
}
// position()
// Returns the position of the cursor in this List. The value returned
// will be in the range 0 to size().

int List::position()
{
    return pos_cursor;
}
// Manipulation procedures -------------------------------------------------

// moveFront()
// Moves cursor to position 0 in this List.

void List::moveFront()
{
    pos_cursor = 0;
    afterCursor = frontDummy->next;
    beforeCursor = frontDummy;
}
// moveBack()
// Moves cursor to position size() in this List.

void List::moveBack()
{
    pos_cursor = size();
    afterCursor = backDummy;
    beforeCursor = backDummy->prev;
}
// peekNext()
// Returns the element after the cursor.
// pre: position()<size()
int List::peekNext()
{
    if (position() >= size()) {
        cerr << "List Error: calling peekNext() on no next element" << endl;
        exit(EXIT_FAILURE);
    }
    else
        return afterCursor->data;
}
// peekPrev()
// Returns the element before the cursor.
// pre: position()>0

int List::peekPrev()
{
    if (position() <= 0) {
        cerr << "List Error: calling peekPrev() on no prev element" << endl;
        exit(EXIT_FAILURE);
    }
    else
        return beforeCursor->data;
}
// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<size() 

int List::moveNext()
{
    if (position() >= size()) {
        cerr << "List Error: calling peekNext() on no next element" << endl;
        exit(EXIT_FAILURE);
    }
    else {
        beforeCursor = beforeCursor->next;
        afterCursor = afterCursor->next;
        pos_cursor++;
        return beforeCursor->data;

    }
}
// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0

int List::movePrev()
{
    if (position() <= 0) {
        cerr << "List Error: calling peekPrev() on no prev element" << endl;
        exit(EXIT_FAILURE);
    }
    else {
        afterCursor = afterCursor->prev;
        beforeCursor = beforeCursor->prev;
        pos_cursor--;
        return afterCursor->data;
    }
}
// insertAfter()
// Inserts x after cursor.

void List::insertAfter(int x)
{
    Node* nodeTemp = new Node(x);

    nodeTemp->prev = beforeCursor;
    nodeTemp->next = afterCursor;
    beforeCursor->next = nodeTemp;
    afterCursor->prev = nodeTemp;
    afterCursor = nodeTemp;
    num_elements++;
}
// insertBefore()
// Inserts x before cursor.

void List::insertBefore(int x)
{
    Node* nodeTemp = new Node(x);

    nodeTemp->prev = beforeCursor;
    nodeTemp->next = afterCursor;
    beforeCursor->next = nodeTemp;
    afterCursor->prev = nodeTemp;
    beforeCursor = nodeTemp;
    num_elements++;
    pos_cursor++;
}
// eraseAfter()
// Deletes element after cursor.
// pre: position()<size()

void List::eraseAfter()
{
    if (position() >= size()) {
        cerr << "List Error: calling eraseAfter() on no element after last." << endl;
        exit(EXIT_FAILURE);
    }
    Node* nodeTemp;
    nodeTemp = afterCursor;
    afterCursor = afterCursor->next;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
    delete nodeTemp;
    num_elements--;
}
// eraseBefore()
// Deletes element before cursor.
// pre: position()>0

void List::eraseBefore()
{
    if (pos_cursor <= 0) {
        cerr << "List Error: calling eraseBefore() on no element before." << endl;
        exit(EXIT_FAILURE);
    }
    Node* nodeTemp;
    nodeTemp = beforeCursor;
    beforeCursor = beforeCursor->prev;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
    delete nodeTemp;
    pos_cursor--;
    num_elements--;
}
// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of the element x.
// If x is found, places the cursor immediately after the found element (so 
// eraseBefore() would remove the found element), and returns the final 
// cursor position. If x is not found, places the cursor at position size(),
// and returns -1. 

int List::findNext(int x)
{
    while (afterCursor != backDummy) {
        if (afterCursor->data == x) {
            this->moveNext();
            return position();
        }
        this->moveNext();
    }
    return -1;
}
// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of the element x.
// If x is found, places the cursor immediately before the found element (so 
// eraseAfter() would remove the found element), and returns the final 
// cursor position. If x is not found, places the cursor at position 0, and 
// returns -1. 

int List::findPrev(int x)
{
    while (beforeCursor != frontDummy) {
        if (beforeCursor->data == x) {
            this->movePrev();
            return position();
        }
        this->movePrev();
    }
    return -1;
}
// cleanup()
// Removes any repeated elements in this List, leaving only unique data
// values. The order of the remaining elements is obtained by retaining
// the frontmost occurrance of each element, and removing all other 
// occurances. The cursor is not moved with respect to the retained 
// elements, i.e. it lies between the same two retained elements that it 
// did before cleanup() was called.

void List::cleanup()
{
    int RealCursor = pos_cursor;
    int counter = 0;
    int CurrentCursor = 0;
    Node* NodeTemp = frontDummy->next;
    while (NodeTemp != backDummy) {
        moveFront();
        findNext(NodeTemp->data);
        while (CurrentCursor != -1) {
            if (NodeTemp->next == backDummy)
                break;
            CurrentCursor = findNext(NodeTemp->data);
            if (pos_cursor <= RealCursor)
                RealCursor--;
            eraseBefore();
        }
        NodeTemp = frontDummy->next;
        counter++;
        for (CurrentCursor = 0; CurrentCursor < counter; CurrentCursor++) {
            NodeTemp = NodeTemp->next;
        }
    }
    moveFront();
    for (CurrentCursor = 0; CurrentCursor < RealCursor; CurrentCursor++)
        moveNext();
}
// clear()
// Deletes all elements in this List, setting it to the empty state.

void List::clear()
{
    this->moveFront();
    while (size() != 0) {
        this->eraseAfter();
    }
}
// concat()
// Returns a new List consisting of the elements of this List, followed
// the elements of L. The returned List's cursor will be at its front
// (position 0).
List List::concat(const List& L)
{
    List J;
    Node* nodeTempN = this->frontDummy->next;
    Node* nodeTempM = L.frontDummy->next;
    while (nodeTempN != this->backDummy) {
        J.insertBefore(nodeTempN->data);
        nodeTempN = nodeTempN->next;
    }
    while (nodeTempM != L.backDummy) {
        J.insertBefore(nodeTempM->data);
        nodeTempM = nodeTempM->next;
    }
    J.moveFront();
    return J;
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.

std::string List::to_string()
{
    Node* nodeTemp = nullptr;
    string s = "(";

    for (nodeTemp = frontDummy->next; nodeTemp != backDummy->prev; nodeTemp = nodeTemp->next) {
        s += std::to_string(nodeTemp->data) + ", ";
    }
    s += std::to_string(nodeTemp->data);
    s += ")";
    return s;
}
// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.

bool List::equals(const List& R)
{
    bool eq = false;
    Node* N = nullptr;
    Node* M = nullptr;

    eq = (this->num_elements == R.num_elements);
    N = this->frontDummy->next;
    M = R.frontDummy->next;
    while (eq && N != this->backDummy) {
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}
// Overriden Operators -----------------------------------------------------

// operator=()
// Overwrites the state of this List with state of L.

List& List::operator=(const List& L)
{
    if (this != &L) {
        List temp = L;
        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(num_elements, temp.num_elements);

    }
    // TODO: insert return statement here
    return *this;
}
// operator<<()
// Inserts string representation of L into stream.

std::ostream& operator<<(std::ostream& stream, List& L)
{
    // TODO: insert return statement here
    return stream << L.List::to_string();
}
// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged are unchanged.

bool operator==(List& A, const List& B)
{
    // TODO: insert return statement here
    return A.List::equals(B);
}
