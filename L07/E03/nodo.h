#ifndef E03_NODO_H
#define E03_NODO_H
#define MAXN 31

#include "string.h"
#include "stdio.h"

typedef struct {
    char nome[MAXN];
    char rete[MAXN];
    int val;
} Nodo;

Nodo NodoSetVoid();

Nodo creaNodo(char nome[], char rete[]);

int GetValue(Nodo x);

void stampaNodo(Nodo x);
#endif
