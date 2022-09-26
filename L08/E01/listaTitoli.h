#ifndef E01_LISTATITOLI_H
#define E01_LISTATITOLI_H

#include "titolo.h"
#include "stdio.h"

typedef struct list *List;

List ListLeggiFile(char nomeFile[], List lista);
List ListInit();
Titolo ricerca(List lista, char *k);
void ListFree(List s);

#endif
