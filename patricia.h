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

void Inicializa(Apontador *t);
char Caractere(int i, String k);
short EExterno(Apontador p);
short EInterno(Apontador p);
Apontador CriaNoInt(int i, Apontador *Esq,  Apontador *Dir, char Caractere);
Apontador CriaNoExt(String k, Apontador *t);
Apontador InsereEntre(String k, Apontador *t, int i, char diff);
void Pesquisa(String k, Apontador t);
Apontador Insere(String k, Apontador *t);
void print(Apontador t);