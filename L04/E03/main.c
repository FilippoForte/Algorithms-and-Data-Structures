//Filippo Forte L04 E03
#include <stdio.h>
#include <stdlib.h>

#define N 4

//enumeratore gemme
typedef enum {
    z, r, t, s
} pietre;

//elenco prototipi funzioni utilizzate
int disp_rip(int pos, int *val, int *sol, int n, int k, int cnt, int *stampato);

int promising(int *sol, int *val, int pos, int i);

void stampa(int *sol, int n);

int main() {
    FILE *fin;
    int val[N], *sol;
    int n = 0, stampato;

    //apertura file
    if ((fin = fopen("../testCase/hard_test_set.txt", "r")) == NULL) {
        printf("Errore nell'apertura del file");
        return 1;
    }

    //lettura numero di collane
    fscanf(fin, "%d", &n);

    for (int i = 0; i < n; i++) {
        //lettura numero di gemme disponibili
        fscanf(fin, "%d%d%d%d", &val[z], &val[r], &val[t], &val[s]);
        printf("#TEST %d\n", i+1);

        //inizio da lunghezza massima accettabile
        for (int k = val[z] + val[r] + val[t] + val[s]; k > 1 && !stampato; k--) {
            //allocazione vettore soluzioni
            sol = (int *) calloc(k, sizeof(int));
            stampato = 0;

            //calcolo soluzione
            disp_rip(0, val, sol, 4, k, 0, &stampato);

        }
        stampato=0;
    }

    //chiusura file
    fclose(fin);

    return 0;
}

int disp_rip(int pos, int *val, int *sol, int n, int k, int cnt, int *stampato) {
    int i;
    //soluzione trovata
    if (pos >= k && (*stampato) == 0) {
        stampa(sol, k);
        //stampa solo della prima occorrenza
        *stampato = 1;
        return cnt + 1;
    }

    //calcolo soluzione
    for (i = 0; i < n && (*stampato) == 0; i++) {
        //verifica se la soluzione è promettente (pruning)
        if (promising(sol, val, pos - 1, i) && (*stampato) == 0) {
            sol[pos] = i;
            val[i]--;
            cnt = disp_rip(pos + 1, val, sol, n, k, cnt, stampato);
            val[i]++;
        }

    }
    return cnt;
}


//funzione di verifica delle condizioni di creazione della collana
int promising(int *sol, int *val, int pos, int i) {
    if (pos == -1)
        return 1;
    if (sol[pos] == z && val[i] > 0 && (i == z || i == r))
        return 1;
    if (sol[pos] == s && val[i] > 0 && (i == s || i == t))
        return 1;
    if (sol[pos] == t && val[i] > 0 && (i == z || i == r))
        return 1;
    if (sol[pos] == r && val[i] > 0 && (i == s || i == t))
        return 1;

    return 0;
}

//stampa della collana
void stampa(int *sol, int n) {
    for (int i = 0; i < n; i++) {
        if (sol[i] == z)
            printf("Zaffiro ");
        else if (sol[i] == s)
            printf("Smeraldo ");
        else if (sol[i] == t)
            printf("Topazio ");
        else if (sol[i] == r)
            printf("Rubino ");
    }
    printf("\nDimensione %d\n\n", n);
}