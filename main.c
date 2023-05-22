#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "./header/patricia.h"

#define MAX_SIZE 100

int main() {
  TipoArvore a = NULL;

  FILE *arquivo;
  char palavra[MAX_SIZE];

  arquivo = fopen("./POCs/cleber.txt", "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return 1;
  }

  while (fscanf(arquivo, "%s", palavra) == 1) {
    printf("Inserindo chave: %s\n", palavra);
    a = Insere(palavra, &a);
  }

  fclose(arquivo);
  return 0;
}
