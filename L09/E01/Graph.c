#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"

#define MAXC 10

//strutture dati utilizzate
typedef struct node *link;
struct node {
    int v;
    int wt;
    link next;
};
struct graph {
    int V;
    int E;
    link *ladj;
    ST tab;
    link z;
};

static Edge EDGEcreate(int v, int w, int wt);

static link NEW(int v, int wt, link next);

static void insertE(Graph G, Edge e);

static void removeE(Graph G, Edge e);

static Edge EDGEcreate(int v, int w, int wt) {
    Edge e;
    e.v = v;
    e.w = w;
    e.wt = wt;
    return e;
}

static link NEW(int v, int wt, link next) {
    link x = malloc(sizeof *x);
    if (x == NULL)
        return NULL;
    x->v = v;
    x->wt = wt;
    x->next = next;
    return x;
}

Graph GRAPHinit(int V) {
    int v;
    Graph G = malloc(sizeof *G);
    if (G == NULL)
        return NULL;

    G->V = V;
    G->E = 0;
    G->z = NEW(-1, 0, NULL);
    if (G->z == NULL)
        return NULL;
    G->ladj = malloc(G->V * sizeof(link));
    if (G->ladj == NULL)
        return NULL;
    for (v = 0; v < G->V; v++)
        G->ladj[v] = G->z;
    G->tab = STinit(V);
    if (G->tab == NULL)
        return NULL;
    return G;
}

void GRAPHfree(Graph G) {
    int v;
    link t, next;
    for (v = 0; v < G->V; v++)
        for (t = G->ladj[v]; t != G->z; t = next) {
            next = t->next;
            free(t);
        }
    STfree(G->tab);
    free(G->ladj);
    free(G->z);
    free(G);
}

Graph GRAPHload(FILE *fin) {
    int V, i, id1, id2, wt;
    char label1[MAXC], label2[MAXC];
    Graph G;

    fscanf(fin, "%d", &V);
    G = GRAPHinit(V);
    if (G == NULL)
        return NULL;

    for (i = 0; i < V; i++) {
        fscanf(fin, "%s", label1);
        STinsert(G->tab, label1, i);
    }

    while (fscanf(fin, "%s %s %d", label1, label2, &wt) == 3) {
        id1 = STsearch(G->tab, label1);
        id2 = STsearch(G->tab, label2);
        if (id1 >= 0 && id2 >= 0)
            GRAPHinsertE(G, id1, id2, wt);
    }
    return G;
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
    insertE(G, EDGEcreate(id1, id2, wt));
}

static void insertE(Graph G, Edge e) {
    int v = e.v, w = e.w, wt = e.wt;

    G->ladj[v] = NEW(w, wt, G->ladj[v]);
    G->E++;
}

static void removeE(Graph G, Edge e) {
    int v = e.v, w = e.w;
    link x;
    if (G->ladj[v]->v == w) {
        G->ladj[v] = G->ladj[v]->next;
        G->E--;
    } else
        for (x = G->ladj[v]; x != G->z; x = x->next)
            if (x->next->v == w) {
                x->next = x->next->next;
                G->E--;
            }
}

//verifica connessione grafo
void dfsRcc(Graph G, int v, int id, int *cc) {
    link t;
    cc[v] = id;
    for (t = G->ladj[v]; t != G->z; t = t->next)
        if (cc[t->v] == -1)
            dfsRcc(G, t->v, id, cc);
}
int GRAPHcc(Graph G) {
    int v, id = 0, *cc;
    cc = malloc(G->V * sizeof(int));
    for (v = 0; v < G->V; v++) cc[v] = -1;
    for (v = 0; v < G->V; v++)
        if (cc[v] == -1) dfsRcc(G, v, id++, cc);

    return id;
}

