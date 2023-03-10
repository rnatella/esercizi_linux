#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#include "registro.h"

void client(int id_coda_registro_richieste, int id_coda_registro_risposte) {

    printf("Client: Avvio...\n");

    srand(getpid());


    int ret;
    int id_server = rand() % 2;
    int id_coda_server;


    messaggio_registro msg_reg;
    msg_reg.tipo = QUERY;
    msg_reg.id_server = id_server;

    printf("Client: Invio messaggio QUERY (id_server=%d)\n", id_server);

    ret = msgsnd(id_coda_registro_richieste, &msg_reg, sizeof(messaggio_registro) - sizeof(long), 0);

    if(ret < 0) {
        perror("Client: Errore msgsnd");
        exit(1);
    }

    printf("Client: Attesa messaggio RESULT...\n");

    messaggio_registro msg_risp;

    ret = msgrcv(id_coda_registro_risposte, &msg_risp, sizeof(messaggio_registro) - sizeof(long), 0, 0);

    if(ret < 0) {
        perror("Client: Errore msgrcv");
        exit(1);
    }

    printf("Client: Ricevuto messaggio RESULT (id_coda=%d)\n", msg_risp.id_coda);

    id_coda_server = msg_risp.id_coda;


    for(int i = 0; i<3; i++) {

        messaggio_server msg_srv;

        msg_srv.tipo = SERVICE;
        msg_srv.valore = rand() % 11;

        printf("Client: Invio messaggio SERVICE (id_server=%d, id_coda=%d, valore=%d)\n", id_server, id_coda_server, msg_srv.valore);

        ret = msgsnd(id_coda_server, &msg_srv, sizeof(messaggio_server) - sizeof(long), 0);

        if(ret < 0) {
            perror("Client: Errore msgsnd");
            exit(1);
        }

        sleep(1);
    }

    printf("Client: Uscita\n");
}
