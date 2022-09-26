#include "nodo.h"

Nodo NodoSetVoid(){
    Nodo x;
    strcpy(x.nome, "-1");
    x.val=-1;
    return x;
}

Nodo creaNodo(char nome[], char rete[]){
    Nodo x;
    strcpy(x.nome, nome);
    strcpy(x.rete, rete);
    x.val=0;
    return x;
}

int GetValue(Nodo x){
    return x.val;
}

void stampaNodo(Nodo x){
    printf("Nome: %s\tRete: %s\n", x.nome, x.rete);
}