#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define D 8 /* depende de TipoChave */

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
} TipoPatNo;

char Caractere(int i, String k) {
    return k[i];
}

short EExterno(Apontador p) {
    return p->TNo == Externo;
}

short EInterno(Apontador p) {
    return p->TNo == Interno;
}

Apontador CriaNoInt(int i, Apontador *Esq, Apontador *Dir, char Caractere) {
    Apontador p;
    p = (Apontador)malloc(sizeof(TipoPatNo));
    p->TNo = Interno;
    p->NO.NInterno.Esq = *Esq;
    p->NO.NInterno.Dir = *Dir;
    p->NO.NInterno.Index = i;
    p->NO.NInterno.caractere = Caractere;
    return p;
}

Apontador CriaNoExt(String k, Apontador *t) {
    Apontador p;
    p = (Apontador)malloc(sizeof(TipoPatNo));
    p->TNo = Externo;
    p->NO.Chave = (String)malloc((strlen(k) + 1) * sizeof(char));
    strcpy(p->NO.Chave, k);
    return p;
}

Apontador InsereEntre(String k, Apontador *t, int i, char diff) {
    Apontador p;

    if (EExterno(*t)) {
        p = CriaNoExt(k, &p);
        /* cria um novo no externo */
        if (strcmp((*t)->NO.Chave, k) < 0) {
            return (CriaNoInt(i, t, &p, diff));
        }
        else {
            return (CriaNoInt(i, &p, t, diff));
        }
    }
    else if (i < (*t)->NO.NInterno.Index) {
        p = CriaNoExt(k, &p);
        if (k[i] < diff) {
            return (CriaNoInt(i, &p, t, diff));
        }
        else {
            return (CriaNoInt(i, t, &p, diff));
        }
    }
    else {
        int index = (*t)->NO.NInterno.Index;
        if (Caractere(index, k) >= (*t)->NO.NInterno.caractere) {
            (*t)->NO.NInterno.Dir = InsereEntre(k, &(*t)->NO.NInterno.Dir, i, diff);
        }
        else {
            (*t)->NO.NInterno.Esq = InsereEntre(k, &(*t)->NO.NInterno.Esq, i, diff);
        }
    }

    return (*t);
}

Apontador Insere(String k, Apontador *t) {
    Apontador p;
    int i;
    char caractere;
    char charDiff;

    if (*t == NULL) {
        return (CriaNoExt(k, &p));
    }
    else {
        p = *t;

        while (!EExterno(p)) {
            if (p->NO.NInterno.Index > strlen(k)) {
                caractere = k[strlen(k)];
            }
            else {
                caractere = Caractere(p->NO.NInterno.Index, k);
            }

            if (caractere < p->NO.NInterno.caractere) {
                p = p->NO.NInterno.Esq;
            }
            else {
                p = p->NO.NInterno.Dir;
            }
        }

        if (strcmp(k, p->NO.Chave) == 0) {
            printf("A palavra já está na árvore: %s\n", p->NO.Chave);
            return (*t);
        }
        else {
            i = 0;

            while (i < strlen(k) && Caractere(i, k) == Caractere(i, p->NO.Chave)) {
                i++;
            }

            if (i < strlen(k)) {
                if (Caractere(i, k) > Caractere(i, p->NO.Chave)) {
                    charDiff = k[i];
                }
                else {
                    charDiff = p->NO.Chave[i];
                }
            }
            else {
                charDiff = '\0';
            }

            return InsereEntre(k, t, i, charDiff);
        }
    }
}

void Pesquisa(String k, Apontador t) {
    if (t == NULL) {
        printf("A árvore está vazia!!!\n");
        return;
    }

    if (EExterno(t)) {
        if (strncmp(k, t->NO.Chave, strlen(k)) == 0) {
            printf("Palavra %s encontrada:\n", t->NO.Chave);
        }
    }
    else {
        Pesquisa(k, t->NO.NInterno.Esq);
        Pesquisa(k, t->NO.NInterno.Dir);
    }
}

void ImprimirPalavras(Apontador t) {
    if (t == NULL) {
        return;
    }

    if (EExterno(t)) {
        printf("%s\n", t->NO.Chave);
    }
    else {
        ImprimirPalavras(t->NO.NInterno.Esq);
        ImprimirPalavras(t->NO.NInterno.Dir);
    }
}

#define tam 200

int main() {
    Apontador arvore = NULL; // Inicializa a árvore como vazia

    char palavra[tam];

    FILE* f;

    char arquivo[] = "./POCs/gabriel.txt";

    f = fopen(arquivo, "r");

    if (f == NULL) {
        printf("Erro ao abrir arquivo %s\n", arquivo);
        return 1;
    }

    while (fscanf(f, "%s", palavra) == 1) {
        arvore = Insere(palavra, &arvore);
    }

    ImprimirPalavras(arvore);

    fclose(f);

    return 0;
}




 // #include <stdlib.h>
// // #include <stdio.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #define TRUE 1
// #define FALSE !TRUE
// #define D 8 /* depende de TipoChave */

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
// } TipoPatNo;


// char Caractere(int i, String k) {
//     return k[i];
// }

// short EExterno(Apontador p) {
//     return p->TNo == Externo;
// }

// short EInterno(Apontador p) {
//     return p->TNo == Interno;
// }

// Apontador CriaNoInt(int i, Apontador *Esq,  Apontador *Dir, char Caractere) { 
// 	Apontador p;
//     p = (Apontador)malloc(sizeof(TipoPatNo));  

