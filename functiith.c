/*DUMITRACHE Daniela Andreea - 311CB*/

#include "hash_table.h"
#include "tlg.h"

 int hash_function(void *ae, size_t M)  //intoarce suma caracterelor ce fac parte din parametru
 {	
 	char *s = (char*)ae;
 	int i, sum = 0;

 	for(i = 0; i < strlen(s); i++)
 		sum += s[i];
 	return sum % M;
 }

int cmp(void *a, void* b)    //functia de comparare pentru ordonarea listei
{
	TEntry p1 = *(TEntry*)a;
	TEntry p2 = *(TEntry*)b;
	
	if(p1.fr == p2.fr)
		return strcmp(p2.key, p1.key); //daca frecventele sunt egale intorc rezultatul compararii alfabetice
	else
		return p1.fr - p2.fr;      //altfel intorc diferenta frecventelor
}

void AfiElemFile(void* ae, FILE *f)
{
  TEntry p = *(TEntry*)ae;
  fprintf(f, "(%s) ", p.value);    //afisez campul value din structura TEntry
}

void AfiElemFile_faraspatii(void* ae, FILE *f)
{
  TEntry p = *(TEntry*)ae;
  fprintf(f, "(%s)", p.value);    //afisez campul value din structura TEntry
}

void freeElem(void *a)   //eliberez un element de tip TEntry
{
	TEntry *p = (TEntry*)a;
	free(p->value);
	free(p->key);
	free(p);
}

int compK(char *s, void *ae)   //compar un sir de caractere cu o valoare data
{
	TEntry a = *(TEntry*)ae;
  
  return strcmp(s, a.key);
}

TH* alocaTH(size_t length)
{
  TH* h = NULL;   //initializez tabela cu null
  int i;

  h = malloc(sizeof(TH));
  h->M= length;      //initializez campul M al tabelei cu dimensiunea data ca parametru

  h->fh = hash_function;   //initializez functia hash a tabelei

  h->v = malloc(sizeof(TLDI) * length);  //aloc vectorul de liste
  for (i = 0; i < length; i++)
  	h->v[i] = NULL;

  return h;
}

void DistrugeHash(TH** h)
{
  int i;

  TH* aux = *h;   //element auxiliar ce urmeaza a fi  eliberat
  
  for (i = 0; i < aux->M; i++) {
    TLDI *p = aux->v + i;   

  	DistrugeL(p, freeElem); //parcurg vectorul de liste si il eliberez element cu element
  }

  free(aux->v); //eliberez vectorul de lista din tabela auxiliara 
  free(aux);    //eliberez tabela auxiliara
  aux = NULL;
}

void print(TH* h, FILE *f) //printeaza tabela hash
{
	int i; 
	for(i = 0; i < h->M; i++)   //parcurg vectorul de liste pana la sfarsit
	{
		if(*(h->v + i) != NULL)   //verific ca lista sa nu fie vida
		{	
			fprintf(f, "%d: ", i);
			int j = 0;
			TLDI *p = h->v + i, el = *p;

			for(j=0; j < LungimeL(*(h->v + i)); j++)  //afisez valoarea pentru fiecare celula din fiecare lista
		{	
			TEntry *a = (TEntry*)(el->info); //cast la structura de tip TEntry pentru a putea accesa campul dorit
			if((LungimeL(*(h->v + i))  == 1)  ||( el->urm == *p))
				fprintf(f, "(%s)", a->value);
			else
				fprintf(f, "(%s) ", a->value);
			el = el->urm;
		}
			fprintf(f, "\n");
		}
	}
}

