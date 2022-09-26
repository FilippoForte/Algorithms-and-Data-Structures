#include "inv.h"

//lettura statistiche da file
void stat_read(FILE *fp, stat_t *statp){
    fscanf(fp, "%d ", &statp->hp);
    fscanf(fp, "%d ", &statp->mp);
    fscanf(fp, "%d ", &statp->atk);
    fscanf(fp, "%d ", &statp->def);
    fscanf(fp, "%d ", &statp->mag);
    fscanf(fp, "%d", &statp->spr);
}

//stampa statistiche su file considerando la soglia minima
void stat_print(FILE *fp, stat_t *statp, int soglia){
    if(statp->hp<soglia)
        fprintf(fp,"0 ");
    else
        fprintf(fp, "%d ", statp->hp);

    if(statp->mp<soglia)
        fprintf(fp,"0 ");
    else
        fprintf(fp, "%d ", statp->mp);

    if(statp->atk<soglia)
        fprintf(fp,"0 ");
    else
        fprintf(fp, "%d ", statp->atk);

    if(statp->def<soglia)
        fprintf(fp,"0 ");
    else
        fprintf(fp, "%d ", statp->def);

    if(statp->mag<soglia)
        fprintf(fp,"0 ");
    else
        fprintf(fp, "%d ", statp->mag);

    if(statp->spr<soglia)
        fprintf(fp,"0\n");
    else
        fprintf(fp, "%d\n", statp->spr);

}

//lettura inventario da file
void inv_read(FILE *fp, inv_t *invp){
    fscanf(fp, "%s", invp->nome);
    fscanf(fp, "%s", invp->tipo);
    stat_read(fp, &(invp->stat));
}

//stampa inventario su file
void inv_print(FILE *fp, inv_t *invp, int soglia){
    stat_t tmp;
    fprintf(fp,"\nNOME OGGETTO: %s\n", invp->nome);
    fprintf(fp,"TIPO OGGETTO: %s\n", invp->tipo);
    tmp=inv_getStat(invp);
    stat_print(fp, &tmp, soglia);
}


stat_t inv_getStat(inv_t *invp){
    return invp->stat;
}

stat_t actualStat(stat_t x, stat_t y){
    stat_t tmp;
    tmp.hp=x.hp+y.hp;
    tmp.mp=x.mp+y.mp;
    tmp.def=x.def+y.def;
    tmp.atk=x.atk+y.atk;
    tmp.spr=x.spr+y.spr;
    tmp.mag=x.mag+y.mag;

    return tmp;
}

void statSetVoid(stat_t *x){
    x->hp=0;
    x->mp=0;
    x->spr=0;
    x->atk=0;
    x->mag=0;
    x->def=0;
}