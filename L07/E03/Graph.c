#include "Graph.h"

struct node {
    int v;
    int wt;
    link next;
};

struct graph {
    int V;
    int E;
    int **madj;
    link *ladj;
    link z;
};

Graph GRAPHinit(int V) {
    Graph G = malloc(sizeof *G);
    int v;
    G->V = V;
    G->E = 0;
    G->madj = MATRIXinit(V, V, 0);
    G->z = NEW(-1, -1, NULL);
    G->ladj = malloc(G->V*sizeof(link));
    for (v = 0; v < G->V; v++)
        G->ladj[v] = G->z;
    return G;

    return G;
}

void GRAPHfree(Graph G) {
    int i;
    int v;
    link t, next;

    for (i = 0; i < G->V; i++)
        free(G->madj[i]);
    free(G->madj);

    for (v = 0; v < G->V; v++)
        for (t = G->ladj[v]; t != G->z; t = next) {
            next = t->next;
            free(t);
        }
    free(G->ladj);
    free(G->z);
    free(G);
}

static int **MATRIXinit(int r, int c, int val) {
    int i, j;
    int **t = malloc(r * sizeof(int *));
    for (i = 0; i < r; i++) t[i] = malloc(c * sizeof(int));
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            t[i][j] = val;
    return t;
}

static Edge EDGEcreate(int v, int w, int wt) {
    Edge e;
    e.v = v;
    e.w = w;
    e.wt = wt;
    return e;
}

Graph GRAPHload(FILE *fin, ST tabella) {
    int id1, id2, wt;
    char nome1[MAXN], nome2[MAXN], rete1[MAXN], rete2[MAXN];
    Graph G;
    G = GRAPHinit(STcount(tabella));
    while (fscanf(fin, "%s %s %s %s %d", nome1, rete1, nome2, rete2, &wt) == 5) {
        id1 = GetValue(STsearch(tabella, nome1));
        id2 = GetValue(STsearch(tabella, nome2));
        if (id1 >= 0 && id2 >= 0)
            GRAPHinsertE(G, id1, id2, wt);
    }
    return G;
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
    insertEMat(G, EDGEcreate(id1, id2, wt));
}

static void insertEMat(Graph G, Edge e) {
    int v = e.v, w = e.w, wt = e.wt;
    if (G->madj[v][w] == 0)
        G->E++;
    G->madj[v][w] = wt;
    G->madj[w][v] = wt;
}

void stampaVerticiCompleta(Graph G, ST tabella) {
    int h, k;
    for (int i = 0; i < G->V; i++) {
        stampaNodo(STselect(tabella, i));
        k = GetValue(STselect(tabella, i));
        for (int j = 0; j < STcount(tabella); j++) {
            h = GetValue(STselect(tabella, j));
            if (G->madj[k][h] != 0) {
                printf("\t");
                stampaNodo(STselect(tabella, j));
            }
        }
    }
}

void stampaVertici(Graph G, ST tabella) {
    for (int i = 0; i < G->V; i++)
        stampaNodo(STselect(tabella, i));
}

int verifica(Graph G, ST tabella, char nome1[], char nome2[], char nome3[]) {
    int x = GetValue(STsearch(tabella, nome1));
    int y = GetValue(STsearch(tabella, nome2));
    int z = GetValue(STsearch(tabella, nome3));

    if (G->madj[x][y] != 0 && G->madj[z][y] != 0 && G->madj[x][z] != 0)
        return 1;

    return 0;
}


void mat_to_list(Graph G) {
    for (int i = 0; i < G->V; i++) {
        for (int j = 0; j < G->V; j++) {
            if(G->madj[i][j]!=0)
                if(i>j)
                insertEList(G, EDGEcreate(i, j,G->madj[i][j]));
        }
    }
}

static void insertEList(Graph G, Edge e) {
    int v = e.v, w = e.w, wt = e.wt;
    G->ladj[v] = NEW(w, wt, G->ladj[v]);
    G->ladj[w] = NEW(v, wt, G->ladj[w]);
}

static link NEW(int v, int wt, link next) {
    link x = malloc(sizeof *x);
    x->v = v; x->wt = wt; x->next = next;
    return x;
}

