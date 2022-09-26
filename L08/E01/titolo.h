#ifndef E01_TITOLO_H
#define E01_TITOLO_H

#include "BSTquotazioni.h"
#include "string.h"
#include "stdlib.h"


typedef struct titolo *Titolo;

Titolo newTitolo();

void freeTitolo(Titolo val);

char *getNomeTitolo(Titolo x);

void setNomeTitolo(char k[], Titolo val);

Titolo titoloSetVoid();

BST getBSTTitolo(Titolo x);

#endif