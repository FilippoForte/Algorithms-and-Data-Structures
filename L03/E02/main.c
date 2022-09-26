//Filippo FOrte L03 E02

#include <stdio.h>
#include <stdlib.h>

//struttura dati utilizzata
typedef struct {char str[255]}canzone;

typedef struct {
    canzone *scelte;
    int num_scelte;
} Livello;

//prototipo funzione princ_molt
int princ_molt(int pos, Livello *val, canzone *sol, int k, int count);

int main() {
    FILE *fin;
    int k = 0;
    Livello *elenco;
    canzone *sol;

    //apertura file
    if ((fin = fopen("../brani.txt", "r")) == NULL) {
        printf("Errore apertura file");
        return 1;
    }

    //numero amici/canzoni da scegliere
    fscanf(fin, "%d", &k);

    //allocazione vettore soluzioni
    sol = (canzone *) calloc(k, sizeof(canzone));
    if (sol == NULL) {
        printf("Allocazione fallita");
        exit(0);
    }

    //allocazione vettore elenco
    elenco = (Livello *)malloc(k * sizeof(Livello));
    if (elenco == NULL) {
        printf("Allocazione fallita");
        exit(0);
    }

    //lettura file e salvataggio nel vettore
    for (int i = 0; i < k; i++) {
        fscanf(fin, "%d", &elenco[i].num_scelte);
        elenco[i].scelte = (canzone *)malloc(elenco[i].num_scelte * sizeof(canzone));

        for (int j = 0; j < elenco[i].num_scelte; j++) {
            fscanf(fin, "%s", &elenco[i].scelte[j]);
        }
    }

    //chiusura file
    fclose(fin);

    //stampa playlist
    printf("%d", princ_molt(0, elenco, sol, k, 0));

    //deallocazione memoria
    free(sol);
    for (int i = 0; i < k; i++)
        free(elenco[i].scelte);
    free(elenco);

    return 0;
}

int princ_molt(int pos, Livello *val, canzone *sol, int k, int count) {
    int i;
    //soluzione trovata
    if (pos >= k) {
        for (i = 0; i < k; i++)
            printf("%s ", sol[i]);
        printf("\n");
        return count + 1;
    }
    //calcolo soluzione
    for (i = 0; i < val[pos].num_scelte; i++) {
        sol[pos] = val[pos].scelte[i];
        count = princ_molt(pos + 1, val, sol, k, count);
    }
    return count;
}