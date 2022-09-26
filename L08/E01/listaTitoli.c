#include "listaTitoli.h"

typedef struct node *link;
struct node {
    Titolo val;
    link next;
};
struct list {
    link head;
};


List ListInit() {
    List x;
    x = (List) malloc(sizeof(struct list));
    x->head = NULL;
    return x;
}


static link newNode(Titolo val, link next) {
    link x = malloc(sizeof *x);
    if (x == NULL)
        return NULL;
    else {
        x->val = val;
        x->next = next;
    }
    return x;
}

static link SortListIns(link h, Titolo val) {
    link x, p;
    char *k = getNomeTitolo(val);
    if (h == NULL || strcmp(getNomeTitolo(h->val), k) > 0)
        return newNode(val, h);

    for (x = h->next, p = h; x != NULL && strcmp(k, getNomeTitolo(x->val)) > 0; p = x, x = x->next);

    if (strcmp(k, getNomeTitolo(p->val)) == 0)
        return h;

    p->next = newNode(val, x);

    return h;
}

List ListLeggiFile(char nomeFile[], List lista) {

    FILE *fin;
    int n, transazioni;
    Titolo tmp;
    char k[21];

    if ((fin = fopen(nomeFile, "r")) == NULL) {
        printf("Errore nell'apertura del file");
        exit(1);
    }

    fscanf(fin, "%d", &n);

    for (int i = 0; i < n; i++) {
        fscanf(fin, "%s %d", &k, &transazioni);
        tmp = newTitolo();
        setNomeTitolo(k, tmp);
        lista->head = SortListIns(lista->head, tmp);

        riempiBST(fin, getBSTTitolo(tmp), transazioni);
    }
    return lista;
}


Titolo SortListSearch(link h, char *k) {
    link x;
    for (x = h; x != NULL; x = x->next)
        if (strcmp(getNomeTitolo(x->val), k) == 0)
            return x->val;
    return titoloSetVoid();
}

Titolo ricerca(List lista, char *k) {
    return SortListSearch(lista->head, k);
}

void ListFree(List s) {
    link x, t;
    for (x = s->head; x != NULL; x = t) {
        t = x->next;
        freeTitolo(x->val);
        free(x);
    }
    free(s);
}