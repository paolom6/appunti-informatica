## input e output

l'unico modo che ha il C di comunicare con l'esterno è leggendo e scrivendo dati su file.
una volta i dati non potevano essere scritti dove volevamo all'interno della memoria, ma venivano scritti su dei nastri magnetici. 
per questo motivo in C quando si parla di file in realtà si parla di flusso di byte o *stream*. questo può essere immaginato come un flusso di dati ai quali si accede sequenzialmente byte per byte.
in C non esistono direttamente degli operatori per accedere ai file, quindi dovremo usare la libreria esterna **stdio.h**
questa libreria definisce il tipo di dato FILE, di cui non conosciamo i dettagli ma con cui possiamo interagire tramite specifiche funzioni
in realtà noi non avremo mai variabili di tipo FILE, ma sempre dei puntatori a FILE, che non andremo mai a dereferenziare perchè non sappiamo cosa farcene

il file viene visto come sequenza di byte, e ogni volta che scriviamo la posizione si sposta avanti di 1 (cioè la distanza fisica che contiene un byte). quindi quando scriviamo e leggiamo stiamo eseguendo le operazioni semplicemente byte per byte
esiste un tipo di file particolare, che permette l'accesso casuale, nel quale possiamo muoverci liberamente, ma solitamente non è possibile.
normalmente scrivere è la cosa facile, mentre leggere è più complicato, perchè dobbiamo interpretare quello che altri hanno scritto, anche solo per il fatto che non sappiamo la grandezza del file da leggere (per esempio, il file tastiera non possiamo sapere quando finisce)
l'unico modo che abbiamo per sapere quando finisce un file è l'*end-of-file*, che avviene nel momento in cui leggendo non si trovano più byte.

ci sono diverse modalità di accesso ai file: la modalità di sola scrittura, la modalità di sola lettura e la modalità append (che solitamente non si usa), che prevede che si possa solo scrivere sul file, iniziando a scrivere dalla file del file. non si utilizza molto ma è possibile avere una modalità di scrittura e lettura in contemporanea
esistono altre due modalità di accesso ai file: la modalità testuale e la modalità binaria. partiamo da dire che non esistono file di testo e file binari, tutti i file in realtà sono binari; i file di testo sono file binari che contengono solo bit che andranno interpretati come codici di caratteri. il motivo per cui vengono distinte le modalità testuale e binaria è puramente storico, ed è legato al carattere "a capo": questo infatti aveva codici diversi per ogni sistema operativo (windows ne usa due, il 13 (\r) e 10 (\n), unix usa solo il 10, macos usa solo il 13)
quando hanno standardizzato il C si è pensato che dovesse esistere una modalità testo, che abilita la traduzione automatica degli "a capo" a seconda del proprio sistema operativo, partendo sempre da un "\n" (codice 10). 
dunque nei sistemi operativi unix non c'è differenza tra le due modalità, mentre su windows gli "a capo" nella modalità testo diventano 13 e 10.
è importante sapere se vogliamo aprire un file in una o l'altra modalità perchè, se il file che stiamo aprendo non contiene testo ma lo stiamo aprendo in modalità testo, se viene letto un byte con dentro 10 questo su windows verrà trasformato in 13 10, rovinando la lettura. quindi, a parte se stiamo lavorando con un file di testo, è sempre meglio aprirli in modalità binaria.

la prima funzione da sapere per lavorare coi file è  quella per aprire un file, cioè la **fopen()**:
```
FILE *fopen(const char *filename, const char *mode);
```
filename è una stringa che contiene il nome del file da aprire, in formato di percorso assoluto (es: "C:\users\paolo\documenti\prova.txt", qui prova.txt è il nome *relativo* del file, e questo lo posso usare il programma si trova nella stessa cartella del file; per alla cartella precedente rispetto a quella in cui si trova il programma, posso scrivere "..", ad esempio "..\\..\prova.txt"). di default su visual studio ci troviamo nella cartella dove si trova il file project (quindi quella dove ci sono tutti i file)
il parametro mode invece è un'altra stringa che serve ad indicare la modalità di apertura del file, che può essere una delle seguenti:
- "r" apre il file in lettura in modalità testuale. ovviamente il file deve esistere
- "w" apre il file in scrittura in modalità testuale. se il file non esiste, viene creato un file vuoto col nome specificato, altrimenti viene sovrascritto da quello nuovo vuoto
- "a" apre il file in append in modalità testuale, cioè in scrittura posizionandosi alla fine
- "rb", "wb" e "ab" aprono in modalità binaria

quando il file non serve più, non esiste un meccanismo automatico in C che libera la risorsa, quindi esiste la funzione **fclose()**:
```
int fclose(FILE *stream);
```
dobbiamo chiudere i file quando abbiamo finito di usarli perchè il numero massimo di file che si possono tenere aperti contemporaneamente è abbastanza basso. in scrittura è fondamentale chiudere i file, perchè finchè non lo chiudiamo non viene effettivamente salvato nulla su disco.
a questa funzione passiamo il puntatore a file.

questo esempio di file semplice apre e chiude un file:
```
#include <stdio.h>
int main(void)
{
	FILE *f = fopen("test.txt", "r");
	if (f == NULL) {
		return -1;
	}
	// operazioni su f...
	fclose(f);
	return 0;
}
```

è importante controllare ogni volta il valore restituito dalla fopen perchè se questo è NULL vuol dire che qualcosa è andato storto con l'apertura.

la funzione di lettura più semplice, che legge un solo byte dallo stream, è la **fgetc()**, che può restituire, oltre al byte letto, un valore negativo (-1) per segnalare che è fallita la lettura
```
int fgetc(FILE *stream);
```
bisogna sempre associarlo a un int perchè ci permette di distuinguere i casi in cui è stato ritornato -1 da tutti gli altri

attenzione: scrivi \#define \_CRT_SECURE_NO_WARNINGS_ all'inizio di ogni file, oppure cambia le impostazioni di visual studio (cerca su google)

```
#define _CRT_SECURE_NO_WARNINGS_
#include <stdio.h>

int main(void){
	FILE *f;
	f = open("input.txt", "r");
	if (f==NULL){
		return EXIT_FAILURE;
	}
	
	char x[10]=""; //per riempirlo di zeri
	size_t n = 0;
	
	while(n<10){
		int s=fgetc(f);
		if(s==EOF){
			break;
		}
		x[n]=s;
		n++;
	}
	
	fclose(f);
	return EXIT_SUCCESS;
}
```

è utile ricordarsi la sequenza *leggi, controlla, usa* durante la lettura di file

posso anche scrivere questo:
```
#define _CRT_SECURE_NO_WARNINGS_
#include <stdio.h>

int main(void){
	FILE *f;
	f = open("input.txt", "r");
	if (f==NULL){
		return EXIT_FAILURE;
	}
	
	char x[10]=""; //per riempirlo di zeri
	size_t n = 0;
	int s=fgetc(f);
	
	while(n<10 || s!=EOF){
		x[n]=s;
		n++;
		s=fgetc(f);
	}
	
	fclose(f);
	return EXIT_SUCCESS;
}
```

