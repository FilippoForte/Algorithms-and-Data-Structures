//Filippo Forte L04 E01
#include <stdio.h>
#include <stdlib.h>

//struttura dati utilizzata per gli archi
typedef struct {
    int inizio;
    int fine;
} arco;


//prototipi di funzioni utilizzate
int powerset(int pos, int *nodi, int *sol, int k, int cnt, arco *archi, int nArchi);

int aggiungiNodo(int *nodi, int nNodi, int inizio, int fine, int cnt);

int check(int *nodi, int *sol, arco *archi, int nNodi, int nArchi);

int main() {
    FILE *fin;
    int nNodi = 0, nArchi, *nodi, *sol, cnt;
    arco *archi;

    //apertura file
    if ((fin = fopen("../grafo.txt", "r")) == NULL) {
        printf("Errore nell'apertura del file");
        return 1;
    }

    //lettura numero di nodi e archi
    fscanf(fin, "%d%d", &nNodi, &nArchi);

    //allocamento vettori
    nodi = (int *) calloc(nNodi, sizeof(int));
    archi = (arco *) malloc(nArchi * sizeof(arco));
    sol = (int *) calloc(nNodi, sizeof(int));

    //azzeramento nodi
    for (int i = 0; i < nNodi;i++){
        nodi[i]=-1;
    }

    //lettura archi e nodi
    for (int i = 0; i < nArchi; i++) {
        fscanf(fin, "%d%d", &archi[i].inizio, &archi[i].fine);
        cnt = aggiungiNodo(nodi, nNodi, archi[i].inizio, archi[i].fine, cnt);
    }

    powerset(0, nodi, sol, nNodi, 0, archi, nArchi);

    //chiusura file
    fclose(fin);

    return 0;
}

//inserimento nodi
int aggiungiNodo(int *nodi, int nNodi, int inizio, int fine, int cnt) {
    int x = 0, y = 0;

    for (int i = 0; i < nNodi; i++) {
        if (nodi[i] == inizio && nodi[i]!=-1)
            x = 1;
        if (nodi[i] == fine && nodi[i]!=-1)
            y = 1;
    }
    if (!x)
        nodi[cnt++] = inizio;
    if (!y)
        nodi[cnt++] = fine;

    return cnt;
}

//powerset con disposizioni ripetute
int powerset(int pos, int *nodi, int *sol, int k, int cnt, arco *archi, int nArchi) {

    //soluzione trovata
    if (pos >= k) {
        //controllo se seoluzione valida
        if(check(nodi, sol,archi, k, nArchi)){
            for (int i = 0; i < k; i++) {
                if(sol[i]!=0){
                    printf("%d ", nodi[i]);
                }
            }
            printf("\n");
        }
        return cnt + 1;
    }

    //calcolo soluzione
    sol[pos] = 0;
    cnt = powerset(pos + 1, nodi, sol, k, cnt, archi, nArchi);
    sol[pos] = 1;
    cnt = powerset(pos + 1, nodi, sol, k, cnt, archi, nArchi);
    return cnt;
}

//funzione di controllo soluzione
int check(int *nodi, int *sol, arco *archi, int nNodi, int nArchi) {
    int out=1;
    //for per tutti gli archi
    for (int i = 0; i < nArchi && out; i++) {
        out=0;
        for (int j = 0; j < nNodi; j++) {
            //controllo che ogni arco contenga almeno un nodo della soluzione
            if(sol[j]!=0 && (nodi[j]==archi[i].inizio || nodi[j]==archi[i].fine))
                out=1;
        }
    }
    return out;
}