//Forte Filippo L05 E02
#include <stdio.h>
#include <stdlib.h>

//variabile globale utilizzata per salvare il valore massimo della scacchiera
int valMax = 0;

//struttura dati utilizzata per riga/colonna
typedef struct {
    char colore;
    int valore;
} Tubo;

//struttura dati utilizzata per le tessere
typedef struct {
    Tubo riga;
    Tubo colonna;
    int fisso;
} Tessera;

//elenco prototipi di funzione utilizzati
void disp(int pos, Tessera *val, Tessera **sol, int *mark, int nr, int nc, int cnt, Tessera **solFinale);

void copiaSoluzione(Tessera **sol, Tessera **solFinale, int nr, int nc);

void stampa(int nr, int nc, Tessera **sol);

int check(Tessera **sol, int nr, int nc);

int main() {
    Tessera **scacchiera = NULL, *elenco = NULL, **solFinale;
    int nr = 0, nc = 0, nT = 0, indice, rotazione, *mark;
    FILE *fin;

    //apertura file tessere
    if ((fin = fopen("../tiles.txt", "r")) == NULL) {
        printf("Errore nell'apertura del file");
        exit(1);
    }
    //lettura numero di tessere
    fscanf(fin, "%d ", &nT);

    //allocazione vettori
    elenco = (Tessera *) malloc(nT * sizeof(Tessera));
    mark = calloc(nT, sizeof(int));

    //salvataggio tessere
    for (int i = 0; i < nT; i++)
        fscanf(fin, "%s %d %s %d", &elenco[i].riga.colore, &elenco[i].riga.valore, &elenco[i].colonna.colore,
               &elenco[i].colonna.valore);

    //chiusura file tessere
    fclose(fin);

    //apertura file scacchiera
    if ((fin = fopen("../board.txt", "r")) == NULL) {
        printf("Errore nell'apertura del file");
        exit(1);
    }
    //lettura numero righe e colonne
    fscanf(fin, "%d%d", &nr, &nc);

    //allocazione matrici
    scacchiera = (Tessera **) malloc(nc * sizeof(Tessera *));
    solFinale = (Tessera **) malloc(nc * sizeof(Tessera *));
    for (int i = 0; i < nr; i++) {
        scacchiera[i] = (Tessera *) malloc(nc * sizeof(Tessera));
        solFinale[i] = (Tessera *) malloc(nc * sizeof(Tessera));
    }

    //lettura scacchiera
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            fscanf(fin, "%d/%d", &indice, &rotazione);
            //cella vuota
            if (indice == -1 && rotazione == -1) {
                scacchiera[i][j].colonna.valore = -1;
                scacchiera[i][j].riga.valore = -1;
            }
            //tessera presente
            else {
                //tessera ruotata
                if (rotazione == 1) {
                    scacchiera[i][j].riga.valore = elenco[indice].colonna.valore;
                    scacchiera[i][j].colonna.valore = elenco[indice].riga.valore;
                    scacchiera[i][j].riga.colore = elenco[indice].colonna.colore;
                    scacchiera[i][j].colonna.colore = elenco[indice].riga.colore;

                }
                //tessera non ruotata
                else
                    scacchiera[i][j] = elenco[indice];

                scacchiera[i][j].fisso = 1;
                mark[indice] = 1;
            }
        }
    }
    //chiusura file scacchiera
    fclose(fin);

    //calcolo soluzione
    disp(0, elenco, scacchiera, mark, nr, nc, 0, solFinale);

    //stampa soluzione
    stampa(nr, nc, solFinale);
    printf("Valore massimo: %d", valMax);

    return 0;
}

void disp(int pos, Tessera *val, Tessera **sol, int *mark, int nr, int nc, int cnt, Tessera **solFinale) {

    int i, x, y, tmp = 0;

    //soluzione trovata
    if (pos >= nr * nc) {
        //controllo soluzione valida
        tmp = check(sol, nr, nc);

        //controllo se è una soluzione ottima
        if (valMax < tmp) {
            copiaSoluzione(sol, solFinale, nr, nc);
            valMax = tmp;
        }
        return;
    }

    //calcolo indici riga colonna
    y = pos / nc;
    x = pos % 3;

    //controllo che l'elemento non sia tra quelli fissi letti da file
    if (sol[y][x].fisso == 1)
        disp(pos + 1, val, sol, mark, nr, nc, cnt, solFinale);
    else {

        //ciclo su numero di tessere disponibili
        for (i = 0; i < nr * nc; i++) {
            if (mark[i] == 0) {
                if (sol[y][x].fisso != 1) {

                    mark[i] = 1;
                    //soluzione con tessera non ruotata
                    sol[y][x] = val[i];
                    disp(pos + 1, val, sol, mark, nr, nc, cnt, solFinale);

                    //soluzione con tessera ruotata
                    sol[y][x].riga.valore = val[i].colonna.valore;
                    sol[y][x].colonna.valore = val[i].riga.valore;
                    sol[y][x].riga.colore = val[i].colonna.colore;
                    sol[y][x].colonna.colore = val[i].riga.colore;

                    disp(pos + 1, val, sol, mark, nr, nc, cnt, solFinale);

                    mark[i] = 0;
                }
            }

        }
    }
    return;
}


//copia della soluzione della matrice finale
void copiaSoluzione(Tessera **sol, Tessera **solFinale, int nr, int nc) {
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            solFinale[i][j] = sol[i][j];
        }
    }
}

//controllo validità della soluzione
int check(Tessera **sol, int nr, int nc) {
    char colore;
    int valido, valore = 0, tmp = 0;

    //verifica delle righe
    for (int i = 0; i < nr; i++) {
        //valori del primo elemento della riga
        colore = sol[i][0].riga.colore;
        tmp = sol[i][0].riga.valore;
        valido = 1;

        //controllo il resto della riga
        for (int j = 1; j < nc && valido; j++) {
            if (sol[i][j].riga.colore == colore) {
                tmp += sol[i][j].riga.valore;
            } else valido = 0;
        }
        if (valido)
            valore += tmp;
    }

    //verifica delle colonne
    for (int j = 0; j < nc; ++j) {
        //valori del primo elemento della colonna
        colore = sol[0][j].colonna.colore;
        tmp = sol[0][j].colonna.valore;
        valido = 1;

        //controllo il resto della colonna
        for (int i = 1; i < nr && valido; i++) {
            if (sol[i][j].colonna.colore == colore) {
                tmp += sol[i][j].colonna.valore;
            } else valido = 0;
        }
        if (valido)
            valore += tmp;
    }
    return valore;
}

//stampa della scacchiera
void stampa(int nr, int nc, Tessera **sol) {
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            printf("%c %d %c %d \t", sol[i][j].riga.colore, sol[i][j].riga.valore, sol[i][j].colonna.colore,
                   sol[i][j].colonna.valore);
        }
        printf("\n\n");
    }
}