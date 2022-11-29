#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <conio.h>

#include "Position.h"

void IncColum(){
    NColumna++;
}
void IncFila(){
    NFila++;
}
void DecColum(){
    NColumna--;
}
void VaciarColum(){
    NColumna=1;
}
