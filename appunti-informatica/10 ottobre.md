## I sottoprogrammi e lo stack

scritto com'è nella slide **Quinta versione**, un programma che mostra un messaggio sul display è organizzato in modo abbastanza comprensibile, dove separiamo le istruzioni e il programma vero e proprio. qui dunque il blocco display si occupa di elaborare l'output, mentre la parte prima è il programma, dove potrebbe avvenire qualcos'altr.
tuttavia questo blocco di istruzioni non è riutilizzabile, avendo in mente che con un unico blocco di istruzioni vorremmo riuscire a visualizzare sul display prima una stringa, poi un'altra diversa.
una soluzione può essere introdurre una variabile che, in base al punto di codice in cui ci troviamo, cambia l'istruzione (fondamentalmente, se abbiamo appena letto la prima stringa la variabile fa ritornare al blocco di istruzioni che ne legge un'altra, e dopo aver letto la seconda facciamo jmp fine)
il codice fatto bene è sulla slide **Sesta versione**, dove vediamo che la variabile DisplayReturnAddress è l'indirizzo a cui torna la funzione DisplayFine, che dopo il primo ciclo sarà Return1, che quindi fa ripetere il ciclo Display, e dopo il secondo ciclo sarà Return2, che invece fa finire il programma. questo è possibile perchè dentro Return1 stiamo cambiando la variabile dentro DisplayReturnAddress dall'indirizzo di Return1 a quello di Return2, cambiando il blocco dove il programma salta dopo un determinato ciclo.

un blocco di istruzioni che possa ritornare alla posizione che ha chiamato quel blocco, si chiama **funzione**, anche se storicamente veniva chiamato *sottoprogramma*

la soluzione che abbiamo fatto funziona, ma è di nuovo un programma automodificante, che in genere è troppo semplificato e poco versatile. la sua limitazione principale sono i problemi *ricorsivi* (roba un po' complicata)
per risolvere questi problemi, i microprocessori ci forniscono lo **stack**, che permette di memorizzare più valori uno "in fila" all'altro.
nella pratica, su ade8 abbiamo un registro chiamato **stack pointer** che punta all'ultimo dato inserito sullo stack. questo ci permette poi di estrarre i dati che vogliamo dallo stack pointer, aumentando di 1 lo stack pointer.
inserire qualcosa nello stack si fa con l'istruzione PUSH (80h), mentre per estrarre un dato si usa l'istruzione POP (81h).
dunque con l'istruzione pop riusciamo ad estrarre e caricare sull'accumulatore l'ultimo valore sullo stack. lo stack pointer lavora a partire dalla fine della memoria, quindi per inserire qualcosa decrementiamo di 1 lo stack pointer, e per estrarre qualcosa lo incrementiamo di 1

tutto ciò è legato alle funzioni perchè ade8, così come tutti i processori, mette a disposizione due istruzioni, che nel nostro caso chiamiamo **CALL** (82h) e **RET** (83h). Call pusha nello stack il valore del program counter, che sarà sempre l'indirizzo successivo a dove sto scrivendo Call, mentre Ret prende l'ultimo indirizzo inserito nello stack e lo inserisce nel program counter, saltando a quell'indirizzo.
nella slide **Settima versione** vediamo come possiamo implementarlo nel programma per visualizzare due stringhe: qui la prima call mette nello stack l'istruzione ldv msg2, la ret in DisplayFine permette di ritornare a questa istruzione, la seconda call mette nello stack il jmp Fine e la ret ritorna a jmp Fine, facendo finire il programma.

lo stack può servire per risolvere anche altri problemi: se abbiamo bisogno di dare più parametri a una funzione, possiamo appoggiarli allo stack con un push. per avere accesso a questi parametri, abbiamo poi delle istruzioni specifiche su ade8, ovvero LDs (03h) e STs (13h), che fanno riferimento allo stack (slide **Accesso indiretto allo stack** e successive, fino alla slide **Istruzioni aggiuntive**, oltre cui non serve niente)

per fare esercizi da esame su ade8 utilizza olj, il link è su moodle
puoi anche allenarti sulla rappresentazione di dati

***

esercizio olj a lezione:
tmp: 0aah

***

C (00 15)

***

## Algebra di Boole

nell'algebra di boole abbiamo solo 0 e 1, e ci sono tre operazioni base: la somma logica (OR, +), il prodotto logico (AND, x) e il complemento (o negazione) (NOT, ') (il negato si può esprimere anche con una linea sopra la variabile)
le operazioni funzionano come su ade8, quindi la somma trasforma in 1 se c'è un 1, il prodotto trasforma in 0 se c'è uno 0, il complemento inverte il numero
le operaioni booleane si descrivono con delle tabelle di verità (quelle nella slide **Introduzione**)

