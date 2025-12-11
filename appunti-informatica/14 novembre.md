### Sempre sulle struct

per far restituire a una funzione un puntatore a struct, non possiamo fare questa cosa:
```
struct punto *medio(struct punto *p1, struct punto *p2) {
	struct punto pm;
	pm.x = (p1->x + p2->x) / 2;
	pm.y = (p1->y + p2->y) / 2;
	return &pm;
}
```
perchè, dato che abbiamo dichiarato la struct dentro la funzione, questa ha automatic storage duration e dunque al termine della funzione la struct non esisterà più.

l'unico modo per restituire un puntatore a struct è allocare dinamicamente un pezzo di memoria per quella struct, e restituirne il puntatore, in questo modo:
```
struct punto *medio(struct punto *p1, struct punto *p2) {
	struct punto *pm = malloc(sizeof(struct punto));
	pm->x = (p1->x + p2->x) / 2;
	pm->y = (p1->y + p2->y) / 2;
	return pm;
}
```
bisogna fare sempre attenzione a evitare dei memory leak, usando una free dopo che abbiamo usato il puntatore. per esempio in questo modo:
```
struct punto p1 = { 0, 0 };
struct punto p2 = { 1, 1 };
struct punto *pm = medio(&p1, &p2);
// operazioni su pm
free(pm);
```

bisogna anche sempre ricordarsi che, in genere, quando stiamo scrivendo una funzione che deve restituire un nuovo puntatore, in genere è buona norma scrivere const davanti ai parametri, se non vogliamo modificarli

le struct vanno definite sempre prima di usarle, e dunque solitamente va definita nel file .h prima delle dichiarazioni delle funzioni di quelle struct, per esempio in questo modo:
```
#pragma once
struct punto {
	double x, y;
};
extern struct punto *medio(const struct punto *p1, const struct punto *p2);
```

in C non possiamo definire una struct senza scrivere esplicitamente che stiamo definire una struct, cioè non possiamo fare questo:
```
punto p;
```
questo perchè il C esistono diversi *namespace*, e il compilatore sta cercando "punto" nell'elenco dei tipi (come sarebbero int, char, ecc), e ovviamente il tipo "punto" non esiste. (slide **Struct, tag e typedef**, guardale)
per risolvere il problema una soluzione potrebbe essere usare un **typedef**, che ci permette di definire un nuovo tipo corrispondente a una struct:
```
struct punto {
	double x, y;
};
typedef struct punto tipo_punto;
```
in questo modo stiamo definendo un tipo "tipo_punto" che è esattamente una struct punto.
in realtà non è un errore neanche scrivere questo:
```
struct punto {
	double x, y;
};
typedef struct punto punto;
```
in modo che sia indifferente scrivere punto o struct punto
un'altra cosa ancora che potremmo fare è questa:
```
typedef struct punto { double x, y; } tipo_punto;
```
che fa ancora la stessa cosa

in genere nei nostri esercizi non nasconderemo le struct con typedef

## break, continue, switch, enum, union

mettiamo di avere un while, dove vogliamo uscire dal while se accade una cosa specifica. fin'ora abbiamo visto diversi metodi per fare questo:
- usare un return se ci troviamo in una funzione, con il contro che però, se abbiamo del codice dopo il while, questo verrà ignorato
- usare un goto che ci porta a dopo il ciclo (che però tendiamo a non usare)
- far sì che la condizione del while non sia più vera, magari cambiando le variabili che vengono controllate
esiste tuttavia una keyword che sostanzialmente fa quello che farebbe il goto, in maniera più semplice e pulita, ovvero il **break**. 
il break serve semplicemente a uscire dal ciclo in cui ci troviamo (che sia un while o un for)

la keyword **continue** invece è specifica per il ciclo for, che serve a saltare un'iterazione di ciclo e continuare con quella successiva. per esempio in questo codice:
```
size_t somma_cifre_dec(const char *s) {
	size_t i, somma = 0;
	for (i = 0; s[i] != 0; ++i) {
		if (!isdigit(s[i]))
			continue;
		somma += s[i] - '0';
	}
	return somma;
}
```
se la condizione dentro l'if si verifica, allora il resto del for non viene eseguito e si passa direttamente alla iterazione successiva del ciclo

