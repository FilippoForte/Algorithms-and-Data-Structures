//Filippo Forte L05 E03
#include "inventario.h"

//lettura ed inserimento degli oggetti da file
oggetto *leggiFileInventario(int *nOggetti) {
    FILE *fin;
    oggetto *elenco;
    int n;

    //apertura file
    if ((fin = fopen("../inventario.txt", "r")) == NULL) {
        printf("Errore nell'apertura del file degli oggetti!");
        exit(1);
    }

    fscanf(fin, "%d", &n);
    //allocazione vettore
    elenco = (oggetto *) malloc(n * sizeof(oggetto));
    *nOggetti=n;

    //lettura singoli oggetti
    for (int i = 0; i < n; i++)
        fscanf(fin, "%s %s %d %d %d %d %d %d ", &elenco[i].nome, &elenco[i].tipo, &elenco[i].stat.hp,
               &elenco[i].stat.mp, &elenco[i].stat.atk, &elenco[i].stat.def, &elenco[i].stat.mag, &elenco[i].stat.spr);

    //chiusura file
    fclose(fin);
    return elenco;
}

//ricerca oggetto per nome
oggetto *cercaOggetto(char ricerca[], oggetto elenco[], int n){
    for (int i = 0; i < n; i++) {
        if(strcmp(elenco[i].nome,ricerca)==0)
            return elenco + i;
    }
    printf("Oggetto ricercato non presente");
    return NULL;
}


//stampa singolo oggetto
void stampaOggetto(oggetto *x){
    printf("\nNOME: %s\nTIPO: %s\nSTATISTICHE\n%d %d %d %d %d %d\n", (*x).nome, (*x).tipo, (*x).stat.hp, (*x).stat.mp, (*x).stat.atk, (*x).stat.def, (*x).stat.mag, (*x).stat.spr);
}

//stampa oggetti completi
void stampaOggettiCompleta(oggetto *inventario, int n){
    for (int i = 0; i < n; i++) {
        stampaOggetto(&inventario[i]);
    }
}