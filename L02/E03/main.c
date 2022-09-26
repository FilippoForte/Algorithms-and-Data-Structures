//Filippo Forte L02 E03
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct utilizzata per memorizare le corse
struct corsa {
    char codice[30];
    char partenza[30];
    char destinazione[30];
    char data[30];
    char ora_partenza[30];
    char ora_arrivo[30];
    int ritardo;
};

//elenco prototipi
int selezionaComando();

struct corsa *InsertionSort_per_partenza(struct corsa V[], int N);

struct corsa *InsertionSort_per_arrivo(struct corsa V[], int N);

struct corsa *InsertionSort_per_codice(struct corsa V[], int N);

struct corsa *InsertionSort_per_data(struct corsa V[], int N);

void ricerca_partenza_dicotomica(struct corsa corse[], int N, char stazione[]);

void stampa(struct corsa *corse, int N);

int sceltaFile(struct corsa corse[]);


int main() {
    selezionaComando();

    return 0;
}

//lettura del comando inserito dall'utente
int selezionaComando() {
    int comando = 0, scelta = 0, N = 0;
    char stazione[30];
    struct corsa *pPartenza, *pArrivo, *pCodice, *pData, corse[1000];

    //lettura file
    N = sceltaFile(corse);

    //allocazione memoria e ordinamento vettori
    pPartenza = InsertionSort_per_partenza(corse, N);
    pArrivo = InsertionSort_per_arrivo(corse, N);
    pCodice = InsertionSort_per_codice(corse, N);
    pData = InsertionSort_per_data(corse, N);

    //elenco comandi
    while (comando != 7) {
        printf("Scegliere una delle seguenti opzioni\n1. ordinamento del vettore per data, e a parita' di date per ora\n2. ordinamento del vettore per codice di tratta\n3. ordinamento del vettore per stazione di partenza\n4. ordinamento del vettore per stazione di arrivo\n5. ricerca di una tratta per stazione di partenza\n6. Cambio File\n7. Esci\nScelta: ");
        scanf("%d", &comando);

        switch (comando) {
            case 1:
                stampa(pData, N);
                break;
            case 2:
                stampa(pCodice, N);
                break;
            case 3:
                stampa(pPartenza, N);
                break;
            case 4:
                stampa(pArrivo, N);
                break;
            case 5:
                printf("Inserire la stazione da ricercare: ");
                scanf("%s", &stazione);
                ricerca_partenza_dicotomica(pPartenza, N, stazione);
                break;

            case 6:
                //deallocazione memoria
                free(pPartenza);
                free(pArrivo);
                free(pCodice);
                free(pData);

                //lettura nuovo file
                N=sceltaFile(corse);

                //allocazione memoria e ordinamento vettori
                pPartenza = InsertionSort_per_partenza(corse, N);
                pArrivo = InsertionSort_per_arrivo(corse, N);
                pCodice = InsertionSort_per_codice(corse, N);
                pData = InsertionSort_per_data(corse, N);

                break;
            case 7:
                printf("Grazie e Arrivederci!");
                break;
        }
    }
}

//funzione per la stampa del risultato a video o su file
void stampa(struct corsa *corse, int N) {
    int scelta = 0;

    printf("Scegliere come visualizzare il risultato:\n1. stampa a video\n2. stampa su file\nScelta:");
    scanf("%d", &scelta);

    //stampa a video
    if (scelta == 1) {
        for (int i = 0; i < N; i++) {
            printf("%s %s %s %s %s %s %d\n", corse[i].codice, corse[i].partenza, corse[i].destinazione,
                   corse[i].data, corse[i].ora_partenza, corse[i].ora_arrivo, corse[i].ritardo);
        }
    }
    //stampa su file
    else if (scelta == 2) {
        FILE *fout;

        if ((fout = fopen("../log.txt", "w")) == NULL)
            printf("Errore nell'apertura del file");

        for (int i = 0; i < N; i++) {
            fprintf(fout, "%s %s %s %s %s %s %d\n", corse[i].codice, corse[i].partenza, corse[i].destinazione,
                    corse[i].data, corse[i].ora_partenza, corse[i].ora_arrivo, corse[i].ritardo);
        }
        fclose(fout);
    }
}

//ordinamento per stazione di partenza
struct corsa *InsertionSort_per_partenza(struct corsa V[], int N) {
    int i, j, l = 0, r = N - 1;
    struct corsa x, *ordinamento;

    //allocazione memoria
    ordinamento = (struct corsa *) malloc(N * sizeof(struct corsa));

    for (int k = 0; k < N; k++) {
        *(ordinamento + k) = V[k];
    }

    //insertion sort
    for (i = l + 1; i <= r; i++) {
        x = V[i];
        j = i - 1;
        while (j >= l && strcmp(x.partenza, ordinamento[j].partenza) < 0) {
            ordinamento[j + 1] = ordinamento[j];
            j--;
        }
        ordinamento[j + 1] = x;
    }
    return ordinamento;
}

//ordinamento per stazione di arrivo
struct corsa *InsertionSort_per_arrivo(struct corsa V[], int N) {
    int i, j, l = 0, r = N - 1;
    struct corsa x, *ordinamento;

