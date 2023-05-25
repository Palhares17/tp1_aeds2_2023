// #include <stdlib.h>
// #include <stdio.h>
#include <sys/time.h>
#include "../header/patricia.h"

char Bit(TipoindexAmp i, char *k)
{
	//  Retorna o i-esimo bit da chave k a partir da esquerda */
	return k[i];
}

short MenorIgual(char a, char b)
{
	if (a == NULL)
		return NULL;

	if (b == NULL)
		return NULL;

	if (a <= b)
	{
		return TRUE;
	}
	else
		return FALSE;
}

short EExterno(TipoArvore p)
{ /* Verifica se p^ e nodo externo */
	return (p->nt == Externo);
}

TipoArvore CriaNoInt(int i, TipoArvore *Esq, TipoArvore *Dir, char caractere)
{
	TipoArvore p;
	p = (TipoArvore)malloc(sizeof(TipoPatNo));
	p->nt = Interno;
	p->NO.NInterno.Esq = *Esq;
	p->NO.NInterno.Dir = *Dir;
	p->NO.NInterno.Index = i;
	p->NO.NInterno.caractere = caractere;
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
	if (MenorIgual(Bit(t->NO.NInterno.Index, k),t->NO.NInterno.caractere)) {
        return Pesquisa(k, t->NO.NInterno.Esq);
	}
    else return Pesquisa(k, t->NO.NInterno.Dir);
}

TipoArvore InsereEntre(char *k, TipoArvore *t, int i)
{
	TipoArvore p;
	char caractere;
	if (EExterno(*t) || i < (*t)->NO.NInterno.Index) { 
		/* cria um novo no externo */
		 if(EExterno(*t)){
           caractere = Bit(i,(*t)->NO.Chave);
        }
        else{
          caractere = (*t)->NO.NInterno.caractere;
        }
        p = CriaNoExt(k);

        if (MenorIgual(Bit(i, k),caractere))
            return (CriaNoInt(i,&p,t,Bit(i, k)));
        else return (CriaNoInt(i,t,&p,caractere));
			
	}
	else
	{
		if (MenorIgual(Bit((*t)->NO.NInterno.Index, k),(*t)->NO.NInterno.caractere))
            (*t)->NO.NInterno.Esq = InsereEntre(k,&(*t)->NO.NInterno.Esq,i);
        else
            (*t)->NO.NInterno.Dir = InsereEntre(k,&(*t)->NO.NInterno.Dir,i);
        return (*t);
	}
}

TipoArvore Insere(char *k, TipoArvore *t)
{
	// printf("Entrou na função insere!!!\n");
	TipoArvore p;
	int i;

	if (*t == NULL)
	{
		return (CriaNoExt(k));
	}

	else
	{
		p = *t;
		while (!EExterno(p))
		{
			if (MenorIgual(Bit(p->NO.NInterno.Index, k), p->NO.NInterno.caractere))
			{
				// printf("Palavra incluida: %s\n", k);
				p = p->NO.NInterno.Esq;
			}
			else
			{
				// printf("%s\n", p->NO.Chave);
				// printf("Palavra incluida: %s\n", k);
				p = p->NO.NInterno.Dir;
			}
		}
		/* acha o primeiro Bit diferente */
		i = 0;

		//(i <= D)

		// Busca o primeiro caractere diferente
		if (strlen(k) > strlen(p->NO.Chave))
		{
			while ((i <= strlen(k)) && (Bit((int)i, k) == Bit((int)i, p->NO.Chave)))
				i++;
			if (i >= strlen(k))
			{
				printf("Erro: chave ja esta na arvore %s = %s\n", k, p->NO.Chave);
				return (*t);
			}
			else
				return (InsereEntre(k, t, i));
		}
		else
		{
			while ((i <= strlen(p->NO.Chave)) && (Bit((int)i, k) == Bit((int)i, p->NO.Chave)))
				i++;
			if (i >= strlen(k))
			{
				printf("Erro: chave ja esta na arvore %s = %s\n", k, p->NO.Chave);
				return (*t);
			}
			else
				return (InsereEntre(k, t, i));
		}
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
