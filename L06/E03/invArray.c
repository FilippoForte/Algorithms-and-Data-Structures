#include "invArray.h"

//vettore inventario
struct invArray_s{
    inv_t *elenco;
    int nOgg;
};

//iniziailizzazione del vettore inventario
invArray_t invArray_init(){
    invArray_t x;
    x=(struct invArray_s*) malloc(sizeof(struct invArray_s));
    x->elenco= NULL;
    x->nOgg=0;
}

//deallocazione del vettore inventario
void invArray_free(invArray_t invArray){
    free(invArray->elenco);
    free(invArray);
}

//lettura del vettore inventario da file
void invArray_read(FILE *fp, invArray_t invArray){
    int n;
    fscanf(fp, "%d", &invArray->nOgg);

    invArray->elenco=(inv_t*) malloc(n*sizeof (inv_t));

    for (int i = 0; i < invArray->nOgg; i++)
        inv_read(fp, &invArray->elenco[i]);
}

//scrittura del vettore inventario su file
void invArray_print(FILE *fp, invArray_t invArray){
    for (int i = 0; i < invArray->nOgg; i++)
        invArray_printByIndex(fp, invArray, i);
}

//scrittura di un elemento del vettore inventario su file
void invArray_printByIndex(FILE *fp, invArray_t invArray, int index){
    inv_print(fp, invArray_getByIndex(invArray, index), INT_MIN);
}

//ritorno di un elemento del vettore inventario
inv_t *invArray_getByIndex(invArray_t invArray, int index){
    return &(invArray->elenco[index]);
}

//ricerca per nome di un elemento nel vettore inventario
int invArray_searchByName(invArray_t invArray, char *name){
    for (int i = 0; i < invArray->nOgg; i++) {
        if(strcmp(name, invArray->elenco[i].nome)==0)
            return i;
    }
    return -1;
}
