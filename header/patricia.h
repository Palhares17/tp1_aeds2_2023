#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE !TRUE
#define D 8 /* depende de TipoChave */

typedef short boolean;

typedef unsigned char* TipoChave; /* a definir*/
typedef unsigned short TipoindexAmp; 
// typedef unsigned char TipoDib;

typedef enum {
    Interno, Externo
} TipoNo;


typedef struct TipoPatNo *TipoArvore;
typedef struct TipoPatNo { 
    TipoNo nt;
    union {
        struct {
            TipoindexAmp Index;
            char caractere;
            TipoArvore Esq, Dir;
        } NInterno;
        char* Chave;
    } NO;
} TipoPatNo;

// Funções

char Bit(TipoindexAmp i, char* k);
short EExterno (TipoArvore p);
TipoArvore CriaNolnt(int i, TipoArvore *Esq, TipoArvore *Dir);
TipoArvore CriaNoExt(char* k);
void Pesquisa(char* k, TipoArvore t);
TipoArvore InsereEntre(char* k, TipoArvore *t, int i);
TipoArvore Insere(char* k, TipoArvore *t);
void printNo(TipoArvore t);
void printArvore(TipoArvore t);
boolean MenorIgual(char a, char b); 

