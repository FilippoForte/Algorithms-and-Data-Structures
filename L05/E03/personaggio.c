//Filippo Forte L05 E03
#include "personaggio.h"

//creazione nuovo nodo
link nuovoNodo(personaggio val, link next) {
    link x = malloc(sizeof *x);
    if (x == NULL)
        return NULL;
    else {
        x->val = val;
        x->val.inventario.inUso = 0;
        for (int i = 0; i < MAXOggetti; i++) {
            x->val.inventario.equip[i] = NULL;
        }
        x->next = next;
    }
    return x;
}

//inserimento nuovo nodo in testa
link inserimentoInTesta(link head, personaggio val) {
    head = nuovoNodo(val, head);
    return head;
}

//aggiunta personaggio da tastiera
link aggiungiPersonaggio(link head) {
    personaggio tmp, x = personaggioSetVoid();

    //lettura dati
    printf("Inserisci codice: ");
    scanf("%s", &x.codice);

    printf("Inserisci nome: ");
    scanf("%s", &x.nome);

    printf("Inserisci classe: ");
    scanf("%s", &x.classe);

    printf("Inserisci statistiche\n");
    printf("hp: ");
    scanf("%d", &x.stat.hp);

    printf("mp: ");
    scanf("%d", &x.stat.mp);

    printf("atk: ");
    scanf("%d", &x.stat.atk);

    printf("def: ");
    scanf("%d", &x.stat.def);

    printf("mag: ");
    scanf("%d", &x.stat.mag);

    printf("spr: ");
    scanf("%d", &x.stat.spr);

    //controllo codice già presente
    tmp = ricercaPersonaggioPerCodice(head, x.codice);
    if (strcmp(tmp.codice, "-1") != 0) {
        printf("Codice %s gia' presente. Inserimento non riuscito.\n", x.codice);
        return head;
    }

    //inserimento in testa
    head = inserimentoInTesta(head, x);
    return head;
}


//lettura ed inserimento personaggi da file
link leggiFilePersonaggi(link head) {
    personaggio x, tmp;
    FILE *fin;

    //apertura file
    if ((fin = fopen("../pg.txt", "r")) == NULL) {
        printf("Errore nell'apertura del file dei personaggi!");
        exit(2);
    }

    //lettura righe
    while (fscanf(fin, "%s %s %s %d %d %d %d %d %d ", x.codice, x.nome, x.classe, &x.stat.hp, &x.stat.mp, &x.stat.atk,
                  &x.stat.def, &x.stat.mag, &x.stat.spr) != EOF) {

        tmp = ricercaPersonaggioPerCodice(head, x.codice);

        //controllo codice già presente
        if (strcmp(tmp.codice, "-1") != 0) {
            printf("Codice %s gia' presente. Inserimento non riuscito.\n", x.codice);
        } else {
            //inserimento in testa
            head = inserimentoInTesta(head, x);
        }
    }
    //chiusura file
    fclose(fin);

    return head;
}

//ricerca di un personaggio per codice dato
personaggio ricercaPersonaggioPerCodice(link head, char k[]) {
    link x;
    for (x = head; x != NULL; x = x->next)
        if (strcmp(x->val.codice, k) == 0)
            return x->val;
    return personaggioSetVoid();
}

//creazione personaggio void
personaggio personaggioSetVoid() {
    personaggio x;
    strcpy(x.codice, "-1");
    x.stat.hp = 0;
    x.stat.mp = 0;
    x.stat.atk = 0;
    x.stat.def = 0;
    x.stat.mag = 0;
    x.stat.spr = 0;
    return x;
}

//estrazione e rimozione personaggio per codice
personaggio estrazionePersonaggioPerCodice(link *hp, char k[]) {
    link *xp, t;
    personaggio i = personaggioSetVoid();
    for (xp = hp; (*xp) != NULL; xp = &((*xp)->next)) {
        if (strcmp((*xp)->val.codice, k) == 0) {
            t = *xp;
            *xp = (*xp)->next;
            i = t->val;
            free(t);
            break;
        }
    }
    return i;
}

//stampa di tutta la lista
void stampaPersonaggiCompleta(link head) {
    link x;
    for (x = head; x != NULL; x = x->next) {
        stampaPersonaggio(x->val);
        printf("______________________________");
    }
}

