#ifndef E03_GRAPH_H
#define E03_GRAPH_H

#include "ST.h"
#include <stdio.h>


typedef struct edge {
    int v;
    int w;
    int wt;
} Edge;

typedef struct graph *Graph;
typedef struct node *link;


Graph GRAPHinit(int V);

Graph GRAPHload(FILE *fin, ST tabella);

void GRAPHfree(Graph G);

static int **MATRIXinit(int r, int c, int val);

static Edge EDGEcreate(int v, int w, int wt);

void GRAPHinsertE(Graph G, int id1, int id2, int wt);

static void insertEMat(Graph G, Edge e);

static link NEW(int v, int wt, link next);

void stampaVerticiCompleta(Graph G, ST tabella);

void stampaVertici(Graph G, ST tabella);

int verifica(Graph G, ST tabella, char nome1[], char nome2[], char nome3[]);

static void insertEList(Graph G, Edge e);

void mat_to_list(Graph G);

#endif

