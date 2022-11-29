#ifndef TOKENSSTRUCT_H_INCLUDED
#define TOKENSSTRUCT_H_INCLUDED

enum TipoToken{
        PalRes,
		Id,
		Num,
		Sim,
		Cad,
};
struct TOKEN{
    enum TipoToken Tipo;
    char Lexeman[80];
    int NCol;
    int NLinea;
    char Nombre[80];
};
struct nodo{
    struct TOKEN info;
    struct nodo *IZQ;
    struct nodo *DER;
};

struct nodo *raiz;
struct nodo *actual;

void insertar(struct TOKEN token);
void imprimirLista(struct nodo *reco);
void PosicionInicio(struct nodo *reco);
#endif // TOKENSSTRUCT_H_INCLUDED
