#include "../header/patricia.h"

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

Apontador CriaNoExt(String k, Apontador *t, int idDoc) {
    Apontador p;
    p = (Apontador)malloc(sizeof(TipoPatNo));
    p->TNo = Externo;
    p->NO.Chave = (String)malloc((strlen(k) + 1) * sizeof(char));
    strcpy(p->NO.Chave, k);
    for (int i = 0; i < MAX_ARQUIVOS; i++) {
        p->contagem[i] = 0;
    }
    p->contagem[idDoc - 1] = 1;
    return p;
}

Apontador InsereEntre(String k, Apontador *t, int i, char diff, int idDoc) {
    Apontador p;

    if (EExterno(*t)) {
        p = CriaNoExt(k, &p, idDoc);
        if (strcmp((*t)->NO.Chave, k) < 0) {
            return (CriaNoInt(i, t, &p, diff));
        }
        else {
            return (CriaNoInt(i, &p, t, diff));
        }
    }
    else if (i < (*t)->NO.NInterno.Index) {
        p = CriaNoExt(k, &p, idDoc);
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
            (*t)->NO.NInterno.Dir = InsereEntre(k, &(*t)->NO.NInterno.Dir, i, diff, idDoc);
        }
        else {
            (*t)->NO.NInterno.Esq = InsereEntre(k, &(*t)->NO.NInterno.Esq, i, diff, idDoc);
        }
    }

    return (*t);
}

Apontador Insere(String k, Apontador *t, int idDoc) {
    Apontador p;
    int i;
    char caractere;
    char charDiff;

    if (strlen(k) < 3) {
        //printf("A palavra '%s' não possui 3 ou mais letras e será ignorada.\n", k);
        return (*t);
    }

    if (*t == NULL) {
        return (CriaNoExt(k, &p, idDoc));
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

        if (strcasecmp(k, p->NO.Chave) == 0) {
            printf("A palavra já está na árvore: %s\n", p->NO.Chave);
            p->contagem[idDoc - 1]++;
            return (*t);
        }
        else {
            i = 0;

            while (i < strlen(k) && tolower(Caractere(i, k)) == tolower(Caractere(i, p->NO.Chave))) {
                i++;
            }

            if (i < strlen(k)) {
                if (tolower(Caractere(i, k)) > tolower(Caractere(i, p->NO.Chave))) {
                    charDiff = k[i];
                }
                else {
                    charDiff = p->NO.Chave[i];
                }
            }
            else {
                charDiff = '\0';
            }

            return InsereEntre(k, t, i, charDiff, idDoc);
        }
    }
}

void Pesquisa(String k, Apontador t) {
    if (t == NULL) {
        printf("A árvore está vazia!!!\n");
        return;
    }

    if (EExterno(t)) {
        if (strncasecmp(k, t->NO.Chave, strlen(k)) == 0) {
            printf("Palavra %s encontrada:\n", t->NO.Chave);
            for (int i = 0; i < MAX_ARQUIVOS; i++) {
                if (t->contagem[i] > 0) {
                    printf("<%d,%d> ", t->contagem[i],  i + 1);
                }
            }
            printf("\n");
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
        printf("Palavra: %s ", t->NO.Chave);
        for (int i = 0; i < MAX_ARQUIVOS; i++) {
            if (t->contagem[i] > 0) {
                printf("<%d,%d> ", t->contagem[i],  i + 1);
            }

        }
        printf("\n");
    }
    else {
        ImprimirPalavras(t->NO.NInterno.Esq);
        ImprimirPalavras(t->NO.NInterno.Dir);
    }
}

void CalcularRelevancia(int numDocumentos, Apontador t, String termo) {
    // Verificar se a árvore está vazia
    if (t == NULL) {
        printf("A árvore está vazia!!!\n");
        return;
    }

    // Inicializar as variáveis para o cálculo de relevância
    int q = strlen(termo); // Número de termos na consulta
    int N = numDocumentos; // Número total de documentos

    // Percorrer a árvore e buscar o termo
    Apontador p = t;
    while (!EExterno(p)) {
        int index = p->NO.NInterno.Index;
        if (Caractere(index, termo) >= p->NO.NInterno.caractere) {
            p = p->NO.NInterno.Dir;
        } else {
            p = p->NO.NInterno.Esq;
        }
    }

    // Verificar se o termo foi encontrado na árvore
    if (strncasecmp(termo, p->NO.Chave, strlen(termo)) == 0) {
        printf("Termo '%s' encontrado:\n", p->NO.Chave);
        for (int i = 0; i < numDocumentos; i++) {
            int f = p->contagem[i]; // Número de ocorrências do termo no documento
            double w = f * log(N) / q; // Cálculo da relevância
            if (f > 0) {
                printf("Documento %d: relevância %.2f\n", i + 1, w);
            }
        }
    } else {
        printf("Termo '%s' não encontrado na árvore.\n", termo);
    }
}