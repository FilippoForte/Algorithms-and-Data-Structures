#include "titolo.h"


struct titolo {
    char nome[21];
    BST quotazioni;
};


Titolo newTitolo() {
    Titolo val = (Titolo) malloc(sizeof(struct titolo));
    if(val==NULL)
        return NULL;

    val->nome[0]='\0';
    val->quotazioni = BSTinit();

    return val;
}

void freeTitolo(Titolo val){
    BSTfree(val->quotazioni);
    free(val);
}

char *getNomeTitolo(Titolo x){
    return x->nome;
}

void setNomeTitolo(char k[], Titolo val){
    strcpy(val->nome, k);
}

BST getBSTTitolo(Titolo x){
    return x->quotazioni;
}

Titolo titoloSetVoid(){
    Titolo val = (Titolo) malloc(sizeof(struct titolo));

    setNomeTitolo("-1", val);
    return val;
}