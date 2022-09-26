#ifndef E01_BSTQUOTAZIONI_H
#define E01_BSTQUOTAZIONI_H

#include "quotazione.h"
#include "data.h"
#include "stdio.h"

typedef struct bst *BST;

BST BSTinit();

void BSTfree(BST bst);

Quotazione BSTsearch(BST bst, data k);

void BSTinsert_leafR(BST bst, float valore, int quote, data x);

void riempiBST(FILE *fin, BST x, int n);

void ricercaTraDateWrap(BST x, data k1, data k2, float *min, float *max);

void visitWrap(BST x, float *min, float *max);

void BSTbalance(BST bst);

#endif
