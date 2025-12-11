## L'elaboratore elettronico

il computer è una macchina che prende un input, fatto da dati e istruzioni, e produce un output in base alle informazioni ricevute.
il calcolatore nasce durante la seconda guerra mondiale, quando alan turing costruisce una macchina per decifrare i messaggi tedeschi. tuttavia, questa macchina era fatta per svolgere un solo compito a ripetizione
i calcolatori con programma cablato potevano comportarsi diversamente in base alle connessioni fatte con dei cavi, che avvenne per la prima volta sul calcolatore ENIAC, che tuttavia era molto faticoso riprogrammare.
più avanti si arrivò al programma memorizzato, di cui è esempio l'architettura di Von Neumann, formata da **memoria, CPU e input/output**. i dispositivi di input e output sono esterni al calcolatore, in quanto il processore da solo non può fare niente. la memoria si può vedere come una lunga serie di scatole numerate, dove ogni scatola (o cella) contiene un byte. se un dato occupa più di 8 bit, ovviamente si può estendere su più celle. il compito della memoria è contenere dati e fornirli al processore. si scrive sulla memoria sempre 8 bit alla volta, non possiamo modificare "parte" di una cella, quindi cambiare solo qualche bit.

## ADE8 (architettura ad esempio a 8 bit)

ADE8 è una CPU (ignoriamo come sia fatta) che ha alcune memorie interne, come tutti i processori, che sono ultra veloci e si chiamano *registri*. l'ADE8 ne ha 4: l'accumulatore (ACC) a 8 bit, il program counter (PC) a 8 bit, lo stack pointer (SP) a 8 bit, il flag (FLAG) a 4 bit.

l'**accumulatore** è il registro che partecipa a tutte le operazioni matematiche e logiche
il **program counter** è il registro che contiene l'indirizzo in memoria (quindi il numero della cella) dove è presente la prossima istruzione da eseguire
lo **stack pointer** è il registro che serve a gestire la memoria in modalità "pila" (per ora lo ignoriamo)
il **flag** è il registro che mantiene lo stato attuale del processore, ovvero delle informazioni che descrivono il risultato dell'ultima operazione

ci sono 4 flag possibili, che sono 1 bit ciascuno: 
0=zero
1=negative
2=overflow
3=carry

se il flag zero vale 1, significa che l'ultima operazione ha prodotto un risultato uguale a zero
se il flag negative vale 1, significa che l'operazione ha prodotto un risultato negativo
se il flag overflow vale 1, significa che l'operazione ha prodotto un overflow, quindi il risultato è andato oltre il 127 o sotto il -128 (per esempio, se faccio 127+1 risulta -128, e il flag overflow varrà 1)
se il flag carry vale 1, che si usa solo per le operazioni senza segno, significa che l'operazione ha prodotto un riporto sul bit più significativo

tutti i processori ricevono dei numeri binari per sapere cosa fare, ovvero delle istruzioni: ADE8 ha 52 istruzioni, di cui alcune hanno bisogno di altre informazioni oltre alla semplice istruzione, quindi hanno bisogno di parametri. per esempio, chiedere di fare l'opposto dell'accumulatore è un'istruzione singola, ma se volessi sommarlo a qualcos'altro bisogna introdurre un parametro.

le istruzioni sono composte da due numeri a 8 bit, quindi 16 bit in totale (dimensione fissa per tutte le istruzioni): il primo dei due byte è il codice operativo (opcode), che quindi ci dice cosa fare; il secondo può essere o un valore o un indirizzo di memoria
ogni opcode dice anche al computer se sia necessario o meno, quindi se usiamo un opcode che non richiede parametri, il byte dei parametri diventa inutile
dentro la memoria non è possibile distinguere un byte di istruzione da un byte che contiene dati normali; solo il processore decide cosa usare
essendo il pc a 8 bit è possibile usare solo 256 byte

il processora funziona continuamente, non si ferma mai finchè il computer è acceso: fa una serie di operazioni definite 
nella slide **il ciclo delle istruzioni di ADE8** ci sono tutte le fasi di ADE8, ma che fondamentalmente esegue ogni tipo di processore.

