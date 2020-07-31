Pipeline di buffer singoli, con probabilità di modifica
=======================================================

Si realizzi un'applicazione **multiprocesso** di tipo
Produttore-Consumatore, utilizzando semafori e **memoria condivisa
UNIX**. Il programma dovrà creare 3 processi produttori, 1 processo
consumatore, ed un ulteriore processo denominato **iniettore**.

I produttori dovranno produrre all'interno di un buffer singolo, che
dovrà contenere una struttura con due campi: un vettore di caratteri, e
un valore intero. Ciascun produttore dovrà inserire[^1] nel vettore di
caratteri rispettivamente le stringhe "MSG1", "MSG2", "MSG3" (ripetendo
la stessa stringa in tutte le produzioni dello stesso produttore); e
inserire nel campo intero la lunghezza della stringa (in questo caso, il
valore "4" poiché vi sono 4 caratteri). Si effettuino 3 produzioni per
ogni produttore.

Il processo Iniettore dovrà avere il ruolo sia di consumatore sia di
produttore. Ad ogni iterazione (per un totale di 9 iterazioni),
l'Iniettore dovrà consumare dal primo buffer, ed effettuare una
produzione sul secondo buffer. L'Iniettore dovrà decidere, in maniera
casuale[^2], se copiare la struttura dati nel secondo buffer in maniera
intatta (50% di probabilità) oppure corrotta. Nel caso si debba
corrompere la struttura, il processo dovrà aggiungere un valore casuale
al campo intero (30% di probabilità) oppure inserire il carattere '\\0'
in una posizione a piacere della stringa (20% probabilità).

Il consumatore dovrà verificare l'integrità del messaggio, controllando
che la lunghezza della stringa[^3] coincida con il valore intero incluso
nella struttura. In caso affermativo, il processo consumatore dovrà
stampare la struttura su terminale. In caso negativo, dovrà stampare un
messaggio di errore.

![image](/images/ambiente_globale/produttore_consumatore/pipeline_di_buffer_singoli_con_probabilita_di_modifica.png)

[^1]: Utilizzare `strcpy(x.stringa, "MSG1")` oppure
    `strcpy(x.stringa, y.stringa)` (definita in `<string.h>`) per
    scrivere nel vettore di caratteri.

[^2]: Si generi un numero casuale tra 0 e 99 mediante `rand() % 100`, e
    si valuti (con una sequenza di `if`) se il numero ricade
    rispettivamente negli intervalli tra 0-49, tra 50-79, oppure tra
    80-99.

[^3]: Utilizzare la funzione `strlen(x.stringa)` per ottenere la
    lunghezza della stringa.