int set(char *key, char *value, TH *h)  //0 pentru inserare nereusita, 1 in caz contrar
{
	int cod = h->fh(key, h->M);   //calculez indicele listei din vectorul h->v unde ar trebui inserat elementul
 	TLDI *p = h->v + cod;
 	TLDI el = *p;

 if(!p)
    return 0;

int n = LungimeL(*(h->v + cod)), i;
for(i = 0; i<n; i++)   //pacurg lista cu indicele cod
{
	if(compK(key, el->info) == 0) //daca key exista deja in lista atunci intrerup procesul de inserare
	{
		return 0;
	}
	el = el->urm;
}

 if(n == h->M)  //verific daca numarul de elemente din lista este egal cu  M
  	{	TEntry *ae = malloc(sizeof(TEntry));  //elementul ce urmeaza a fi inserat in tabela
	    ae->key = strdup(key);
	    ae->value = strdup(value);
	    ae->fr = 0;
  		DistrugeCel(h->v + cod, freeElem, cmp, (*p)->pre->info);  //sterg ultimul element din lista
  		InsL(h->v + cod, ae, sizeof(TEntry), cmp);     //realizez inserarea
  		return 1;   
  	}
  
  	int sum = 0;
  	for(i=0; i < h->M; i++)    //calculez in sum numarul de elemente din tabela
  		sum += LungimeL(*(h->v + i));

  if(sum < 2*h->M)  //daca sum este < 2*M atunci inserez fara relocarea vectorului h->v
  	{
	  	TEntry *ae = malloc(sizeof(TEntry));  //elementul ce urmeaza a fi inserat in tabela
	  	ae->key = strdup(key);
	  	ae->value = strdup(value);
	  	ae->fr = 0;
	  	InsL(h->v + cod, ae, sizeof(TEntry), cmp);
	  	return 1;
  	}

    TH *h1 = alocaTH(2*h->M);  //in acest caz trebuie sa realoc tabela
    if(!h1)
      return 0; 
    int j;
    for(i = 0; i < h->M; i++)    //parcurg tabela veche si inserez in noua tabela valorile vechi
    {
      TLDI *p = h->v + i;
      TLDI el = *p;
      for(j = 0; j < LungimeL(el); j++)   //parcurg fiecare lista si inserez element cu element in noua tabela
      {
        TEntry *x = (TEntry*)el->info;
        int cod1 = h1->fh(x->key, h1->M);
        InsL(h1->v + cod1, x, sizeof(TEntry), cmp);
        el = el->urm;
      }
    }

    TEntry *ae = malloc(sizeof(TEntry));  //elementul ce urmeaza a fi inserat in tabela cea noua
    ae->key = strdup(key);
    ae->value = strdup(value);
    ae->fr = 0;
    int cod2 = h1->fh(key, h1->M);
    TLDI *b = h1->v + cod2;
  	InsL(h1->v + cod2, ae, sizeof(TEntry), cmp);
    *h = *h1;    //trec de la tabela veche h la cea noua cu 2*h->M elemente
    return 1;
  
}

void print_list(int index, TH *h, FILE *f) //afisez lista cu indicele index
{
	if(index < h->M)    //verific ca numarul dat sa fie un indice valid de lista
	{
		TLDI *p = h->v + index, el = *p;
		fprintf(f, "%d: ", index);
		if(*p == NULL)         //verific ca lista sa nu fie vida
			fprintf(f, "VIDA");
	
		int i;
		for(i = 0; i < LungimeL(*p); i++)  //parcurg lista pana la sfarsit
		{	
			if( el->urm == *p)    //afisez valoarea din fiecare celula printr-o functie speciala
				 AfiElemFile_faraspatii(el->info, f);
			else
				AfiElemFile(el->info, f);

			el = el->urm;
		}
		fprintf(f, "\n");
	}
}

int Remove(TH *h, char *key)   //0 in caz de eliminare nereusita, 1 altfel
{
	int cod = h->fh(key, h->M);   //calculez indicele listei unde ar trebui sa se afle elementul
	TLDI *p = h->v + cod, el = *p;
	int i;
	for(i = 0; i < LungimeL(el); i++)  //parcurg lista
	{
		if(compK(key, el->info) == 0)    //verific ca elemntul sa existe in lista
		{	if(LungimeL(el) == 1)
				DistrugeL(h->v + cod, freeElem);    //daca este singurul elemnt din lista distrug lista

			DistrugeCel(h->v + cod, freeElem, cmp, el->info); //daca nu elimin elementul din lista
 			return 1;
		}
		el = el->urm;
	}
	return 0;
}


char *get(TH *h, char *key)   //intorc valoarea daca exista elementul, NULL altfel
{
	int cod = h->fh(key, h->M);   //calculez indicele listei unde ar trebui sa se afle elementul
	TLDI *p = h->v + cod, el = *p;
	int i;
	for(i = 0; i < LungimeL(el); i++)  //parcurg lista
	{
		if(compK(key, el->info) == 0)   //daca gasesc elementul
		{	
			TEntry *a = (TEntry*)el->info;   //stiu ca pare ciudat, dar mi s-a parut mai usor asa :)
			a->fr++;                          //salvez frecventa incrementata si restul valorilor din elemntul dat ca parametru
			int fr = a->fr;
			char *val = strdup(a->value);
			char *key1 = strdup(a->key);
			//Remove(h, key);     //il sterg din tabela
			if(LungimeL(*(h->v + cod)) > 1)
				DistrugeCel(h->v + cod, freeElem, cmp, a);
			else
				DistrugeL(h->v + cod, freeElem);

			TEntry *ae = malloc(sizeof(TEntry));   //il inserez din nou in lista cu frecventa marita
  			ae->key = strdup(key1);
  			ae->value = strdup(val);
  			ae->fr = fr;
  			InsL(h->v + cod, ae, sizeof(TEntry), cmp);
  			return val;
		}
		el = el->urm;
	}

	return NULL;
}