al momento del reset (quindi all'accensione) del processore, ADE8 azzera tutti i registri (quindi ACC, PC SP E FLAG). quindi sappiamo che, all'accensione del processore, esso inizia sempre a caricare i due byte presenti agli indirizzi 0 e 1

le istruzioni hanno codici numerici e ognuna ha un significato (usiamo il suffisso h per indicare che sono in esadecimale)
per descriverle usiamo una notazione compatta e comprensibile, ad esempio:
- istruzione 70h: ACC <- -ACC ; dove "<-" significa *assume il valore*, e il segno meno ha il suo normale significato matematico
- istruzione 01h: ACC <- param
- istruzione 00h: ACC <- mem[param] ; dove "mem[]" indica il contenuto della cella di memoria all'indirizzo indicato tra parentesi quadre

### codici mnemonici

nella slide **Mnemonici** ci sono tutte le istruzioni, raggruppate in questo modo:
- i gruppi 1 e 2 hanno istruzioni semplici
- il gruppo 3 ha istruzioni con accesso indiretto alla memoria
- il gruppo 4 a istruzioni con utilizzo dello stack

nella slide **Le istruzioni dell'ADE8** sono descritte le istruzioni principali, con il nome e il codice corrispettivo in esadecimale (non le riscrivo, guardale sulle slide)

l'operazione **not** di un bit serve a invertire il bit (quindi not di 0 diventa 1)
ACC = 1001.0110
not ACC = 0110.1001

l'operazione **and** corrisponde alla moltiplicazione bit per bit, per esempio:
ACC = 1001.0110
ACC and 0111.0110 = 0001.0110
sostanzialmente moltiplico in colonna, dove tutto da 0 a parte 1x1, quindi lo scopo dell'and è azzerare alcuni bit.

l'operazione **or** è una specie di addizione (somma logica), dove quindi 0+0 fa 0, 0+1 fa 1 e 1+1 fa 1, per esempio:
ACC = 1001.0110
ACC or 0111.0110 = 1111.0110
questa sostanzialmente serve a mettere a 1 dei bit

not non ha bisogno di parametri, mentre and e or si

si può notare come nelle operazioni con la v finale (tipo ADDv) utilizzano dei parametri che non sono in memoria, mentre quelle senza la v (tipo ADD) utilizzano parametri prelevandoli da una cella di memoria

le istruzioni che permettono di cambiare il program counter si chiamano **salti**, e il salto incondizionato ci permette di eseguire un'istruzione dal numero che vogliamo noi. le istruzioni per le selezioni sono dei **salti condizionati**, che fanno il salto se il flag corrispondente vale 1: questo ci permette di passare a un'altra istruzione solo se l'operazione precedente ci ha dato un determinato risultato

noi useremo due salti in particolare: *jump if equal* (JE) che ci permette di saltare a un'istruzione se l'ultima operazione è un confronto dove i due elementi erano uguali; *jump if lower* (JLs e JLu), in cui il JLs serve per i numeri con segno e il JLu serve per quelli senza segno.

proviamo a fare una semplice calcolatrice a 8 bit che fa somma e differenza.
mettiamo due numeri in memoria all'indirizzo 08h e 09h, dove mettiamo i valori 23 (17h) e 48 (30h), vogliamo fare un programma che esegua la somma e metta il risultato 71 (47h) all'indirizzo 0Ah.

mem[0Ah] <- mem[08h] + mem[09h]

ACC <- mem[08h] ovvero                      LD 08h
ACC <- ACC + mem[09h] ovvero        ADD 09h
mem [0Ah] <- ACC ovvero                    STORE 0Ah

scritto tutto in memoria diventa 00 (che sarebbe la LD) 08 40 (ADD) 09 10 (STORE) 0A
appena acceso il processore, esso legge il program counter che è 00, quindi va a leggere l'istruzione all'indirizzo di memoria 00, dove legge l'istruzione 00 (LD). poi viene incrementato il program counter, e il processore va a prendere l'istruzione all'indirizzo 01, dove legge il parametro 08; andando avanti, al program counter = 02 si va all'istruzione 40 (ADD), dove inizia la fase di esecuzione, che quindi fa la prima operazione. durante tutte le operazioni, i numeri associati a opcode e param permettono di fare le operazioni.
questo va avanti anche per le successive istruzioni fino ad arrivare al program counter 06, a seguito di cui il processore però non sa cosa fare, perchè le due celle successive sono vuote.
per questo motivo usiamo dei **jump**, quindi aggiungiamo 90 e 06 alle celle 06 e 07 che facciano "loopare" il programma tra queste due celle all'infinito, dato che il processore non può mai fermarsi.

così abbiamo scritto un programma in linguaggio macchina, e ogni processore ha il suo linguaggio macchina. in questo caso abbiamo scritto un programma nel linguaggio macchina di ade8

tuttavia non si programma praticamente mai in linguaggio macchina, ma si utilizza l'**assemblatore**, dove non c'è bisogno di cambiare ogni volta l'indirizzo delle celle a cui si sta facendo riferimento e non serve dare il codice delle operazioni, ma si possono utilizzare gli mnemonici

guarda tutte le slide **Da assembly a linguaggio macchina**