#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "prodcons_msg.h"
#include "prodcons_server.h"

#define TOTALE_WORKER 3
#define RICHIESTE_PER_WORKER 2

void * worker(void *);

struct param {

    int id_coda_richieste;
    int id_coda_risposte;
};

int main() {

    key_t chiave_coda_richieste = /* TBD: Scegliere una chiave per la coda richieste */

    int id_coda_richieste = /* TBD: Creare la coda richieste */



    key_t chiave_coda_risposte = /* TBD: Scegliere una chiave per la coda risposte */

    int id_coda_risposte = /* TBD: Creare la coda risposte */



    init_monitor();




    for(int i=0; i<TOTALE_WORKER; i++) {

        /* TBD: Creare il gruppo di thread "Worker", 
                facendogli eseguire la funzione worker(),
                e passandogli gli id delle code in ingresso
                usando "struct param" (definita sopra).
         */
    }


    for(int i=0; i<TOTALE_WORKER; i++) {

        /* TBD: Attendere la terminazione dei thread Worker */
    }

    remove_monitor();

    return 0;
}


void * worker(void * x) {

    int id_coda_richieste = /* TBD: Prendere in ingresso lo ID della coda richieste */
    int id_coda_risposte = /* TBD: Prendere in ingresso lo ID della coda risposte */

    int ret;
    int risultato;
    int errore;

    printf("[Worker] In attesa di richieste...\n");


    for(int i=0; i<RICHIESTE_PER_WORKER; i++) {

        /* TBD: Ricevere un messaggio di richiesta RPC */

        
        if( /* TBD: Il tipo di richiesta è "PRODUCI CON SOMMA" */) {

            int val1 = /* TBD */
            int val2 = /* TBD */
            int val3 = /* TBD */

            printf("[Worker] Ricevuta richiesta di tipo PRODUCI CON SOMMA(%d, %d, %d)\n", val1, val2, val3);

            produci_con_somma(val1, val2, val3);

            risultato = 0;
            errore = 0;

        }
        else if(/* TBD: Il tipo di richiesta è "PRODUCI" */) {

            int val1 = /* TBD */

            printf("[Worker] Ricevuta richiesta di tipo PRODUCI(%d)\n", val1);

            produci(val1);

            risultato = 0;
            errore = 0;
        }
        else if(/* TBD: Il tipo di richiesta è "CONSUMA" */) {

            printf("[Worker] Ricevuta richiesta di tipo CONSUMA(nessun parametro)\n");

            risultato = consuma();
            errore = 0;
        }
        else {

            printf("[Worker] Errore, tipo di richiesta sconosciuta");

            risultato = -1;
            errore = 1;
        }

        /* TBD: Inviare un messaggio di risposta RPC,
                in cui inserire "risultato" ed "errore"
         */


        printf("[Worker] Inviato risposta: risultato=%d, errore=%d\n", risultato, errore);

    }




    printf("[Worker] Terminazione\n");

    return NULL;
}
