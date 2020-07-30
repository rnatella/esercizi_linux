#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "Header.h"


int id_c,id_s,i;


int main(){

	pid_t pidc, pids;
	int ret;


	id_c=msgget(IPC_PRIVATE, IPC_CREAT|0664);

	if(id_c < 0) {
		perror("Errore allocazione coda");
		exit(1);
	}

	id_s=msgget(IPC_PRIVATE, IPC_CREAT|0664);

	if(id_s < 0) {
		perror("Errore allocazione coda");
		exit(1);
	}



	for(i=0;i<CLIENT;i++){

		pidc=fork();

		if(pidc<0) {
			perror("Errore fork client");
			exit(1);
		}

		if(pidc==0){
			client();
			exit(0);
		}
	}


	pids=fork();

	if(pids<0) {
		perror("Errore fork server");
		exit(1);
	}

	if(pids==0){
		server();
		exit(0);
	}


	for(i=0;i<CLIENT;i++) {
		wait(0);
	}


	Buffer_C uscita;
	uscita.v1=-1;
	uscita.v2=-1;
	uscita.pid=getpid();

	ret = msgsnd(id_c,&uscita,sizeof(Buffer_C)-sizeof(long),0);
	if(ret < 0) {
		perror("Errore invio messaggio di terminazione");
		exit(1);
	}

	wait(0);

	msgctl(id_c,0,IPC_RMID);
	msgctl(id_s,0,IPC_RMID);

	return 0;

}

