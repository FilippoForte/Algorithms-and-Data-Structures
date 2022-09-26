#include "BSTquotazioni.h"

typedef struct nodo *link;
struct nodo {
    Quotazione item;
    link l;
    link r;
    int N;
};
struct bst {
    link root;
    link z;
};

static link NEW(Quotazione item, link l, link r, int N) {
    link x = malloc(sizeof *x);
    x->item = item;
    x->l = l;
    x->r = r;
    x->N = N;
    return x;
}

BST BSTinit() {
    BST tree = malloc(sizeof *tree);
    tree->root = (tree->z = NEW(QuotazioneSetVoid(), NULL, NULL, 0));
    return tree;
}

static void treeFree(link h, link z) {
    if (h == z)
        return;
    treeFree(h->l, z);
    treeFree(h->r, z);
    free(h);
}

void BSTfree(BST bst) {
    if (bst == NULL)
        return;
    treeFree(bst->root, bst->z);
    free(bst->z);
    free(bst);
}


static link insertR(link h, Quotazione x, link z) {
    if (h == z)
        return NEW(x, z, z, 1);
    if (dataCmp(getDataQuotazione(x), getDataQuotazione(h->item)) == -1)
        h->l = insertR(h->l, x, z);
    else
        h->r = insertR(h->r, x, z);

    (h->N)++;
    return h;
}

void BSTinsert_leafR(BST bst, float valore, int quote, data x) {
    bst->root = insertR(bst->root, newQuotazione(valore, quote, x), bst->z);
}

void riempiBST(FILE *fin, BST x, int n) {
    data tmp;
    int aa, mm, gg, quote;
    float valore;
    Quotazione quotTmp;

    for (int i = 0; i < n; i++) {

        fscanf(fin, "%d/%d/%d %*c%*c%*c%*c%*c %f %d", &aa, &mm, &gg, &valore, &quote);
        setData(&tmp, aa, mm, gg);

        quotTmp = BSTsearch(x, tmp);
        if (getQuantita(quotTmp) == -1)
        {
            setQuantita(quotTmp, quote);
            setValore(quotTmp, valore*quote);
            setGiornata(quotTmp, tmp);
            x->root = insertR(x->root, quotTmp, x->z);
        }
        else {
            setQuantita(quotTmp, getQuantita(quotTmp) + quote);
            setValore(quotTmp, getValore(quotTmp) + quote * valore);
        }

    }
}

Quotazione searchR(link h, data k, link z) {
    int cmp;
    if (h == z)
        return QuotazioneSetVoid();
    cmp = dataCmp(k, getDataQuotazione(h->item));
    if (cmp == 0)
        return h->item;
    if (cmp == -1)
        return searchR(h->l, k, z);
    return searchR(h->r, k, z);
}

Quotazione BSTsearch(BST bst, data k) {
    return searchR(bst->root, k, bst->z);
}

void ricercaTraDate(link root, data k1, data k2, float *min, float *max) {
    if (getQuantita(root->item) == -1)
        return;
    if (dataCmp(getDataQuotazione(root->l->item), k1) >= 0)
        ricercaTraDate(root->l, k1, k2, min, max);

    if (*min > (float) (getValore(root->item) / (float) getQuantita(root->item)))
        *min = (float) (getValore(root->item) / (float) getQuantita(root->item));
    if (*max < (float) (getValore(root->item) / (float) getQuantita(root->item)))
        *max = (float) (getValore(root->item) / (float) getQuantita(root->item));

    if (dataCmp(getDataQuotazione(root->l->item), k2) <= 0)
        ricercaTraDate(root->r, k1, k2, min, max);
}

void ricercaTraDateWrap(BST x, data k1, data k2, float *min, float *max) {
    ricercaTraDate(x->root, k1, k2, min, max);

}


void visit(link root, float *min, float *max, int *pos) {
    if (root == NULL) {
        if (*pos > *max)
            *max = *pos;
        else if (*pos < *max)
            *min = *pos;
        return;
    }
    (*pos)++;
    visit(root->l, min, max, pos);
    visit(root->r, min, max, pos);
    (*pos)--;
}

void visitWrap(BST x, float *min, float *max) {
    int pos=1;
    visit(x->root, min, max, &pos);
}


link rotR(link h) {
    link x = h->l;
    h->l = x->r;
    x->r = h;
    return x;
}

link rotL(link h) {
    link x = h->r;
    h->r = x->l;
    x->l = h;
    return x;
}

link partR(link h, int r) {
    int t = h->l->N;
    if (t > r) {
        h->l = partR(h->l, r);
        h = rotR(h);
    }
    if (t < r) {
        h->r = partR(h->r, r - t - 1);
        h = rotL(h);
    }
    return h;
}


static link balanceR(link h, link z) {
    int r;
    if (h == z)
        return z;
    r = (h->N + 1) / 2 - 1;
    h = partR(h, r);
    h->l = balanceR(h->l, z);
    h->r = balanceR(h->r, z);
    return h;
}

void BSTbalance(BST bst) {
    bst->root = balanceR(bst->root, bst->z);
}