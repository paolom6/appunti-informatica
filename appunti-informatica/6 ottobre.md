## Accesso indiretto

noi fin'ora abbiamo fatto solo acccesso diretto nei nostri programmi, dove ogni dato occupa solo una cella di memoria. in questo modo perdiamo uno degli scopi principali del computer, ovvero la possibilità di elaborare grandi quantità di dati.
per uscire da queste limitazioni ci serve un nuovo modo per accedere alla memoria

mettiamo di voler sommare 10 numeri, che possiamo associare a una n-pla. quello che vogliamo fare è calcolare la sommatoria mostrata nella slide **Lavorare con più dati**. ne facciamo una che risulta 243 potremmo anche rappresentarla a 8 bit senza segno, solo che farlo con le conoscienze che abbiamo ora significherebbe associare a ogni numero una variabile diversa, ognuna che occupa una cella di memoria (slide **Somma di 10 numeri**). questo programma funziona, ma gli manca la flessibilità di avere un numero variabile di elementi.
consideriamo l'istruzione *ADD x1*: questa in linguaggio macchina diventa *40 1d*, ma è facile notare come in realtà il programma stia semplicemente andando al byte successivo ogni volta per prelevare la nuova variabile

nella slide **Somma di N numeri**, la funzione *ldv x* carica sull'accumulatore il numero 24h, ovvero la cella in cui dichiariamo x (in questo caso, è dove si trova il 12). la differenza con *LD x* è che con LD stiamo caricando sull'accumulatore il contenuto della cella 24h, mentre *LDv x* prende l'indirizzo della variabile x e lo carica sull'assemblatore. LDv = LA (load address)
la linea *st Cosa* serve a scrivere il contenuto dell'accumulatore nella cella che corrisponde alla variabile Cosa, quindi di fatto stiamo salvando quello che c'è sull'accumulatore in x
il vero programma comincia nella variabile **Ciclo**, dove sommo il valore di s (che all'inizio è 0) all'indirizzo di memoria di x, che all'inizio fa riferimento a 12, per poi rimetterlo in s. successivamente si incrementa la variabile Cosa, in modo da far passare x all'indirizzo di memoria successivo, che indica il numero successivo da sommare, e si va avanti così fin chè la N non raggiunge zero
abbiamo scritto un programma **automodificante**, che quindi cambia le sue istruzioni nel corso del programma. qui il pezzo di programma che cambia le sue istruzioni è proprio il "ld Cosa | addv 1 | st Cosa" dove sto aumentando di 1 ogni volta l'etichetta Cosa per accedere alle celle successive

in questo caso il programma automodificante è relativamente semplice e funziona, ma con compiti più complessi si può andare incontro a soluzioni molto complesse. al giorno d'oggi gli unici programmi automodificanti sono i malware, che hanno come obiettivo avere il codice più incomprensibile possibile.
noi abbiamo fatto un programma automodificante per accedere in memoria a più indirizzi diversi con una sola istruzione
quindi quello che a noi serve veramente è un modo di accedere ad un indirizzo di memoria che può cambiare, ovvero ci servono delle variabili che contengono indirizzi.
queste variabili che contengono indirizzi sono chiamate **puntatori**

per ottenere il programma fatto prima senza modificare delle istruzioni, dobbiamo introdurre nuove istruzioni che ci permettano un accesso indiretto alla memoria.
abbiamo per l'ade8 le seguenti istruzioni:
LDi (02h): va in memoria a prendere un numero all'indirizzo *param*, che utilizza per andare di nuovo in memoria all'indirizzo del primo numero
STi (12h): la stessa cosa ma, invece di leggere il dato, lo salva

mettiamo di avere le seguenti celle di memoria 
|3C| alla cella 39
|7| alla cella 3a
|3a| alla cella 3b
|17| alla cella 3c

le seguenti istruzioni caricano tutte sull'accumulatore qualcosa di diverso:
- LDv 39h -> ACC: 39h
- LD 39h -> ACC: 3ch
- LDi 39h -> ACC: 17h
in LDv la memoria non ha nessun utilizzo; in LD si va in memoria alla cella 39h e si carica il contenuto (3ch) nell'accumulatore; in LDi uso la variabile all'indirizzo 39h, quindi 3ch, come **puntatore** per la cella 3ch, che contiene 17h che quindi viene caricato sull'accumulatore.
quindi qui 3ch è il puntatore che stiamo utilizzando

usando queste nuove istruzioni, possiamo riscrivere il programma come scritto nella slide **Accesso indiretto alla memoria**. qui la variabile P è il puntatore. si può notare che ora il programma è decisamente più leggibile e comprensibile a livello logico.
all'inizio P punta all'indirizzo di 12, quindi 21h, e il programma continua aumentando di 1 ogni volta l'indirizzo a cui P sta puntando.
allo stesso tempo, stiamo sommando alla cella puntata da P la variabile S, per poi salvarla in S stesso. 
in questo modo sommiamo al numero puntato da P ogni volta la somma dei numeri passati fino a un determinato momento, e alla fine S sarà la somma di tutti i numeri.

slide **Altri esercizi**, fai il calcolo del massimo, del minimo, pari e positivi.


## Input e output

in ade8, il processore ignora i dispositivi a cui è collegato, e l'unica cosa che fa è avere una comunicazione con l'esterno con cui butta fuori indirizzi e dati tramite 8 fili, che contengono gli 8 bit che possono uscire o entrare dalla memoria.
se invece di collegare a questi 8 fili la memoria colleghiamo qualcos'altro, ade8 non cambia comportamento, in quanto si aspetta sempre che i dati che sta spedendo vengano scritti su una memoria.
quindi se invece di collegare la memoria ci collego altre cose, quei bit finiranno su altri dispositivi

questo metodo viene detto **memory mapped input output**. su ade8 si è deciso che gli indirizzi che cominciano con D, quindi se il numero che stiamo utilizzando ha come 4 bit più significativi 1101, allora la memoria li ignora e vanno a interagire con altri dispotivi
quindi di fatto la memoria di ade8 non è a 8 bit, ma tutti gli indirizzi che partono con D non vanno a finire in memoria.

se i primi 4 bit sono 1101 so già che sto interagendo con un dispositivo esterno, mentre gli altri 4 bit vengono detti **porta di input/output**. 
alla porta 0 è collegato un doppio display a 7 segmenti (tipo le sveglie digitali) che visualizza in esadecimale il valore scritto. quindi se scrivo all'indirizzo d0 il numero 7, lo vedrò mostrato sul display a 7 segmenti
se volessi vedere sul display il numero 75h, basterebbe scrivere:
LDv 75h -> metto 75 nell'accumulatore
ST 0d0h -> scrivo 75 nella porta 0 dei dispositivi input/output, ovvero il display a 7 segmenti

alla porta 1 è collegato un display a caratteri, che mostra le lettere leggendo il codice ascii in esadecimale (a 7 bit) che gli passiamo
LDv 61h -> metto 61h (che è 96, l'ascii della a minuscola) nell'accumulatore
ST 0d1h -> scrivo 61h nella porta 1 dei dispositivi i/o, ovvero scrivo la a minuscola nel display a caratteri

alla porta 2 sono collegati 8 interruttori che possono valere 0 o 1, permettendoci di comporre numeri a 8 bit. questo è un dispositivo di input, che permette al processore di leggere un numero inserito dall'utente.
se accendessi gli interruttori in modo da scrivere 0110.1101 e scrivessi LD d2h, sull'accumulatore troverei 6dh

quando sto usando gli esadecimali per riferirmi a un indirizzo che comincia con d, o con qualsiasi lettera, devo metterci prima lo zero, per far capire all'assemblatore che non è un etichetta, per esempio: 
ldv 48h
st 0d1h
con cui sto scrivendo l'ascii di 48h sul display a caratteri

naturalmente è molto scomodo mettere ogni volta l'esadecimale dell'ascii di una lettera, quindi su ade8 possiamo mettere quello che vogliamo scrivere tra apici '' e il processore lo tradurrà in automatico nel suo esadecimale in ascii, per esempio:
ldv 'h'
st 0d1h

vediamo però alla slide **Seconda versione** che stiamo rifacendo la stessa cosa praticamente uguale diverse volte, cosa che possiamo sistemare con l'accesso indiretto, spiegato nella slide **Terza versione**

l'assemblatore può anche convertire in byte singoli se scriviamo "Hello world!" invece di scrivere le singole lettere, ma vorremmo anche non dover dichiarare ogni volta in anticipo il numero di lettere che stiamo per usare. 
per evitare questo problema possiamo usare il codice ascii 0 (non il simbolo 0, che ha come codice ascii 30h) che non corrisponde a nessun simbolo. in questo modo possiamo vedere nella slide **Quarta versione** come scrivere un programma tutto sommato semplice e comprensibile, grazie all'utilizzo dei puntatori.

RICORDATI DI FARE GLI ESERCIZI SULL'ACCESSO INDIRETTO