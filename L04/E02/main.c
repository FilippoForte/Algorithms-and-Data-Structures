#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 50

//struttura dati utilizzata per memorizzare le date
typedef struct {
    int gg;
    int mm;
    int aa;
} data;

//struttura dati utilizzata per memorizzare l'anagrafica
typedef struct {
    char codice[MAXN];
    char nome[MAXN];
    char cognome[MAXN];
    data nascita;
    char via[MAXN];
    char citta[MAXN];
    int cap;
} persona;

//struttura dati utilizzata per i nodi della lista
typedef struct node *link;
struct node {
    persona val;
    link next;
};

//elenco prototipi di funzione

link inserimentoDaTastiera(link head);

link inserimentoDaFile(link head);

void ricercaPerCodice(link head);

persona ricerca(link head, char k[]);

link estraiPerCodice(link head);

link estraiPerDate_wrap(link head);

persona estraiPerDate(link *hp, data inizio, data fine);

int compreso(data x, data inizio, data fine);

persona estrai(link *hp, char k[]);

link inserimentoPerData(link head, persona val);

int controllaData(data k1, data k2);

link newNode(persona val, link next);

void stampa(link head);

persona setPersonaNull();

int main() {
    link head = NULL;
    int scelta = 0;

    //switch per le varie opzioni
    while (scelta != 7) {
        printf("\nScegliere un'operazione da effettuare: \n1.Inserimento di un'elemento da tastiera\n2.Inserimento di elementi da file\n3.Ricerca per codice\n4.Cancellazione di un dato per codice\n5.Cancellazione di piu' elementi in un intervallo di date\n6.Stampa di tutti gli elementi su una lista\n7.Esci\nInserire una scelta:");
        scanf("%d", &scelta);

        switch (scelta) {
            case 1:
                head = inserimentoDaTastiera(head);
                break;
            case 2:
                head = inserimentoDaFile(head);
                break;
            case 3:
                ricercaPerCodice(head);
                break;
            case 4:
                head = estraiPerCodice(head);
                break;
            case 5:
                head = estraiPerDate_wrap(head);
                break;
            case 6:
                stampa(head);
                break;
            case 7:
                printf("Grazie e Arrivederci");
                break;
            default:
                printf("Scelta non valida");
                break;
        }
    }
    return 0;
}

//inserimento nuova persona da tastiera
link inserimentoDaTastiera(link head) {
    persona val, tmp;

    //lettura valori
    printf("Inserire codice: ");
    scanf("%s", val.codice);

    printf("Inserire nome: ");
    scanf("%s", val.nome);

    printf("Inserire cognome: ");
    scanf("%s", val.cognome);

    printf("Inserire data di nascita (gg/mm/aaaa): ");
    scanf("%d/%d/%d", &val.nascita.gg, &val.nascita.mm, &val.nascita.aa);

    printf("Inserire via: ");
    scanf("%s", val.via);

    printf("Inserire citta': ");
    scanf("%s", val.citta);

    printf("Inserire cap: ");
    scanf("%d", &val.cap);

    //controllo che non sia già presente un'altra persona con lo stesso codice
    tmp = ricerca(head, val.codice);
    if (tmp.cap == -1)
        //inserimento
        head = inserimentoPerData(head, val);
    else
        printf("Codice gia' presente\n");

    return head;
}

//inserimento nuove persone da file
link inserimentoDaFile(link head) {
    FILE *fin;
    persona val, tmp;

    //apertura file
    if ((fin = fopen("../anag1.txt", "r")) == NULL) {
        printf("Errore nell'apertura del file");
        exit(1);
    }

    //lettura fino alla fine del file
    while (fscanf(fin, "%s %s %s %d/%d/%d %s %s %5d", val.codice, val.nome, val.cognome, &val.nascita.gg,
                  &val.nascita.mm, &val.nascita.aa, val.via, val.citta, &val.cap) != EOF) {

        //controllo che non sia già presente un'altra persona con lo stesso codice
        tmp = ricerca(head, val.codice);
        if (tmp.cap == -1)
            //inserimento
            head = inserimentoPerData(head, val);
        else
            printf("Codice gia' presente\n");

    }
    //chiusura file
    fclose(fin);
    return head;
}

//ricerca persona per codice
void ricercaPerCodice(link head) {
    persona val;
    char codice[MAXN];

    //lettura dati
    printf("Inserisci il codice da ricercare: ");
    scanf("%s", codice);

    //ricerca
    val = ricerca(head, codice);

    //controllo che esista una persona con quel codice
    if (val.cap != -1)
        printf("%s %s %s %d/%d/%d %s %s %d\n", val.codice, val.nome, val.cognome, val.nascita.gg, val.nascita.mm,
               val.nascita.aa, val.via, val.citta, val.cap);
    else
        printf("Elemento non trovato\n");
}

