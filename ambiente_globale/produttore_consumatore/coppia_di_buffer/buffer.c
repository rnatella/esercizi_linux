#include "buffer.h"

#include <unistd.h>
#include <stdio.h>

void produzione(int sem_id, buffer *buf1, buffer *buf2, int valore)
{

    Wait_Sem(sem_id, SPAZIO_DISP);

    /* Non è necessario qui acquisire un MUTEX_P
     * per la ricerca di un buffer LIBERO, vi è un
     * solo produttore.
     */

    if (buf1->stato == LIBERO)
    {
        buf1->stato = INUSO;

        printf("[%d] In produzione su buf1...\n", getpid());

        sleep(1);

        buf1->valore = valore;

        buf1->stato = OCCUPATO;

        printf("[%d] Prodotto il valore %d su buf1\n", getpid(), valore);
    }
    else
    {

        /* se il programma è arrivato a questo punto, vi
         * deve essere almeno uno spazio disponibile, e 
         * quello spazio non è in "buf1", per cui "buf2"
         * è necessariamente libero.
         */

        buf2->valore = valore;

        printf("[%d] In produzione su buf2...\n", getpid());

        buf2->stato = INUSO;

        sleep(1);

        buf2->valore = valore;

        buf2->stato = OCCUPATO;

        printf("[%d] Prodotto il valore %d su buf2\n", getpid(), valore);

    }

    Signal_Sem(sem_id, MESSAGGIO_DISP);
}

int consumazione(int sem_id, buffer *buf1, buffer *buf2)
{

    int valore;

    Wait_Sem(sem_id, MESSAGGIO_DISP);

    /* Non è necessario qui acquisire un MUTEX_C
     * per la ricerca di un buffer OCCUPATO, vi è un
     * solo consumatore.
     */

    if (buf1->stato == OCCUPATO)
    {
        buf1->stato = INUSO;

        printf("[%d] In consumazione su buf1...\n", getpid());

        sleep(2);

        valore = buf1->valore;

        buf1->stato = LIBERO;

        printf("[%d] Consumato il valore %d su buf1\n", getpid(), valore);

    }
    else
    {
        /* se il programma è arrivato a questo punto, vi
         * deve essere almeno un messaggio disponibile, e 
         * quel messaggio non è in "buf1", per cui "buf2"
         * è necessariamente occupato.
         */

        buf1->stato = INUSO;

        printf("[%d] In consumazione su buf2...\n", getpid());

        sleep(2);

        valore = buf2->valore;

        buf2->stato = LIBERO;

        printf("[%d] Consumato il valore %d su buf2\n", getpid(), valore);

    }

    Signal_Sem(sem_id, SPAZIO_DISP);

    return valore;
}