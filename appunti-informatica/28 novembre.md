le funzioni di lettura non distinguono tra il raggiungimento della fine del file e il verificarsi di un errore: quando una funzione di lettura ritorna qualcosa diverso dal numero di elementi che si volevano leggere, è possibile controllare gli errori attraverso le funzioni **feof()** e **ferror()**. 
feof() ritorna un valore diverso da 0 se l'ultima operazione di lettura è fallita perchè si è tentato di leggere oltre la fine del file.
ferror() ritorna un valore diverso da 0 se l'ultima operazione di lettura o scrittura è fallita per altri tipi di errore

l'analogo in scrittura della fread() è la fwrite(), che scrive byte per byte quello che gli passiamo:
```
size_t fwrite(const void *buffer, size_t size, size_t count, FILE *stream);
```
e ritorna il numero di byte scritti (che, senza errori, dovrebbe essere uguale al parametro count)


esistono delle funzioni per spostare il cursore nello stream, senza per forza effettuare la lettura. 
la più semplice è la **rewind()**, che ci permette di spostare il cursore all'inizio del file passato come parametro (sintassi: void rewind(FILE \*stream));
la funzione **ftell()** ci restituisce la posizione del cursore all'interno del file
la funzione **fseek()** è quella che ci permette veramente di spostare in modo flessibile il cursore all'interno del file:
```
int fseek(FILE *stream, long offset, int origin);
```
nel parametro origin possiamo mettere le seguenti macro:
- SEEK_SET indica l'inizio del file (potrei usare anche 0)
- SEEK_CUR indica la posizione attuale del cursore
- SEEK_END indica la fine del file

per calcolare la dimensione di un file, può bastarmi aprire il file, fare una fseek alla fine del file e usare una ftell per sapere dove si trova il cursore (quindi sapere quanto avanti si è spostato, in modo da sapere quanto è grande il file)


## Linea di comando

esiste una versione della funzione main che permette di accedere ai parametri passati sulla linea di comando:
```
extern int main(int argc, char *argv[]);
```
dove arcg indica il numero di parametri passati separati da uno spazio, mentre argv è un array di stringhe, cioè quello che abbiamo scritto sulla linea di comando separato da uno spazio

il seguente programma visualizza su ogni riga i parametri passati a linea di comando:
```
#include <stdio.h>
int main(int argc, char **argv)
{
	for (int i = 0; i < argc; ++i) {
		printf("parametro %d: \"%s\"\n", i, argv[i]);
	}
	return 0;
}
```

la linea di comando è particolarmente utile quando si vuole far scegliere all'utente il file da aprire, passandolo come elemento di arcg\[]. 
possono essere passate solo stringhe, quindi se vogliamo prendere un numero dalla riga di comando dobbiamo convertire una stringa in valore numerico binario (con strtol o strtod).
questo esempio va imparato:
```
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	if (argc != 2) {
		return EXIT_FAILURE;
	}
	char *endptr;
	int n = strtol(argv[1], &endptr, 10);
	if (*endptr != 0 || n <= 0) {
		return EXIT_FAILURE;
	}
	for (int i = 0; i < n; ++i) {
		printf("ciao");
	}
	printf("\n");
	return EXIT_SUCCESS;
}
```

#### Chiarezze sulle definizioni

in questo codice:
```
int *K[3];
```
K è un puntatore ad array di 3 int?
oppure è un array di 3 puntatori a int?
le due cose sono molto diverse, e in realtà è un array di 3 puntatori a int. questo perchè le dichiarazioni si leggono da destra a sinistra. quindi sostanzialmente il compilatore sta leggendo prima il nome della variabile (K), poi va a destra (array di 3 elementi), poi va a sinistra e vede che questi 3 elementi sono dei puntatori a int.

se invece volessimo definire un puntatore ad array di 3 int, dovrei scrivere questo:
```
int (*K)[3];
```

#### Matrici

come posso definire una matrice, ad esempio, 3x2?
```
int mat[3][2];
```
questo è un array di 3 array di 2 int.
mettiamo di avere questa matrice 3x2:
|3 2|
|7 9|
|8 5|
l'elemento mat\[1]\[0] sarà 7.

sorgono però dei problemi nel momento in cui vogliamo passare questo tipo di dato a una funzione
```
int funzione(int x[3][2]){
}
```
qui x viene trattato come un puntatore ad array di 2 int.
è come scrivere:
```
int x[][2];
int (*x)[2];
```
di conseguenza gli array di array non sono utilizzabili per fare matrici di dimensione variabile, visto che gli array di array avranno sempre dimensione fissata. non potremo mai fare questa cosa:
```
int x[][]; // non ha senso
```

gli array di array possono avere senso solo se parliamo di tabelle, ma se vogliamo gestire matrici di dimensione arbitraria no, perchè la dimensione deve poter variare

un opzione che abbiamo è usare dei puntatori a puntatori
```
int *m = malloc(3*sizeof(int*));
for(size_t i=0; i<3; ++i){
	m[i]=malloc(2*sizeof(int));
}
```
per liberare la memoria, dovremo poi fare anche:
```
for(size_t i=0; i<3, ++i){
	free(m[i]);
}
free(m);
```

questo metodo tuttavia ha senso puramente didattico, i programmi veri che utilizzano le matrici non usano i puntatori a puntatori, ma riescono comunque a mettere i dati tutti contigui in memoria

quello che si fa solitamente è una sola malloc:
```
m=malloc(3*2*sizeof(int));
free(m);
```
dove però sacrifichiamo leggermente la comodità di utilizzo, infatti non possiamo più usare righe e colonne chiaramente come prima, ma dobbiamo far capire che elemento vogliamo in un'unica espressione

mettiamo di avere 5 righe (m) e 4 colonne (n). semplicemente gli elementi saranno divisi in questo modo:
0   1  2  3
4   5  6  7
8   9 10 11
12 13 14 15
16 17 18 19

per trovare un certo elemento devo andare all'indice (considerando r la riga, c la colonna e cols il numero di colonne della matrice): r\*cols+c