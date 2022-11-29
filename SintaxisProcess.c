#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <conio.h>

#include "SintaxisProcess.h"
#include "VarPublic.h"

void ERROR(){
    printf("Error esta en la Columna:Fila %s:%s \n",aux->info.NCol,aux->info.NLinea);
    exit(-1);
}

void Match(char Expect){
    if(aux->info.Lexeman==Expect){
        aux=aux->DER;
    }else{
        exit(-1);
    }
}

void OperadoresTermORSig(){

    if(strcmp(aux->info.Lexeman,"=")==0){
        aux=aux->DER;

    }else if(strcmp(aux->info.Lexeman,";")==0){
        aux=aux->DER;
    }
}

void Variable(){

    if(aux->info.Tipo==1){
        aux=aux->DER;
        OperadoresTermORSig();
    }else{
        ERROR();
    }
}

void IDVariable(){
    char *Reservada[]={"int","float","string"};
    int tam=sizeof(Reservada)/sizeof(char *);
    for(int x=0; x<tam; x++){
        printf("%d \n",(strcmp(Reservada[x],aux->info.Lexeman)==0));
        if((strcmp(Reservada[x],aux->info.Lexeman)==0) && aux!=NULL){
            printf("Entre \n");
            aux=aux->DER;
            Variable();
        }
        printf("X=%d , Tam=%d  \n",x,tam);
    }
}

void ProccessSintexis(struct nodo *reco){

    aux=reco;

    while(aux!=NULL){
        /*switch(aux->info.Tipo){
            case 1:
                //printf("%s \n",aux->info.Lexeman);
                IDVariable();

                break;
            case 2:
                printf("%s \n",aux->info.Lexeman);
                break;
            case 3:
                printf("%s \n",aux->info.Lexeman);
                break;
        } End Switch */
        IDVariable();

    }
    printf("No ha habido ningun problema");

}
