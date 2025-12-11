## sempre funzioni della libreria string.h

**strcpy()**: \*strcpy(char \*dest, const char \*src) dove i parametri sono la stringa di destinazione dest in cui copiare la stringa sorgente src, serve a copiare tutti i caratteri della stringa src, compreso il terminatore, nell'array puntato da dest. la funzione ritorna un puntatore copia di dest. 
si hanno degli undefined behaviour se l'array dest non è abbastanza grande per contenere la stringa copiata, se le due stringhe si sovrappongono in memoria, se src non punta a un array zero terminato.
esempio:
```
#include <string.h>
int main(void) {
	char s1[] = "stringa da copiare";
	char s2[] = "stringa da copiare molto più lunga della prima";
	char dest[25];
	strcpy(dest, s1);
	return 0;
}
```

**strcat()**: si utilizza per concatenare due stringhe, ha sempre dichiarazione char \*strcat(char \*dest, const char \*src) e copia tutti i caratteri di src compreso il terminatore in coda a dest. la funzione ritorna una copia del puntatore dest

entrambe queste funzioni hanno una variante con "n", cioè strncpy() e strncat(), che possono eseguire le operazioni su un certo numero di caratteri, con la seguente dichiarazione:
```
char *strncpy(char *dest, const char *src, size_t count);
char *strncat(char *dest, const char *src, size_t count);
```

Attenzione: strncpy() è l’unica funzione ad avere un comportamento
diverso dalle altre funzioni per le stringhe.
Se durante la copia vengono raggiunti i count caratteri copiati l’array destinazione non viene zero terminato!
Inoltre se il terminatore della stringa da copiare viene raggiunto prima di count, nei restanti byte vengono copiati degli zeri.
La strncpy() esegue quindi sempre count scritture.

strncat() invece aggiunge sempre alla fine della stringa concatenata il terminatore.
strncat() quindi, se dopo count caratteri copiati non ha raggiunto il
terminatore lo scrive lo stesso, per un totale di count + 1 scritture.
Un array di char su cui viene applicata la strncat() deve quindi essere grande almeno strlen(dest) + count + 1


ci sono alcune funzioni che si occupano di array di char ma non di stringhe, quindi senza dare per scontato che sono zero terminati (**Altre funzioni di string.h**):

**memset()** ci permette di riempire tutti i suoi byte con un certo valore, con la seguente sintassi:
```
void *memset(void *dest, int ch, size_t count);
```

**memchr()** ci permette di cercare un certo valore di byte all'interno di un array, con la seguente sintassi:
```
void* memchr(const void* ptr, int ch, size_t count);
```

**memcmp()** ci permette di confrontare byte per byte due array, con la seguente sintassi:
```
int memcmp(const void* lhs, const void* rhs, size_t count);
```

**memcpy()** ci permette di copiare il contenuto di un array in un altro. è estremamente ottimizzata per ogni processore, per questo è molto usata. la sintassi è:
```
void* memcpy(void *dest, const void *src, size_t count);
```

**memmove()** ci permette di copiare array, ma in questo caso si risolve il problema di copiare zone di memoria sovrapposte, che nel memcpy() generava un undefined behaviour, come se prima i dati passassero per un array temporaneo. la sintassi è:
```
void* memmove(void* dest, const void* src, size_t count);
```


## Altre librerie

#### assert.h
questa libreria contiene una macro che serve a verificare delle condizioni che devono essere sempre valide all'interno del nostro programma. la sintassi è:
```
assert (int-expression);
```
e mi serve solamente a fare debug, quindi nel momento in cui sto eseguendo il programma in modalità release viene ignorata.

#### float.h e limits.h
**float.h**
la libreria float.h contiene alcune macro che rappresentano le caratteristiche dei tipi decimali.

**limits.h**
fa la stessa cosa di float.h per dei tipi interi.

float.h e limits.h hanno il vantaggio di poter capire se ci troviamo in un sistema dove i tipi di dato cambiano dimensione, dove quindi non ci saranno problemi.

