#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <conio.h>

#include "SintaxisProcess.h"
#include "VarPublic.h"

void SigLineCol(){
    if(aux!=NULL){
        LineaSintaxis=aux->info.NLinea;
        ColumnaSintaxis=aux->info.NCol;
    }else{
        ColumnaSintaxis+=1;
    }
}

void SigAux(){

    aux=aux->DER;
    SigLineCol();
    //printf("Col/%d Fila/%d\n",ColumnaSintaxis,LineaSintaxis);

}

void ERROR(char* Message){
    printf("Error: %s esta en la Columna:Linea %d:%d \n",Message,ColumnaSintaxis,LineaSintaxis);
    exit(-1);
}

void Match(char* Expect){

    if(strcmp(aux->info.Lexeman,Expect)==0){
        SigAux();
    }else{
        ERROR(Expect);
    }

}

int Opemasmen(){
    if(strcmp(aux->info.Lexeman,"+")==0)return 1;
    if(strcmp(aux->info.Lexeman,"-")==0)return 1;
    return 0;
}
int Opemuldiv(){
    if(strcmp(aux->info.Lexeman,"*")==0)return 1;
    if(strcmp(aux->info.Lexeman,"/")==0)return 1;
    return 0;
}

int Operador(){
    if(aux==NULL){
        ERROR(";");
    }
    if(Opemasmen() || Opemuldiv()){
        SigAux();
        return 1;
    }
    return 0;
}

void Term(){

    if(aux==NULL){
        ERROR(";");
    }

    if(aux->info.Tipo==1 || aux->info.Tipo==2 || aux->info.Tipo==4){

        SigAux();

        if(Operador()){
            Term();
        }

    }else if(strcmp(aux->info.Lexeman,"(")==0){
        Term();
        Match(")");
    }else{
        ERROR("Fallo en agregar valor");
    }

}


void Asicnadores(){

    if(aux==NULL){
        ERROR(";");
        SigLineCol();
    }else if(strcmp(aux->info.Lexeman,"=")==0){
        SigAux();
        Term();

    }

}

void Variable(){

    if(aux->info.Tipo==1){
        SigAux();
        Asicnadores();
        Match(";");
    }else{
        ERROR("No se debe usar simbolos o numeros");
    }
}

void IDVariable(){
    char *Reservada[]={"int","float","string"};
    int tam=sizeof(Reservada)/sizeof(char *);
    for(int x=0; x<tam; x++){

        if(aux==NULL)break;

        if(strcmp(Reservada[x],aux->info.Lexeman)==0){

            SigAux();
            Variable();
        }

    }
}

void ProccessSintexis(struct nodo *reco){

    aux=reco;
    LineaSintaxis=aux->info.NLinea;
    ColumnaSintaxis=aux->info.NCol;

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
