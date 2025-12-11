## Preprocessore e compilazione

se volessimo riutilizzare in un nuovo programma delle funzioni che abbiamo scritto precedentemente, può bastare fare copia incolla delle funzioni che ci servono. questo tuttavia può diventare scomodo nel momento in cui i programmi si fanno più complessi. il problema diventa ancora più grande nel momento in cui vogliamo cambiare qualcosa all'interno della funzione, il che ci obbliga a modificarla in tutti i nostri programmi.
per semplificare l'implementazione di funzioni esterne nel nostro programma, si è pensato di utilizzare un **preprocessore**.
per includere delle direttive del preprocessore, si utilizza una sintassi particolare in modo da non confonderlo con il programma vero e proprio: ogni direttiva è composta dal simbolo # seguito da una parola. una direttiva molto importante è \#include, seguito da un nome di file indicato tra virgolette "" o tra <>. questa direttiva include serve ad aprire il file specificato ed è come se incollasse all'interno del programma. se modifichiamo il file che stiamo includendo, questo verrà modificato anche nel programma.
nella slide **Esempio** si capisce bene il funzionamento, che è abbastanza intuitivo.
sarà il compilatore ad aprire il file che vogliamo includere e incollarlo nel programma

tuttavia nei nostri programmi non dobbiamo mai fare l'include con un file .c
questo perchè, se avessimo un file da includere che contiene un numero elevato di funzioni, il compilatore va a compilare tutte le funzioni, quindi anche quelle che non ci servono. questo rallenta sensibilmente la compilazione senza che ce ne sia bisogno
quindi l'\#include non è una soluzione possibile, dato che quello che vorremmo fare è compilare separatamente solo main.c e il file .c che ci serve, in modo che la compilazione del file esterno non si ripeta nel momento in cui andiamo a fare una modifica al main. 
questo meccanismo tuttavia non può funzionare, dato che per farlo andare il main in linguaggio macchina dovrebbe fare una call alla cella di memoria che contiene il file esterno, senza sapere qual è.

la soluzione che si utilizza in C sta nell'aggiunta di un passaggio intermedio, tramite l'utilizzo di un **file oggetto**. il passaggio intermedio sta nella compilazione di un file, detto file oggetto, che contiene dei pezzi non completati
in questo il codice macchina con tutte le istruzioni e i dati viene effettivamente generato, mentre tutte le informazioni esterne, come una call all'indirizzo di una funzione esterna, non vengono specificate (il compilatore metterà una call a una cella vuota). servirà anche il codice macchina delle funzioni esterne, una sezione detta *export* dove viene associata a una funzione il suo indirizzo di memoria, e una sezione detta *import* dove si specifica come sostituire ai buchi che abbiamo lasciato gli indirizzi delle funzioni che si trovano in export
c'è un esempio di file oggetto nelle slide **File oggetto**, dove si capisce abbastanza bene il funzionamento
in export troviamo l'indirizzo della funzione del programma che vogliamo esportare, mentre in import troviamo l'indirizzo della funzione esterna che vogliamo usare all'interno del nostro file.
per collegare i due file questi vengono messi uno dopo l'altro, e gli export e gli import vengono cambiati in base a dove si trovano le funzioni nel nuovo programma. questa conversione è semplice dato che, per le funzioni che si trovano nel secondo programma, basta aggiungere all'indirizzo originario la lunghezza del primo programma.
il processo si conclude quando al posto dei buchi in main si mette l'indirizzo della funzione che ci interessava

in questo modo abbiamo trovato un modo di utilizzare radice.c dentro main.c, senza aver bisogno di ricompilare radice.c ogni volta che ricompiliamo main.c
tuttavia abbiamo detto che vorremmo anche compilare main.c e radice.c indipendentemente, infatti nell'esempio della slide **Identificatori non definiti**, nel main.c il compilatore ci direbbe che non abbiamo definito radq. per risolvere bisogna introdurre il concetto di **dichiarazione**, che è un modo per dire al compilatore che esiste un certo simbolo, descrivendone le caratteristiche. per far capire al compilatore che non sto definendo una variabile, uso la parola chiave **extern**, che segnala al compilatore che questo identificatore verrà poi definito successivamente.
in realtà non è indispensabile mettere extern davanti alle funzioni, dato che si capisce lo stesso che non è una definizione dal momento che mancano le graffe con i comandi dentro, ma noi lo metteremo sempre. è anche facoltativo dare il nome ai parametri quando dichiaro una funzione, dato che sarebbe sufficiente scrivere il tipo. gli esempi nella slide **La dichiarazione** sono tutti corretti e fanno la stessa cosa. noi alla fine dichiareremo le funzioni sempre così:
```
extern float fraz(int a, int b);
```

se volessimo introdurre una ipotetica funzione radq in un file esterno, potremmo fare così:

```
extern double radq(double a);

int main(void) {
	double d = radq(137.0);
	return 0;
}
```

questo codice compila già da solo, ma ovviamente per farlo funzionare dobbiamo creare anche un file che contiene la funzione radq e compilarlo. l'eseguibile che si genera è nato dal collegameto tra main.obj e radice.obj
visual studio sa dove pescare le funzioni esterne se le trova in un file che si trova nello stesso progetto.