#### time.h
gestire il tempo nell'informatica è sempre abbastanza complicato. in C per farlo esiste la libreria time.h
questa libreria definisce un tipo di dato *time_t*, che è un numero che definisce quanto tempo è passato rispetto a un certo istante temporale.
i sistemi attuali definiscono il tempo con un long long. 
la funzione per avere il valore dell'istante attuale è:
```
time_t time(time_t *arg);
```
che solitamente viene scritto solamente time(NULL)

avere il numero di secondi da una data ignota però non ci serve a molto, per questo esiste una struct specifica:
```
struct tm {
	int tm_sec; // seconds after the minute - [0, 60] including leap second
	int tm_min; // minutes after the hour - [0, 59]
	int tm_hour; // hours since midnight - [0, 23]
	int tm_mday; // day of the month - [1, 31]
	int tm_mon; // months since January - [0, 11]
	int tm_year; // years since 1900
	int tm_wday; // days since Sunday - [0, 6]
	int tm_yday; // days since January 1 - [0, 365]
	int tm_isdst; // daylight savings time flag
};
```
che possiamo ottenere con due funzioni:
```
struct tm *gmtime_r(const time_t *timer, struct tm *buf);
struct tm *localtime_r(const time_t *timer, struct tm *buf);
```
di cui la prima utilizza UTC, mentre la seconda utilizza l'orario locale
in visual studio si utilizza una versione non standard:
```
struct tm* gmtime_r(const time_t* timer, struct tm* buf) {
	return gmtime_s(buf, timer) ? NULL : buf;
}
struct tm* localtime_r(const time_t* timer, struct tm* buf) {
	return localtime_s(buf, timer) ? NULL : buf;
}
```

se volessi produrre una stringa di testo che contiene l'orario, esiste la funzione asctime_s():
```
errno_t asctime_s(char *buf, rsize_t bufsz, const struct tm *time_ptr);
```
che produce una stringa standard che rappresenta il contenuto di struct tm.

per ottenere una rappresentazione testuale personalizzata si utilizza:
```
size_t strftime(char *str, size_t count, const char *format, const struct tm
*tp);
```

esempio di tutto:
```
#include <time.h>
struct tm* gmtime_r(const time_t* timer, struct tm* buf) {
	return gmtime_s(buf, timer) ? NULL : buf;
}
struct tm* localtime_r(const time_t* timer, struct tm* buf) {
	return localtime_s(buf, timer) ? NULL : buf;
}
int main(void)
{
	time_t t = time(NULL); // Ottengo il "tempo" attuale (quanti secondi dal 1 gennaio 1970)
	struct tm tutc;
	gmtime_r(&t, &tutc); // time_t -> struct tm (UTC)
	char date[26]; // 26 è la dimensione minima per il formato di default
	asctime_s(date, 26, &tutc); // struct tm -> testo (standard)
	char mydate[20];
	strftime(mydate, 20, "%d/%m/%Y %H:%M:%S", &tutc);
	struct tm tloc;
	localtime_r(&t, &tloc); // time_t -> struct tm (localtime)
	char locdate[26];
	asctime_s(locdate, 26, &tloc); // struct tm -> testo (standard)
	return 0;
}
```


a volte è utile misurare il tempo in modo più preciso, perchè il secondo non è sufficiente. ci viene in aiuto questa struct:
```
struct timespec {
	time_t tv_sec; // Seconds - >= 0
	long tv_nsec; // Nanoseconds - [0, 999999999]
};
```
che arriva fino alla precisione dei nanosecondi. questo dato si ottiene con la funzione:
```
int timespec_get(struct timespec *ts, int base);
```
dove "base" deve essere sempre TIME_UTC


#### stdlib.h
oltre a quelle già viste, contiene altre funzioni utili

contiene due funzioni per la generazione di numeri casuali, ovvero rand() e srand().

la funzione **rand()** ha la dichiarazione 
```
int rand(void);
```
e ritorna un numero intero pseudo-casuale che va da 0 a RAND_MAX, partendo da un seed

se vogliamo invece decidere noi il seed utilizzato dalla funzione, dobbiamo usare **srand()**:
```
void srand(unsigned int seed);
```
un modo utile per usarlo è, per esempio, prendere il seed dall'orario:
```
srand((unsigned int) time(NULL));
```
il modo di usarlo è chiamare una volta srand all'inizio del main, e dopo usare rand()