    //allocazione memoria
    ordinamento = (struct corsa *) malloc(N * sizeof(struct corsa));

    for (int k = 0; k < N; k++) {
        *(ordinamento + k) = V[k];
    }

    //insertion sort
    for (i = l + 1; i <= r; i++) {
        x = V[i];
        j = i - 1;
        while (j >= l && strcmp(x.destinazione, ordinamento[j].destinazione) < 0) {
            ordinamento[j + 1] = ordinamento[j];
            j--;
        }
        ordinamento[j + 1] = x;
    }
    return ordinamento;
}

//ordinamento per stazione di arrivo
struct corsa *InsertionSort_per_codice(struct corsa V[], int N) {
    int i, j, l = 0, r = N - 1;
    struct corsa x, *ordinamento;

    //allocazione memoria
    ordinamento = (struct corsa *) malloc(N * sizeof(struct corsa));

    for (int k = 0; k < N; k++) {
        *(ordinamento + k) = V[k];
    }

    //insertion sort
    for (i = l + 1; i <= r; i++) {
        x = V[i];
        j = i - 1;
        while (j >= l && strcmp(x.codice, ordinamento[j].codice) < 0) {
            ordinamento[j + 1] = ordinamento[j];
            j--;
        }
        ordinamento[j + 1] = x;
    }
    return ordinamento;
}

//ordinamento per stazione di partenza
struct corsa *InsertionSort_per_data(struct corsa V[], int N) {
    int i, j, l = 0, r = N - 1;
    struct corsa x, *ordinamento;

    //allocazione memoria
    ordinamento = (struct corsa *) malloc(N * sizeof(struct corsa));

    for (int k = 0; k < N; k++) {
        *(ordinamento + k) = V[k];
    }

    //insertion sort
    for (i = l + 1; i <= r; i++) {
        x = V[i];
        j = i - 1;
        while (j >= l && strcmp(x.ora_partenza, ordinamento[j].ora_partenza) < 0) {
            ordinamento[j + 1] = ordinamento[j];
            j--;
        }
        ordinamento[j + 1] = x;
    }

    for (i = l+1; i <= r; i++) {
        x = ordinamento[i];
        j = i - 1;
        while (j >= l && strcmp(x.data, ordinamento[j].data) < 0) {
            ordinamento[j + 1] = ordinamento[j];
            j--;
        }
        ordinamento[j + 1] = x;
    }
    return ordinamento;
}

//ricerca dicotomica parziale con stampa delle occorrenze
void ricerca_partenza_dicotomica(struct corsa corse[], int N, char stazione[]) {
    int l = 0, r = N - 1, m = 1, risultato = 0, trovato = 0, i = 1;

    while (l <= r && !trovato) {
        m = (l + r) / 2;
        risultato = strncmp(corse[m].partenza, stazione, strlen(stazione));
        //stazione trovata
        if (risultato == 0) {
            printf("%s %s %s %s %s %s %d\n", corse[m].codice, corse[m].partenza, corse[m].destinazione,
                   corse[m].data, corse[m].ora_partenza, corse[m].ora_arrivo, corse[m].ritardo);
            trovato = 1;

            //stampa occorrenze
            while (strncmp(corse[m + i].partenza, stazione, strlen(stazione)) == 0) {
                printf("%s %s %s %s %s %s %d\n", corse[m + i].codice, corse[m + i].partenza, corse[m + i].destinazione,
                       corse[m + i].data, corse[m + i].ora_partenza, corse[m + i].ora_arrivo, corse[m + i].ritardo);
                i++;
            }
            i = -1;
            while (strncmp(corse[m + i].partenza, stazione, strlen(stazione)) == 0) {
                printf("%s %s %s %s %s %s %d\n", corse[m + i].codice, corse[m + i].partenza, corse[m + i].destinazione,
                       corse[m + i].data, corse[m + i].ora_partenza, corse[m + i].ora_arrivo, corse[m + i].ritardo);
                i--;
            }
            return;

        } else if (risultato > 0) {
            r = m - 1;
        } else if (risultato < 0) {
            l = m + 1;
        }
    }
    printf("La stazione inserita non e' presente!\n");
}

int sceltaFile(struct corsa corse[]) {

    FILE *sorgente;
    int N = 0;
    char nomeFile[30]="../";

    //inserimento nome file
    printf("Inserire il nome del file: ");
    scanf("%s", &nomeFile[3]);

    //apertura file
    if ((sorgente = fopen(nomeFile, "r")) == NULL)
    {
        printf("Errore apertura file");
        return 1;
    }

    //lettura tabella
    fscanf(sorgente, "%d", &N);
    for (int i = 0; i < N; i++) {
        fscanf(sorgente, "%s%s%s%s%s%s%d", &corse[i].codice, &corse[i].partenza, &corse[i].destinazione, &corse[i].data,
               &corse[i].ora_partenza, &corse[i].ora_arrivo, &corse[i].ritardo);
    }

    //chiusura file
    fclose(sorgente);

    return N;
}