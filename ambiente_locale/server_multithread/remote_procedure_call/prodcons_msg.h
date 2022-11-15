#ifndef PRODCONS_MSG
#define PRODCONS_MSG

typedef struct {
    
    /* TBD: Definire il messaggio di richiesta.
            Il messaggio può contenere fino al massimo
            3 parametri di ingresso.
     */

} richiesta_rpc;

typedef struct {

    /* TBD: Definire il messaggio di risposta. */

} risposta_rpc;

void produci_con_somma(int val1, int val2, int val3);
void produci(int val);
int consuma();

/* TBD: Definire con delle macro i valori del tipo di messaggio */

/* Nota: nei messaggi di risposta, usare come valore di "type" il PID del client */

#endif