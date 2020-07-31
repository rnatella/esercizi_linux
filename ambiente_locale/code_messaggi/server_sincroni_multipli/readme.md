Server sincroni multipli
========================

Si realizzi in linguaggio C/C++ la seguente applicazione di tipo
client-server basata su **code di messaggi UNIX**. L'applicazione dovrà
prevedere **client multipli** e **server multipli**, e adottare la
seguente variante dello schema di **send sincrona**. L'applicazione
dovrà inizialmente creare 2 code, rispettivamente dedicate ai messaggi
di tipo `REQUEST TO SEND` (da client a server) e `OK TO SEND` (da server
a client). Un client deve inizialmente sincronizzarsi con uno dei
server, mandando prima una richiesta `REQUEST TO SEND`, indicando il
proprio PID all'interno del messaggio, e attendendo una risposta
`OK TO SEND` con il proprio PID nel campo "tipo" del messaggio di
risposta.

Ognuno dei server, al proprio avvio, dovrà creare una ulteriore coda di
messaggi (ogni server avrà una propria coda di messaggi). È a
discrezione dello studente la scelta della chiave da utilizzare per
questa coda. Quando un server riceve una `REQUEST TO SEND`, nella sua
risposta `OK TO SEND` dovrà indicare l'ID della propria coda al client,
utilizzando un campo nel messaggio `OK TO SEND`.

Il client, dopo aver ricevuto il messaggio `OK TO SEND` con il proprio
PID, invierà un messaggio al server sulla coda indicata nella
`OK TO SEND`. Il client dovrà inviare un messaggio contenente un valore
intero generato casualmente. Il server dovrà ricevere il messaggio, e
stampare a video il valore intero.

È richiesto che il codice dei client e dei server sia in eseguibili
distinti. Si creino 4 processi client e 2 processi server. Ogni client
dovrà ripetere le operazioni descritte sopra per 2 volte, e ogni server
dovrà ripetere per 4 volte, per poi terminare.

![image](/images/ambiente_locale/code_messaggi/server_sincroni_multipli.png)