void dfsR(Graph G, Edge e, int *time, int *pre, int *post, int *st, int *ciclo) {
    link t;
    int v, w = e.w;
    Edge x;

    st[e.w] = e.v;
    pre[w] = (*time)++;

    for (t = G->ladj[w]; t != G->z && *ciclo == 0; t = t->next)
        if (pre[t->v] == -1)
            dfsR(G, EDGEcreate(w, t->v, t->wt), time, pre, post, st, ciclo);
        else {
            v = t->v;
            x = EDGEcreate(w, v, t->wt);
            //verifica presenza cicli
            if (post[v] == -1)
                *ciclo = 1;

        }
    post[w] = (*time)++;
}

int GRAPHdfs(Graph G, int id) {
    int v, time = 0, *pre, *post, *st, ciclo = 0;

    st = malloc(G->V * sizeof(int));
    pre = malloc(G->V * sizeof(int));
    post = malloc(G->V * sizeof(int));

    for (v = 0; v < G->V; v++) {
        pre[v] = -1;
        post[v] = -1;
        st[v] = -1;
    }

    dfsR(G, EDGEcreate(id, id, 0), &time, pre, post, st, &ciclo);
    for (v = 0; v < G->V; v++)
        if (pre[v] == -1)
            dfsR(G, EDGEcreate(v, v, 0), &time, pre, post, st, &ciclo);

    //verifica grafo connesso
    if (ciclo)
        return 0;
    else if (GRAPHcc(G) > 1)
        return 0;

    return 1;
}

int powerset_r(Edge *val, int k, Edge *sol, int j, int pos, int start, Graph G, int *trovato, Edge *solMax, int *max) {
    int cnt = 0, i, somma = 0;

    //soluzione trovata
    if (pos == j) {
        //verifica validità
        if (rimuoviArchi(G, sol, j)) {
            if (j == 0) {
                printf("Il grafo e' gia' un DAG\n");
                *trovato = 2;

            } else {
                //stampa della soluzione
                for (int h = 0; h < pos; h++) {
                    somma += sol[h].wt;
                    printf("%s --> %s  %d\n", STsearchByIndex(G->tab, sol[h].v), STsearchByIndex(G->tab, sol[h].w),
                           sol[h].wt);
                }
                printf("------------\n");
                //verifica peso dell'insieme
                if (somma > *max) {
                    *max = somma;
                    for (int j = 0; j < k; j++) {
                        solMax[j].v = sol[j].v;
                        solMax[j].w = sol[j].w;
                        solMax[j].wt = sol[j].wt;
                    }
                }
                *trovato = 1;
            }
        }
    }
    //ricerca soluzione
    for (i = start; i < k; i++) {
        sol[pos].w = val[i].w;
        sol[pos].wt = val[i].wt;
        sol[pos].v = val[i].v;

        cnt += powerset_r(val, k, sol, j, pos + 1, i + 1, G, trovato, solMax, max);
    }
    return cnt;
}

int findSetDAG(Graph G) {
    int trovato = 0, i = 0, max = 0;
    Edge *val, *sol, *solMax, *tmp;

    sol = (Edge *) calloc(G->E, sizeof(Edge));
    solMax = (Edge *) calloc(G->E, sizeof(Edge));

    //creazione elenco di tutti gli archi
    val = creaElencoArchi(G);

    printf("ARCHI CHE CREANO CICLI:\n");

    for (i = 0; i < G->E - 1 && trovato == 0; i++)
        powerset_r(val, G->E, sol, i, 0, 0, G, &trovato, solMax, &max);

    //rimozione archi
    if (trovato == 1) {
        for (int h = 0; h < i; h++)
            removeE(G, solMax[h]);

        //stampa archi rimossi
        printf("Arco rimosso:\n");
        for (int h = 0; h < i - 1; h++) {
            printf("%s --> %s  %d\n", STsearchByIndex(G->tab, solMax[h].v), STsearchByIndex(G->tab, solMax[h].w),
                   solMax[h].wt);
        }
    }
    free(sol);
    free(solMax);
    free(val);
}

