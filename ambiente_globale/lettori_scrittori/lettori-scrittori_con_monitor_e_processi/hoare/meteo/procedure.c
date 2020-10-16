#include <stdio.h>
#include "header.h"

void InizioLettura(Monitor* m, Buffer * buf){
	enter_monitor(m);
        
	if (buf->occupato && buf->numlettori==0) //se ci sono già scrittori, si deve bloccare
		wait_condition(m,SYNCHL);
	buf->occupato = 1;
	buf->numlettori=buf->numlettori+1;
	
	signal_condition(m,SYNCHL); // sblocco di eventuali altri lettori, 
				    // se la segnalazione non è fatta per 
				    // tutti dallo scrittore che rilascia

	leave_monitor(m);
}

void FineLettura(Monitor* m, Buffer * buf) {
	enter_monitor(m);

	buf->numlettori=buf->numlettori-1;
	if (buf->numlettori==0) {// se sono finiti i lettori lo segnala agli scrittori
     		buf->occupato=0;
		signal_condition(m,SYNCHS);
	}

	leave_monitor(m);
}



//Procedure di inizio e fine scrittura

void InizioScrittura(Monitor* m,Buffer*buf){
	enter_monitor(m);
	if (buf->occupato) //se ci sono già lettori o scrittori, si deve bloccare     	
		wait_condition(m,SYNCHS);
	buf->occupato = 1;
	leave_monitor(m);
}

void FineScrittura(Monitor* m, Buffer*buf){
	enter_monitor(m);

	if (queue_condition(m,SYNCHS)>0) { // sblocco di eventuali altri scrittori
		signal_condition(m,SYNCHS);
        } else if (queue_condition(m,SYNCHL)>0) { // sblocco di eventuali altri lettori
		signal_condition(m,SYNCHL);
	} else {
		buf->occupato = 0;
	}

	leave_monitor(m);
}



void Servizio(Monitor* m, Buffer * buf){

	srand(time(0));

	int i;
	for(i=0; i<20; i++) {

		InizioScrittura(m,buf);

		buf->meteo.temperatura = (rand()%101)-50;
		buf->meteo.umidita = rand()%101;
		buf->meteo.pioggia = rand()%2;

		printf("<%d> scrittura: Temperatura=%d, Umidità=%d, Pioggia=%s\n", getpid(), buf->meteo.temperatura, buf->meteo.umidita, (buf->meteo.pioggia ? "si" : "no") );

		FineScrittura(m,buf);

		sleep(2);
	}

}

void Utente(Monitor* m, Buffer * buf) {

	int i;
	for(i=0; i<10; i++) {
		
		InizioLettura(m,buf);

		printf("<%d> lettura: Temperatura=%d, Umidità=%d, Pioggia=%s\n", getpid(), buf->meteo.temperatura, buf->meteo.umidita, (buf->meteo.pioggia ? "si" : "no") );

		FineLettura(m,buf);

		sleep(1);
	}

}


