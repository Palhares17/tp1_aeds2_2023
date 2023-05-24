#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define D 8 /* depende de TipoChave */

typedef unsigned char* TipoChave; /* a definir*/
typedef unsigned char TipoindexAmp; 
typedef unsigned char TipoDib;
typedef enum {
    Interno, Externo
} TipoNo;
typedef struct TipoPatNo *TipoArvore;
typedef struct TipoPatNo { 
    TipoNo nt;
    union {
        struct {
            TipoindexAmp Index;
            TipoArvore Esq, Dir;
        } NInterno;
        char* Chave;
    } NO;
} TipoPatNo;

TipoDib Bit (TipoindexAmp i, char* k);
short EExterno (TipoArvore p);
TipoArvore CriaNolnt(int i, TipoArvore *Esq, TipoArvore *Dir);
TipoArvore CriaNoExt(char* k);
void Pesquisa(char* k, TipoArvore t);
TipoArvore InsereEntre(char* k, TipoArvore *t, int i);
TipoArvore Insere (char* k, TipoArvore *t);
void printNo(TipoArvore t);
void printArvore(TipoArvore t);

