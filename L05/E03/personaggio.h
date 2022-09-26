//Filippo Forte L05 E03
#ifndef E03_PERSONAGGIO_H
#define E03_PERSONAGGIO_H
#define MAXOggetti 8

#include "inventario.h"

//struttura dati utilizzata per l'equipaggiamento di un personaggio
typedef struct {
    oggetto *equip[MAXOggetti];
    int inUso;
} equipaggiamento;

//struttura dati utilizzata per il personaggio
typedef struct {
    char codice[7];
    char nome[MAXN];
    char classe[MAXN];
    statistiche stat;
    equipaggiamento inventario;
} personaggio;


//tipo di dato utilizzato per la creazione della lista
typedef struct nodo *link;
struct nodo {
    personaggio val;
    link next;
};


//elenco prototipi utilizzati
link nuovoNodo(personaggio val, link next);

link inserimentoInTesta(link head, personaggio val);

link aggiungiPersonaggio(link head);

personaggio ricercaPersonaggioPerCodice(link head, char k[]);

personaggio estrazionePersonaggioPerCodice(link *hp, char k[]);

personaggio personaggioSetVoid();

link leggiFilePersonaggi(link head);

void stampaPersonaggio(personaggio x);

void stampaPersonaggiCompleta(link head);

personaggio aggiungiOggettoPersona(link head, char persona[], oggetto *elemento);

void rimuoviOggettoPersona(link head, char elemento[], char persona[]);

void stampaStatistiche(link head, char k[]);

#endif
