#include "ST.h"

struct symbtab {
    Nodo *a;
    int maxN;
    int size;
};


ST STinit(int maxN) {
    ST st;
    int i;
    st = malloc(sizeof(*st));
    st->a = malloc(maxN * sizeof(Nodo));
    for (i = 0; i < maxN; i++)
        st->a[i] = NodoSetVoid();
    st->maxN = maxN;
    st->size = 0;
    return st;
}


void STinsert(ST st, Nodo val) {
    int i = st->size;
    if (st->size >= st->maxN) {
        st->a = realloc(st->a, (2 * st->maxN) * sizeof(Nodo));
        if (st->a == NULL) return;
        st->maxN = 2 * st->maxN;
    }
    if (STsearch(st, val.nome).val == -1) {
        strcpy(st->a[i].nome, val.nome);
        strcpy(st->a[i].rete, val.rete);
        st->a[i].val = st->size;
        st->size++;
    }
}

int STcount(ST st) {
    return st->size;
}

Nodo STsearch(ST st, char k[]) {
    int i;
    if (st->size == 0)
        return NodoSetVoid();

    for (i = 0; i < st->size; i++)
        if (strcmp(k, st->a[i].nome) == 0)
            return st->a[i];
    return NodoSetVoid();
}

Nodo STselect(ST st, int r){
    return st->a[r];
}

void STfree(ST st) {
    free(st->a);
    free(st);
}

void QuickSort(ST st) {
    int l = 0, r = st->size - 1;
    quicksortR(st->a, l, r);
}

void quicksortR(Nodo *A, int l, int r) {
    int q;
    if (r <= l)
        return;
    q = partition(A, l, r);
    quicksortR(A, l, q - 1);
    quicksortR(A, q + 1, r);
    return;
}

int partition(Nodo *A, int l, int r) {
    int i = l - 1, j = r;
    Nodo x = A[r];
    for (;;) {
        while (strcmp(A[++i].nome, x.nome) < 0);
        while (strcmp(A[--j].nome, x.nome) > 0)
            if (j == l)
                break;
        if (i >= j)
            break;
        Swap(A, i, j);
    }
    Swap(A, i, r);
    return i;
}

void Swap(Nodo *v, int n1, int n2) {
    Nodo temp;
    temp = v[n1];
    v[n1] = v[n2];
    v[n2] = temp;
    return;
}

Nodo STsearchByIndex(ST st, int i){
    return st->a[i];
}