essendo che il valore di una variabile può essere solo 0 e 1, sarebbe teoricamente possibile scrivere una qualsiasi funzione in riga, elencando tutte le possibili combinazioni di 0 e 1. alla slide **Variabili, funzioni e espressioni** possiamo vedere un esempio, dove calcoliamo tutte le possibili combinazioni tramite una tabella di verità e poi mettiamo l'elenco come risultato della funzione (l'ordine dei numeri è fondamentale).
f(x, y, z) è una funzione, mentre "xy + z(x + y) + xz" è un'espressione.

ci sono alcuni teoremi (slide **Proprietà e teoremi**), ma sono molto semplici da dimostrare dato che basta mettere tutte le combinazioni possibili di 0 e 1 per dimostrarli. inoltre, per il principio di dualità, il teorema rimane valido se scambio le operazioni e gli 0 e 1 (per esempio, x + 0 = 1 rimane vero se faccio x * 1 = 0)
la seconda **proprietà distributiva** non funziona come nell'algebra normale, è un po' particolare
il **teorema di De Morgan** ci dice che il negato della somma, non è la somma dei negati. ma bensì, il negato della somma è il prodotto dei negati, e il negato del prodotto è la somma dei negati

l'applicazione principale dell'algebra di boole è la costruzioni di reti logiche per i microprocessori

ovviamente, date n variabili ci sono 2^n combinazioni possibili, e dunque le funzioni logiche di n variabili sono 2^(2^n). la funzione logica che ci interessa è f2, ovvero il NOT, per cui viene utilizzato il simbolo mostrato nella slide **Funzioni logiche**. possiamo mettere insieme più simboli per creare degli schemi logici
le funzioni logiche di 2 variabili sono 2^(2^2) ovvero 16, di cui notiamo come f1 e f7 sono AND e OR, mentre la f6 è detta *o esclusivo*, indicata con XOR. ognuna di queste ha il corrispondene negato, indicati con NAND, NOR E XNOR.
ognuna di queste ha un simbolo associato, dove la versione negata è uguale al corrispettivo con un pallino in fondo, ma sono cose che per ora non dobbiamo sapere.
se volessimo sapere che funzione logica corrisponde a un grafico logico, dovrei fare la prova con tutte le combinazioni possibili. nel caso di **Simboli delle funzioni logiche** abbiamo due variabili.

x y | f
0 0 | 0
0 1 | 0
1 0 | 0
1 1 | 0

ogni circuito può essere tradotta in espressione logica, che a sua volta può essere convertita a una delle possibili funzioni logiche. per farlo devo risolvere l'espressione logica, cosa che posso fare utilizzando i teoremi dell'algebra di boole
per ogni funzione logica, esistono infinite espressioni che possono rappresentarla

dovremo saper risolvere esercizi sull'algebra di boole (dove + è l'or e * è l'and)

f(a,b,c) = a'+b(a+c')

f(1,1,0)=1
f(0,1,1)=1
f(0,0,1)=1
f(0,0,0)=1

f(a,b,c) = a(b+c)+a+c'

f(0,0,1) = 0

fanne un po' di questi, vanno capiti bene

posso ragionare in questo modo: se sommo a 1 qualcosa, sicuramente farà 1; e se sto moltiplicando qualcosa per 0, sicuramente farà 0