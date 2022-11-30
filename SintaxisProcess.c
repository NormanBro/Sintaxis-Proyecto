#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <conio.h>

#include "SintaxisProcess.h"
#include "VarPublic.h"

void ContenidoLlaves(){

    while(aux!=NULL){
        printf("%s \n",aux->info.Lexeman);
        if(aux!=NULL)IDVariable();
        if(aux!=NULL)Variable();
        if(aux!=NULL)SentCondicional();
        if(aux!=NULL)SentCiclosMientras();

        if(aux==NULL)break;
        if(strcasecmp(aux->info.Lexeman,"}")==0)break;

    }
}

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

int Sentencias(){
    if(strcmp(aux->info.Lexeman,"if")==0)return 0;
    if(strcmp(aux->info.Lexeman,"while")==0)return 0;
    return 1;
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
        Match(";");
    }else if(strcmp(aux->info.Lexeman,";")){
        Match(";");
    }

}

void Variable(){

    if(aux->info.Tipo==1 && Sentencias() ){
        SigAux();
        Asicnadores();
    }else if(!(strcmp(aux->info.Lexeman,"if") || strcmp(aux->info.Lexeman,"while"))){
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

void Exp(){
    if(aux==NULL){
        ERROR("; o la falta de un valor");
    }
    if(aux->info.Tipo==1 || aux->info.Tipo==2 ){
        SigAux();

        if(Operador()){
            Term();
        }
    }else if(strcmp(aux->info.Lexeman,"(")==0){
        Term();
        Match(")");
    }

}

void SentCondicional(){

    if(strcmp(aux->info.Lexeman,"if")==0){
        SigAux();

        Match("(");
        Exp();
        Match(")");
        Match("{");
        ContenidoLlaves();
        Match("}");
    }
}
void SentCiclosMientras(){
    if(strcmp(aux->info.Lexeman,"while")==0){
        SigAux();

        Match("(");
        Exp();
        Match(")");
        Match("{");
        ContenidoLlaves();
        Match("}");
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
        Variable();
        SentCondicional();
        SentCiclosMientras();

    }
    printf("No ha habido ningun problema");

}
