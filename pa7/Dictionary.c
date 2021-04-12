/*
Name: Moises Perez
CruzID: mperez86
Assignment: pa7
*/

#include "Dictionary.h"
#define BLACK 1
#define RED 2

typedef struct NodeObj {

    KEY_TYPE key;
    VAL_TYPE value;
    int color;
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
    Node nil;
}DictionaryObj;

Node newNode(KEY_TYPE k, VAL_TYPE v) {
    Node N = malloc(sizeof(NodeObj));
    N->key = k;
    N->value = v;
    N->color = BLACK;
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
    D->nil = newNode(KEY_UNDEF, VAL_UNDEF);
    D->size = 0;
    D->cursor = D->nil;
    D->unique = unique;
    D->root = D->nil;
    return D;
}
// freeDictionary()
// Frees heap memory associated with *pD, sets *pD to NULL.
void freeDictionary(Dictionary* pD)
{
    if (pD != NULL && *pD != NULL) {
        //free((*pD)->dummy);
        makeEmpty(*pD);
        free((*pD)->nil);
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

Node findKey(Dictionary D, Node R, KEY_TYPE k) {
    if (R == D->nil || KEY_CMP(k, R->key) == 0) {
        return R;
    }
    if (KEY_CMP(k, R->key) < 0)
        return findKey(D, R->left, k);
    else
        return findKey(D, R->right, k);

}
Node TreeMinimum(Dictionary D, Node n) {
    while (n->left != D->nil) {
        n = n->left;
    }
    return n;
}

Node TreeMaximum(Dictionary D, Node n) {
    while (n->right != D->nil) {
        n = n->right;
    }
    return n;
}
Node TreePredecessor(Dictionary D, Node n) {

    if (n->left != D->nil) {
        n = TreeMaximum(D, n->left);
        return n;
    }
    else if (n == D->nil)
        return D->nil;
    else {
        Node x = n->parent;
        while (n == x->left) {
            n = x;
            x = x->parent;
        }
        return x;

    }
}
Node TreeSuccessor(Dictionary D, Node n) {
    if (n->right != D->nil) {
        n = TreeMinimum(D, n->right);
        return n;
    }
    else if (n == D->nil)
        return D->nil;
    else {
        Node x = n->parent;
        while (x != D->nil && n == x->right) {
            n = x;
            x = x->parent;
        }
        return x;

    }
}

//Helper functions for the RBT ADT
//need rotates (left and right), rb insertfixup, rb transplant, rb delete
//print for in order, pre order and post order

/*

//-----------------------------------------------------------------------------
LeftRotate(T, x)
   // set y
   y = x.right

   // turn y's left subtree into x's right subtree
   x.right = y.left
   if y.left != T.nil     // not necessary if using sentinal nil node
      y.left.parent = x

   // link y's parent to x
   y.parent = x.parent
   if x.parent == T.nil
      T.root = y
   else if x == x.parent.left
      x.parent.left = y
   else
      x.parent.right = y

   // put x on y's left
   y.left = x
   x.parent = y
//-----------------------------------------------------------------------------

*/
void LeftRotate(Dictionary D, Node x) {
    Node y = x->right;
    x->right = y->left;

    if (y->left != D->nil)
        y->left->parent = x;

    y->parent = x->parent;
    if (x->parent == D->nil)
        D->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}
/*
//-----------------------------------------------------------------------------
RotateRight(T, x)
   // set y
   y = x.left

   // turn y's right subtree into x's left subtree
   x.left = y.right
   if y.right != T.nil  // not necessary if using sentinal nil node
      y.right.parent = x

   // link y's parent to x
   y.parent = x.parent
   if x.parent == T.nil
      T.root = y
   else if x == x.parent.right
      x.parent.right = y
   else
      x.parent.left = y

   // put x on y's right
   y.right = x
   x.parent = y
//-----------------------------------------------------------------------------
*/
void RightRotate(Dictionary D, Node x) {
    Node y = x->left;
    x->left = y->right;

    if (y->right != D->nil)
        y->right->parent = x;

    y->parent = x->parent;
    if (x->parent == D->nil)
        D->root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;

    y->right = x;
    x->parent = y;
}
/*
//-----------------------------------------------------------------------------
RB_InsertFixUp(T, z)
   while z.parent.color == RED
      if z.parent == z.parent.parent.left
         y = z.parent.parent.right
         if y.color == RED
            z.parent.color = BLACK              // case 1
            y.color = BLACK                     // case 1
            z.parent.parent.color = RED         // case 1
            z = z.parent.parent                 // case 1
         else
            if z == z.parent.right
               z = z.parent                     // case 2
               LeftRotate(T, z)                 // case 2
            z.parent.color = BLACK              // case 3
            z.parent.parent.color = RED         // case 3
            RightRotate(T, z.parent.parent)     // case 3
      else
         y = z.parent.parent.left
         if y.color == RED
            z.parent.color = BLACK              // case 4
            y.color = BLACK                     // case 4
            z.parent.parent.color = RED         // case 4
            z = z.parent.parent                 // case 4
         else
            if z == z.parent.left
               z = z.parent                     // case 5
               RightRotate(T, z)                // case 5
            z.parent.color = BLACK              // case 6
            z.parent.parent.color = RED         // case 6
            LeftRotate(T, z.parent.parent)      // case 6
   T.root.color = BLACK
//-----------------------------------------------------------------------------
*/
void RB_InsertFixUp(Dictionary D, Node z) {
    Node y = D->nil;
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    LeftRotate(D, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                RightRotate(D, z->parent->parent);
            }
        }
        else {
            y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    RightRotate(D, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                LeftRotate(D, z->parent->parent);
            }
        }
    }
    D->root->color = BLACK;
}
/*
//-----------------------------------------------------------------------------
RB_Insert(T, z)
   y = T.nil
   x = T.root
   while x != T.nil
      y = x
      if z.key < x.key
         x = x.left
      else
         x = x.right
   z.parent = y
   if y == T.nil
      T.root = z
   else if z.key < y.key
      y.left = z
   else
      y.right = z
   z.left = T.nil
   z.right = T.nil
   z.color = RED
   RB_InsertFixUp(T, z)
//-----------------------------------------------------------------------------
*/
void RB_Insert(Dictionary D, Node z) {
    Node y = D->nil;
    Node x = D->root;
    while (x != D->nil) {
        y = x;
        if (KEY_CMP(z->key, y->key) < 0) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == D->nil) {
        D->root = z;
    }
    else if (KEY_CMP(z->key, y->key) < 0) {
        y->left = z;
    }
    else {
        y->right = z;
    }
    z->left = D->nil;
    z->right = D->nil;
    z->color = RED;
    RB_InsertFixUp(D, z);
}
/*
//-----------------------------------------------------------------------------
RB_Transplant(T, u, v)
   if u.parent == T.nil
      T.root = v
   else if u == u.parent.left
      u.parent.left = v
   else
      u.parent.right = v
   v.parent = u.parent
//-----------------------------------------------------------------------------
*/
void RB_Transplant(Dictionary D, Node u, Node v) {

    if (u->parent == D->nil)
        D->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    v->parent = u->parent; 
}
/*
//-----------------------------------------------------------------------------
RB_DeleteFixUp(T, x)
   while x != T.root and x.color == BLACK
      if x == x.parent.left
         w = x.parent.right
         if w.color == RED
            w.color = BLACK                        // case 1
            x.parent.color = RED                   // case 1
            LeftRotate(T, x.parent)                // case 1
            w = x.parent.right                     // case 1
         if w.left.color == BLACK and w.right.color == BLACK
            w.color = RED                          // case 2
            x = x.parent                           // case 2
         else
            if w.right.color == BLACK
               w.left.color = BLACK                // case 3
               w.color = RED                       // case 3
               RightRotate(T, w)                   // case 3
               w = x.parent.right                  // case 3
            w.color = x.parent.color               // case 4
            x.parent.color = BLACK                 // case 4
            w.right.color = BLACK                  // case 4
            LeftRotate(T, x.parent)                // case 4
            x = T.root                             // case 4
      else
         w = x.parent.left
         if w.color == RED
            w.color = BLACK                        // case 5
            x.parent.color = RED                   // case 5
            RightRotate(T, x.parent)               // case 5
            w = x.parent.left                      // case 5
         if w.right.color == BLACK and w.left.color == BLACK
            w.color = RED                          // case 6
            x = x.parent                           // case 6
         else
            if w.left.color == BLACK
               w.right.color = BLACK               // case 7
               w.color = RED                       // case 7
               LeftRotate(T, w)                    // case 7
               w = x.parent.left                   // case 7
            w.color = x.parent.color               // case 8
            x.parent.color = BLACK                 // case 8
            w.left.color = BLACK                   // case 8
            RightRotate(T, x.parent)               // case 8
            x = T.root                             // case 8
   x.color = BLACK
//-----------------------------------------------------------------------------
*/
void RB_DeleteFixUp(Dictionary D, Node x) {
    Node w = D->nil;
    while (x != D->root && x->color == BLACK) {
        if (x == x->parent->left) {
            w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                LeftRotate(D, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    RightRotate(D, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                LeftRotate(D, x->parent);
                x = D->root;
            }
        }
        else {
            w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                RightRotate(D, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    LeftRotate(D, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                RightRotate(D, x->parent);
                x = D->root;
            }
        }
    }
    x->color = BLACK;
}
/*
//-----------------------------------------------------------------------------
RB_Delete(T, z)
   y = z
   y_original_color = y.color
   if z.left == T.nil
      x = z.right
      RB_Transplant(T, z, z.right)
   else if z.right == T.nil
      x = z.left
      RB_Transplant(T, z, z.left)
   else
      y = TreeMinimum(z.right)
      y_original_color = y.color
      x = y.right
      if y.parent == z
         x.parent = y
      else
         RB_Transplant(T, y, y.right)
         y.right = z.right
         y.right.parent = y
      RB_Transplant(T, z, y)
      y.left = z.left
      y.left.parent = y
      y.color = z.color
   if y_original_color == BLACK
      RB_DeleteFixUp(T, x)
//-----------------------------------------------------------------------------
*/
void RB_Delete(Dictionary D, Node z) {
    Node y = z;
    Node x = D->nil;
    int y_original_color = y->color;
    if (z->left == D->nil) {
        x = z->right;
        RB_Transplant(D, z, z->right);
    }
    else if (z->right == D->nil) {
        x = z->left;
        RB_Transplant(D, z, z->left);
    }
    else {
        y = TreeMinimum(D, z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        }
        else {
            RB_Transplant(D, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        RB_Transplant(D, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (y_original_color == BLACK) {
        RB_DeleteFixUp(D, x);
    }
}

/*
//-----------------------------------------------------------------------------
InOrderTreeWalk(x)
   if x != NIL
      InOrderTreeWalk(x.left)
      print(x.key)
      InOrderTreeWalk(x.right)
//-----------------------------------------------------------------------------
*/
void InOrderTreeWalk(Dictionary D, FILE* out, Node x) {
    if (x != D->nil) {
        InOrderTreeWalk(D, out, x->left);
        fprintf(out, "%s\n", x->key);
        InOrderTreeWalk(D, out, x->right);
    }
}
/*
//-----------------------------------------------------------------------------
PreOrderTreeWalk(x)
   if x != NIL
      print(x.key)
      PreOrderTreeWalk(x.left)
      PreOrderTreeWalk(x.right)
//-----------------------------------------------------------------------------
*/
void PreOrderTreeWalk(Dictionary D, FILE* out, Node x) {
    if (x != D->nil) {
        fprintf(out, "%s\n", x->key);
        PreOrderTreeWalk(D, out, x->left);
        PreOrderTreeWalk(D, out, x->right);
    }
}
/*
//-----------------------------------------------------------------------------
PostOrderTreeWalk(x)
   if x != NIL
      PostOrderTreeWalk(x.left)
      PostOrderTreeWalk(x.right)
      print(x.key)
//-----------------------------------------------------------------------------
*/
void PostOrderTreeWalk(Dictionary D, FILE* out, Node x) {
    if (x != D->nil) {
        PostOrderTreeWalk(D, out, x->left);
        PostOrderTreeWalk(D, out, x->right);
        fprintf(out, "%s\n", x->key);
    }
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
    Node N = findKey(D, D->root, k);
    if (N == D->nil)
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
    RB_Insert(D, N);
    D->size++;
}
//void Transplant(Dictionary D, Node u, Node v) {
//    if (u->parent == NULL) {
//        D->root = v;
//    }
//    else if (u == (u->parent)->left) {
//        u->parent->left = v;
//    }
//    else {
//        u->parent->right = v;
//    }
//    if (v != NULL) {
//        v->parent = u->parent;
//    }
//}

// delete()
// Remove the pair whose key is k from Dictionary D.
// Pre: lookup(D,k)!=VAL_UNDEF (i.e. D contains a pair whose key is k.)
void delete(Dictionary D, KEY_TYPE k) {
    Node z = findKey(D, D->root, k);
    if (D->cursor == z) {
        D->cursor = D->nil;
    }
    RB_Delete(D, z);
    freeNode(&z);
    D->size--;
}
// makeEmpty()
// Reset Dictionary D to the empty state, containing no pairs.

void makeEmpty(Dictionary D)
{
    if (D->size == 0)
        return;
    else {
        while (D->root != D->nil) {
            delete(D, D->root->key);
        }
        D->cursor = D->nil;
    }
}
// beginForward()
// If D is non-empty, starts a forward iteration over D at the first key 
// (as defined by the order operator KEY_CMP()), then returns the first
// value. If D is empty, returns VAL_UNDEF. 

VAL_TYPE beginForward(Dictionary D)
{
    if (D->size == 0) {
        return VAL_UNDEF;
    }
    D->cursor = TreeMinimum(D, D->root);
    return currentVal(D);
}
// beginReverse()
// If D is non-empty, starts a reverse iteration over D at the last key 
// (as defined by the order operator KEY_CMP()), then returns the last
// value. If D is empty, returns VAL_UNDEF.

VAL_TYPE beginReverse(Dictionary D)
{
    if (D->size == 0) {
        return VAL_UNDEF;
    }
    D->cursor = TreeMaximum(D, D->root);
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

// next()
// If an iteration (forward or reverse) over D has started, and has not
// reached the last pair, moves to the next key in D (as defined by the 
// order operator KEY_CMP()), and returns the value corresponding to the 
// new key. If an iteration has started, and has reached the last pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway, 
// returns VAL_UNDEF.

VAL_TYPE next(Dictionary D)
{
    if (D->cursor == D->nil)
        return currentVal(D);
    D->cursor = TreeSuccessor(D, D->cursor);
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
    if (D->cursor == D->nil)
        return currentVal(D);
    D->cursor = TreePredecessor(D, D->cursor);
    return currentVal(D);

}
// Other operations -----------------------------------------------------------

// printDictionary()
// Prints a text representation of D to the file pointed to by out. Each key-
// value pair is printed on a single line, with the two items separated by a
// single space.  The pairs are printed in the order defined by the operator
// KEY_CMP().

//void printHelper(FILE* out, Node n) {
//    if (n != NULL) {
//        printHelper(out, n->left);
//        fprintf(out, "%s %d\n", n->key, n->value);
//        printHelper(out, n->right);
//    }
//}

void printDictionary(FILE* out, Dictionary D, const char* ord)
{
    Node n = D->root;
    if (strcmp(ord, "pre") == 0) {
        PreOrderTreeWalk(D, out, n);
    }
    else if (strcmp(ord, "in") == 0) {
        InOrderTreeWalk(D, out, n);
    }
    else if (strcmp(ord, "post") == 0) {
        PostOrderTreeWalk(D, out, n);
    }
}
