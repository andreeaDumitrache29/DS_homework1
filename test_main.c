/*DUMITRACHE Daniela Andreea - 311CB*/
#include "hash_table.h"
#include "tlg.h"

int main(int argc, char const *argv[])
{
	char *sursa, *dest;
	int M = atoi(argv[1]);   //numarul de elemente M din vectorul de lsite
	sursa = strdup(argv[2]);  //fisierul de intrare
	dest = strdup(argv[3]);   //fisierul de iesire

	FILE *f1 = fopen(sursa, "r");
	FILE *f2 = fopen(dest, "w");

	TH *h ;
	h = alocaTH(M);

	char *op = calloc(100, sizeof(char*)); //operatia

	while(fscanf(f1, "%s", op) == 1) //citesc cate o operatie pana la finalul fisierului
	{
		char *val = calloc(100, sizeof(char*));
		char *key = calloc(100, sizeof(char*));
		int i;

		if(strcmp(op, "set") == 0)  //verific ce operatie trebuie executata si apelez functia corespunzatoare
		{	fscanf(f1, "%s", key);
			fscanf(f1, "%s", val);
			set(key, val, h);
		}
		else if(strcmp(op, "print") == 0)
		{
			print(h, f2);
		}
		else if(strcmp(op, "print_list") == 0)
		{	
			fscanf(f1, "%d" , &i);
			print_list(i, h, f2);
		}
		else if(strcmp(op, "remove") == 0)
		{
			fscanf(f1, "%s", key);
			Remove(h, key);
		}
		else if(strcmp(op, "get") == 0)
		{
			fscanf(f1, "%s", key);
			if(get(h, key) != NULL)
				fprintf(f2, "%s\n", get(h, key));
			else
				fprintf(f2, "NULL\n");
		}

	free(key);
	free(val);
	}	

	free(op);
	free(sursa);
	free(dest);
	DistrugeHash(&h);
	fclose(f1);
	fclose(f2);

	return 0;
}
