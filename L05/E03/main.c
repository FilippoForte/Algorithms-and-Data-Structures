//Filippo Forte L05 E03
#include <stdio.h>
#include "personaggio.h"

int main() {
    link head = NULL, *xp;
    oggetto *elenco, *oggettoTmp;
    personaggio personaggioTmp;
    int scelta, elencoCaricato = 0, nOggetti = 0;
    char codice[7], elemento[MAXN];

    while (scelta != 9) {

        printf("\n1.Carica personaggi in lista\n2.Carica inventario in vettore\n3.Aggiungi un nuovo personaggio\n4.Elimina un personaggio\n5.Aggiungi equipaggiamento personaggio\n6.Rimuovi equipaggiamento personaggio\n7.Calcola statistiche\n8.Stampa personaggi\n9.Esci\nScegli:");
        scanf("%d", &scelta);

        switch (scelta) {
            //Opzione 1 caricamento personaggi da file in lista
            case 1:
                head = leggiFilePersonaggi(head);
                break;

                //Opzione 2 caricamento inventario da file in vettore
            case 2:
                elenco = leggiFileInventario(&nOggetti);
                elencoCaricato = 1;
                break;

                //Opzione 3 aggiunta personaggio da tastiera
            case 3:
                head = aggiungiPersonaggio(head);
                break;

                //Opzione 4 eliminazione personaggio
            case 4:
                //controllo lista vuota
                if (head != NULL) {

                    printf("ELENCO PERSONAGGI");
                    stampaPersonaggiCompleta(head);
                    printf("\nInserire il codice del personaggio da eliminare: ");
                    scanf("%s", &codice);

                    xp = &head;
                    //estrazione personaggio
                    personaggioTmp = estrazionePersonaggioPerCodice(xp, codice);

                    //controllo esistenza personaggio
                    if (strcmp(personaggioTmp.codice, "-1") == 0)
                        printf("Personaggio non presente\n");
                    else {
                        //stampa personaggio eliminato
                        printf("Personaggio eliminato: ");
                        stampaPersonaggio(personaggioTmp);
                    }
                } else
                    printf("Nessun personaggio presente!\n");
                break;

                //Opzione 5 aggiunta equipaggiamento personaggio
            case 5:
                //controllo lista vuota
                if (head != NULL) {
                    printf("ELENCO PERSONAGGI");
                    stampaPersonaggiCompleta(head);

                    printf("\nScegliere il personaggio a cui modificare l'equipaggiamento:");
                    scanf("%s", &codice);

                    //controllo inventario vuoto
                    if (elencoCaricato) {
                        stampaOggettiCompleta(elenco, nOggetti);

                        printf("Scegliere l'oggetto da aggiungere:");
                        scanf("%s", &elemento);

                        oggettoTmp = cercaOggetto(elemento, elenco, nOggetti);
                        if (oggettoTmp!=NULL){
                            //aggiunta oggetto
                            personaggioTmp = aggiungiOggettoPersona(head, codice, oggettoTmp);
                            //controllo esistenza personaggio
                            if (strcmp(personaggioTmp.codice, "-1") == 0)
                                printf("Codice personaggio inesistente");
                        }
                    } else
                        printf("Nessun oggetto presente!\n");
                } else
                    printf("Nessun personaggio presente!\n");

                break;

                //Opzione 6 rimozione equipaggiamento personaggio
            case 6:
                //controllo lista vuota
                if (head != NULL) {
                    printf("ELENCO PERSONAGGI");
                    stampaPersonaggiCompleta(head);

                    printf("\nScegliere il personaggio a cui modificare l'equipaggiamento:");
                    scanf("%s", &codice);

                    if (elencoCaricato) {
                        stampaOggettiCompleta(elenco, nOggetti);

                        printf("Scegliere l'oggetto da rimuovere:");

                        scanf("%s", &elemento);

                        //rimozione oggetto
                        rimuoviOggettoPersona(head, elemento, codice);

                    } else
                        printf("Nessun oggetto presente!\n");
                } else
                    printf("Nessun personaggio presente!\n");

                break;

                //Opzione 7 stampa statiche personaggio con bonus/malus
            case 7:
                if (head != NULL) {

                    printf("Scegliere il personaggio di cui si vogliono visualizzare le statistiche complete: ");
                    scanf("%s", &codice);

                    stampaStatistiche(head, codice);
                } else
                    printf("Nessun personaggio presente!\n");

                break;

                //Opzione 8 stampa completa
            case 8:
                //controllo lista vuota
                if (head != NULL) {
                    printf("ELENCO PERSONAGGI");
                    stampaPersonaggiCompleta(head);
                } else
                    printf("Nessun personaggio presente!\n");
                break;
            case 9:
                printf("Grazie e arrivederci!");
                break;
        }
    }
    return 0;
}