Edge *creaElencoArchi(Graph G) {
    Edge *elencoArchi;
    int h = 0;
    link t;

    elencoArchi = (Edge *) calloc(G->E, sizeof(Edge));

    for (int i = 0; i < G->V; i++)
        for (t = G->ladj[i]; t != G->z; t = t->next) {
            elencoArchi[h].v = i;
            elencoArchi[h].w = t->v;
            elencoArchi[h++].wt = t->wt;
        }
    return elencoArchi;
}

int rimuoviArchi(Graph G, Edge *elenco, int k) {
    int valido = 0;

    for (int i = 0; i < k; i++)
        removeE(G, elenco[i]);

    //verifica aciclicità e connesione
    valido = GRAPHdfs(G, 0);

    for (int i = 0; i < k; i++)
        insertE(G, elenco[i]);

    return valido;
}

//ordinamento topologico
void TSdfsR(Graph G, int v, int *ts, int *pre, int *time) {
    link t;
    pre[v] = 0;
    for (t = G->ladj[v]; t != G->z; t = t->next)
        if (pre[t->v] == -1)
            TSdfsR(G, t->v, ts, pre, time);
    ts[(*time)++] = v;
}
void DAGrts(Graph G) {
    int v, time = 0, *pre, *ts;

    pre = (int *) calloc(G->V, sizeof(int));
    ts = (int *) calloc(G->V, sizeof(int));
    for (v = 0; v < G->V; v++) {
        pre[v] = -1;
        ts[v] = -1;
    }
    for (v = 0; v < G->V; v++)
        if (pre[v] == -1) TSdfsR(G, v, ts, pre, &time);

    free(pre);
    free(ts);
}
Graph reverse(Graph G) {
    int v;
    link t;
    Graph R = GRAPHinit(G->V);
    for (v = 0; v < G->V; v++)
        for (t = G->ladj[v]; t != G->z; t = t->next)
            GRAPHinsertE(R, t->v, v, t->wt);
    return R;
}

void GRAPHlpBF(Graph G, int id) {
    int v, w;
    link t;
    int *st, *mindist, negcycfound;

    st = malloc(G->V * sizeof(int));
    mindist = malloc(G->V * sizeof(int));
    if ((st == NULL) || (mindist == NULL))
        return;

    for (v = 0; v < G->V; v++) {
        st[v] = -1;
        mindist[v] = 0;
    }

    mindist[id] = 1;
    st[id] = id;

    //individuazione lunghezza massima
    for (w = 0; w < G->V - 1; w++)
        for (v = 0; v < G->V; v++)
            if (mindist[v] > 0)
                for (t = G->ladj[v]; t != G->z; t = t->next)
                    if (mindist[t->v] < mindist[v] + t->wt) {
                        mindist[t->v] = mindist[v] + t->wt;
                        st[t->v] = v;
                    }
    negcycfound = 0;
    //verifica cicli negativi
    for (v = 0; v < G->V; v++)
        if (mindist[v] >0)
            for (t = G->ladj[v]; t != G->z; t = t->next)
                if (mindist[t->v] < mindist[v] + t->wt)
                    negcycfound = 1;
    if (negcycfound == 0) {
        //stampa distanze
        printf("\n Distanze massime dal nodo %s\n", STsearchByIndex(G->tab, id));
        for (v = 0; v < G->V; v++) {
            if (mindist[v] == 0)
                printf("Nodo %s irraggiungibile dal nodo %s\n", STsearchByIndex(G->tab, v),
                       STsearchByIndex(G->tab, id));
            else
                printf("Distanza massima per raggiungere %s dal nodo %s: %d \n", STsearchByIndex(G->tab, v),
                       STsearchByIndex(G->tab, id), mindist[v] - 1);
        }
    } else
        printf("\n Negative cycle found!\n");
}


void GRAPHspD_Wrap(Graph G) {

    //ordinamento topologico
    DAGrts(G);
    Graph R = reverse(G);
    R->tab = G->tab;

    for (int v = 0; v < R->V; v++)
        GRAPHlpBF(R, v);
}