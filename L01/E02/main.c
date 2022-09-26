//Filippo Forte L01 E02
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

//elenco comandi
typedef enum {
    r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine
} comando_e;


//elenco prototipi
int leggiComando();

void selezionaDati(int comando, int N, struct corsa corse[]);

void ricerca_per_date(struct corsa corse[], int N, char data_inizio[], char data_fine[], int ritaro);

void ricerca_stazione_partenza(struct corsa corse[], int N, char stazione[]);

void ricerca_stazione_arrivo(struct corsa corse[], int N, char stazione[]);

void ritardo_tot(struct corsa corse[], int N, int codice);


int main() {

    FILE *sorgente;
    int N = 0, comando = 0;
    struct corsa corse[1000];

    //apertura file
    if ((sorgente = fopen("../corse.txt", "r")) == NULL)
        return "Errore nell'apertura del file";

    //lettura tabella
    fscanf(sorgente, "%d", &N);
    for (int i = 0; i < N; i++) {
        fscanf(sorgente, "%s%s%s%s%s%s%d", &corse[i].codice, &corse[i].partenza, &corse[i].destinazione, &corse[i].data,
               &corse[i].ora_partenza, &corse[i].ora_arrivo, &corse[i].ritardo);
    }

    //chiusura file
    fclose(sorgente);

    //esecuzione vari comandi
    while (comando != r_fine) {
        comando = leggiComando();
        selezionaDati(comando, N, corse);
    }

    return 0;
}

//lettura del comando inserito dall'utente
int leggiComando() {
    char comando[30];
    int scelta = 0;

    printf("Scegliere uno dei seguenti comandi: date/partenza/capolinea/ritardo/ritardo_tot/fine: ");
    scanf("%s", &comando);

    //elenco comandi possibili
    char tab[6][15] = {
            "date", "partenza", "capolinea", "ritardo", "ritardo_tot", "fine"
    };

    while (scelta < r_fine && strcmp(comando, tab[scelta]) != 0)
        scelta++;
    return scelta;

}

//funzione per l'inserimento dei dati necesari e chiamata della relativa funzione
void selezionaDati(int comando, int N, struct corsa corse[]) {

    char data_inizio[11] = {}, data_fine[11] = {}, stazione[30] = {}, codice[30];
    int ritardo;

    switch (comando) {
        case r_date:

            printf("Inserire un intervallo di date nel formato aaaa/mm/gg!\nData di inizio intervallo:");
            scanf("%s", &data_inizio);
            printf("Data di fine intervallo:");
            scanf("%s", &data_fine);
            ricerca_per_date(corse, N, data_inizio, data_fine, 0);
            break;

        case r_partenza:
            printf("Inserire la stazione di partenza dei treni: ");
            scanf("%s", stazione);
            ricerca_stazione_partenza(corse, N, stazione);
            break;

        case r_capolinea:
            printf("Inserire la stazione di arrivo dei treni: ");
            scanf("%s", stazione);
            ricerca_stazione_arrivo(corse, N, stazione);
            break;

        case r_ritardo:
            printf("Inserire un intervallo di date nel formato aaaa/mm/gg!\nData di inizio intervallo:");
            scanf("%s", &data_inizio);
            printf("Data di fine intervallo:");
            scanf("%s", &data_fine);
            ricerca_per_date(corse, N, data_inizio, data_fine, ritardo);
            break;

        case r_ritardo_tot:
            printf("Inserire un codice corsa: ");
            scanf("%s", codice);
            ritardo_tot(corse, N, codice);
            break;

        case r_fine:
            printf("Grazie e Arrivederci!");
            break;

    }

}

//funzione per la ricerca in intervallo di date con e senza ritardo
void ricerca_per_date(struct corsa corse[], int N, char data_inizio[], char data_fine[], int ritardo) {

    for (int i = 0; i < N; i++) {
        if (strcmp(corse[i].data, data_inizio) == 1 && strcmp(corse[i].data, data_fine) == -1) {
            if (ritardo != 0) {
                if (corse[i].ritardo != 0) {
                    printf("%s %s %s %s %s %s %d\n", corse[i].codice, corse[i].partenza, corse[i].destinazione,
                           corse[i].data, corse[i].ora_partenza, corse[i].ora_arrivo, corse[i].ritardo);
                }
            } else {
                printf("%s %s %s %s %s %s %d\n", corse[i].codice, corse[i].partenza, corse[i].destinazione,
                       corse[i].data, corse[i].ora_partenza, corse[i].ora_arrivo, corse[i].ritardo);
            }
        }
    }
}

//funzione ricerca corse da stazione di partenza
void ricerca_stazione_partenza(struct corsa corse[], int N, char stazione[]) {
    int trovato = 0;

    printf("Elenco corse con partenza %s:\n", stazione);

    for (int i = 0; i < N; i++) {
        if (strcmp(corse[i].partenza, stazione) == 0) {
            printf("%s %s %s %s %s %s %d\n", corse[i].codice, corse[i].partenza, corse[i].destinazione,
                   corse[i].data, corse[i].ora_partenza, corse[i].ora_arrivo, corse[i].ritardo);

            trovato = 1;
        }
    }
    if (!trovato) {
        printf("Non sono presenti corse con partenza da %s\n", stazione);
    }
}

//funzione ricerca corse da stazione capolinea
void ricerca_stazione_arrivo(struct corsa corse[], int N, char stazione[]) {
    int trovato = 0;

    printf("Elenco corse con capolinea %s:\n", stazione);

    for (int i = 0; i < N; i++) {
        if (strcmp(corse[i].destinazione, stazione) == 0) {
            printf("%s %s %s %s %s %s %d\n", corse[i].codice, corse[i].partenza, corse[i].destinazione,
                   corse[i].data, corse[i].ora_partenza, corse[i].ora_arrivo, corse[i].ritardo);

            trovato = 1;
        }
    }
    if (!trovato) {
        printf("Non sono presenti corse con capolinea %s\n", stazione);
    }
}


//funzione per il calcolo del ritardo totale
void ritardo_tot(struct corsa corse[], int N, int codice) {
    int ritardo = 0;
    for (int i = 0; i < N; i++) {
        if (strcmp(corse[i].codice, codice) == 0)
            ritardo += corse[i].ritardo;
    }

    printf("Il ritardo totale accumulato sulle corse con codice %s è di %d minuti\n", codice, ritardo);
}