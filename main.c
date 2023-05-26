#include "./header/patricia.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tam 200

int main() {
    Apontador arvore = NULL; // Inicializa a árvore como vazia

    char palavra[tam];

    FILE *f;
    
    char arquivo[] = "./POCs/gabriel.txt";

    f = fopen(arquivo, "r");

    if (f == NULL) {
        printf("Erro ao abrir arquivo %s\t", arquivo);
        return 1;
    }

    while (fscanf(f, "%s ", palavra) == 1) {
        arvore = Insere(palavra, &arvore);
        print(arvore);
    }

    // printf("\n################# Pesquisando chave: #################\n");
    // char* pesquisaChar = "te";
    // Pesquisa(pesquisaChar, a);

    // int i = 0;
    // while(i < 5){
    //     print(arvore);
    //     i++;
    // }

    return 0;
}
