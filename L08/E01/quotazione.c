#include "quotazione.h"

struct quotazione {
    data giornata;
    float valoreTot;
    int quantitaTot;
};

Quotazione newQuotazione(float valore, int quote, data x) {
    Quotazione tmp = (Quotazione)malloc(sizeof(Quotazione));

    tmp->quantitaTot = quote;
    tmp->valoreTot = valore;
    tmp->giornata = x;
    return tmp;
}

Quotazione QuotazioneSetVoid() {
    Quotazione x = (Quotazione)malloc(sizeof(Quotazione));

    x->valoreTot = -1;
    x->quantitaTot = -1;
    return x;
}

data getDataQuotazione(Quotazione x) {
    return x->giornata;
}

int getQuantita(Quotazione x) {
    return x->quantitaTot;
}

int getValore(Quotazione x) {
    return x->valoreTot;
}

void setQuantita(Quotazione x, int q) {
    x->quantitaTot = q;
}

void setValore(Quotazione x, int v) {
    x->valoreTot = v;
}

void setGiornata(Quotazione x, data k) {
    x->giornata = k;
}