#include "./header/patricia.h"

#define tam 200

int main() {
    Apontador arvore = NULL; // Inicializa a árvore como vazia

    char palavra[tam];

    FILE *f;
    
    char arquivo[] = "./POCs/cleber.txt";

    f = fopen(arquivo, "r");

    if (f == NULL) {
        printf("Erro ao abrir arquivo %s\t", arquivo);
        return 1;
    }

    while (fscanf(f, "%s ", palavra) == 1) {
        arvore = Insere(palavra, &arvore);
        //print(arvore);
    }

    Pesquisa("aaaaa", arvore);
    print(arvore);

    return 0;
}
