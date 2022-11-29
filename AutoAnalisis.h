#ifndef AUTOANALISIS_H_INCLUDED
#define AUTOANALISIS_H_INCLUDED

#include "TokensStruct.h"

void AutoID(struct TOKEN token, char CARACTER[80]);
void AutoNumeric(struct TOKEN token,char CARACTER[80]);
void AutoSymbol(struct TOKEN token,char CARACTER);
void AutoCadena(struct TOKEN token);

#endif // AUTOANALISIS_H_INCLUDED
