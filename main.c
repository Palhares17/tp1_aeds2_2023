#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patricia.h"

int main() {
    TipoArvore arvore = NULL; // Inicializa a árvore como vazia
    
    // Exemplo de uso das funções
    TipoChave chave = 42;
    Insere(chave, &arvore);
    Pesquisa(chave, arvore);

    return 0;
}