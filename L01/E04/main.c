//Filippo Forte L01 E04
#include <stdio.h>
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
int selezionaComando(int N, struct corsa corse[]);

void InsertionSort_per_data_ora(struct corsa V[], int N, struct corsa *ordinamento[]);


void InsertionSort_per_codice(struct corsa V[], int N, struct corsa *ordinamento[]);

void InsertionSort_per_partenza(struct corsa V[], int N, struct corsa *ordinamento[]);

void InsertionSort_per_arrivo(struct corsa V[], int N, struct corsa *ordinamento[]);

void ricerca_partenza_dicotomica(struct corsa *corse[], int N, char stazione[]);

void stampa(struct corsa *corse[], int N);


int main() {

    FILE *sorgente;
    int N = 0, comando = 0;
    struct corsa corse[1000];

    //apertura file
    if ((sorgente = fopen("../corse.txt", "r")) == NULL) {
        printf("Errore nell'apertura del file");
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

    selezionaComando(N, corse);

    return 0;
}

//lettura del comando inserito dall'utente
int selezionaComando(int N, struct corsa corse[]) {
    int comando = 0, scelta = 0;
    char stazione[30];
    struct corsa *pData[1000], *pCodice[1000], *pPartenza[1000], *pArrivo[1000];

    InsertionSort_per_data_ora(corse, N, pData);
    InsertionSort_per_codice(corse, N, pCodice);
    InsertionSort_per_partenza(corse, N, pPartenza);
    InsertionSort_per_arrivo(corse, N, pArrivo);

    while (comando != 6) {
        printf("Scegliere una delle seguenti opzioni\n1. ordinamento del vettore per data, e a parita' di date per ora\n2. ordinamento del vettore per codice di tratta\n3. ordinamento del vettore per stazione di partenza\n4. ordinamento del vettore per stazione di arrivo\n5. ricerca di una tratta per stazione di partenza\n6. Esci\nScelta: ");
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
        }
    }
}


//funzione per la stampa del risultato a video o su file
void stampa(struct corsa *corse[], int N) {
    int scelta = 0;

    printf("Scegliere come visualizzare il risultato:\n1. stampa a video\n2. stampa su file\nScelta:");
    scanf("%d", &scelta);

    //stampa a video
    if (scelta == 1) {
        for (int i = 0; i < N; i++) {
            printf("%s %s %s %s %s %s %d\n", corse[i]->codice, corse[i]->partenza, corse[i]->destinazione,
                   corse[i]->data, corse[i]->ora_partenza, corse[i]->ora_arrivo, corse[i]->ritardo);
        }
    }
        //stampa su file
    else if (scelta == 2) {
        FILE *fout;

        if ((fout = fopen("../log.txt", "w")) == NULL)
            printf("Errore nell'apertura del file");

        for (int i = 0; i < N; i++) {
            fprintf(fout, "%s %s %s %s %s %s %d\n", corse[i]->codice, corse[i]->partenza, corse[i]->destinazione,
                    corse[i]->data, corse[i]->ora_partenza, corse[i]->ora_arrivo, corse[i]->ritardo);
        }
        fclose(fout);
    }
}



//ordinamento per data e ora
void InsertionSort_per_data_ora(struct corsa V[], int N, struct corsa *ordinamento[]) {
    int i, j, l = 0, r = N - 1;
    struct corsa *x;

    for (int k = 0; k < N; k++) {
        ordinamento[k] = &V[k];
    }

    for (i = l + 1; i <= r; i++) {
        x = &V[i];
        j = i - 1;
        while (j >= l && strcmp(x->ora_partenza, ordinamento[j]->ora_partenza) < 0) {
            ordinamento[j + 1] = ordinamento[j];
            j--;
        }
        ordinamento[j + 1] = x;
    }

    for (i = l + 1; i <= r; i++) {
        x = ordinamento[i];
        j = i - 1;
        while (j >= l && strcmp(x->data, ordinamento[j]->data) < 0) {
            ordinamento[j + 1] = ordinamento[j];
            j--;
        }
        ordinamento[j + 1] = x;
    }

}

//ordinamento per codice tratta
void InsertionSort_per_codice(struct corsa V[], int N, struct corsa *ordinamento[]) {
    int i, j, l = 0, r = N - 1;
    struct corsa *x;

    for (int k = 0; k < N; k++) {
        ordinamento[k] = &V[k];
    }

    for (i = l + 1; i <= r; i++) {
        x = &V[i];
        j = i - 1;
        while (j >= l && strcmp(x->codice, ordinamento[j]->codice) < 0) {
            ordinamento[j + 1] = ordinamento[j];
            j--;
        }
        ordinamento[j + 1] = x;
    }
}

//ordinamento per stazione di partenza
void InsertionSort_per_partenza(struct corsa V[], int N, struct corsa *ordinamento[]) {
    int i, j, l = 0, r = N - 1;
    struct corsa *x;

    for (int k = 0; k < N; k++) {
        ordinamento[k] = &V[k];
    }

    for (i = l + 1; i <= r; i++) {
        x = &V[i];
        j = i - 1;
        while (j >= l && strcmp(x->partenza, ordinamento[j]->partenza) < 0) {
            ordinamento[j + 1] = ordinamento[j];
            j--;
        }
        ordinamento[j + 1] = x;
    }
}

//ordinamento per stazione di arrivo
void InsertionSort_per_arrivo(struct corsa V[], int N, struct corsa *ordinamento[]) {
    int i, j, l = 0, r = N - 1;
    struct corsa *x;

    for (int k = 0; k < N; k++) {
        ordinamento[k] = &V[k];
    }

    for (i = l + 1; i <= r; i++) {
        x = &V[i];
        j = i - 1;
        while (j >= l && strcmp(x->destinazione, ordinamento[j]->destinazione) < 0) {
            ordinamento[j + 1] = ordinamento[j];
            j--;
        }
        ordinamento[j + 1] = x;
    }
}

//ricerca dicotomica parziale con stampa delle occorrenze
void ricerca_partenza_dicotomica(struct corsa *corse[], int N, char stazione[]) {
    int l = 0, r = N - 1, m = 1, risultato = 0, trovato = 0, i = 1;

    while (l <= r && !trovato) {
        m = (l + r) / 2;
        risultato = strncmp(corse[m]->partenza, stazione, strlen(stazione));
        //stazione trovata
        if (risultato == 0) {
            printf("%s %s %s %s %s %s %d\n", corse[m]->codice, corse[m]->partenza, corse[m]->destinazione,
                   corse[m]->data, corse[m]->ora_partenza, corse[m]->ora_arrivo, corse[m]->ritardo);
            trovato = 1;

            //stampa occorrenze
            while ((m + i) < N && strncmp(corse[m + i]->partenza, stazione, strlen(stazione)) == 0) {
                printf("%s %s %s %s %s %s %d\n", corse[m + i]->codice, corse[m + i]->partenza,
                       corse[m + i]->destinazione,
                       corse[m + i]->data, corse[m + i]->ora_partenza, corse[m + i]->ora_arrivo, corse[m + i]->ritardo);
                i++;
            }
            i = -1;
            while ((m + i) > 0 && strncmp(corse[m + i]->partenza, stazione, strlen(stazione)) == 0) {
                printf("%s %s %s %s %s %s %d\n", corse[m + i]->codice, corse[m + i]->partenza,
                       corse[m + i]->destinazione,
                       corse[m + i]->data, corse[m + i]->ora_partenza, corse[m + i]->ora_arrivo, corse[m + i]->ritardo);
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