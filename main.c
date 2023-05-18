#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "patricia.h"

// int main() {
//     TipoArvore arvore = NULL; // Inicializa a árvore como vazia

//     // Exemplo de uso das funções
//     TipoChave chave = 42;

//     printf("entrei nessa buceta");
//     Insere(chave, &arvore);
//     Pesquisa(chave, arvore);

//     return 0;
// }

int main(int argc, char *argv[])
{
    TipoArvore a = NULL;
    TipoChave c;
    int i, j, k, n;
    int min = 32, max = 126;
    TipoChave vetor[95];
    /* Gera uma permutacao aleatoria de chaves dos caracteres ASCII 32 a  126 */
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
    /* Insere cada chave na arvore */
    for (i = min; i <= max; i++)
    {
        c = vetor[i - 32];
        printf("Inserindo chave: %c\n", c);
        a = Insere(c, &a);
    }
    /* Gera outra permutacao aleatoria de chaves */
    for (i = min; i <= max; i++)
    {
        k = min + (int)((float)(max - min) * rand() / (RAND_MAX + 1.0));
        j = min + (int)((float)(max - min) * rand() / (RAND_MAX + 1.0));
        n = vetor[k - 32];
        vetor[k - 32] = vetor[j - 32];
        vetor[j - 32] = n;
    }
    /* Pesquisa cada chave na arvore */
    for (i = min; i <= max; i++)
    {
        c = vetor[i - 32];
        printf("Pesquisando chave: %c\n", c);
        Pesquisa(c, a);
    }
    return 0;
}
