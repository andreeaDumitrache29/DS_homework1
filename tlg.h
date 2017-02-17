/*DUMITRACHE Daniela Andreea - 311CB*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <unistd.h>

#ifndef _LISTA_GENERICA_
#define _LISTA_GENERICA_

typedef struct celulag
{ 
  void* info;           /* adresa informatie */
  struct celulag *urm, *pre;   /* adresa urmatoarei celule si a ultimei celule */
} TCelulaG, *TLDI; /* tipurile Celula si Lista  */

typedef int (*TFElem)(void*);     /* functie prelucrare element */
typedef int (*TFCmp)(void*, void*); /* functie de comparare doua elemente */
typedef void (*TFAfi)(void*);     /* functie afisare un element */
typedef void Myfree(void *a);   /*functie de eliberare element tip structura TEntry*/

/*- inserare ordonata in lista: 1 daca reuseste, 0 in caz contrar -*/
int InsL(TLDI *aL, void* ae, size_t d, TFCmp f);

void DistrugeCel(TLDI*,Myfree, TFCmp fcomp, void *ae); /* elimina celula a carei informatie corepsunde cu o valoare data */
void DistrugeL(TLDI* aL, Myfree); /* distruge lista */

size_t LungimeL(TLDI);   /* intoarce numarul de elemente din lista */

/* afiseaza elementele din lista */
void AfisareL(TLDI a, TFAfi f);

#endif
