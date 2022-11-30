#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>


#include "Position.h"
//#include "VariablesPublic.h"
#include "VarPublic.h"
//#include "AutoAnalisis.h"
#include "AutoAnalisis.h"
//#include "VarArch.h"
#include "VarArch.h"
//#include "VerifPalRes.h"
#include "VerifPalRes.h"
//#include "TokensStruct.h"
#include "TokensStruct.h"

void AutoID(struct TOKEN token, char CARACTER[80]){
    Caracters=CARACTER;
    char CADENA[80]="";

    int estado=1;
    int inc=0;
    int finalizar=0;

    while(finalizar==0 || feof(Arch)==0){
        if(Caracters=='\n'){
            IncFila();
            finalizar=1;
            break;
        }
        IncColum();
        switch(estado){
        case 1:
            if(isalpha(Caracters)){
                CADENA[inc]=Caracters;
                inc++;
                estado=2;
            }else{
                finalizar=1;
            }
            break;
        case 2:
            if(isalnum(Caracters)){
                CADENA[inc]=Caracters;
                inc++;
            }else{
                finalizar=1;
            }
            break;

        }//end Switch
        if(finalizar==1){
            break;
        }
        CaractersAnt=Caracters;
        Caracters=fgetc(Arch);
    }//end While

    if(estado==2){
        DecColum();

        if(!VerificarPalabra(CADENA)){
            token.Tipo=Id;
            strcpy(token.Nombre,"Indentificador");
            strcpy(token.Lexeman,CADENA);
            insertar(token);

        }else{
            token.Tipo=PalRes;
            strcpy(token.Nombre,"PalabraReservada");
            strcpy(token.Lexeman,CADENA);
            insertar(token);

        }
    }

}

void AutoNumeric(struct TOKEN token,char CARACTER[80]){
    Caracters=CARACTER;
    char CADENA[80]="";

    int estado=1;
    int inc=0;
    int finalizar=0;
    while(finalizar==0 || feof(Arch)==0){
        if(Caracters=='\n'){
            IncFila();
            finalizar=1;
            break;
        }
        IncColum();

        switch(estado){
            case 1:
                if(isdigit(Caracters)){
                    CADENA[inc]=Caracters;
                    inc++;
                    estado=2;
                }else{
                    finalizar=1;
                }
                break;
            case 2:
                if(isdigit(Caracters)){
                    CADENA[inc]=Caracters;
                    inc++;
                }else if(Caracters=='.'){
                    CADENA[inc]=Caracters;
                    inc++;
                    estado=3;
                }else{
                    finalizar=1;
                }
                break;
            case 3:
                if(isdigit(Caracters)){
                    CADENA[inc]=Caracters;
                    inc++;
                    estado=2;
                }else{
                    finalizar=1;
                }
                break;
        }//end Switch

        if(finalizar==1){
            break;
        }
        CaractersAnt=Caracters;
        Caracters=fgetc(Arch);
    }//end while
    if(estado==2){
        DecColum();
        token.Tipo=Num;
        strcpy(token.Nombre,"Numerico");
        strcpy(token.Lexeman,CADENA);
        insertar(token);
    }
}

void AutoSymbol(struct TOKEN token,char CARACTER){
    Caracters=CARACTER;
    char CADENA[80]="";

    int estado=1;
    int inc=0;
    int finalizar=0;
    while(finalizar==0 || feof(Arch)==0){

        if(Caracters=='\n'){
            IncFila();
            finalizar=1;
            break;
        }

        IncColum();

        switch(estado){
            case 1:
                if( (Caracters==43 || Caracters==45) && (!isdigit(CaractersAnt) && !isalpha(CaractersAnt) && CaractersAnt!=34 )){
                    estado=2;
                    CADENA[inc]=Caracters;
                    inc++;
                }else if(Caracters==' '){
                    finalizar=1;
                }else if( (Caracters==60 || Caracters ==62) ){
                    estado=3;
                    CADENA[inc]=Caracters;
                    inc++;
                }else if( (Caracters>=33 || Caracters<=47) || (Caracters>=58 || Caracters<=64) || (Caracters>=91 || Caracters<=96) || (Caracters>=123 || Caracters<=126)){
                    estado=4;
                    finalizar=1;
                    CADENA[inc]=Caracters;
                    inc++;
                }else{
                    finalizar=1;
                }
                break;
            case 2:
                if(isdigit(Caracters)){
                    CADENA[inc]=Caracters;
                    inc++;
                }else{
                    estado=5;
                    finalizar=1;
                }
                break;
            case 3:
                if(Caracters==61){
                    estado=4;
                    finalizar=1;
                    CADENA[inc]=Caracters;
                    inc++;
                }else{
                    finalizar=1;
                }
                break;
        }//end Swirch

        if(finalizar==1){
            break;
        }
        CaractersAnt=Caracters;
        Caracters=fgetc(Arch);
    }//end While

    if(estado==4){
        DecColum();
        token.Tipo=Sim;
        strcpy(token.Nombre,"Simbolo");
        strcpy(token.Lexeman,CADENA);
        insertar(token);

    }else if(estado==5 || estado==2){
        DecColum();
        token.Tipo=Num;
        strcpy(token.Nombre,"Numerico");
        strcpy(token.Lexeman,CADENA);
        insertar(token);
    }
}

void AutoCadena(struct TOKEN token){

    char CADENA[80]="";

    int estado=1;
    int inc=0;
    int finalizar=0;
    while(finalizar==0 || feof(Arch)==0){
        if(Caracters=='\n'){
            IncFila();
        }
        IncColum();
        switch(estado){
            case 1:
                if(Caracters=='"'){
                    CADENA[inc]=Caracters;
                    inc++;
                    estado=2;
                }else{
                    finalizar=1;
                }
                break;
            case 2:
                if(Caracters!='�' && Caracters!='"'){
                    CADENA[inc]=Caracters;

                    if(Caracters=='\n'){
                        CADENA[inc]=' ';
                    }
                    inc++;
                }else if(Caracters=='"'){
                    CADENA[inc]=Caracters;
                    inc++;
                    estado=3;
                    finalizar=1;
                }else{
                    estado=3;
                    finalizar=1;
                }
                break;

        }//end Swithc
        if(finalizar==1){
            break;
        }
        CaractersAnt=Caracters;
        Caracters=fgetc(Arch);
    }//end While
    if(Caracters=='"'){
        CaractersAnt=Caracters;
        Caracters=fgetc(Arch);
    }
    if(estado==3){
        token.Tipo=Cad;
        strcpy(token.Nombre,"Cadena");
        strcpy(token.Lexeman,CADENA);
        insertar(token);
    }
}
