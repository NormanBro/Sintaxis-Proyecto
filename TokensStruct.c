#include <stdio.h>
#include <stdlib.h>
#include "TokensStruct.h"

void insertar(struct TOKEN token){
    struct nodo *nuevo;

    nuevo=malloc(sizeof(struct nodo));

    nuevo->info=token;
    nuevo->IZQ=NULL;
    nuevo->DER=NULL;

    if(raiz==NULL){
        raiz=nuevo;
        actual=nuevo;
    }else{
        nuevo->IZQ=actual;
        actual->DER=nuevo;
        actual=nuevo;
    }
}
void imprimirLista(struct nodo *reco){
    struct nodo *aux;

    aux=reco;

    printf("|\tINFO\t|\tTIPO\t|\tNumColumnas\t|\tNumFila\t|\tNombre\t| \n");
    while(aux!=NULL){
        printf("|\t %s \t|\t %d \t|\t %d \t|\t %d \t|\t %s \t| \n",aux->info.Lexeman,aux->info.Tipo,aux->info.NCol,aux->info.NLinea,aux->info.Nombre);
        aux=aux->DER;
    }
}
void PosicionInicio(struct nodo *reco){
    struct nodo *aux;
    aux=reco;
    while(aux!=NULL){
        aux=aux->IZQ;
    }
}
