## Gestione della memoria e array

quando un identificatore ha *file scope*, cioè ha visibilità a livello di file, di solito è una variabile globale, cioè possiamo accedervi da qualunque funzione in quel file. in questo caso la definiamo fuori da ogni funzione
se invece la definiamo all'interno di una funzione si dice che ha *block scope*, e possiamo chiamarle variabili locali, anche se non è un termine così preciso
nella slide **Visibilità delle variabili** c'è l'esempio di codice

dobbiamo anche capire quanto dura l'esistenza di una variabile, cioè il suo tempo di vita. esso è legato di solito alla visibilità: le variabili che hanno file scope nascono all'avvio del programma (prima ancora della chiamata della funzione main) e muoiono al termine del programma, mentre le variabili locali nascono nel momento in cui si entra nel blocco (cioè nella funzione) e muoiono quando finisce il blocco.
le variabili globali si dice che hanno una *static storage duration*, mentre quelle locali hanno l'*automatic storage duration*. tramite i puntatori e le funzioni malloc, realloc, ecc possiamo far sì che le variabili usate dentro una funzione non abbiano l'automatic storage duration (cioè possiamo farle durare anche dopo il termine del blocco)
le variabili statiche vengono inizializzate a 0 se non si specifica un valore, mentre quelle automatiche verranno inizializzate con valori casuali

è possibile in C decidere il tipo di variabile (globale o locale) e un tempo di vita diverso da quello normale. questa roba normalmente non si deve fare, ma esiste e si usa molto raramente
per farlo possiamo usare la parola static davanti alla definizione, cioè rendere globale una variabile, anche se la definizione si trova dentro il blocco. il vantaggio di definire una variabile globale dentro una funzione è che questa non può essere usata da nessuna altra funzione all'interno del programma

in questo programma
```
int f(void) {
	static int v;
	return v++;
}
int main(void) {
	int x, y, z;
	x = f();
	y = f();
	z = f();
	return 0;
}
```
v diventa una variabile globale, e le variabili x, y e z avranno i valori:
x=0
y=1
z=2
dato che v++ vale v, e solo dopo viene incrementato di 1. il valore di v viene incrementato ogni volta perchè non si resetta dopo la chiamata di funzione

invece in questo programma
```
int main(void)
{
	int s = 0;
	for (int i = 0; i < 5; ++i) {
		int a = 0;
		++a;
		s = s + a;
	}
return 0;
}
```
s varrà 5 alla fine, perchè a ogni iterazione del for stiamo azzerando a.

per fare valere s=15, dobbiamo scrivere questo:
```
int main(void)
{
	int s = 0;
	for (int i = 0; i < 5; ++i) {
		static int a = 0;
		++a;
		s = s + a;
	}
	return 0;
}
```
che sostanzialmente è come dichiarare la variabile fuori dal ciclo, ma solo il ciclo può usarla.
l'unico reale utilizzo per questa cosa potrebbe essere se vogliamo usare due variabili con lo stesso nome in due parti diverse del programma

