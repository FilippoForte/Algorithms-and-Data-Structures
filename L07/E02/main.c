//Filippo Forte L07 E02

#include <stdio.h>
#include <stdlib.h>

#define MAXN 100
#define nDiag 3
#define nAcrob 5

typedef struct {
    char nome[MAXN];
    int tipologia;
    int ingresso;
    int uscita;
    int precedenza;
    int finale;
    float valore;
    int difficolta;
} acrobazia;

typedef struct {
    acrobazia acrob[nAcrob];
    int nElementi;
    int uscita;
    int difficolta;
} diagonale;

typedef struct {
    diagonale diag[nDiag];
    int difficolta;
} programma;

acrobazia *leggiFile(acrobazia *elenco, int *n);

void creaProgramma(acrobazia *elenco, programma *p, int nElementi, int DD, int DP);

void setNull(programma *p, int i, int j);

void terzaDiagonale(acrobazia *elenco, int pos, programma *p, int nElementi, int DD, int DP);

void secondaDiagonale(acrobazia *elenco, int pos, programma *p, int nElementi, int DD, int DP);

void primaDiagonale(acrobazia *elenco, int pos, programma *p, int nElementi, int DD, int DP);

void stampaProgramma(programma p);

void MergeSort(acrobazia *A, int N);

void moltiplicatoreUltimaDiagonale(programma *p);


int main() {
    acrobazia *elenco;
    programma prog;
    int n = 0, dd = 10, dp = 20;

    elenco = leggiFile(elenco, &n);
    if (n == -1) {
        return -1;
    }

    //ordinamento
    MergeSort(elenco, n);

    //creazione programma di gara
    creaProgramma(elenco, &prog, n, dd, dp);

    //stampa programma di gara
    stampaProgramma(prog);

    return 0;
}

acrobazia *leggiFile(acrobazia *elenco, int *n) {
    FILE *fin;

    if ((fin = fopen("../elementi.txt", "r")) == NULL) {
        printf("Errore nell'apertura del file");
        exit(1);
    }

    fscanf(fin, "%d", n);

    elenco = (acrobazia *) malloc(*n * sizeof(acrobazia));

    for (int i = 0; i < *n; i++) {
        fscanf(fin, "%s", &elenco[i].nome);
        fscanf(fin, "%d", &elenco[i].tipologia);
        fscanf(fin, "%d", &elenco[i].ingresso);
        fscanf(fin, "%d", &elenco[i].uscita);
        fscanf(fin, "%d", &elenco[i].precedenza);
        fscanf(fin, "%d", &elenco[i].finale);
        fscanf(fin, "%f", &elenco[i].valore);
        fscanf(fin, "%d", &elenco[i].difficolta);
    }
    fclose(fin);
    return elenco;
}

void creaProgramma(acrobazia *elenco, programma *p, int nElementi, int DD, int DP) {

    //azzeramento diagonali
    p->difficolta=0;
    for (int i = 0; i < nDiag; i++)
        for (int j = 0; j < nAcrob; j++)
            setNull(p, i, j);

    for (int i = 0; i < nAcrob; i++) {
        terzaDiagonale(elenco, i, p, nElementi, DD, DP);
        secondaDiagonale(elenco, i, p, nElementi, DD, DP);
        primaDiagonale(elenco, i, p, nElementi, DD, DP);
    }

    moltiplicatoreUltimaDiagonale(p);
}


