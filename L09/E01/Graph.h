#ifndef GRAPH_H
#define GRAPH_H

#include "ST.h"

typedef struct edge { int v; int w; int wt; } Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *fin);
void  GRAPHinsertE(Graph G, int id1, int id2, int wt);
void  GRAPHlpBF(Graph G, int id);
int GRAPHdfs(Graph G, int id);
Edge *creaElencoArchi(Graph G);
int rimuoviArchi(Graph G, Edge *elenco, int k);
int findSetDAG(Graph G) ;
void GRAPHspD_Wrap(Graph G);

#endif
