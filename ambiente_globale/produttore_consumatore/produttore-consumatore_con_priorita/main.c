
#include "monitor.h"
#include "procedure.h"
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main(int argc,char* argv[])
{
	
	
	int num_produttori_1,num_produttori_2,num_consumatori;
	int status,indice;
	PriorityProdCons* p = NULL;
	int id_prod_cons;
	pid_t pid;

    num_produttori_1= 1;
	num_produttori_2 = 3;
	num_consumatori = 1;

	
    
    //richiesta del buffer

	id_prod_cons=shmget(IPC_PRIVATE, sizeof(PriorityProdCons),IPC_CREAT|0664);
	printf("[DEBUG] - id_monitor=%d \n",id_prod_cons);
    
	p =(PriorityProdCons *) (shmat(id_prod_cons,0,0));
	
    inizializza_prod_cons(p);

    
	srand(time(NULL));
	
    int num_produzioni_1 = 3;
	int num_produzioni_2 = 3;
	int num_consumazioni = 12;
	
	int num_processi = num_produttori_1+num_produttori_2+ num_consumatori;
    
	// generazione produttori e consumatori
	int i,k;
	for (k=0;k<num_produttori_1;k++) {
		pid=fork();
		if (pid==0)  {                //processo figlio
			printf("sono il produttore 1. Il mio pid %d \n",getpid());
			i = 0;
			while(i < num_produzioni_1){
				produci_alta_prio(p);
				sleep(4);
				i++;
			}
			_exit(0);
		}
	}

	for (k=0;k<num_produttori_2;k++) {
		pid=fork();
		if (pid==0)  {  
	                //processo figlio
			i = 0;
			printf("sono il produttore 2. Il mio pid %d \n",getpid());

			while(i < num_produzioni_2){
				produci_bassa_prio(p);
				sleep(2);
				i++;
			}
			_exit(0);
		}
	}

	for (k=0;k<num_consumatori;k++) {

		pid=fork();
		if (pid==0)  {                //processo figlio
			printf("sono il consumatore. Il mio pid %d \n",getpid());
			i = 0;
			while(i < num_consumazioni){
				sleep(1);
				consuma(p);
				i++;
			}
			_exit(0);
		}
	}

	for (k=0; k<num_processi;k++){

		pid=wait(&status);
		if (pid==-1)
			 perror("errore");
		else
			 printf ("Figlio n.ro %d e\' morto con status= %d \n ",pid,status);
		}

	printf("Processo padre terminato...\n");
	// rimozione memoria condivisa e semafori
	rimuovi_prod_cons(p);
	shmctl(id_prod_cons,IPC_RMID,0);
	return 1;
}
