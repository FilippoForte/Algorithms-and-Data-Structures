#include <stdio.h>
#include "ST.h"
#include "Graph.h"

int main() {

    FILE *fin;
    ST tabella;
    Graph G;
    int archi = 0, scelta=-1;
    char nome1[MAXN], nome2[MAXN],nome3[MAXN], rete1[MAXN], rete2[MAXN];

    int wt;

    if ((fin = fopen("../grafo.txt", "r")) == NULL) {
        printf("Errore nell'apertura del file");
        exit(1);
    }

    while (fscanf(fin, "%s %s %s %s %d", nome1, rete1, nome2, rete2, &wt) != EOF)
        archi++;

    tabella = STinit(archi * 2);
    fflush(fin);
    rewind(fin);

    while (fscanf(fin, "%s %s %s %s %d", nome1, rete1, nome2, rete2, &wt) == 5) {
        STinsert(tabella, creaNodo(nome1, rete1));
        STinsert(tabella, creaNodo(nome2, rete2));
    }

    QuickSort(tabella);

    fflush(fin);
    rewind(fin);
    G = GRAPHload(fin, tabella);

    fclose(fin);

    while (scelta!=0){
        printf("1.Stampa nodi\n2.Verifica sotto grafo completo\n3.Genera lista adiacenze\n0.Esci\nScegli:");
        scanf("%d", &scelta);

        switch (scelta) {
            case 0:
                printf("Grazie e arrivederci");
                break;
            case 1:
                stampaVerticiCompleta(G, tabella);
                break;
            case 2:
                stampaVertici(G, tabella);

                printf("Inserire il primo nodo:");
                scanf("%s", nome1);
                if(GetValue(STsearch(tabella, nome1))==-1){
                    printf("Nodo inesistente\n");
                    break;
                }

                printf("Inserire il secondo nodo:");
                scanf("%s", nome2);
                if(GetValue(STsearch(tabella, nome2))==-1){
                    printf("Nodo inesistente\n");
                    break;
                }

                printf("Inserire il terzo nodo:");
                scanf("%s", nome3);
                if(GetValue(STsearch(tabella, nome3))==-1){
                    printf("Nodo inesistente\n");
                    break;
                }

                if(verifica(G, tabella, nome1, nome2, nome3))
                    printf("Vertici adiacenti a coppie\n");
                else
                    printf("Vertici non adiacenti a coppie\n");

                break;
            case 3:
                mat_to_list(G);
                break;
            default:
                printf("Scelta non valida");
                break;
        }
    }
    GRAPHfree(G);
    STfree(tabella);
}

