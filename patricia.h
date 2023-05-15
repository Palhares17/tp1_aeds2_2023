#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define D 8 /* depende de TipoChave */

typedef unsigned char TipoChave; /* a definir*/
typedef unsigned char TipoindexAmp; 
typedef unsigned char TipoDib;
typedef enum {
    Interno, Externo
} TipoNo;
typedef struct TipoPatNo* TipoArvore;
typedef struct TipoPatNo { 
    TipoNo nt;
    union {
        struct {
            TipoindexAmp Index;
            TipoArvore Esq, Dir;
        } NInterno;
        TipoChave Chave;
    } NO;
} TipoPatNo;

TipoDib Bit (TipoindexAmp i, TipoChave k);
short EExterno (TipoArvore p);
TipoArvore CriaNolnt(int i, TipoArvore *Esq, TipoArvore *Dir);
TipoArvore CriaNoExt(TipoChave k);
void Pesquisa(TipoChave k, TipoArvore t);
TipoArvore InsereEntre(TipoChave k, TipoArvore *t, int i);
TipoArvore Insere (TipoChave k, TipoArvore *t);

