//Filippo Forte L01 E01
#include <stdio.h>
#include <string.h>

char *cercaRegexp(char *src, char *regexp);

int main() {

    //definizione di sorgente e regexp
    char sorgente[100] = "Hello World", espressione[100] = "\\Aor[^asdfg]", *src, *regexp;
    char *posizione;

    src = &sorgente[0];
    regexp = &espressione[0];

    //chiamata funzione
    posizione = cercaRegexp(src, regexp);

    //stampa risultati
    printf("Valore=%c Puntatore=%p", *posizione, posizione);

    return 0;
}


char *cercaRegexp(char *src, char *regexp) {
    int nonValido = 0, j = 0, k = 0, i = 0, trovato = -1;

    //ciclo per tutta la lunghezza della sorgente
    while (i < strlen(src)) {

        j = 0;
        //ciclo sulla regexp
        while (j < strlen(regexp)) {

            //controllo di non essere alla fine della sorgente
            if (*(src+i)=='\0')
                return NULL;
            //controllo regexp .
            else if (*(regexp + j) == '.') {
                j++;
                i++;
            }
            //controllo regexp \A e \a
            else if (*(regexp + j) == '\\') {

                if (*(regexp + j + 1) == 'A') {
                    //controllo se carattere è maiuscolo
                    if (*(src + i) < 90 && *(src + i) > 64) {
                        j += 2;
                        i++;
                    } else {
                        j = 0;
                        i++;
                        trovato = i;
                    }
                } else if (*(regexp + j + 1) == 'a') {
                    //controllo se carattere è minuscolo
                    if (*(src + i) < 123 && *(src + i) > 96) {
                        j += 2;
                        i++;
                    } else {
                        j = 0;
                        i++;
                        trovato = i;
                    }
                }
            }
            //controllo regexp [^][]
            else if (*(regexp + j) == '[') {
                if (*(regexp + j + 1) == '^') {
                    nonValido = 0;

                    //controllo tutti i caratteri da scartare
                    for (k = 0; *(regexp + j + 1 + k) != ']' && !nonValido; k++) {
                        if (*(src + i) == *(regexp + j + 1 + k)) {
                            nonValido = 1;
                        }
                    }
                    if (!nonValido) {
                        j += k + 3;
                        i++;
                    } else {
                        j = 0;
                        i++;
                        trovato = i;
                    }
                } else {
                    nonValido = 1;
                    //controllo tutti i caratteri accettabili
                    for (k = 0; *(regexp + j + k) != ']' && nonValido; k++) {
                        if (*(src + i) == *(regexp + j + 1 + k)) {
                            nonValido = 0;
                        }
                    }
                    if (!nonValido) {
                        j += k + 2;
                        i++;
                    } else {
                        j = 0;
                        i++;
                        trovato = i;
                    }
                }
            }
            //controllo nel caso sia presente soltanto un carattere alfanumerico
            else if (*(regexp + j) == *(src + i)) {
                j++;
                i++;
            } else {
                j = 0;
                i++;
                trovato = i;
            }
        }
        //ritorno del puntatore alla prima occorrenza
        return src + trovato;
    }
    return NULL;
}