mettiamo ora caso di avere una funzione che consiste nella verifica di diverse condizioni, che formano una serie di if che operano tutti sulla stessa variabile. esiste un comando apposito (ma relativamente inutile) per compattare il tutto, ovvero lo **switch**, che è sostanzialmente un altro goto mascherato, con la seguente sintassi (esempio):
```
double esegui_operazione(char op, double n1, double n2) {
	double risultato;
	switch (op) {
	case '+': risultato = n1 + n2;
		break;
	case '-': risultato = n1 - n2;
		break;
	case '*': risultato = n1 * n2;
		break;
	case '/': risultato = n1 / n2;
		break;
	default: risultato = 0;
		break;
	}
	return risultato;
}
```
il default fa la stessa cosa dell'else in un if.

non ci sono vere differenze tra if e switch, sono fondamentalmente la stessa cosa. lo switch è stato inventato inizialmente per una questione di efficienza, ma i compilatori moderni capiscono già se stiamo facendo una cascata di if e si adatta di conseguenza

altra keyword è **enum**, che serve a definire una lista di parole chiave che caratterizzano una condizione (?)
il senso dell'enum è creare un tipo per enumerare una serie di cose, associando dei nomi sensati per il programmatore
è più chiaro con questo esempio:
in questo codice:
```
enum colori {
	rosso,
	blu,
	verde,
	bianco,
	nero
};
```
la parola "rosso" è un numero intero che significa 1, "blu" significa 2, "verde" il 3 ecc.
posso anche fare così:
```
enum colori {
	rosso,
	blu = 18,
	verde,
	bianco = 32,
	nero
};
```
e qui il "verde" sarà 19 e il "nero" sarà 33.
quindi sostanzialmente l'enum è solo un elenco di possibili valori
se definiamo un nome dentro un enum, è come se stessimo definendo una variabile normale, quindi quel nome non potremo più utilizzarlo per definire un'altra variabile nel programma
inoltre, l'enum in C può essere solo un int

questo potrebbe essere un utilizzo utile di switch e enum:
```
enum oper { add, sub, mul, div };
double op(enum oper x, double n1, double n2) {
	double risultato;
	switch (x) {
	case add: risultato = n1 + n2; break;
	case sub: risultato = n1 - n2; break;
	case mul: risultato = n1 * n2; break;
	case div: risultato = n1 / n2; break;
	default: risultato = 0; break;
	}
	return risultato;
}
```


in C è possibile dichiarare anche un altro tipo di dato strutturato, ovvero l'**union**, la cui sintassi per la dichiarazione è praticamente uguale alle struct.
sostanzialmente una union è una struct in cui tutte le variabili sono sovrapposta in memoria allo stesso indirizzo. cioè, se già sappiamo che useremo solo una delle variabili, possiamo usare una union invece di una struct per risparmiare memoria. infatti per una union il compilatore riserva spazio solo per contenere la variabile di dimensione maggiore.

non useremo mai le union in questo corso

## Le librerie software

useremo alcune librerie standard che useremo durante il corso:

#### string.h

questa libreria ha le seguenti funzioni già fatte:

**strlen()**: ha come parametro una stringa e restituisce un size_t con la lunghezza della stringa

**strcmp()**: dato che non esiste il tipo stringa in C, non possiamo fare dei veri e propri confronti tra stringhe, ma li facciamo tra array di char. fare questo:
```
char s[]="ciao";
if(s=="ciao"){
	x=2;
}else{
	x=3;
}
```  
ci darà sempre 3, dato che nell'if sto vedendo se l'indirizzo di memoria a cui punta s (dato che s è un puntatore) corrisponde a "ciao" (cosa senza senso)
detto ciò, se voglio comparare delle stringhe posso usare la funzione strcmp(), che accetta come parametri due puntatori alle stringhe da confrontare, e ritorna un intero con segno che contiene il risultato del confronto.
ritornerà 0 se le due stringhe sono uguali, un valore negativo se la prima stringa è minore in ordine lessicografico, e un valore positivo se la prima stringa è maggiore in ordine lessicografico (che confronta praticamente il valore ascii delle singole lettere. per esempio, "aereo"<"casa", "casa">"cane", "casa"<"casale", "Casa"<"cane" perchè la C maiuscola viene prima della c minuscola nella tabella ascii)

**strncmp()**: è un strcmp() che confronta solo una parte della stringa

**funzioni di ricerca**: 
- strchar() cerca la prima occorrenza di un carattere
- strrchr() cerca l'ultima occorrenza di un carattere
- strstr() cerca la prima occorrenza di una stringa all'interno di un'altra
queste 3 funzioni non ritornano l'indice del carattere dove hanno trovato la stringa, ma ritornano il puntatore all'indirizzo dove hanno trovato il valore richiesto, e ritornano NULL se non trovano niente