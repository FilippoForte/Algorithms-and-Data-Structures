#include "equipArray.h"

//vettore equipaggiamento
struct equipArray_s {
    int v[EQUIP_SLOT];
    int inUso;
};

//inizializzazione vettore equipaggiamento
equipArray_t equipArray_init() {
    equipArray_t x;
    x = malloc(sizeof(struct equipArray_s));
    x->inUso = 0;
    return x;
}

//deallocazione vettore equipaggiamento
void equipArray_free(equipArray_t equipArray) {
    free(equipArray);
};

//oggetti presenti nel vettore equipaggiamento
int equipArray_inUse(equipArray_t equipArray) {
    return equipArray->inUso;
}

//stampa vettore equipaggiamento su file
void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray) {
    inv_t *tmp;
    for (int i = 0; i < equipArray->inUso; i++) {
        tmp = invArray_getByIndex(invArray, equipArray->v[i]);
        inv_print(fp, tmp, INT_MIN);
    }
}

//modica del vettore equipaggiamento
void equipArray_update(equipArray_t equipArray, invArray_t invArray) {
    int scelta;
    printf("Scegliere l'operazione da effettuare:\n1.Aggiungi oggetto\n2.Rimuovi oggetto\n3.Modifica oggetto esistente\n");
    scanf("%d", &scelta);

    switch (scelta) {
        case 1:
            aggiungiEquipaggiamento(equipArray, invArray);
            break;
        case 2:
            rimuoviEquipaggiamento(equipArray, invArray);
            break;
        case 3:
            modificaEquipaggiamento(equipArray, invArray);
            break;
        default:
            printf("Errore nell'inserimento!");
            break;
    }
}

//aggiunta di un elemento nel vettore equipaggiamento
void aggiungiEquipaggiamento(equipArray_t equipArray, invArray_t invArray) {
    int indice;
    char nome[LEN];

    if (equipArray->inUso < EQUIP_SLOT) {

        invArray_print(stdout, invArray);
        printf("Scegli un elemento da aggiungere: ");
        scanf("%s", nome);

        indice = invArray_searchByName(invArray, nome);
        if (indice != -1) {
            equipArray->v[equipArray->inUso] = indice;
            equipArray->inUso++;

        } else printf("Oggetto inserito inesistente");
    } else printf("Equipaggiamento massimo raggiunto");

}

//rimozione di un elemento nel vettore equipaggiamento
void rimuoviEquipaggiamento(equipArray_t equipArray, invArray_t invArray) {
    char nome[LEN];
    int indice, valido;

    if (equipArray->inUso > 0) {
        equipArray_print(stdout, equipArray, invArray);
        printf("\nScegli un elemento da eliminare:");
        scanf("%s", nome);

        if (indice = (invArray_searchByName(invArray, nome)) != -1) {
            for (int i = 0; i < equipArray->inUso; i++) {
                if ((equipArray_getEquipByIndex(equipArray, i) == indice) || valido) {
                    valido = 1;
                    equipArray->v[i] = equipArray->v[i + 1];
                }
            }
            equipArray->inUso--;
        }
    } else printf("Nessun oggetto presente");
}

//modifica di un elemento nel vettore equipaggiamento
void modificaEquipaggiamento(equipArray_t equipArray, invArray_t invArray) {
    if (equipArray_inUse(equipArray) > 0) {
        rimuoviEquipaggiamento(equipArray, invArray);
        aggiungiEquipaggiamento(equipArray, invArray);
    } else printf("Nessun oggetto presente");
}

//ritorna posizione nell'inventario dell'oggetto in posizione index nell'equipaggiamento
int equipArray_getEquipByIndex(equipArray_t equipArray, int index) {
    return equipArray->v[index];
}

