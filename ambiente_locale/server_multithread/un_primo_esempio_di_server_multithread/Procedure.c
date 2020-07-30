#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

#include "Header.h"


extern int id_c,id_s;

void client(){

	int k;
	int ret;

	srand(getpid());

	Buffer_S BS;
	Buffer_C BC;

	BC.pid=getpid();
	BC.v1=rand()%101;
	BC.v2=rand()%101;

	for(k=0;k<RICHIESTE;k++){

		printf("Richiesta %d Inviata (%d, %d) [PID=%ld]\n\n", k, BC.v1, BC.v2, BC.pid);

		ret = msgsnd(id_c, &BC, sizeof(Buffer_C)-sizeof(long), 0);

		if(ret < 0) {
			perror("Errore invio richiesta client");
			exit(1);
		}



		ret = msgrcv(id_s, &BS, sizeof(Buffer_S)-sizeof(long), getpid(), 0);

		if(ret < 0) {
			perror("Errore ricezione risposta client");
			exit(1);
		}

		printf("Risposta %d Ricevuta (%d) [PID=%ld]\n\n", k, BS.v3, BC.pid);
	}

}


pthread_mutex_t mutex;

void server(){

	int k;
	int ret;

	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_mutex_init(&mutex,NULL);

	while(1){

		/**********

		ATTENZIONE: è errato in questo contesto allocare
		la struttura dati del messaggio sullo stack
		(ossia come variabile automatica), poiché lo spazio
		dello stack è privato per il thread e non deve
		essere condiviso con altri thread.

		Esempio di CODICE ERRATO:

		Buffer_C BC;
		...
		msgrcv(id_c, &BC, sizeof(Buffer_C)-sizeof(long), 0, 0);

		**********/

		Buffer_C * BC = (Buffer_C*) malloc(sizeof(Buffer_C));

		BC->v1=0;
		BC->v2=0;
		BC->pid=0;
	
		ret = msgrcv(id_c, BC, sizeof(Buffer_C)-sizeof(long), 0, 0);

		if(ret < 0) {
			perror("Errore ricezione richiesta server");
			exit(1);
		}

		if(BC->v1==-1 && BC->v2==-1){
			exit(0);
		}

		pthread_t t;
		pthread_create(&t, &attr, Prodotto, (void*) BC);

	}

}



void* Prodotto(void* v){

	int ret;

	Buffer_C* BC=(Buffer_C*) v;

	Buffer_S BS;

	BS.pid=BC->pid;
	BS.v3=BC->v1*BC->v2;

	pthread_mutex_lock(&mutex);  

		printf("\nSono Prodotto di Server. Invio del calcolo: %d\n\n",BS.v3);  

		ret = msgsnd(id_s, &BS, sizeof(Buffer_S)-sizeof(long), 0);

		if(ret < 0) {
			perror("Errore invio risposta server");
			exit(1);
		}

	pthread_mutex_unlock(&mutex);

	free(BC);

	pthread_exit(NULL);
}

