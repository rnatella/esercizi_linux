#ifndef __PROCEDURE_H
#define __PROCEDURE_H

#include "monitor_signal_continue.h"

#define DIM 3

typedef struct{
	int buffer[DIM];
	Monitor m;
	int testa;
	int coda;
	int count;
}PriorityProdCons;


void inizializza_prod_cons(PriorityProdCons* p);
void produci_alta_prio(PriorityProdCons* p );
void produci_bassa_prio(PriorityProdCons* p);
void consuma(PriorityProdCons* p);
void rimuovi_prod_cons(PriorityProdCons* p);

#endif
