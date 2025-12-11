nella riga
```
z = (float)x / (float)y;
```
abbiamo 4 operatori: in ordine di esecuzione sono conversione a float (eseguita 2 volte), divisione e assegnamento

quando in C passo un parametro in una funzione non sto passando la variabile in sè, ma il valore contenuto in quella variabile.
qua per esempio:
```
int y = 7;
void raddoppia (int x) {
	x = x*2;
}
int main(void) {
	raddoppia(y);
	return 0;
}
```
non passiamo a raddoppia la y, ma il valore contenuto in y (in questo caso 7). tuttavia in questo programma la y non viene realmente modificata, dato che la modifica del parametri all'interno della funzione non tocca in alcun modo le variabili esterne ad essa.
anche se cambiassi il nome del parametro dentro la funzione raddoppia(), la situazione non cambierebbe, dato che in ogni caso la y dentro la funzione rimane interna ad essa.

il modo corretto di far sì che la funzione serva a qualcosa anche fuori di essa è restituire un valore attraverso il return: 
```
int y = 7;
int raddoppia (int x) {
	return x*2;
}
int main(void) {
	y = raddoppia(y);
	return 0;
}
```

con tutti i concetti fatti messi insieme (while, if, funzioni) possiamo fare il programma dell'mcd in questo modo:
```
unsigned int m = 15, n = 6, t, mcd;
unsigned int MCD (unsigned int m, unsigned int n)
{
	if (m == 0)
		return 0;
	if (n == 0)
		return 0;
	while (m != n) {
		if (m < n) {
			t = m;
			m = n;
			n = t;
		}
		m -= n;
	}
	return m;
}
int main(void)
{
	mcd = MCD(m, n);
	return 0;
}
```
ma questa non è realmente riutilizzabile se volessimo semplicemente copiare e incollare la funzione su un altro programma, dato che stiamo utilizzando una variabile che è stata definita esternamente alla funzione (la variabile t)
per risolvere questo problema, esistono le variabili locali: all'interno di un qualsiasi blocco di comandi possiamo inserire definizioni di variabili. la funzione può diventare pienamente riutilizzabile in questo modo: 
```
unsigned int MCD (unsigned int m, unsigned int n)
{
	if (m == 0) {
		return 0;
	}
	if (n == 0) {
		return 0;
	}
	while (m != n) {
		if (m < n) {
			unsigned int t = m;
			m = n;
			n = t;
		}
		m -= n;
	}
	return m;
}
int main(void)
{
	unsigned int m = 15;
	unsigned int n = 6;
	unsigned int mcd;
	mcd = MCD(m, n);
	return 0;
}
```
è dimostrato che è possibile fare qualsiasi programma utilizzando solo variabili locali

su visual studio posso eseguire tutto il debugging fino alla riga dove ho il cursore con ctrl+f10, e fermo il debugging con shift+f5.

in C prima di ogni uso di qualsiasi nome (sia variabili che funzioni) lo devo dichiarare (quindi non posso usare una funzione prima di averla dichiarata)

operatori logici (non binari, com'erano quelli di ade8):
- AND: &&
- OR: ||
- NOT: ! davanti a un'espressione
tutti questi operatori hanno priorità più bassa rispetto agli operatori aritmetici

con l'utilizzo dell'else il programma dell'mcd può essere ulteriormente migliorato
```
unsigned int MCD (unsigned int m, unsigned int n)
{
	if (m == 0 || n == 0) {
		return 0;
	}
	while (m != n) {
		if (m < n) {
			n -= m;
		}
		else {
			m -= n;
		}
	}
	return m;
}
int main(void)
{
	unsigned int m = 15;
	unsigned int n = 6;
	unsigned int mcd;
	mcd = MCD(m, n);
	return 0;
}
```


in un ciclo while ci sono 4 parti principali: in una inizializziamo delle variabili di controllo, in una verifichiamo la condizione, una è l'insieme dei comandi da ripetere e una aggiorna le variabili da controllare. ma esistono casi in cui vogliamo eseguire almeno una volta il ciclo, e solo dopo verificare se è necessario riperne l'esecuzione.
questo si potrebbe fare semplicemente facendo semplicemente una volta i comandi prima del while, oppure si può fare con il comando do...while:
```
do {
	Body
	Update
} while ( Check );
```
che è sostanzialmente la stessa cosa di mettere il body fuori dal while (non è molto usato)