//     p->TNo = Interno;
//     p->NO.NInterno.Esq = *Esq;
//     p->NO.NInterno.Dir = *Dir;

//     p->NO.NInterno.Index = i;
//     p->NO.NInterno.caractere = Caractere;

//     return p;
// }

// Apontador CriaNoExt(String k, Apontador *t) {
// 	Apontador p;
//     p = (Apontador)malloc(sizeof(TipoPatNo));
//     p->TNo = Externo;

//     p->NO.Chave = (String)malloc(strlen(k) * sizeof(char));
//     strcpy(p->NO.Chave, k);

//     return p;
// }

// Apontador InsereEntre(String k, Apontador *t, int i, char diff) {
// 	Apontador p;

//     if (EExterno(*t)) {
//         p = CriaNoExt(k, &p);
//         /* cria um novo no externo */
//         if (strcmp((*t)->NO.Chave, k) < 0) {
//            return (CriaNoInt(i, t, &p, diff));
//         }
//         else {
//            return (CriaNoInt(i, &p, t, diff));
//         }
//     }

//     else if (i < (*t)->NO.NInterno.Index) {
//         CriaNoExt(k, &p);

//         if (k[i] < diff) {
//             return (CriaNoInt(i, &p, t, diff));
//         } 
//         else {
//             return (CriaNoInt(i, t, &p, diff));
//         }
//     }

//     else {
//         int i = (*t)->NO.NInterno.Index;

//         if (Caractere((*t)->NO.NInterno.Index, k) >= (*t)->NO.NInterno.caractere) {
//             (*t)->NO.NInterno.Dir = InsereEntre(k, &(*t)->NO.NInterno.Dir, i, diff);
//         }
//         else {
//             (*t)->NO.NInterno.Dir = InsereEntre(k, &(*t)->NO.NInterno.Dir, i, diff);
//         }
//     }

//     return (*t);
// }

// Apontador Insere(String k, Apontador *t) {
    
//     Apontador p;
//     int i;
//     char caractere;
//     char charDiff;

//     // printf("Entrou na funcao!!!"); 
//     if (*t == NULL) {
//         return (CriaNoExt(k, &p));
//     }

//     else {
//         p = *t;

//         while (!EExterno(p)) { // Verifica se é interno 
//             if (p->NO.NInterno.Index > strlen(k)) {
//                 caractere = k[strlen(k)];
//             }
//             else {
//                 caractere = Caractere(p->NO.NInterno.Index, k);
//             }

//             if (caractere < p->NO.NInterno.caractere) {
//                 p = p->NO.NInterno.Esq;
//             }
//             else {
//                 p = p->NO.NInterno.Dir;
//             }
//         }

//         if (strcmp(k, p->NO.Chave) == 0) {
//             //printf("A palavra já está na arvore: %s\n", p->NO.Chave);
//             return (*t);
//         }
//         else {
//             i = 0;

//             while (Caractere(i, k) == Caractere(i, p->NO.Chave)) i++;

//             if (Caractere(i, k) >  Caractere(i, p->NO.Chave)) {
//                 charDiff = k[i];
//             }
//             else {
//                 charDiff = k[i];
//             }

//             return InsereEntre(k, t, i, charDiff);
//         }
//     }
// }

// void Pesquisa(String k, Apontador t) {
//     if (t == NULL) printf("Arvore está vazia!!!");

// 	if (EExterno(t)) {
// 		if (strncmp(k, t->NO.Chave, strlen(k)) == 0) {
// 			printf("Palavra %s encontrada:\n", t->NO.Chave);
// 		}
// 	}
//     else {
//         Pesquisa(k, t->NO.NInterno.Esq);
//         Pesquisa(k, t->NO.NInterno.Dir);
//     }
// }

// // void print(Apontador t) {
// //     if (t == NULL) return;

// //     if (!EExterno(t)) print(t->NO.NInterno.Esq);
    
// //     printf("%s\n", t->NO.Chave);

// //     if(!EExterno(t)) print(t->NO.NInterno.Dir);
// // }

// void ImprimirPalavras(Apontador t) {
//     if (t == NULL)
//         return;

//     if (EExterno(t))
//         printf("%s\n", t->NO.Chave);
//     else {
//         ImprimirPalavras(t->NO.NInterno.Esq);
//         ImprimirPalavras(t->NO.NInterno.Dir);
//     }
// }


// #define tam 200

// int main() {
//     Apontador arvore = NULL; // Inicializa a árvore como vazia

//     char palavra[tam];

//     FILE *f;
    
//     char arquivo[] = "./POCs/gabriel.txt";

//     f = fopen(arquivo, "r");

//     if (f == NULL) {
//         printf("Erro ao abrir arquivo %s\t", arquivo);
//         return 1;
//     }

//     while (fscanf(f, "%s", palavra) == 1) {
//         arvore = Insere(palavra, &arvore);
//         //print(arvore);
//     }
    
//     ImprimirPalavras(arvore);


//     //Pesquisa("aaaaa", arvore);
//     //print(arvore);

//     // printf("\n################# Pesquisando chave: #################\n");
//     // char* pesquisaChar = "te";
//     // Pesquisa(pesquisaChar, a);

//     // int i = 0;
//     // while(i < 5){
//     //     print(arvore);
//     //     i++;
//     // }

//     return 0;
// }
