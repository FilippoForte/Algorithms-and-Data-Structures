#ifndef E01_QUOTAZIONE_H
#define E01_QUOTAZIONE_H

#include "stdlib.h"
#include "data.h"

typedef struct quotazione *Quotazione;

Quotazione QuotazioneSetVoid();

data getDataQuotazione(Quotazione x);

int getQuantita(Quotazione x);


int getValore(Quotazione x);

void setQuantita(Quotazione x, int q);
void setGiornata(Quotazione x, data k) ;

void setValore(Quotazione x, int v);

Quotazione newQuotazione(float valore, int quote, data x);

#endif