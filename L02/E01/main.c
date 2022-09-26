//Filippo Forte L02 E01
#include <stdio.h>

int gcd(int a, int b);

int main() {

    int A = 0, B = 0, tmp = 0;

    printf("Inserire il numero A: ");
    scanf("%d", &A);

    printf("Inserire il numero B: ");
    scanf("%d", &B);

    //swap variabili
    if (B > A) {
        tmp = A;
        A = B;
        B = tmp;
    }

    printf("Massimo comun divisore: %d", (gcd(A, B)));

    return 0;
}

int gcd(int a, int b) {
    //condizioni di ritorno
    if (a == 1 || b == 1)
        return 1;
    if (a == b)
        return b;

    //entrambi pari
    if (b % 2 == 0 && a % 2 == 0)
        return 2 * (gcd(a / 2, b / 2));

    //A pari - B dispari
    if (b % 2 == 1 && a % 2 == 0)
        return (gcd(a / 2, b));

    //B pari - A dispari
    if (b % 2 == 0 && a % 2 == 1)
        return (gcd(a, b / 2));

    //entrambi dispari
    if (a > b)
        return (gcd((a - b) / 2, b));

    return (gcd((b - a) / 2, a));

}
