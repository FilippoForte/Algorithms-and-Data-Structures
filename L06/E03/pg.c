#include "pg.h"

//inizializzazione nuovo personaggio
int pg_read(FILE *fp, pg_t *pgp) {
    if (fscanf(fp, "%s %s %s", pgp->cod, pgp->nome, pgp->classe) == EOF)
        return -1;
    else {
        stat_read(fp, &pgp->b_stat);
        statSetVoid(&pgp->eq_stat);
        pgp->equip = equipArray_init();
        return 1;
    }
}

//liberazione personaggio
void pg_clean(pg_t *pgp) {
    equipArray_free(pgp->equip);
}

//stampa personaggio
void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray) {
    stat_t tmp;

    fprintf(fp, "\n\nCODICE: %s\n", pgp->cod);
    fprintf(fp, "NOME: %s\n", pgp->nome);
    fprintf(fp, "CLASSE: %s\n", pgp->classe);

    fprintf(fp, "\nSTATISTICHE:\n");
    tmp=actualStat(pgp->b_stat, pgp->eq_stat);
    stat_print(fp, &tmp, MIN_STAT);

    if (equipArray_inUse(pgp->equip) > 0) {
        printf("\nEQUIPAGGIAMENTO:\n");
        equipArray_print(fp, pgp->equip, invArray);
    }
}

//modifica equipaggiamento personaggio
void pg_updateEquip(pg_t *pgp, invArray_t invArray) {
    equipArray_update(pgp->equip, invArray);
    modificaStatistiche(pgp, invArray);
}

void modificaStatistiche(pg_t *pgp, invArray_t invArray){
    stat_t tmp;
    for (int i = 0; i < equipArray_inUse(pgp->equip); i++) {
        tmp= inv_getStat(invArray_getByIndex(invArray, equipArray_getEquipByIndex(pgp->equip, i)));
        pgp->eq_stat.hp+=tmp.hp;
        pgp->eq_stat.mp+=tmp.mp;
        pgp->eq_stat.atk+=tmp.atk;
        pgp->eq_stat.def+=tmp.def;
        pgp->eq_stat.mag+=tmp.mag;
        pgp->eq_stat.spr+=tmp.spr;
    }
}
