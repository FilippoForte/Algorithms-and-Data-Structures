//Filippo Forte L02 E02
#include <stdio.h>
#include <stdlib.h>

//prototipi funzioni utilizzate
int **malloc2dR(int nr, int nc, FILE *fin);

void separa(int **mat, int nr, int nc, int *bianco, int *nero);

int main() {
    int **matr, nr, nc, *bianco, *nero;
    FILE *fin;

    //apertura file
    if ((fin = fopen("../mat.txt", "r")) == NULL) {
        printf("Errore apertura file");
        return 1;
    }

    fscanf(fin, "%d%d", &nr, &nc);

    //lettura del file e salvatagio nella matrice
    matr = malloc2dR(nr, nc, fin);
    //chiusura file
    fclose(fin);

    //allocazione memoria dei vettori bianco e nero
    bianco = (int *) malloc((nr * nc + 1) * sizeof(int));
    nero = (int *) malloc((nr * nc + 1) * sizeof(int));

    //separazione della matrice nei vettori bianco e nero
    separa(matr, nr, nc, bianco, nero);

    //stampa dei vettori bianco e nero
    printf("Bianco: ");
    for (int i = 0; i < (nr * nc + 1) / 2; i++)
        printf("%d ", bianco[i]);

    printf("\nNero: ");
    for (int i = 0; i < nr * nc / 2; i++)
        printf("%d ", nero[i]);


    //deallocazione memoria matrice, bianco e nero
    for (int i = 0; i < nr; i++)
        free(matr[i]);
    free(matr);
    free(bianco);
    free(nero);

    return 0;
}

int **malloc2dR(int nr, int nc, FILE *fin) {
    int **matr;

    //allocazione memoria vettore di puntatori
    matr = (int **) malloc(nr * sizeof(int *));
    if (matr == NULL) {
        printf("Memoria non disponibile");
        exit(1);
    }

    //allocazione memoria righe
    for (int i = 0; i < nr; i++) {
        matr[i] = (int *) malloc(nc * sizeof(int));
        if (matr[i] == NULL) {
            printf("Memoria non disponibile");
            exit(1);
        }
        //riempimento matrice
        for (int j = 0; j < nc; j++)
            fscanf(fin, "%d", &matr[i][j]);
    }

    return matr;
}

void separa(int **mat, int nr, int nc, int *bianco, int *nero) {

    int x = 1; //variabile utilizzata per alternare bianco e nero
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            if (x) {
                *(bianco++) = mat[i][j];
                x = 0;
            } else {
                *(nero++) = mat[i][j];
                x = 1;
            }
        }
    }
}