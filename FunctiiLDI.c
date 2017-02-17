/*DUMITRACHE Daniela Andreea - 311CB*/

#include "tlg.h"

int InsL(TLDI *aL, void* ae, size_t d, TFCmp f)
{
	TLDI aux = malloc(sizeof(TCelulaG));  /*celula ce urmeaza a fi inserata*/
 	if(!aux) return 0;
 	aux->info = malloc(d);
 	if(!aux->info)          //verific alocarea
 	{free(aux);
 	 return 0;}
 	memcpy(aux->info, ae, d); //copiez informatia in aux  

 	if((*aL) == NULL)    /*verific daca lista este vida*/
 	{
 		*aL = aux;
 		(*aL)->urm = *aL;
 		(*aL)->pre = *aL;
 		return 1;
 	}
 	
 	int  i; TLDI p =*aL;
	for(i = 0; i < LungimeL(*aL); i++) //parcurg lista pana gassesc elemntul inaintea caruia se va insera
	{
		if(f(p->info,ae) < 0)
		{
			break;
		}
		p = p->urm;
	}
	aux->urm = p;    /*refacerea legaturilor*/
	aux->pre = p->pre;
	p->pre = aux;
	aux->pre->urm = aux;
	if(p == *aL)     /*verific daca trebuie schimbat inceputul de lista*/
	{
		if(f((*aL)->info, aux->info) < 0)
			*aL = aux;	}
  	return 1;
}

void DistrugeCel(TLDI* aL, Myfree f, TFCmp fcomp, void *ae) 
{	 int i;
	TLDI p = *aL;
 	for(i = 0; i < LungimeL(*aL); i++) /*parcurg lista panagasesc elementul ce trebuie eliminat*/
 	{
 		if(fcomp(p->info, ae) == 0)
 		{	
 			TLDI aux = p;             /*aux ce urmeaza a fi eliberat*/
 			p->urm->pre = p->pre;    //refacerea legaturilor
 			p->pre->urm = p->urm;
 			if(p == *aL)               //verific daca trebuie schimbat capatul de lista
 				*aL = p->urm;
 			else
 				p = p->urm;
 			f(aux->info);       //eliberez informatia si apoi celula
 			free(aux);
 			break;
 		}
 		p = p->urm;
 	}
}

void DistrugeL(TLDI* aL, Myfree f)
{

	while(LungimeL(*aL) > 0)	//parcurg lista pana la sfarsit
	{	
		TLDI p = *aL;
 		TLDI aux ;
 		if(LungimeL(*aL) == 1)    //daca lista are un singur element il elimin direct
 			{
 				aux = *aL;
 				f(aux->info);
 				free(aux);
 				*aL = NULL;
 				break;
 			}
 		aux = p;                  //altfel eliberez element cu element ca mai sus
 		p->urm->pre = p->pre; 
 		p->pre->urm = p->urm;
 		
 		if(p == *aL)
 			*aL = p->urm;
 		else
 			p = p->urm;
 		f(aux->info);
 		free(aux);
	}
}

size_t LungimeL(TLDI a)
{
	size_t count = 1;      
	if(a == NULL)
		return 0;
	if(a->urm == a)
		return  1;
	TLDI p = a->urm;         //parcurg lista si incrementez count la fiecare element pana ma intorc la inceput
	for(;p != a; p = p->urm)
		count ++;
	return count;
}

void AfisareL(TLDI a, TFAfi f)
{	int n = LungimeL(a), i;

	if(a == NULL)          //verificare lista vida
		printf("lista vida\n");
	TLDI p = a;             
	for(i = 0; i<n; i++)    //parcurg lista si afisez fiecare element din ea printr-o functie speciala
	{	
		f(p->info);
		p = p->urm;
	}
}