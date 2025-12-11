le funzioni in C possono anche non restituire nulla, e si dichiarano con il tipo **void**. allo stesso modo, possiamo dire che una funzione non usa dei parametri mettendo void dentro le parentesi tonde.

i nostri programmi C saranno sempre ospitati (hosted) da un altro programma (il sistema operativo), e per far capire al sistema operativo quale funzione eseguire per prima la si chiama **main**, che deve sempre ritornare int e non accettare parametri. quindi tutti i programmi devono avere una funzione main

non si possono definire funzioni dentro altre funzioni, un programma è una semplice lista di funzioni

i comandi si chiamano *statement*, e il più importante è il **return**, che con la sintassi 
```
return <espressione>;
```
può terminare la funzione (come il RET in ade8) in cui si trova oppure restituire un valore.

il programma più semplice che possiamo fare, che non fa nulla, è questo:
```
int main(void)
{
	return 0
}
```
il return 0 è un valore classico per dire che il programma è terminato correttamente

un altro comando molto importante è l'**expression statement**, che prevede scrivere un'espressione e poi mettere un punto e virgola. quindi sto dicendo al programma di valutare ciò che c'è scritto nell'espressione, per poi "buttare via" il valore. sintatticamente questa espressione potrebbe essere qualsiasi cosa, anche un semplice numero, però ovviamente il comando ha senso nel momento in cui l'espressione produce un risultato, tramite degli **operatori**

l'operatore principale è l'assegnamento (=), che permette di memorizzare qualcosa in una cella di memoria, con la forma più generale scritta 
```
<lvalue> = <rvalue>
```
rvalue e lvalue sono due espressioni: a destra dell'uguale devo per forza mettere qualcosa con un valore (quindi, per esempio, non potrei mettere una funzione di tipo void), mentre a sinistra devo mettere delle espressioni che hanno un indirizzo di memoria (quindi dovrei averle definite prima)

ecco ora un programma in C un po' più elaborato:
```
char x;
char y;
char z;
int main(void) {
	x = 3;
	y = x;
	z = 0xf5;
	x = z;
	return 0;
}
```
all'inizio ho 3 definizioni di variabili, poi ho una definizione di una funzione, poi ho un expression statement "x=3;" dove x è un lvalue e 3 è un rvalue, e la funzione finisce con un return statement.
essendo z di tipo char, qua z vale -11, che sarebbe f5h a 8 bit con segno.
in C ogni istruzione viene eseguita in un momento diverso, quindi l'ultima istruzione è quella che viene eseguita (perciò, alla fine del programma nella cella di memoria di x avremo -11)

altri operatori che possiamo usare sono i tipici +, moltiplicazione (asterisco), -, / e %. la divisione, se non usiamo numeri con la virgola, restituisce un numero intero (quindi 1/2 farà 0)
esistono anche due operatori unari, ovvero il + e il -, da mettere davari ai numeri per specificarne il segno

gli int sono formati da 8 byte, quindi possono arrivare a 2^31 (dato che metà di 2^32 sono dedicati ai numeri negativi)

in questo codice:
```
int x;
int y;
int z;
int t = 5;
int main (void) {
	x = 3;
	y = x + 5;
	z = y * 3 + 2;
	x = 2 + y * 3;
	y = x / -t;
	z = x % -t;
	return 0;
}
```
l'uguale in "int t = 5;" non è un operatore di assegnamento, ma è una definizione, dove l'uguale fa parte di un'inizializzazione con la quale riserviamo della memoria per la variabile t.
quindi è importante ricordare che assegnamento != inizializzazione, anche se possono sembrare uguali
in C le espressioni avvengono in ordine logico, cioè si eseguono prima le operazioni (sempre in ordine logico, quindi prima moltiplicazioni e divisioni e dopo le somme) e dopo il valore viene assegnato alla variabile. se abbiamo degli operatori unari (come nella linea "y = x / -t") prima viene calcolato il valore della variabile con l'operatore unario, poi si fa il resto (quindi prima viene calcolato l'opposto di t, poi si fa la divisione)
per decidere una precedenza come la vogliamo noi, basta usare le parentesi tonde come si fa in aritmetica normale

le operazioni in matematica non si eseguono sempre da sinistra a destra, e queste sono dette non associative (normalmente sì, come per la sottrazione e la divisione come mostrato nella slide **Associatività** che sono associative a sinistra), infatti nel caso dell'elevamento a potenza questo non accade (a^b^c non è (a^b)^c, ma a^(bxc)) nelle operazioni associative a destra.
tuttavia, in C tutte le operazioni che abbiamo elencato utilizzano la regola dell'associatività a sinistra (in C non esiste un operatore di elevamento a potenza, quindi non si pone il problema)

ogni dato in C ha un tipo associato, anche i risultati delle espressioni. per esempio, se faccio un'operazione tra int, viene restituito un int. in:
```
int x = 7;
int y = 3;
double z;

z = x / y
```
anche se z è un double, il suo valore sarà 3, dato che sto facendo la divisione tra interi e verrà restituito e assegnato un intero.

quando mischiamo diversi tipi di dato in un espressione, ci sono regole diverse e poco chiare, ma fondamentalmente si usa sempre il tipo "più forte", cioè per esempio se uno degli argomenti dell'operatore è un int e l'altro un double, il primo viene convertito in double; lo stesso vale se lo faccio tra un double e un float, diventando entrambi float.
se invece sto provando ad assegnare un dato intero a uno con più bit la conversione avviene normalmente (7 diventa 7.00), mentre se avviene il contrario vengono eliminate le cifre decimali.
guarda la slide **Conversione di tipo** per capire.