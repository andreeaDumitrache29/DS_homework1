/*DUMITRACHE Daniela Andreea - 311CB*/

#include "tlg.h"

typedef int (*TFHash)(void*, size_t M);  /* functia hash a tabelei*/

typedef struct
{
	size_t M; /*dimensiune vector de liste*/
	TFHash fh; /*functia hash asociata*/
	TLDI *v;   /*vectorul de liste */
} TH;

typedef struct {      /*structura ce simuleaza un element din serverul de DNS */
char *key, *value;
int fr;
 } TEntry;


void AfiEntry(void * ae); /*functii de afisare structura TEntry*/
void AfiElemFile_faraspatii(void* ae, FILE *f);
void AfiElemFile(void* ae, FILE *f);

int compKey(char *key, void *ae);   /*compara o cheie cu o valoare daca ca parametru */

TH* alocaTH(size_t length);    /*functie de alocare  tabela hash*/
void DistrugeHash(TH** h);     /*functie pentru eliberarea tabelei hash*/

/*functiile cerute in enuntul temei*/
int set(char *key, char *value, TH *h); 
void print(TH* h, FILE* F);
void print_list(int index, TH *h, FILE *f);
int Remove(TH *h, char *key);
char *get(TH *h, char *key);
