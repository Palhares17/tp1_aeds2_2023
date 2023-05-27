#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define tam 200
#define MAX_ARQUIVOS 50

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

// char Caractere(int i, String k);
// short EExterno(Apontador p);
// short EInterno(Apontador p);
// Apontador CriaNoInt(int i, Apontador *Esq, Apontador *Dir, char Caractere);
// Apontador CriaNoExt(String k, Apontador *t, int idDoc);
// Apontador InsereEntre(String k, Apontador *t, int i, char diff, int idDoc);
// Apontador Insere(String k, Apontador *t, int idDoc);
// void Pesquisa(String k, Apontador t);
// void ImprimirPalavras(Apontador t);

char Caractere(int i, String k);
short EExterno(Apontador p);
short EInterno(Apontador p);
Apontador CriaNoInt(int i, Apontador *Esq, Apontador *Dir, char Caractere);
Apontador CriaNoExt(String k, Apontador *t, int idDoc);
Apontador InsereEntre(String k, Apontador *t, int i, char diff, int idDoc);
Apontador Insere(String k, Apontador *t, int idDoc);
void Pesquisa(String k, Apontador t);
void ImprimirPalavras(Apontador t);