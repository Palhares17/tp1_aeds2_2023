// #include <stdlib.h>
// #include <stdio.h>
#include <sys/time.h>
#include "../header/patricia.h"

TipoDib Bit(TipoindexAmp i, char *k)
{
  //  Retorna o i-esimo bit da chave k a partir da esquerda */
  return k[i];
}

short EExterno(TipoArvore p)
{ /* Verifica se p^ e nodo externo */
  return (p->nt == Externo);
}

TipoArvore CriaNoInt(int i, TipoArvore *Esq, TipoArvore *Dir) 
{
  TipoArvore p;
  p = (TipoArvore)malloc(sizeof(TipoPatNo));
  p->nt = Interno;
  p->NO.NInterno.Esq = *Esq;
  p->NO.NInterno.Dir = *Dir;
  p->NO.NInterno.Index = i;
  return p;
}

TipoArvore CriaNoExt(char *k)
{
  TipoArvore p;
  p = (TipoArvore)malloc(sizeof(TipoPatNo));
  p->nt = Externo;
  // strcpy(p->NO.Chave, k);
  p->NO.Chave = k;
  return p;
}

void Pesquisa(char *k, TipoArvore t)
{
  printf("palavra pesquisada: %s\n", k);

  if (EExterno(t))
  {
    if (strncmp(k, t->NO.Chave, strlen(k)) == 0)
    {
      printf("Elemento encontrado\n");
      printf("%s\n", t->NO.Chave);
    }
    else
    {
      printf("%s\n", t->NO.Chave);
      printf("Elemento nao encontrado\n");
    }
    return;
  }
  if (Bit(t->NO.NInterno.Index, k) == 0)
  {
    Pesquisa(k, t->NO.NInterno.Esq);
    printf("%s\n", t->NO.Chave);
  }
  else
    Pesquisa(k, t->NO.NInterno.Dir);
}

TipoArvore InsereEntre(char *k, TipoArvore *t, int i)
{
  TipoArvore p;
  if (EExterno(*t) || i < (*t)->NO.NInterno.Index)
  { /* cria um novo no externo */
    p = CriaNoExt(k);
    if (Bit(i, k) == 1)
      return (CriaNoInt(i, t, &p));
    else
      return (CriaNoInt(i, &p, t));
  }
  else
  {
    if (Bit((*t)->NO.NInterno.Index, k) == 1)
      (*t)->NO.NInterno.Dir = InsereEntre(k, &(*t)->NO.NInterno.Dir, i);
    else
      (*t)->NO.NInterno.Esq = InsereEntre(k, &(*t)->NO.NInterno.Esq, i);
    return (*t);
  }
}

TipoArvore Insere(char *k, TipoArvore *t)
{
  // printf("Entrou na função insere!!!\n");
  TipoArvore p;
  int i; // D, aux = 0, l = 0;

  /*while (k[l] != '\0')
      {
        aux++;
      }
      D = aux*8;*/
  if (*t == NULL)
    return (CriaNoExt(k));
  else
  {
    p = *t;
    while (!EExterno(p))
    {
      if (Bit(p->NO.NInterno.Index, k) == 1)
      {
        // printf("Palavra incluida: %s\n", k);
        p = p->NO.NInterno.Dir;
      }
      else
      {
        // printf("%s\n", p->NO.Chave);
        // printf("Palavra incluida: %s\n", k);
        p = p->NO.NInterno.Esq;
      }
    }
    /* acha o primeiro bit diferente */
    i = 0;

    //(i <= D)
    while ((i < strlen(k)) && (Bit((int)i, k) == Bit((int)i, p->NO.Chave)))
      i++;
    if (i > D)
    {
      printf("Erro: chave ja esta na arvore\n");
      return (*t);
    }
    else
      return (InsereEntre(k, t, i));
  }
}

void printNo(TipoArvore t)
{
  if (t == NULL)
    printf("No Nulo\n");
  else if (t->nt == Externo)
  {
    printf("No{\n Tipo: Externo\n Chave:%s\n};\n", t->NO.Chave);
  }
  /*else{
    printf("No{\n Tipo: Interno\n Indice: %d\n Caractere: %c\n};\n",no->NO.NInterno.Index,no->NO.NInterno.Caractere);
  }*/
}

void printArvore(TipoArvore t)
{
  if (t == NULL)
    return;
  if (!EExterno(t))
    printArvore(t->NO.NInterno.Esq);
  printNo(t);
  if (!EExterno(t))
    printArvore(t->NO.NInterno.Dir);
}