esiste anche un terzo tempo di vita oltre a static e automatic, cioè l'*allocated storage duration*, ovvero quello della memoria allocata dalle funzioni malloc(), calloc() e realloc(). il tempo di vita allocato finisce quando si fa una free(), altrimenti quando finisce il programma.
nel programma:
```
int funzione(void){
	int *p = malloc (10*sizeof(int));
	return 0;
}
```
la variabile p, di tipo puntatore a int, ha tempo di vita static (dato che altro non è che l'indirizzo di memoria a cui deve puntare), mentre il pezzo di memoria grande 40 byte allocato, ha tempo di vita allocato. al termine della funzione la variabile p muore, ma la memoria allocata no, quindi avviene un *memory leak*, cioè ci sono dei pezzi di memoria allocati a cui non possiamo più accedere, dato che abbiamo perso il loro indirizzo di memoria. per evitare ciò possiamo o fare una free all'interno della funzione, oppure far restituire alla funzione la variabile p in modo che sia poi possibile avere l'indirizzo di memoria dove abbiamo allocato la memoria anche fuori dalla funzione.

#### Slide Gestione della memoria
nel file binario la parte che contiene i dati viene detta segmento dati (data segment in inglese), mentre la parte che contiene il codice vero e proprio è il segmento codice (text segment)
le variabili globali e quelle dichiarate static finiscono quindi nel segmento dati

le variabili automatiche finiscono invece sullo stack, dove quindi vengono aggiunte con delle specie di push e tolte con delle pop.

le variabili allocate vengono messe nella memoria *heap* (cioè a mucchio), che viene gestita in maniera estremamente complessa e sofisticata, e le variabili rimangono qui finchè non vengono esplicitamente tolte con la free() (oppure finchè non termina il programma)

fin'ora abbiamo visto come allocare tot elementi in memoria uno di fianco all'altro solo in maniera dinamica, cioè con la malloc(), ma ovviamente c'è un modo anche di fare la stessa cosa in maniera statica. questo si fa con una variabile chiamata **array**

la sintassi per definire un array è la seguente:
```
<tipo> <identificatore> [ <N> ];
```
dove N è un'espressione intera costante maggiore di zero, che indica quanti elementi di tipo \<tipo> si intende definire. con il codice
```
int a[5];
```
si definisce un array di 5 int, che occuperanno 5 byte di memoria consecutivi. 
**importante**: il tipo di a è "array di 5 int".

se faccio questo programma: 
```
#include <stdlib.h>
int main(void)
{
	int a[10];
	size_t n = 10;
	for (size_t i = 0; i < n; ++i) {
		a[i] = 0;
	}
	return 0;
	}
```
è come quello che facevamo di solito con la malloc.

dunque l'array è un pezzo di memoria che contiene i dati veri e propri, non solo un indirizzo di memoria. tuttavia, nelle espressioni come quella vista nel codice sopra, l'array diventa a tutti gli effetti un puntatore al suo primo elemento.

esistono delle eccezioni a questa regola: se faccio
```
int arr[10];
sizeof(arr);
```
sizeof(arr) non restituisce 8, che sarebbe la normale dimensione di un puntatore, ma restituisce 40 che è la dimensione dell'array in sè.

l'altro caso particolare è l'operatore &: questo restituisce un puntatore ad array di N elementi di tipo T, cioè:
```
int a[5];
int *p1 = a; // ok (a qui è di tipo puntatore a int)
int *p2 = &a; // errore: tipi incompatibili
```

**attenzione**: questa cosa:
```
#include <stdlib.h>
int main(void)
{
	size_t n = 10;
	int a[n];
	for (size_t i = 0; i < n; ++i) {
		a[i] = 0;
	}
	return 0;
}
```

non si può fare, perchè n non è una costante. la dimensione dell'array deve **sempre** essere una costante. 
il compilatore me lo fa fare, perchè è un'estensione del C99 nota come variable length array, ma è un casino perchè in questo modo l'array finisce sullo stack che ha una dimensione estremamente limitata

non si può fare neanche se scrivo "const size_t n = 10;", perchè n non è una costante, ma rimane una variabile, solo che è di sola lettura.

una soluzione, se vogliamo per forza avere la dimensione dell'array in una variabile, è la seguente:
```
#include <stdlib.h>
int main(void)
{
	int a[10];
	size_t n = sizeof a / sizeof *a;
	for (size_t i = 0; i < n; ++i) {
		a[i] = 0;
	}
	return 0;
}
```
dato che l'espressione "sizeof a" calcola la dimensione dell'array in byte, mentre l'espressione "sizeof \*a" calcola la dimensione del primo elemento
tuttavia questo metodo **NON LO POSSIAMO USARE** dato che spesso viene inteso come metodo di calcolo della dimensione degli array erroneamente.

per inizializzare un array e metterci subito dentro i valori che vogliamo, usare la seguente sintassi:
```
<tipo> <identificatore>[<N>] = { <espressione>, ...};
```
se è presente l'inizializzazione, il numero N si può anche omettere; se N è presente, i valori non possono essere più di N; 
se N è presente e specifichiamo meno di N valori dentro l'array, gli altri diventano degli zeri.

**in C non esistono parametri di tipo array**. se scrivo
```
void func(int a[4]){}
```
a non è un parametro di tipo array di 4 int, ma è un puntatore a int. quindi è la stessa cosa di scrivere
```
void func(int *a){}
```
oppure
```
void func(int a[]){}
```

il numero che potrei mettere dentro le parentesi quadre viene completamente ignorato, quindi i tre codici fanno esattamente la stessa cosa, dato che il compilatore capisce che stiamo passando un semplice puntatore a int
non è possibile sapere la dimensione di un array che sto passando alla funzione, ma è necessario anche passare alla funzione il numero di elementi contenuti in un array

ecco una funzione per calcolare la media di un array:
```
double media(int array[], size_t n){
	double m = 0;
	for(size_t i=0; i<n; i++){
		m = m + a[i];
	}
	return m / n;
}
```

gli array non hanno l'assegnamento, non possiamo assegnare un array a un altro array. questa roba non possiamo farla:
```
int a[3] = { 1, 2, 3 };
int b[3];
b = a; // errore
```
per fare questa cosa fatta bene potremmo fare un semplice ciclo for come questo
```
void copia_arr(const double *src, double *dst, size_t n)
{
	for (size_t i = 0; i < n; ++i)
		dst[i] = src[i];
}
```
dove usiamo il const per assicurarci che l'array di partenza non verrà modificato

introdotti gli array, possiamo finalmente parlare di testo, con gli **array di char**, che usiamo per fare sequenze di caratteri ascii. così possiamo creare la stringa di caratteri
essendo degli array e non potendo sapere la lunghezza della stringa, si utilizza uno zero per far capire al programma quando è finita la stringa (e quindi quando finisce l'array)
gli esempi di come si usano sono nella slide **Inizializzazione di stringhe**

**attenzione**: se uso un solo apice, sto definendo un int. se uso due apici, sto dicendo che quello che c'è dentro è un array di n char. la dimensione dell'array di char è sempre il numero di caratteri +1, che serve allo zero terminatore. per esempio:
```
char s3[11] = "fondamenti";
```
per non dover specificare la dimensione, possiamo anche scrivere così:
```
s4[] = "di";
```
oppure non è un errore anche inizializzare un array con molti più elementi del numero di caratteri della stringa, come:
```
char s5[15] = "informatica";
```

è molto diverso scrivere questo:
```
char s[]="fondamenti";
```
e questo
```
char *s="fondamenti";
```
dato che la versione col puntatore non è modificabile, e molto probabilmente il programma va in crash se si prova a farlo. di conseguenza sarebbe più giusto scrivere const prima della dichiarazione.

possiamo scrivere \n nella stringa per andare a capo. l'espressione "prova\n" è un array di 7 char, perchè il \n viene riconosciuto come un solo carattere (ovvero il codice ascii 10)
l'espressione "!\xff\\\\!" invece è di tipo array di 5 char.
l'espressione "" è di tipo array di 1 char, perchè contiene solo il terminatore 0.
è un errore mettere gli a capo all'interno delle stringhe, che deve essere tutta su un'unica riga. (slide **Letterali di tipo stringa**)

### Struct

mettiamo caso di voler creare una funzione che calcola la distanza tra due punti. per quello che sappiamo fino ad ora, sappiamo farla solo passando alla funzione 4 parametri. tuttavia, i punti sono 2, e quindi ci servirebbe un contenitore che contenga 2 double, per rendere meglio il concetto di punto
ci serve una struttura per contenere più cose assieme

in C questi contenitori sono le struct (che in altri linguaggi si chiamano oggetti), cioè un solo contenitore al cui interno posso mettere più variabili. la sintassi è:
```
struct <tag> { <declaration-list> };
```
la struct è un **nuovo tipo di dato** che possiamo usare per definire altre variabili o come base per altri tipi. 
a differenza delle funzioni, qua ci vuole il ; dopo la graffa di chiusura

in questo codice:
```
struct punto{
	double x, y;
};
```
il nuovo tipo di dato è il struct punto
a questo punto io posso scrivere 
```
struct punto p;
```

**attenzione**: in memoria una struct non occupa la somma dei dati che ha dentro. occupa **almeno** la somma dei dati che ha dentro. il compilatore tra un dato e l'altro e dopo l'ultimo dato è autorizzato a inserire spazio "vuoto" in più (ma potrebbe anche non farlo)
questo accade perchè gli accessi in memoria non sono tutti uguali: i nostri processori non leggono un byte alla volta dalla memoria, ma ne leggono diversi, di conseguenza il compilatore tenta di "allineare" la struct alla posizione dove va a leggere il processore, in base a quanti byte riesce a leggere alla volta (è un po' difficile da spiegare)
dunque non possiamo sapere a priori quanti byte occuperà una struct, se non chiedendolo al compilatore con l'operatore sizeof. possiamo solo sapere che sarà almeno la dimensione di quello che c'è dentro.

per accedere a ciò che c'è dentro una struct posso usare il .
per esempio:
```
struct punto {
	double x, y;
}
struct punto p;
p.x = 12.1;
p.y = 2.4;
```

possiamo anche definire una struct in questo modo:
```
struct punto p = {12.2, 56.3};
```
dove i valori vengono assegnati alla variabile corrispondente

nè negli array, nè nelle struct possiamo fare degli assegnamenti con le parentesi rispettivamente quadre o graffe. possiamo solo usarle per inizializzare

come per gli array possiamo inizializzare una struct solo in parte, e il resto verrà riempito di zeri; lo stesso se mettiamo troppi elementi, che non si può fare.

in questa struct:
```
struct persona{
	char nome[20];
	int anni;
	double altezza;
};

struct persona per = {"Marco", 25, 1.78};
```
cambiando l'ordine verrà comunque fatto l'assegnamento con i membri sbagliati. esiste un modo molto più chiaro per fare questo, che risulta utile soprattutto per struct molto complesse:
```
struct persona per = {.anni = 25, .altezza = 1.78, .nome = "Marco"};
```

volendo possiamo anche fare struct di altre struct (slide **Struct come membri di altre struct**)
```
struct rettangolo {
	struct punto top_left;
	double width, height;
};

struct rettangolo rect = { { 4.5, 5.6 }, 10.3, 60.0 };
```

nelle struct, a differenza degli array, è possibile fare assegnamenti tra struct dello stesso tipo. per esempio:
```
struct punto p1 = {1.2, 5.4};
struct punto p2;
p2 = p1;
```
qua semplicemente il compilatore fa la copia dei byte di p1 e li mette in p2

possiamo anche passare le struct alle funzioni come paraemtri, con la stessa sintassi dei tipi fondamentali. ritornando all'esempio della distanza tra due punti:
```
double dist(struct punto p1, struct punto p2) {
	return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y- p2.y));
}

int main(void){
	struct punto a = {0, 1};
	struct punto b = {1, 1};
	double d = dist(a, b);
	return 0;
}
```

se invece volessi fare il punto medio, mi servirebbe una funzione che ha un'altra struct punto come tipo di ritorno. potremmo fare così:
```
struct punto medio(struct punto p1, struct punto p2)
{
	struct punto pm;
	pm.x = (p1.x + p2.x) / 2;
	pm.y = (p1.y + p2.y) / 2;
	return pm;
}
```

dato che non sto cambiando una variabile esterna, avrei potuto anche fare così:
```
struct punto medio(struct punto p1, struct punto p2) {
	p1.x = (p1.x + p2.x) / 2;
	p1.y = (p1.y + p2.y) / 2;
	return p1;
}
```

generalmente, per velocizzare il programma è utile non copiare mai dei dati. che è esattamente quello che stiamo facendo nel momento in cui passiamo una struct a una funzione (slide **Passaggio di struct come parametro**)
per questo motivo, se le struct si iniziano a fare grandi si usano dei puntatori a struct (slide **Puntatori a struct**). tuttavia bisogna cambiare un bel po' di cose, che finsce per il cambiare l'accesso agli elementi della struct in questo modo:
```
struct punto medio(struct punto *p1, struct punto *p2) {
	struct punto pm;
	pm.x = ((*p1).x + (*p2).x) / 2;
	pm.y = ((*p1).y + (*p2).y) / 2;
	return pm;
}
```

ma visto che sta roba è brutta, esiste un altro operatore in C, definito "->" che fa la stessa cosa di quello che abbiamo appena scritto
```
<expression> -> <member-name>;
// cioè
p1->x; // è la stessa cosa di
(*p1).x;
```