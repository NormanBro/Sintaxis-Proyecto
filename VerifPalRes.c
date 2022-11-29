#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "VerifPalRes.h"

int VerificarPalabra(char Cadena[80]){

    char *Reservada[]={"sinnada","entero","palabra","decimales","flotaras","si","siono","otalvez","vacia","vidrio","cortar","importado","devuelvete","avacede","huevo","publico","nomires","estetica","mientrastanto","cambiando","esqueleto"};
    int tam=sizeof(Reservada)/sizeof(char *);

    for(int x=0; x<tam; x++){

        if(strcmp(Reservada[x],Cadena)==0){
            return 1;
        }
    }
    return 0;
}
