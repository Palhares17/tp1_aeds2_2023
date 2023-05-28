#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define tam 200
#define MAX_ARQUIVOS 3

typedef char* String;
typedef struct TipoPatNo* Apontador;
typedef unsigned char TipoIndexAmp;

typedef enum {
    Interno,
    Externo
} TipoNo;

typedef struct TipoPatNo {
    TipoNo TNo;
    union {
        struct {
            TipoIndexAmp Index;
            char caractere;
            Apontador Esq, Dir;
        } NInterno;
        String Chave;
    } NO;
    int contagem[MAX_ARQUIVOS];
} TipoPatNo;