void terzaDiagonale(acrobazia *elenco, int pos, programma *p, int nElementi, int DD, int DP) {
    int inserito = 0;
    for (int i = 0; i < nElementi && !inserito; i++) {
        //primo elemento
        if (pos == 0) {
            if (elenco[i].precedenza == 0 && elenco[i].tipologia != 0) {
                if (elenco[i].difficolta + p->diag[0].difficolta < DD && p->difficolta + elenco[i].difficolta < DP) {
                    p->diag[2].acrob[pos] = elenco[i];
                    p->diag[2].uscita = elenco[i].uscita;
                    p->diag[2].difficolta += elenco[i].difficolta;
                    p->diag[2].nElementi++;
                    p->difficolta += elenco[i].difficolta;
                    inserito = 1;
                }
            }
        } else {
            //elementi successivi al primo
            if (p->diag[2].uscita = elenco[i].ingresso) {
                if (elenco[i].difficolta + p->diag[0].difficolta < DD && p->difficolta + elenco[i].difficolta < DP) {
                    p->diag[2].acrob[pos] = elenco[i];
                    p->diag[2].uscita = elenco[i].uscita;
                    p->diag[2].difficolta += elenco[i].difficolta;
                    p->diag[2].nElementi++;
                    p->difficolta += elenco[i].difficolta;
                    inserito = 1;
                }
            }
        }
    }
    //verifica ultimo elemento
    if (!inserito)
        if (p->diag[2].acrob[pos - 1].finale == 1)
            for (int i = 0; i < nElementi && !inserito; i++)
                if (p->diag[2].acrob[pos - 2].uscita = elenco[i].ingresso)
                    if (elenco[i].difficolta + p->diag[0].difficolta < DD && p->difficolta + elenco[i].difficolta < DP)
                        if (elenco[i].finale = 0)
                        p->diag[2].acrob[pos - 1] = elenco[i];
}

void secondaDiagonale(acrobazia *elenco, int pos, programma *p, int nElementi, int DD, int DP) {
    int inserito = 0;
    for (int i = 0; i < nElementi && !inserito; i++) {
        //primo elemento
        if (pos == 0) {
            if (elenco[i].precedenza == 0 && elenco[i].tipologia == 2) {
                if (elenco[i].difficolta + p->diag[0].difficolta < DD && p->difficolta + elenco[i].difficolta < DP) {
                    p->diag[1].acrob[pos] = elenco[i];
                    p->diag[1].uscita = elenco[i].uscita;
                    p->diag[1].difficolta += elenco[i].difficolta;
                    p->diag[1].nElementi++;
                    p->difficolta += elenco[i].difficolta;
                    inserito = 1;

                }
            }
        } else if (pos == 1) {
            //secondo elemento
            if (p->diag[1].uscita = elenco[i].ingresso) {
                if (elenco[i].difficolta + p->diag[0].difficolta < DD && p->difficolta + elenco[i].difficolta < DP) {
                    if (elenco[i].tipologia != 0) {
                        p->diag[1].acrob[pos] = elenco[i];
                        p->diag[1].uscita = elenco[i].uscita;
                        p->diag[1].difficolta += elenco[i].difficolta;
                        p->diag[1].nElementi++;
                        p->difficolta += elenco[i].difficolta;
                        inserito = 1;
                    }
                }
            }
        } else {
            //elementi successivi al secondo
            if (p->diag[1].uscita = elenco[i].ingresso) {
                if (elenco[i].difficolta + p->diag[0].difficolta < DD && p->difficolta + elenco[i].difficolta < DP) {
                    p->diag[1].acrob[pos] = elenco[i];
                    p->diag[1].uscita = elenco[i].uscita;
                    p->diag[1].difficolta += elenco[i].difficolta;
                    p->diag[1].nElementi++;
                    p->difficolta += elenco[i].difficolta;
                    inserito = 1;
                }
            }
        }
    }
    //verifica ultimo elemento
    if (!inserito)
        if (p->diag[2].acrob[pos - 1].finale == 1)
            for (int i = 0; i < nElementi && !inserito; i++)
                if (p->diag[2].acrob[pos - 2].uscita = elenco[i].ingresso)
                    if (elenco[i].difficolta + p->diag[0].difficolta < DD && p->difficolta + elenco[i].difficolta < DP)
                        if (elenco[i].finale = 0)
                            p->diag[2].acrob[pos - 1] = elenco[i];
}

