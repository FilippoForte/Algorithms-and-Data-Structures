#include "pgList.h"

typedef struct nodo *link;
struct nodo {
    pg_t val;
    link next;
};

struct pgList_s {
    link head;
};

//inizializzazione lista
pgList_t pgList_init() {
    pgList_t x = (pgList_t) malloc(sizeof(pgList_t));
    x->head = NULL;
    return x;
}

//cancellazione lista
void pgList_free(pgList_t pgList) {
    link x, t;
    for (x = pgList->head; x != NULL; x = t) {
        t = x->next;
        free(x);
    }
    free(pgList);
}

//lettura lista da file
void pgList_read(FILE *fp, pgList_t pgList) {
    pg_t personaggio;


    while(pg_read(fp, &personaggio)!=-1)
        pgList_insert(pgList, personaggio);

}

//scrittura lista su file
void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray) {
    link x;

    for (x = pgList->head; x != NULL; x = x->next) {
        pg_print(fp, &x->val, invArray);
    }
}

//aggiunta nuovo nodo
void pgList_insert(pgList_t pgList, pg_t pg) {
    link x = malloc(sizeof *x);
    if (x==NULL)
        pgList->head= NULL;
    else {
        x->val = pg;
        x->next = pgList->head;
        pgList->head=x;
    }
}

//rimozione nodo
void pgList_remove(pgList_t pgList, char *cod) {
    link x, tmp;
    for (x = pgList->head, tmp = NULL; x != NULL; tmp = x, x = x->next) {
        if (strcmp(x->val.cod, cod) == 0) {
            tmp->next = x->next;
            pg_clean(&x->val);
            free(x);
            return;
        }
    }
    printf("Personaggio non trovato");
}

//ricerca personaggio in lista per codice
pg_t *pgList_searchByCode(pgList_t pgList, char *cod) {
    link x;

    for (x = pgList->head; x != NULL; x = x->next) {
        if (strcmp(x->val.cod, cod) == 0) {
            return &x->val;
        }
    }
}
