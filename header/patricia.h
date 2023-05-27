// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #define TRUE 1
// #define FALSE !TRUE
// #define D 8 /* depende de TipoChave */

// typedef char *String;

// typedef enum {
//     Interno,
//     Externo
// } TipoNo;

// typedef struct TipoPatNo *Apontador;
// typedef struct TipoPatNo {
//     TipoNo TNo;
//     union {
//         struct { 
//             short Index;
//             char caractere;
//             Apontador Esq, Dir;
//         } NInterno;
//         String Chave;
//     } NO;
// } TipoPatNo;

// char Caractere(int i, String k);
// short EExterno(Apontador p);
// short EInterno(Apontador p);
// Apontador CriaNoInt(int i, Apontador *Esq,  Apontador *Dir, char Caractere);
// Apontador CriaNoExt(String k, Apontador *t);
// Apontador InsereEntre(String k, Apontador *t, int i, char diff);
// void Pesquisa(String k, Apontador t);
// Apontador Insere(String k, Apontador *t);
// void print(Apontador t);