un'altra funzione utile di stdlib.h è la funzione **exit()**, che serve a terminare il programma

la funzione **div()** esegue la divisione intera tra due numeri interi (non si sa bene a cosa serva, possiamo solo usare /) e restituisce una struct.

la funzione **abs()** calcola il valore assoluto
```
int abs(int n);
long labs(long n);
long long llabs(long long n);
```


effettuare conversioni da stringa a numero può essere molto tedioso e complicato, per questo esistono delle funzioni già fatte in stdlib.h con le funzioni **strto*()**, ovvero strod(), strtof(), strtold() per le conversioni in floating point e strtol(), strotoll(), strtoul(), strtoull() per le conversioni in interi.
le sintassi sono:
per i numeri floating point:
```
double strtod (const char* str, char** endptr);
float strtof (const char* str, char** endptr);
long double strtold (const char* str, char** endptr);
```
per gli interi:
```
long int strtol (const char* str, char** endptr, int base);
long long int strtoll (const char* str, char** endptr, int base);
unsigned long int strtoul (const char* str, char** endptr, int base);
unsigned long long int strtoull (const char* str, char** endptr, int base);
```

vediamo tra i parametri dei puntatori a puntatori a char (per esempio char** endptr), ovvero un puntatore a un puntatore che conterrà l'indirizzo del primo carattere della stringa successivo al numero appena convertito. possiamo metterlo a NULL, se non ci importa la posizione dove ha finito di fare la conversione
il motivo per cui usiamo un puntatore a puntatore è che noi dobbiamo definire un puntatore a char per sapere la posizione di un dato all'interno di un array di char, e la funzione per modificare questo puntatore deve usare un puntatore a questo puntatore.

ecco alcuni esempi:
```
#include <stdlib.h>
int main(void)
{
	errno = 0;
	char *input;
	char *endptr;
	long x; // In Windows long è sinonimo di int (in Linux invece è long long)
	ptrdiff_t numchar;
	
	input = "123";
	x = strtol(input, &endptr, 0);
	numchar = endptr - input;
	// x qua varrà 123
	// endptr sarà un puntatore al terminatore
	// numchar vale la differenza tra i 2 puntatori, cioè 3, che sarebbe il numero di caratteri convertiti
	
	input = "\r \t \n 456";
	x = strtol(input, &endptr, 0);
	numchar = endptr - input;
	// x vale 456
	// endptr sarà un puntatore al terminatore
	// num char vale 9
	
	input = "123 456";
	x = strtol(input, &endptr, 0);
	numchar = endptr - input;
	
	input = "456xyz";
	x = strtol(input, &endptr, 0);
	numchar = endptr - input;
	
	input = "abc123";
	x = strtol(input, &endptr, 0);
	numchar = endptr - input;
	// x vale 0
	// endptr punta all'indirizzo della "a"
	
	return EXIT_SUCCESS;
}
```

se vogliamo controllare se il numero è rappresentabile possiamo usare errno (vedi slide **strto*()**).


#### math.h

in questa libreria troviamo praticamente tutte le funzioni matematiche di cui possiamo avere bisogno

sono interessanti le funzioni per gli arrotondamenti dei double:
**ceil()** restituisce l'intero superiore, **floor()** restituisce l'intero inferiore, **round()** fa un arrotondamento generico

il valore assoluto di un numero con la virgola si fa con fabsf() per i float e fabs() per i double

il resto con la virgola si può fare con le funzioni fmodf() e fmod()

esistono due macro importanti, NAN e INFINITY, che spesso si usano nei confronti con le funzioni isinf(x) e isnan(x)


#### errno.h

questa libreria serve a gestire gli errori provenienti dalle funzioni della libreria standard. 
utilizza la macro errno, che va impostata a zero per poi chiamare la funzione di interesse.
gli errori principali sono nella slide **La libreria errno.h**, e qui c'è un esempio:
```
#include <math.h>
#include <errno.h>
int main(void)
{
	errno = 0;
	double res = sqrt(-1);
	if (errno != 0){
		// strerror(errno)
		return EXIT_FAILURE;
	}
	return 0;
}
```
dove se errno è diverso da zero so che è avvenuto un errore