void primaDiagonale(acrobazia *elenco, int pos, programma *p, int nElementi, int DD, int DP) {
    int inserito = 0;
    for (int i = 0; i < nElementi && !inserito; i++) {
        if (pos == 0) {
            //primo elemento
            if (elenco[i].precedenza == 0 && elenco[i].tipologia == 1) {
                if (elenco[i].difficolta + p->diag[0].difficolta < DD && p->difficolta + elenco[i].difficolta < DP) {
                    p->diag[0].acrob[pos] = elenco[i];
                    p->diag[0].uscita = elenco[i].uscita;
                    p->diag[0].difficolta += elenco[i].difficolta;
                    p->diag[0].nElementi++;
                    p->difficolta += elenco[i].difficolta;
                    inserito = 1;
                }
            }
        } else {
            //elementi successivi al primo
            if (p->diag[0].uscita = elenco[i].ingresso) {
                if (elenco[i].difficolta + p->diag[0].difficolta < DD && p->difficolta + elenco[i].difficolta < DP) {
                    p->diag[0].acrob[pos] = elenco[i];
                    p->diag[0].uscita = elenco[i].uscita;
                    p->diag[0].difficolta += elenco[i].difficolta;
                    p->diag[0].nElementi++;
                    p->difficolta += elenco[i].difficolta;
                    inserito = 1;
                }
            }
        }
    }
    //verifica ultimo elemento
    if (!inserito)
        if (p->diag[2].acrob[pos - 1].finale == 1)
            for (int i = 0; i < nElementi && !inserito; i++)
                if (p->diag[2].acrob[pos - 2].uscita = elenco[i].ingresso)
                    if (elenco[i].difficolta + p->diag[0].difficolta < DD && p->difficolta + elenco[i].difficolta < DP)
                        if (elenco[i].finale = 0)
                            p->diag[2].acrob[pos - 1] = elenco[i];
}

void moltiplicatoreUltimaDiagonale(programma *p){
    int i=0;
    for (i = 0; i < nAcrob && p->diag[2].acrob[i].difficolta!=-1; ++i);

    if(p->diag[2].acrob[i-1].difficolta>=8)
    {
        p->difficolta-=p->diag[2].difficolta;
        p->diag[2].difficolta=p->diag[2].difficolta*1.5;
        p->difficolta+=p->diag[2].difficolta;
    }
}


//stampa del programma di gara
void stampaProgramma(programma p) {

    //prima diagonale
    printf("PRIMA DIAGONALE:");
    for (int i = 0; i < p.diag[0].nElementi; ++i) {
        printf("\n\t%s", p.diag[0].acrob[i].nome);
    }
    printf("\n\tDifficolta' diagonale: %d\n", p.diag[0].difficolta);

    //seconda diagonale
    printf("SECONDA DIAGONALE:");
    for (int i = 0; i < p.diag[1].nElementi; ++i) {
        printf("\n\t%s", p.diag[1].acrob[i].nome);
    }
    printf("\n\tDifficolta' diagonale: %d\n", p.diag[1].difficolta);

    //terza diagonale
    printf("TERZA DIAGONALE:");
    for (int i = 0; i < p.diag[2].nElementi; ++i) {
        printf("\n\t%s", p.diag[2].acrob[i].nome);
    }
    printf("\n\tDifficolta' diagonale: %d\n", p.diag[2].difficolta);

    printf("\nDifficolta' programma: %d\n", p.difficolta);

}

//ordinamento cosi
void Merge(acrobazia *A, acrobazia *B, int l, int q, int r) {
    int i, j, k;
    i = l;
    j = q + 1;
    for (k = l; k <= r; k++)
        if (i > q)
            B[k] = A[j++];
        else if (j > r)
            B[k] = A[i++];
        else if ((float) (A[i].valore / (float) A[i].difficolta) >= (float) (A[j].valore / (float) A[j].difficolta))
            B[k] = A[i++];
        else
            B[k] = A[j++];
    for (k = l; k <= r; k++)
        A[k] = B[k];
    return;
}

void MergeSortR(acrobazia *A, acrobazia *B, int l, int r) {
    int q;
    if (r <= l)
        return;
    q = (l + r) / 2;
    MergeSortR(A, B, l, q);
    MergeSortR(A, B, q + 1, r);
    Merge(A, B, l, q, r);
}

void MergeSort(acrobazia *A, int N) {
    int l = 0, r = N - 1;
    acrobazia *B = (acrobazia *) malloc(N * sizeof(acrobazia));
    if (B == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }
    MergeSortR(A, B, l, r);
}

void setNull(programma *p, int i, int j) {
    p->diag[i].difficolta = 0;
    p->diag[i].nElementi = 0;
    p->diag[i].acrob[j].difficolta = 0;
    p->diag[i].acrob[j].uscita = -1;
    p->diag[i].acrob[j].ingresso = -1;
    p->diag[i].acrob[j].precedenza = -1;
    p->diag[i].acrob[j].tipologia = -1;
    p->diag[i].acrob[j].valore = -1;
    p->diag[i].acrob[j].finale = -1;
}
