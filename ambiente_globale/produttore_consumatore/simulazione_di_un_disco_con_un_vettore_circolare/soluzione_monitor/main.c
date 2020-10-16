#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "header.h"

int main() {

	int id_shm;


	/*
	  Allocazione di una memoria condivisa per la coda di richieste
	*/

	id_shm = shmget(IPC_PRIVATE, sizeof(MonitorSchedulatore), IPC_CREAT|0664);

	if( id_shm < 0 ) {

		perror("Errore shmget()");
		exit(1);
	}



	/*
	  Inizializzazione di un puntatore alla memoria condivisa
	*/

	MonitorSchedulatore * s = (MonitorSchedulatore *) shmat(id_shm, NULL, 0);

	if( s == (void *)-1 ) {

		perror("Errore shmat()");
		exit(1);
	}



	InizializzaMonitor(s);


	int i;
	pid_t p;

	/*
	  Creazione dei processi figli Utente, ricevono in ingresso
	  un puntatore al monitor
	*/

	for(i=0; i<TOTALE_UTENTI; i++) {

		p = fork();


		if(p == 0) {

			printf("Processo figlio utente in esecuzione (PID %d)\n", getpid());

			Utente(s);
			exit(0);
		}

		if(p < 0) {

			perror("Errore fork() utente");
			exit(1);
		}
	}



	/*
	  Creazione del processo figlio Schedulatore, riceve in ingresso
	  un puntatore al monitor
	*/

	p = fork();

	if(p == 0) {

		printf("Processo figlio schedulatore in esecuzione (PID %d)\n", getpid());

		Schedulatore(s);
		exit(0);
	}

	if(p < 0) {

		perror("Errore fork() schedulatore");
		exit(1);
	}
		


	/*
	  Il processo padre si pone in attesa della terminazione
	  dei processi Utente e del processo Schedulatore
	*/

	for(i=0; i<TOTALE_UTENTI+1; i++) {

		wait(NULL);

		printf("Processo figlio terminato\n");
	}



	/*
	  Deallocazione delle risorse
	*/

	RimuoviMonitor(s);

	int ret = shmctl(id_shm, IPC_RMID, NULL);

	if(ret < 0) {

		perror("Errore shmctl()");
		exit(1);
	}


	return 0;
}
 