per portare direttamente nel mail tutte le dichiarazioni presenti in un file, quindi non mettere direttamente il nome della funzione.
non esiste un metodo automatico, ma quello che possiamo fare è fare l'include di un file aggiuntivo, che avrà come estensione .h (che sta per header) che contiene la dichiarazione delle funzioni nel file che le contiene effettivamente. l'esempio è nella slide **L'esempio corretto con \#include**

un'altra funzionalità fornita dal preprocessore sono le **macro**, dove attraverso \#define possiamo sostanzialmente usare un "trova e sostituisci" per il nostro codice. ne esistono due versioni, di cui in una possiamo passare anche dei parametri. in entrambi i casi vanno scritte in una sola riga. la sintassi si trova alla slide **Le macro**, e il loro utilizzo nelle slide **Esempio di uso del \#define**

in questo esempio
```
#define TRUE 1
#define FALSE 0
...
int finito = FALSE;
	while (finito != TRUE) {
	...
}
```
FALSE non ha nessun tipo, dato che non è una variabile nè un'espressione, non viene neppure compilato. semplicemente, prima di compilare, tutti i FALSE diventano uno 0
realisticamente le macro si utilizzano se abbiamo bisogno di cambiare un valore che viene utilizzato tante volte

volendo una macro può anche corrispondere al testo vuoto (slide **definizioni vuote**)

le macro con parametri si usano come alla slide **Macro con parametri**
attenzione: le macro sono semplice sostituzione di testo, se definiamo una macro " quadrato(x) x\*x " e scriviamo poi quadrato(3+1), questa diventa 3+1\*3+1, che fa 7.
le diverse complicazioni che derivano dalle macro con parametri ci portano al volerle evitare completamente. piuttosto, useremo delle funzioni normali

nel creare i file .h bisogna seguire le regole definite nell'ultima slide **L'include guard (5)**, che il prof ci spiegherà poi.

## Di nuovo puntatori

esiste in C una libreria chiamata **libreria standard**, che viene già linkata dal compilatore, che contiene molte funzioni fondamentali.

una libreria che useremo molto è la **stdint.h**, che ci permette di definire dei tipi interi a larghezza fissa, signed e unsigned e i rispettivi valori minimi e massimi. (slide **La libreria stdint.h**)

la libreria **stdlib.h** contiene varie funzioni e macro, ma la cosa più importante è la macro NULL, che serve a creare dei puntatori che puntano a 0. 
questa libreria contiene anche un tipo di dato senza segno chiamato size_t, che mi consente di rappresentare le dimensioni di un oggetto che sto implementando.

la libreria **stdbool.h** definisce tre macro: true, false e bool, che corrispondono rispettivamente a 1, 0 e \_Bool.

esiste un operatore del C chiamato sizeof, che con le tonde può darci la dimensione di un tipo di dato, e senza tonde ci può dare la dimensione del tipo di un'espressione.
sizeof 'c' sarà 4 perchè 'c' è un int, e quindi a 4 byte
sizeof(255+10) sarà 4, perchè 265 è un int

il vero scopo dei puntatori è accedere a tanti dati tutti dello stesso tipo. in C l'incremento dei puntatori ha un'aritmetica particolare (**Aritmetica dei puntatori**). se proviamo a incrementare un puntatore, questo viene incrementato dei byte del tipo del puntatore.
quindi in un certo senso ci aiuta, dato che sarà sufficiente incrementare del numero di elementi senza calcolare in base alla loro dimensione.
per esempio, se ho un puntatore a int e lo incremento di 2, questo verrà in realtà incrementato di 8 (4 byte per 2)
guardati tutte le slide su questo argomento, sembrano importanti

in C esiste una funzione apposita che chiede al sistema operativo di riservare memoria, chiamata **malloc()**. questa chiede al sistema di allocare un nunmero di byte che decidiamo noi, e ritorna un puntatore al primo byte della zona di memoria che è appena stata riservata, in modo da farcela utilizzare.
per utilizzarlo posso scrivere direttamente:
```
int *ip = (int*)malloc(12);
```
per far sì che il puntatore ip punti all'indirizzo di memoria riservato dalla funzione malloc, che avrà riservato 12 byte, dove quindi possono starci 3 int.

normalmente quello che faremo per allocare la memoria di un numero arbitrario di variabili sarà scrivere 3*\sizeof(tipo), in modo da non dover specificare il numero di byte che vogliamo riservare ma lasciare che il programma lo faccia per noi sapendo solamente quanti iterazioni di quel tipo di dato vogliamo allocare

per liberare la memoria quando non serve più, si utilizza la funzione **free(puntatore)**, che comunica al sistema operativo che la memoria puntata da un puntatore è da deallocare.

possiamo utilizzare la funzione malloc come mostrato alla slide **Accesso alle variabili appena allocate**, cioè incrementando il puntatore in modo da fare riferimento a uno specifico elemento allocato in memoria tramite malloc