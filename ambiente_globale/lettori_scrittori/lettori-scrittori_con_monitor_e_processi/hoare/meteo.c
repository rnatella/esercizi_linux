#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

int main(){


	key_t id_meteo = shmget(IPC_PRIVATE,sizeof(MonitorMeteo),IPC_CREAT|0664);
	MonitorMeteo * p = (MonitorMeteo *) (shmat(id_meteo,0,0));

	init_monitor(&(p->m), NUM_CONDITIONS);

	p->numlettori = 0;
	p->numscrittori = 0;

	pid_t pid;

	int k;
	for (k=0; k<NUM_UTENTI; k++) {

		pid=fork();
		if (pid==0) {
			Utente(p);
			exit(0);
     	} else if(pid<0) {
			perror("fork");
		}
	}


	pid=fork();
	if (pid==0) {
		Servizio(p);
		exit(0);
	} else if(pid<0) {
		perror("fork");
	}


	int status;
	for (k=0; k<NUM_UTENTI+1; k++) {
		pid=wait(&status);
		if (pid==-1)
			perror("errore");
	}

	remove_monitor(&(p->m));

	shmctl(id_meteo,IPC_RMID,0);

	return 0;
}
