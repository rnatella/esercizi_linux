#include "stack.h"

#include <stdlib.h>

void StackInit(Stack * s, int dim) {
	pthread_mutex_init( &(s->m), NULL );
	pthread_cond_init( &(s->ok_push), NULL );
	pthread_cond_init( &(s->ok_pop), NULL );

	s->dati = (Elem *) malloc(sizeof(Elem)*dim);

	s->dim = dim;
	s->testa = 0;
}


void StackRemove(Stack * s) {
	pthread_mutex_destroy( &(s->m) );
	pthread_cond_destroy( &(s->ok_push) );
	pthread_cond_destroy( &(s->ok_pop) );

	free(s->dati);
}

void StackPush(Stack * s, Elem e) {
	pthread_mutex_lock( &(s->m) );

	while( s->dim==s->testa )
		pthread_cond_wait( &(s->ok_push), &(s->m) );
	
	s->dati[s->testa] = e;
	s->testa++;

	pthread_cond_signal( &(s->ok_pop) );

	pthread_mutex_unlock( &(s->m) );
}


Elem StackPop(Stack * s) {

	int elemento;

	pthread_mutex_lock( &(s->m) );


	while( s->testa==0 )
		pthread_cond_wait( &(s->ok_pop), &(s->m) );

	s->testa--;	
	elemento=s->dati[s->testa];

	pthread_cond_signal( &(s->ok_push) );

	pthread_mutex_unlock( &(s->m) );

	return elemento;
}

int StackSize(Stack * s) {
	int size;

	pthread_mutex_lock( &(s->m) );

	size = s->testa;

	pthread_mutex_unlock( &(s->m) );

	return size;
}
