// #include <stdlib.h>
// #include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE !TRUE
#define D 8 /* depende de TipoChave */

typedef char *String;

typedef enum {
    Interno,
    Externo
} TipoNo;

typedef struct TipoPatNo *Apontador;
typedef struct TipoPatNo {
    TipoNo TNo;
    union {
        struct { 
            short Index;
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

Apontador CriaNoInt(int i, Apontador *Esq,  Apontador *Dir, char Caractere) { 
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

    p->NO.Chave = (String)malloc(strlen(k) * sizeof(char));
    strcpy(p->NO.Chave, k);
 
    return *t;
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
        CriaNoExt(k, &p);

        if (k[i] < diff) {
            return (CriaNoInt(i, &p, t, diff));
        } 
        else {
            return (CriaNoInt(i, t, &p, diff));
        }
    }

    else {
        int i = (*t)->NO.NInterno.Index;

        if (Caractere((*t)->NO.NInterno.Index, k) >= (*t)->NO.NInterno.caractere) {
            (*t)->NO.NInterno.Dir = InsereEntre(k, &(*t)->NO.NInterno.Dir, i, diff);
        }
        else {
            (*t)->NO.NInterno.Dir = InsereEntre(k, &(*t)->NO.NInterno.Dir, i, diff);
        }
    }

    return (*t);
}

Apontador Insere(String k, Apontador *t) {
    Apontador p;
    int i;
    char caractere;
    char charDiff;

    // printf("Entrou na funcao!!!"); 
    if (*t == NULL) {
        return (CriaNoExt(k, &p));
    }

    else {
        p = (*t);

        while (!EExterno(p)) { // Verifica se é interno 
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

        if (strncmp(k, p->NO.Chave, strlen(k)) == 0) {
            printf("A palavra já está na arvore: %s\n", p->NO.Chave);
            return (*t);
        }
        else {
            i = 0;

            while (Caractere(i, k) == Caractere(i, p->NO.Chave)) i++;

            if (Caractere(i, k) >  Caractere(i, p->NO.Chave)) {
                charDiff = k[i];
            }
            else {
                charDiff = k[i];
            }

            return InsereEntre(k, t, i, charDiff);
        }
    }
}

void Pesquisa(String k, Apontador t) {
    if (t == NULL) printf("Arvore está vazia!!!");

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

void print(Apontador t) {
    if (t == NULL) return;

    if (!EExterno(t)) print(t->NO.NInterno.Esq);
    
    printf("%s\n", t->NO.Chave);

    if(!EExterno(t)) print(t->NO.NInterno.Dir);
}