//Filippo Forte L05 E03
#ifndef E03_INVENTARIO_H
#define E03_INVENTARIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 51

//struttura dati utilizzata per la memorizzazione delle statistiche
typedef struct {
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
} statistiche;

//struttura dati utilizzata per memorizzare gli oggetti
typedef struct {
    char nome[MAXN];
    char tipo[MAXN];
    statistiche stat;
} oggetto;


//elenco prototipi utilizzati
oggetto *leggiFileInventario(int *nOggetti);

oggetto *cercaOggetto(char ricerca[], oggetto elenco[], int n);

void stampaOggettiCompleta(oggetto *inventario, int n);

void stampaOggetto(oggetto *x);

#endif
