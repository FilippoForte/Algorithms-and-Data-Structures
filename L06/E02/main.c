//Forte Filippo L06 E02
#include <stdio.h>
#include <stdlib.h>

#define N 4
typedef enum {
    z, r, t, s
} Pietre;

typedef struct {
    int val[N];
    int *zaffiri;
    int *rubini;
    int *topazi;
    int *smeraldi;
} collana;

int fZ(collana x, int lunghezza);

int fR(collana x, int lunghezza);

int fT(collana x, int lunghezza);

int fS(collana x, int lunghezza);

void inizializzaVettore(collana v1, int nMax);

int max(int x, int y);

int main() {
    int n = 0, nMax = 0;
    FILE *fin;
    collana x;

    if ((fin = fopen("../hard_test_set.txt", "r")) == NULL) {
        printf("Errore nell'apertura del file!");
        exit(1);
    }

    fscanf(fin, "%d", &n);

    for (int i = 0; i < n; i++) {
        fscanf(fin, "%d %d %d %d ", &x.val[z], &x.val[r], &x.val[t], &x.val[s]);

        nMax = x.val[z] + x.val[r] + x.val[t] + x.val[s];
        x.zaffiri = (int *) calloc(nMax, sizeof(int));
        x.rubini = (int *) calloc(nMax, sizeof(int));
        x.topazi = (int *) calloc(nMax, sizeof(int));
        x.smeraldi = (int *) calloc(nMax, sizeof(int));
        printf("Collana %d\n", i);


        x.val[z]--;
        printf("LUNGHEZZA MASSIMA COLLANA CHE INIZIA CON ZAFFIRI: %d\n", fZ(x, nMax)+1);
        inizializzaVettore(x, nMax);
        x.val[z]++;

        x.val[r]--;
        printf("LUNGHEZZA MASSIMA COLLANA CHE INIZIA CON RUBINI: %d\n", fR(x, nMax)+1);
        inizializzaVettore(x, nMax);
        x.val[r]++;

        x.val[t]--;
        printf("LUNGHEZZA MASSIMA COLLANA CHE INIZIA CON TOPAZI: %d\n", fT(x, nMax)+1);
        inizializzaVettore(x, nMax);
        x.val[t]++;

        x.val[s]--;
        printf("LUNGHEZZA MASSIMA COLLANA CHE INIZIA CON SMERALDI: %d\n", fS(x, nMax)+1);
        printf("\n");
        x.val[s]++;

    }

    fclose(fin);

    return 0;
}


int fZ(collana x, int lunghezza) {
    int lunghezza1=0, lunghezza2=0;

    if (lunghezza == 0)
        return 0;

    if (x.val[z] == 0 && x.val[r] == 0)
        return 0;

    if (x.val[z] > 0) {
        if (x.zaffiri[lunghezza - 1] != 0)
            lunghezza1 = x.zaffiri[lunghezza - 1];
        else {
            x.val[z]--;
            lunghezza1 = fZ(x, lunghezza - 1);
        }
    }

    if (x.val[r] > 0) {
        if (x.rubini[lunghezza - 1] != 0)
            lunghezza2 = x.rubini[lunghezza - 1];
        else {
            x.val[r]--;
            lunghezza2 = fR(x, lunghezza - 1);
        }
    }

    return max(lunghezza1 + 1, lunghezza2 + 1);
}


int fT(collana x, int lunghezza) {
    int lunghezza1=0, lunghezza2=0;

    if (lunghezza == 0)
        return 0;

    if (x.val[z] == 0 && x.val[r] == 0)
        return 0;

    if (x.val[z] > 0) {
        if (x.zaffiri[lunghezza - 1] != 0)
            lunghezza1 = x.zaffiri[lunghezza - 1];
        else {
            x.val[z]--;
            lunghezza1 = fZ(x, lunghezza - 1);
        }
    }

    if (x.val[r] > 0) {
        if (x.rubini[lunghezza - 1] != 0)
            lunghezza2 = x.rubini[lunghezza - 1];
        else {
            x.val[r]--;
            lunghezza2 = fR(x, lunghezza - 1);
        }
    }

    return max(lunghezza1 + 1, lunghezza2 + 1);
}


int fS(collana x, int lunghezza) {
    int lunghezza1=0, lunghezza2=0;

    if (lunghezza == 0)
        return 0;

    if (x.val[s] == 0 && x.val[t] == 0)
        return 0;

    if (x.val[s] > 0) {
        if (x.smeraldi[lunghezza - 1] != 0)
            lunghezza1 = x.smeraldi[lunghezza - 1];
        else {
            x.val[s]--;
            lunghezza1 = fS(x, lunghezza - 1);
        }
    }

    if (x.val[t] > 0) {
        if (x.topazi[lunghezza - 1] != 0)
            lunghezza2 = x.topazi[lunghezza - 1];
        else {
            x.val[t]--;
            lunghezza2 = fT(x, lunghezza - 1);
        }
    }

    return max(lunghezza1 + 1, lunghezza2 + 1);
}

int fR(collana x, int lunghezza) {
    int lunghezza1=0, lunghezza2=0;

    if (lunghezza == 0)
        return 0;

    if (x.val[s] == 0 && x.val[t] == 0)
        return 0;

    if (x.val[s] > 0) {
        if (x.smeraldi[lunghezza - 1] != 0)
            lunghezza1 = x.smeraldi[lunghezza - 1];
        else {
            x.val[s]--;
            lunghezza1 = fS(x, lunghezza - 1);
        }
    }

    if (x.val[t] > 0) {
        if (x.topazi[lunghezza - 1] != 0)
            lunghezza2 = x.topazi[lunghezza - 1];
        else {
            x.val[t]--;
            lunghezza2 = fT(x, lunghezza - 1);
        }
    }

    return max(lunghezza1 + 1, lunghezza2 + 1);
}

void inizializzaVettore(collana v1, int nMax) {

    for (int i = 0; i < nMax; i++) {
        v1.topazi[i] = 0;
        v1.rubini[i] = 0;
        v1.smeraldi[i] = 0;
        v1.zaffiri[i] = 0;
    }
}


int max(int x, int y) {
    if (x > y)
        return x;

    return y;
}