//stampa singolo personaggio
void stampaPersonaggio(personaggio x) {
    printf("\nCODICE: %s\nNOME: %s\nCLASSE: %s\n", x.codice, x.nome, x.classe);
    printf("STATISTICHE:\n%d %d %d %d %d %d\n", x.stat.hp, x.stat.mp, x.stat.atk, x.stat.def, x.stat.mag, x.stat.spr);

    //controllo presenza equipaggiamento
    if (x.inventario.inUso > 0) {
        printf("\nEQUIPAGGIAMENTO:\n");

        //stampa equipaggiamento
        for (int i = 0; i < MAXOggetti; i++) {
            if (x.inventario.equip[i] != NULL) {
                stampaOggetto(x.inventario.equip[i]);
                printf("\n");
            }
        }
    }
}

//aggiunta oggetto a personaggio
personaggio aggiungiOggettoPersona(link head, char persona[], oggetto *elemento) {
    link x;
    int i;
    oggetto tmp;

    //scorrimento completo lista
    for (x = head; x != NULL; x = x->next) {

        //confronto e ricerca del codice con un personaggio in lista
        if (strcmp(x->val.codice, persona) == 0) {
            i = x->val.inventario.inUso;

            //controllo numero massimo di oggetti
            if (i < 8) {
                //aggiunta oggetto
                for (int j = 0; j < MAXOggetti; j++) {
                    if (x->val.inventario.equip[j] == NULL)
                    {
                        x->val.inventario.equip[j] = elemento;
                        x->val.inventario.inUso++;
                        printf("Oggetto aggiunto");
                        return x->val;
                    }
                }
            }
            if (i == 8)
                printf("Numero massimo di oggetti raggiunto per questo personagio\n");
        }
    }

    return personaggioSetVoid();
}

void rimuoviOggettoPersona(link head, char elemento[], char persona[]) {
    link x;
    int i, valido = 1;

    //scorrimento completo lista
    for (x = head; x != NULL && valido; x = x->next) {

        //confronto e ricerca del codice con un personaggio in lista
        if (strcmp(x->val.codice, persona) == 0) {
            i = x->val.inventario.inUso;

            //controllo presenza di almeno un oggetto nell'equipaggiamento
            if (i > 0) {
                for (int j = 0; j < i; j++) {

                    //ricerca oggetto per nome oggetto
                    if (strcmp(x->val.inventario.equip[j]->nome, elemento) == 0) {
                        //rimozione oggetto
                        x->val.inventario.equip[j] = NULL;
                        x->val.inventario.inUso--;
                        valido = 0;
                        printf("Oggetto rimosso");

                    }
                }
                if (valido) {
                    printf("Oggetto non trovato!\n");
                    valido = 0;
                }

            } else{
                printf("Non sono presenti oggetti da eliminare");
                return;
            }
        }
    }
    if (valido) {
        printf("Personaggio non trovato!\n");
    }
}

//stampa di un personaggio con le statistiche a seconda dei bonus/malus
void stampaStatistiche(link head, char k[]) {

    personaggio tmp = ricercaPersonaggioPerCodice(head, k);

    if (strcmp(tmp.codice, "-1") == 0) {
        printf("Personaggio non presente!");
    } else {

        //calcolo statistiche
        for (int i = 0; i < tmp.inventario.inUso; i++) {

            tmp.stat.hp += tmp.inventario.equip[i]->stat.hp;
            tmp.stat.mp += tmp.inventario.equip[i]->stat.mp;
            tmp.stat.atk += tmp.inventario.equip[i]->stat.atk;
            tmp.stat.def += tmp.inventario.equip[i]->stat.def;
            tmp.stat.mag += tmp.inventario.equip[i]->stat.mag;
            tmp.stat.spr += tmp.inventario.equip[i]->stat.spr;
        }
        printf("\nCODICE: %s\nNOME: %s\nCLASSE: %s\nSTATISTICHE:\n", tmp.codice, tmp.nome, tmp.classe);

        //stampa statistiche
        if (tmp.stat.hp > 0)
            printf("%d ", tmp.stat.hp);
        else printf("0 ");
        if (tmp.stat.mp > 0)
            printf("%d ", tmp.stat.mp);
        else printf("0 ");
        if (tmp.stat.atk > 0)
            printf("%d ", tmp.stat.atk);
        else printf("0 ");
        if (tmp.stat.def > 0)
            printf("%d ", tmp.stat.def);
        else printf("0 ");
        if (tmp.stat.mag > 0)
            printf("%d ", tmp.stat.mag);
        else printf("0 ");
        if (tmp.stat.spr > 0)
            printf("%d ", tmp.stat.spr);
        else printf("0 ");
    }
}