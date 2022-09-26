//Filippo Forte L03E01
#include <stdio.h>

int maggioritario(int l, int r, int *a);
int majority(int *a, int N);

int main() {
    int a[8]={4,3,4,3,4,3,4,4};

    majority(a, 7);

    return 0;
}

//funzione wrapper
int majority(int *a, int N) {
    //stampa del risultato
    printf("%d",maggioritario(0, N, a));
}

int maggioritario(int l, int r, int *a) {
    int m = (l + r) / 2, left, right, cLeft=0, cRight=0;

    //condizione di terminazione corrispondente al vettore di un singolo elemento
    if (l == r) {
        return a[l];
    }

    //calcolo elemento maggioritario sottovettore sinistro
    left = maggioritario(l, m, a);
    //calcolo elemento maggioritario sottovettore destro
    right = maggioritario(m + 1, r, a);

    //conteggio delle occcorrenze degli elementi maggioritari dei sottovettori nel vettore completo
    for (int i = l; i < r; i++) {
        if(a[i]==left)
            cLeft++;
        if(a[i]==right)
            cRight++;
    }

    //verifica che l'elemento maggioritario del sottovettore destro è maggioritario del vettore completo
    if(cRight>(r-l)/2)
        return right;

    //verifica che l'elemento maggioritario del sottovettore sinistro è maggioritario del vettore completo
    if(cLeft>(r-l)/2)
        return left;

    return -1;
}
