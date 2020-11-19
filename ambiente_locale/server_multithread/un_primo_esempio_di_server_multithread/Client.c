#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

#include "Header.h"

void client(int id_c, int id_s){

	int k;
	int ret;

	srand(getpid());

	Buffer_S BS;
	Buffer_C BC;

	BC.pid = getpid();
	BC.v1 = rand()%101;
	BC.v2 = rand()%101;

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

