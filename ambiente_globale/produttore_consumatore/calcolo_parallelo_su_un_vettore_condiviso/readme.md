Calcolo parallelo su un vettore condiviso
=========================================

Si realizzi in linguaggio C/C++ un'applicazione **multiprocesso** che
svolga, in parallelo su più processi, la **ricerca del valore minimo**
all'interno di un vettore di grandi dimensioni. Il processo padre dovrà
allocare un vettore di 10.000 valori interi, ed inizializzare il vettore
con valori non negativi da scegliere casualmente. Dopodiché, il processo
padre dovrà creare un gruppo di 10 processi figli, e scambiare con loro
il vettore di interi.

Ciascuno dei processi figli dovrà lavorare su **una porzione distinta
del vettore** creato dal padre. Ad esempio, il primo figlio dovrà
lavorare sui primi 1000 elementi; il secondo figlio sui secondi 1000
elementi; etc.. Ogni figlio dovrà cercare il valore minimo all'interno
dalla porzione di vettore assegnatagli, e trasmettere al padre il valore
minimo trovato. Il processo padre dovrà raccogliere i valori minimi di
ogni figlio, e cercare il valore minimo tra tutti i valori raccolti. Si
stampi a video i valori trasmessi e ricevuti, e il risultato finale
della ricerca. Per comunicare il risultato da un processo figlio al
padre, si utilizzi lo schema **produttore-consumatore con buffer
singolo**, usando una **memoria condivisa e semafori UNIX**.

![image](/images/ambiente_globale/produttore_consumatore/calcolo_parallelo_su_un_vettore_condiviso.png)
