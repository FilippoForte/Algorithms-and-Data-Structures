#include <stdio.h>
#include "listaTitoli.h"

int main() {
    int scelta = 1, gg, mm, aa;
    float min = INT_MAX, max = 0, soglia;
    char nomeFile[21] = "../", nomeTitolo[21];
    List lista=ListInit();
    Titolo azione=titoloSetVoid();
    data dataTmp, dataTmp2;
    Quotazione quotazioneTmp;

    while (scelta != 0) {
        printf("1.Lettura file\n2.Ricerca titolo azionari\n3.Ricerca quotazione in un titolo\n4.Ricerca min e max tra date\n5.Ricerca min e max completa\n6.Bilanciamento albero quotazioni\n0.Esci\nScegli:");
        scanf("%d", &scelta);

        switch (scelta) {
            case 1:
                printf("Inserire il nome de file da leggere: ");
                scanf("%s", &nomeFile[3]);
                lista = ListLeggiFile(nomeFile, lista);
                break;
            case 2:
                printf("Inserire il titolo del titolo azionario da ricercare:");
                scanf("%s", nomeTitolo);

                azione = ricerca(lista, nomeTitolo);

                if (strcmp(getNomeTitolo(azione), "-1") != 0)
                    printf("Titolo selezionato con successo\n");
                else
                    printf("Titolo non trovato\n");

                break;

            case 3:

                if (strcmp(getNomeTitolo(azione), "-1") == 0)
                    printf("Si prega di selezionare un titolo (opzione 2)\n");
                else {
                    printf("Inserire data da ricercare (gg/mm/aaaa):");
                    scanf("%d/%d/%d", &gg, &mm, &aa);

                    setData(&dataTmp, aa, mm, gg);
                    quotazioneTmp = BSTsearch(getBSTTitolo(azione), dataTmp);

                    printf("La quotazione del titolo selezionato nella data indicata e': %.2f\n",
                           (float) (getValore(quotazioneTmp) / (float) getQuantita(quotazioneTmp)));
                }
                break;
            case 4:
                if (strcmp(getNomeTitolo(azione), "-1") == 0)
                    printf("Si prega di selezionare un titolo (opzione 2)\n");
                else {
                    min = INT_MAX, max = 0;

                    printf("Inserire data inzio (gg/mm/aaaa):");
                    scanf("%d/%d/%d", &gg, &mm, &aa);
                    setData(&dataTmp, aa, mm, gg);

                    printf("Inserire data fine (gg/mm/aaaa):");
                    scanf("%d/%d/%d", &gg, &mm, &aa);
                    setData(&dataTmp2, aa, mm, gg);

                    ricercaTraDateWrap(getBSTTitolo(azione), dataTmp, dataTmp2, &min, &max);
                    printf("Minimo: %.2f\tMassimo: %.2f\n", min, max);
                }
                break;

            case 5:
                if (strcmp(getNomeTitolo(azione), "-1") == 0)
                    printf("Si prega di selezionare un titolo (opzione 2)\n");
                else {
                    min = INT_MAX, max = 0;
                    setData(&dataTmp, -1, -1, -1);
                    setData(&dataTmp2, INT_MAX, INT_MAX, INT_MAX);

                    ricercaTraDateWrap(getBSTTitolo(azione), dataTmp, dataTmp2, &min, &max);
                    printf("Minimo: %.2f\tMassimo: %.2f\n", min, max);
                }
                break;
            case 6:
                if (strcmp(getNomeTitolo(azione), "-1") == 0)
                    printf("Si prega di selezionare un titolo (opzione 2)\n");
                else {
                    printf("Inserire soglia rapporto cammini massimo/minimo:");
                    scanf("%f", &soglia);

                    min = INT_MAX, max = 0;
                    visitWrap(getBSTTitolo(azione), &min, &max);

                    if (min / max > soglia) {
                        BSTbalance(getBSTTitolo(azione));
                        printf("Bilanciamento effettuato\n");
                    } else printf("Albero gia' bilanciato\n");
                }
                break;
            case 0:
                ListFree(lista);
                break;
        }
    }
    return 0;
}
