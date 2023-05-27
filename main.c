// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ctype.h>
#include "./header/patricia.h"

#define tam 200
#define MAX_ARQUIVOS 2


// typedef char* String;
// typedef struct TipoPatNo* Apontador;
// typedef unsigned char TipoIndexAmp;

// typedef enum {
//     Interno,
//     Externo
// } TipoNo;

// typedef struct TipoPatNo {
//     TipoNo TNo;
//     union {
//         struct {
//             TipoIndexAmp Index;
//             char caractere;
//             Apontador Esq, Dir;
//         } NInterno;
//         String Chave;
//     } NO;
//     int contagem[MAX_ARQUIVOS];
// } TipoPatNo;

// char Caractere(int i, String k);
// short EExterno(Apontador p);
// short EInterno(Apontador p);
// Apontador CriaNoInt(int i, Apontador *Esq, Apontador *Dir, char Caractere);
// Apontador CriaNoExt(String k, Apontador *t, int idDoc);
// Apontador InsereEntre(String k, Apontador *t, int i, char diff, int idDoc);
// Apontador Insere(String k, Apontador *t, int idDoc);
// void Pesquisa(String k, Apontador t);
// void ImprimirPalavras(Apontador t);

int main() {
    Apontador arvore = NULL; // Inicializa a árvore como vazia

    char palavra[tam];

    FILE* f[MAX_ARQUIVOS];
    char arquivos[MAX_ARQUIVOS][50] = {
        "./POCs/cleber.txt",
        "./POCs/gabriel.txt",
        // "./POCs/arquivo1.txt",
        // "./POCs/arquivo2.txt",
        // "./POCs/arquivo3.txt",
        // "./POCs/arquivo4.txt",

    };

    for (int i = 0; i < MAX_ARQUIVOS; i++) {
        f[i] = fopen(arquivos[i], "r");
        if (f[i] == NULL) {
            printf("Erro ao abrir arquivo %s\n", arquivos[i]);
            return 1;
        }
    }

    int idDoc = 1;
    while (idDoc <= MAX_ARQUIVOS) {
        while (fscanf(f[idDoc - 1], "%s", palavra) == 1) {
            // Remove caracteres especiais, acentuação e pontuação
            int len = strlen(palavra);
            for (int i = 0; i < len; i++) {
                if (!isalnum(palavra[i])) {
                    memmove(&palavra[i], &palavra[i + 1], len - i);
                    len--;
                    i--;
                }
            }

            // Converte a palavra para minúsculas
            for (int i = 0; i < len; i++) {
                palavra[i] = tolower(palavra[i]);
            }

            arvore = Insere(palavra, &arvore, idDoc);
        }
        idDoc++;
    }

    ImprimirPalavras(arvore);

    Pesquisa("teste", arvore);

    for (int i = 0; i < MAX_ARQUIVOS; i++) {
        fclose(f[i]);
    }

    return 0;
}