//estrazione per codice
link estraiPerCodice(link head) {
    persona val;
    link *xp;
    char codice[MAXN];

    //lettura dati
    printf("Inserisci il codice della persona da eliminare: ");
    scanf("%s", codice);

    xp = &head;
    //estrazione
    val = estrai(xp, codice);

    //controllo che esista una persona con quel codice
    if (val.cap != -1)
        printf("Persona eliminata:\n%s %s %s %d/%d/%d %s %s %d\n", val.codice, val.nome, val.cognome, val.nascita.gg,
               val.nascita.mm, val.nascita.aa, val.via, val.citta, val.cap);
    else
        printf("Elemento non trovato\n");

    return *xp;
}

//funzione wrap per l'estrazione da un range di date
link estraiPerDate_wrap(link head) {
    data inizio, fine;
    link *xp;
    persona val;
    val.cap = 1;

    //lettura dati
    printf("Inserire la data di inizio cancellazione (gg/mm/aaaa): ");
    scanf("%d/%d/%d", &inizio.gg, &inizio.mm, &inizio.aa);

    printf("Inserire la data di fine cancellazione (gg/mm/aaaa): ");
    scanf("%d/%d/%d", &fine.gg, &fine.mm, &fine.aa);


    //controllo che esista una persona in quel range
    while (val.cap != -1) {
        xp = &head;
        //estrazione
        val = estraiPerDate(xp, inizio, fine);

        if (val.cap != -1)
            printf("Persona eliminata:\n%s %s %s %d/%d/%d %s %s %d\n", val.codice, val.nome, val.cognome,
                   val.nascita.gg,
                   val.nascita.mm, val.nascita.aa, val.via, val.citta, val.cap);
    }
    return *xp;
}

//estrazione singolo nodo per date
persona estraiPerDate(link *hp, data inizio, data fine) {
    link *xp, t;
    persona i = setPersonaNull();

    //scorrimento lista
    for (xp = hp; (*xp) != NULL; xp = &((*xp)->next)) {

        //controllo appartenenza al range di date
        if (compreso((*xp)->val.nascita, inizio, fine)) {
            //estrazione
            t = *xp;
            *xp = (*xp)->next;
            i = t->val;
            free(t);
            break;
        }
    }
    return i;
}

//controllo data compresa in range
int compreso(data x, data inizio, data fine) {
    if (x.aa < fine.aa && x.aa > inizio.aa)
        return 1;

    if (x.aa == fine.aa || x.aa == inizio.aa){
        if (x.mm < fine.mm && x.mm > inizio.mm)
            return 1;
    }

    if (x.aa == fine.aa || x.aa == inizio.aa){
        if (x.mm == fine.mm || x.mm == inizio.mm)
                if (x.gg <= fine.gg && x.gg >= inizio.gg)
                    return 1;
            }
    return 0;
}

//estrazione singolo nodo per codice
persona estrai(link *hp, char k[]) {
    link *xp, t;
    persona i = setPersonaNull();

    //scorrimento lista
    for (xp = hp; (*xp) != NULL; xp = &((*xp)->next)) {

        //controllo uguaglianza codice
        if (strcmp((*xp)->val.codice, k) == 0) {
            //estrazione
            t = *xp;
            *xp = (*xp)->next;
            i = t->val;
            free(t);
            break;
        }
    }
    return i;
}

//ricerca persona con codice
persona ricerca(link head, char k[]) {
    link x;
    for (x = head; x != NULL; x = x->next)
        if (strcmp(x->val.codice, k) == 0)
            return x->val;
    return setPersonaNull();
}

//inserimento di un nuovo nodo ordinando per data
link inserimentoPerData(link head, persona val) {
    link x, p;

    //inserimento in testa
    if (head == NULL || controllaData(val.nascita, head->val.nascita))
        return newNode(val, head);

    //inserimento al centro
    for (x = head->next, p = head; x != NULL && controllaData(x->val.nascita, val.nascita); p = x, x = x->next);
    p->next = newNode(val, x);
    return head;
}

//controllo data per inserimento
int controllaData(data k1, data k2) {
    if (k1.aa > k2.aa) {
        return 1;
    } else if (k1.aa == k2.aa && k1.mm > k2.mm) {
        return 1;
    } else if (k1.aa == k2.aa && k1.mm == k2.mm && k1.gg > k2.gg)
        return 1;

    return 0;
}


//creazione nuovo nodo
link newNode(persona val, link next) {
    link x = malloc(sizeof *x);
    if (x == NULL)
        return NULL;
    else {
        x->val = val;
        x->next = next;
    }
    return x;
}

//stampa dell'intera lista
void stampa(link head) {
    link x;
    for (x = head; x != NULL; x = x->next) {
        printf("%s %s %s %d/%d/%d %s %s %d\n", x->val.codice, x->val.nome, x->val.cognome, x->val.nascita.gg,
               x->val.nascita.mm,
               x->val.nascita.aa, x->val.via, x->val.citta, x->val.cap);
    }
}

//creazione persona vuota
persona setPersonaNull() {
    persona val;
    val.cap = -1;
    return val;
}