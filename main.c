#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "patricia.h"

#define MAX_SIZE 100

int main(int argc, char *argv[])
{
    TipoArvore a = NULL;
    
    /*TipoChave c;
    int i, j, k, n;
    int min = 32, max = 126;
    TipoChave vetor[95];*/

    FILE *arquivo;
    char palavra[MAX_SIZE];

    arquivo = fopen("gabriel.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    while (fscanf(arquivo, "%s", palavra) == 1) {
        //printf("Palavra: %s\n", palavra);
       // strcpy(c, palavra);
        printf("Inserindo chave: %s\n", palavra);
        a = Insere(palavra, &a);
    }

    fclose(arquivo);




    /* Gera uma permutacao aleatoria de chaves dos caracteres ASCII 32 a  126 
    struct timeval semente;
    gettimeofday(&semente, NULL);
    srand((int)(semente.tv_sec + 1000000 * semente.tv_usec));
    for (i = min; i <= max; i++)
        vetor[i - 32] = i;
    for (i = min; i <= max; i++)
    {
        k = min + (int)((float)(max - min) * rand() / (RAND_MAX + 1.0));
        j = min + (int)((float)(max - min) * rand() / (RAND_MAX + 1.0));
        n = vetor[k - 32];
        vetor[k - 32] = vetor[j - 32];
        vetor[j - 32] = n;
    }
    // Insere cada chave na arvore 
    for (i = min; i <= max; i++)
    {
        c = vetor[i - 32];
        printf("Inserindo chave: %c\n", c);
        a = Insere(c, &a);
    }
    // Gera outra permutacao aleatoria de chaves
    for (i = min; i <= max; i++)
    {
        k = min + (int)((float)(max - min) * rand() / (RAND_MAX + 1.0));
        j = min + (int)((float)(max - min) * rand() / (RAND_MAX + 1.0));
        n = vetor[k - 32];
        vetor[k - 32] = vetor[j - 32];
        vetor[j - 32] = n;
    }*/
    // Pesquisa cada chave na arvore 
    /*for (i = min; i <= max; i++)
    {
        c = vetor[i - 32];
        printf("Pesquisando chave: %c\n", c);
        Pesquisa(c, a);
    }*/
    return 0;
}
