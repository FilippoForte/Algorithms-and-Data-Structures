#ifndef E03_ST_H
#define E03_ST_H

#include "nodo.h"
#include "stdlib.h"

typedef struct symbtab *ST;

ST STinit(int maxN);

void STfree(ST st);

int STcount(ST st);

void STinsert(ST st, Nodo val);

Nodo STsearch(ST st, char k[]);

Nodo STsearchByIndex(ST st, int i);

void QuickSort(ST st);

void quicksortR(Nodo *A, int l, int r);

int partition(Nodo *A, int l, int r);

void Swap(Nodo *v, int n1, int n2);


void STdelete(ST st, char k[]);

Nodo STselect(ST st, int r);

void STdisplay(ST st);

#endif
