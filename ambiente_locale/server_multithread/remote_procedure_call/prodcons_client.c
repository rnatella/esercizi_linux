#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "prodcons_msg.h"
#include "prodcons_client.h"

static int id_coda_richieste;
static int id_coda_risposte;

void init_client(int id_coda_richieste_parametro, int id_coda_risposte_parametro) {

    id_coda_richieste = id_coda_richieste_parametro;
    id_coda_risposte = id_coda_risposte_parametro;
}

void produci_con_somma(int val1, int val2, int val3) {

    /* TBD: Inviare un messaggio di tipo "PRODUCI CON SOMMA" */

    printf("[Client] Invio richiesta PRODUCI_CON_SOMMA(%d, %d, %d)\n", val1, val2, val3);


    /* TBD: Ricevere un messaggio di risposta */


    int risultato = /* TBD */;
    int errore = /* TBD */;

    printf("[Client] Ricevuto risposta: risultato=%d, errore=%d\n", risultato, errore);
}

void produci(int val) {

    /* TBD: Inviare un messaggio di tipo "PRODUCI" */

    printf("[Client] Invio richiesta PRODUCI(%d)\n", val);


    /* TBD: Ricevere un messaggio di risposta */

    int risultato = /* TBD */
    int errore = /* TBD */

    printf("[Client] Ricevuto risposta: risultato=%d, errore=%d\n", risultato, errore);
}

int consuma() {

    /* TBD: Inviare un messaggio di tipo "CONSUMA" */

    printf("[Client] Invio richiesta CONSUMA(nessun parametro)\n");


    /* TBD: Ricevere un messaggio di risposta */

    int risultato = /* TBD */
    int errore = /* TBD */

    printf("[Client] Ricevuto risposta: risultato=%d, errore=%d\n", risultato, errore);

    return risultato;
}