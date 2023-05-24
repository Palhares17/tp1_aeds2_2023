#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "./header/patricia.h"

#define MAX_SIZE 100

int main() {
  TipoArvore a = NULL;
  // int numArq = 0;
  FILE *arquivo;
  char palavra[MAX_SIZE];

  // printf("QUantidade de arquivos: ");
  // scanf("%d", &numArq);

  // for (int i = 0; i < numArq; i++) {}

  arquivo = fopen("./POCs/cleber.txt", "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return 1;
  }

  while (fscanf(arquivo, "%s", palavra) == 1) {
    // printf("Inserindo chave: %s\n", palavra);
    a = Insere(palavra, &a);
  }

  printf("\n################# Pesquisando chave: #################\n");
  char* pesquisaChar = "te";
  // Pesquisa(pesquisaChar, a);
  printArvore(a);
  fclose(arquivo);
  return 0;
}
