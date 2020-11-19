#include <sys/types.h>

#define RICHIESTE 5
#define CLIENT 3

typedef struct{
	long pid;
	int v1;
	int v2;
}Buffer_C;

typedef struct{
	long pid;
	int v3;
}Buffer_S;

void client(int id_c, int id_s);
void server(int id_c, int id_s);
void* Prodotto(void*);
