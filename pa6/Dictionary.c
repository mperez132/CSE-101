/*
Name: Moises Perez
CruzID: mperez86
Assignment: pa6
*/

#include "Dictionary.h"

typedef struct NodeObj {

    KEY_TYPE key;
    VAL_TYPE value;

    struct NodeObj* parent;
    struct NodeObj* left;
    struct NodeObj* right;

}NodeObj;

typedef NodeObj* Node;

typedef struct DictionaryObj {
    Node root;
    Node cursor;
    int size;
    int unique;
    //Node dummy;
}DictionaryObj;

Node newNode(KEY_TYPE k, VAL_TYPE v) {
    Node N = malloc(sizeof(NodeObj));
    N->key = k;
    N->value = v;
    N->parent = NULL;
    N->left = NULL;
    N->right = NULL;
    return(N);
}
// newDictionary()
// Creates a new empty Dictionary. If unique==false (0), then the Dictionary 
// will accept duplicate keys, i.e. distinct pairs with identical keys. If 
// unique==true (1 or any non-zero value), then duplicate keys will not be 
// accepted. In this case, the operation insert(D, k) will enforce the 
// precondition: lookup(D, k)==VAL_UNDEF

Dictionary newDictionary(int unique)
{
    Dictionary D = malloc(sizeof(DictionaryObj));
    D->size = 0;
    D->cursor = NULL;
    D->unique = unique;
    D->root = NULL;
    //D->dummy = newNode(KEY_UNDEF, VAL_UNDEF);
    return D;
}
// freeDictionary()
// Frees heap memory associated with *pD, sets *pD to NULL.
void freeDictionary(Dictionary* pD)
{
    if (pD != NULL && *pD != NULL) {
        //free((*pD)->dummy);
        makeEmpty(*pD);
        free(*pD);
        *pD = NULL;
    }
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

// size()
// Returns the number of (key, value) pairs in Dictionary D.

int size(Dictionary D)
{
    if (D == NULL) {
        printf("Dictionary Error: calling size() on NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }
    return D->size;
}
// getUnique()
// Returns true (1) if D requires that all pairs have unique keys. Returns
// false (0) if D accepts distinct pairs with identical keys.

int getUnique(Dictionary D)
{
    if (D == NULL) {
        printf("Dictionary Error: calling getUnique() on NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }
    return D->unique;
}

Node findKey(Node R, KEY_TYPE k) {
    if (R == NULL || KEY_CMP(k, R->key) == 0) {
        return R;
    }
    if (KEY_CMP(k, R->key) < 0)
        return findKey(R->left, k);
    else
        return findKey(R->right, k);

}
// lookup()
// If Dictionary D contains a (key, value) pair whose key matches k (i.e. if
// KEY_CMP(key, k)==0), then returns value. If D contains no such pair, then
// returns VAL_UNDEF.

VAL_TYPE lookup(Dictionary D, KEY_TYPE k)
{
    if (D == NULL) {
        printf("Dictionary Error: calling lookup() on NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }
    Node N = findKey(D->root, k);
    if (N == NULL)
        return VAL_UNDEF;
    return N->value;
}
// Manipulation procedures ----------------------------------------------------

// insert()
// Insert the pair (k,v) into Dictionary D. 
// If getUnique(D) is false (0), then there are no preconditions.
// If getUnique(D) is true (1), then the precondition lookup(D, k)==VAL_UNDEF
// is enforced. 

void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v)
{
    if (D == NULL) {
        printf("Dictionary Error: calling insert() on NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }
    if (getUnique(D) == 1) {
        if (lookup(D, k) != VAL_UNDEF) {
            printf("Dictionary Error: can't insert() a key that already exists\n");
            exit(EXIT_FAILURE);
        }
    }
    Node N = newNode(k, v);
    Node Leaf = D->root;
    Node A = NULL;
    while (Leaf != NULL) {
        A = Leaf;
        if (KEY_CMP(k, Leaf->key) < 0) {
            Leaf = Leaf->left;
        }
        else {
            Leaf = Leaf->right;
        }
    }
    if (A == NULL) {
        N->parent = A;
        D->root = N;
    }
    else if (KEY_CMP(k, A->key) < 0) {
        N->parent = A;
        A->left = N;
    }
    else {
        N->parent = A;
        A->right = N;
    }
    D->size++;
}
void Transplant(Dictionary D, Node u, Node v) {
    if (u->parent == NULL) {
        D->root = v;
    }
    else if (u == (u->parent)->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    if (v != NULL) {
        v->parent = u->parent;
    }
}
Node TreeMinimum(Node n) {
    if (n != NULL) {
        while (n->left != NULL) {
            n = n->left;
        }
    }
    return n;
}
// delete()
// Remove the pair whose key is k from Dictionary D.
// Pre: lookup(D,k)!=VAL_UNDEF (i.e. D contains a pair whose key is k.)
void delete(Dictionary D, KEY_TYPE k) {
    if (D == NULL) {
        printf("Dictionary Error: calling insert() on NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }
    if (lookup(D, k) == VAL_UNDEF) {
        printf("Dictionary Error: can't delete() a key that doesn't exist\n");
        exit(EXIT_FAILURE);
    }
    else if (lookup(D, k) != VAL_UNDEF) {
        Node N = findKey(D->root, k);
        Node A = NULL;
        //cursor
        if (D->cursor == N) {
            D->cursor = NULL;
        }
        if (N->left == NULL) {
            Transplant(D, N, N->right);
            freeNode(&N);
            N = NULL;
        }
        else if (N->right == NULL) {
            Transplant(D, N, N->left);
            freeNode(&N);
            N = NULL;
        }
        else {
            A = TreeMinimum(N->right);
            if (A->parent != N) {
                Transplant(D, A, A->right);
                A->right = N->right;
                A->right->parent = A;
            }
            Transplant(D, N, A);
            A->left = N->left;
            A->left->parent = A;
            freeNode(&N);
            N = NULL;
        }
        D->size--;
        freeNode(&N);
    }
}


// makeEmpty()
// Reset Dictionary D to the empty state, containing no pairs.

void makeEmpty(Dictionary D)
{
    if (D == NULL) {
        printf("Dictionary Error: calling makeEmpty() on NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }
   if (D->size == 0)
        return;
    else {
        while (D->root != NULL) {
            delete(D, D->root->key);
        }
        D->cursor = NULL;
        D->root = NULL;
        D->size = 0;
    }
}
Node TreeMaximum(Node n) {
    if (n != NULL) {
        while (n->right != NULL) {
            n = n->right;
        }
    }
    return n;
}
// beginForward()
// If D is non-empty, starts a forward iteration over D at the first key 
// (as defined by the order operator KEY_CMP()), then returns the first
// value. If D is empty, returns VAL_UNDEF. 

VAL_TYPE beginForward(Dictionary D)
{
    if (D == NULL) {
        printf("Dictionary Error: calling beginForward() on NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }
    if (D->size == 0) {
        return VAL_UNDEF;
    }
    D->cursor = TreeMinimum(D->root);
    return currentVal(D);
}
// beginReverse()
// If D is non-empty, starts a reverse iteration over D at the last key 
// (as defined by the order operator KEY_CMP()), then returns the last
// value. If D is empty, returns VAL_UNDEF.

VAL_TYPE beginReverse(Dictionary D)
{
    if (D == NULL) {
        printf("Dictionary Error: calling beginReverse() on NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }
    if (D->size == 0) {
        return VAL_UNDEF;
    }
    D->cursor = TreeMaximum(D->root);
    return currentVal(D);
}
// currentKey()
// If an iteration (forward or reverse) over D has started, returns the 
// the current key. If no iteration is underway, returns KEY_UNDEF.

KEY_TYPE currentKey(Dictionary D)
{
    if (D->cursor == NULL) 
        return KEY_UNDEF;
    return D->cursor->key;
}
// currentVal()
// If an iteration (forward or reverse) over D has started, returns the 
// value corresponding to the current key. If no iteration is underway, 
// returns VAL_UNDEF.

VAL_TYPE currentVal(Dictionary D)
{
    if (D->cursor == NULL)
        return VAL_UNDEF;
    return D->cursor->value;
}

Node TreePredecessor(Node n) {
    if (n->left != NULL) {
        n = TreeMaximum(n->left);
        return n;
    }
    Node x = n->parent;
    while (x != NULL && KEY_CMP(n->key, x->key) < 0) {
        n = x;
        x = x->parent;
    }
    return x;
}
Node TreeSuccessor(Node n) {
    if (n->right != NULL) {
        n = TreeMinimum(n->right);
        return n;
    }
    Node x = n->parent;
    while (x != NULL && n == x->right) {
        n = x;
        x = x->parent;
    }
    return x;

}
// next()
// If an iteration (forward or reverse) over D has started, and has not
// reached the last pair, moves to the next key in D (as defined by the 
// order operator KEY_CMP()), and returns the value corresponding to the 
// new key. If an iteration has started, and has reached the last pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway, 
// returns VAL_UNDEF.

VAL_TYPE next(Dictionary D)
{
    if (D->cursor == NULL)
        return currentVal(D);
    D->cursor = TreeSuccessor(D->cursor);
    return currentVal(D);
}
// prev()
// If an iteration (forward or reverse) over D has started, and has not
// reached the first pair, moves to the previous key in D (as defined by the 
// order operator KEY_CMP()), and returns the value corresponding to the 
// new key. If an iteration has started, and has reached the first pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway, 
// returns VAL_UNDEF. 

VAL_TYPE prev(Dictionary D)
{
    if (D->cursor == NULL)
        return currentVal(D);
    D->cursor = TreePredecessor(D->cursor);
    return currentVal(D);

}
// Other operations -----------------------------------------------------------

// printDictionary()
// Prints a text representation of D to the file pointed to by out. Each key-
// value pair is printed on a single line, with the two items separated by a
// single space.  The pairs are printed in the order defined by the operator
// KEY_CMP().

void printHelper(FILE* out, Node n) {
    if (n != NULL) {
        printHelper(out, n->left);
        fprintf(out, "%s %d\n", n->key, n->value);
        printHelper(out, n->right);
    }
}

void printDictionary(FILE* out, Dictionary D)
{
    if (D == NULL) {
        printf("Dictionary Error: calling printDictionary() on NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }
    Node n = D->root;
    if (n != NULL) {
        printHelper(out, n);
    }
}
