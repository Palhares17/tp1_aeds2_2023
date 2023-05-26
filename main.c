#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "patricia.h"

#define UPPER_A 65
#define UPPER_Z 90

#define LOWER_A 97
#define LOWER_Z 122

#define STRING_SIZE 256

int main() {
    Apontador arvore; // Inicializa a árvore como vazia
    Inicializa(&arvore);

    char palavra[STRING_SIZE];
    char ch;

    FILE *f;
    
    char arquivo[] = "gabriel.txt";

    f = fopen(arquivo, "r");

    if (f == NULL) {
        printf("Erro ao abrir arquivo %s\t", arquivo);
        return 1;
    }

    while (fscanf(f, "%s ", palavra) == 1) {
        arvore = Insere(palavra, &arvore);
        // print(arvore);
        Pesquisa("pato", arvore);
    }

    // printf("\n################# Pesquisando chave: #################\n");
    // char* pesquisaChar = "te";
    // Pesquisa(pesquisaChar, a);

    int i = 0;
    while(i < 5){
        print(arvore);
        i++;
    }

    return 0;
}