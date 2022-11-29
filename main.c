#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <conio.h>

#include "Position.h"
#include "VarPublic.h"
#include "VarArch.h"
#include "TokensStruct.h"
#include "AutoAnalisis.h"
#include "SintaxisProcess.h"

int main()
{
    Arch=fopen("Codigo.txt","r");

    NColumna=1;
    NFila=1;

    raiz=NULL;
    actual=NULL;
    struct TOKEN token;

    if(Arch==NULL){
        printf("ERROR de encontrar Archivo");
        return 1;
    }
    CaractersAnt="";
    Caracters=fgetc(Arch);

    while(feof(Arch)==0){

        if(Caracters=='\n'){
            IncFila();
            VaciarColum();
        }


        if(isalpha(Caracters)){
            token.NCol=NColumna;
            token.NLinea=NFila;
            AutoID(token,Caracters);
        }else if(isdigit(Caracters)){
            token.NCol=NColumna;
            token.NLinea=NFila;
            AutoNumeric(token,Caracters);
        }else if(isspace(Caracters)){
            IncColum();
            CaractersAnt=Caracters;
            Caracters=fgetc(Arch);
        }else if(Caracters=='"'){
            IncColum();
            CaractersAnt=Caracters;
            AutoCadena(token);
        }else{
            AutoSymbol(token,Caracters);
            Caracters=fgetc(Arch);
        }

        //Caracter=fgetc(Arch);

    }//While End

    imprimirLista(raiz);
    //printf("Numero de filas: %d \n",NFila);
    ProccessSintexis(raiz);

    return 0;
}
