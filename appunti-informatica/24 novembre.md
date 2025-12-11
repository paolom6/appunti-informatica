il corrispondente in scrittura di fgetc() è la funzione **fputc**():
```
int fputc(int ch, FILE *stream);
```
che ha un funzionamento analogo a fgetc() per quanto riguarda il valore sostituito

esiste un'altra funzione che ci permette di leggere direttamente una stringa da file, la **fgets**():
```
char *fgets(char *str, int count, FILE *stream);
```
che prova a leggere dal file puntato da stream un certo numero di caratteri peri a count-1, e li scrive nell'array puntato da str.
se durante la lettura si incontra un "a capo" o la fine del file, la lettura si ferma anche se non si è arrivati a count-1. in caso di successo la funzione ritorna una copia del puntatore str, altrimenti ritorna NULL.
dopo la lettura il cursore si sposta in avanti del numero di byte letti

naturalmente esiste anche il corrispondente di fgets() in scrittura, ovvero **fputs**():
```
int fputs(const char *str, FILE *stream);
```

ogni programma all'avvio viene dotato di tre file già aperti, ovvero gli stream standard. questi sono:
- **stdin** è un file aperto in lettura per ricevere input, che solitamente legge dalla console, ovvero la finestra del terminale, dove il testo viene utilizzato come buffer di lettura ogni volta che premiamo invio sulla tastiera. per terminare la lettura di stdin, è possibile digitare ctrl+z e invio su windows e ctrl+d su linux
- **stdout** e **stderr** invece scrivono sulla console
volendo posso modificare i file di input e output mettendo < o > quando eseguo il programma. (ad esempio, se scrivo "main.exe < input.txt" l'input verrà preso da questo file)

per eliminare il "\n" da una stringa, posso scrivere questo codice:
```
riga[strcspn(riga, "\n")] =  0;
```
dove strscpn() restituisce un puntatore alla prima occorrenza di un certo carattere in una stringa, e se non lo trova restituisce un puntatore al terminatore. in questo modo, che ci sia o non ci sia il "\n", viene eliminato e non cambia nient'altro.

esiste nella libreria standard del C anche una funzione che ci permette di creare output formattato, ovvero **fprintf()**:
```
int fprintf(FILE *stream, const char *format, ...);
```
dove i ... alla fine sono effettivamente parte della sintassi, dato che indicano che oltre ai primi due parametri possono comparirne altri, in numero variabile
il parametro stream è il puntatore al file su cui vogliamo scrivere la stringa.
il parametro format è una stringa C che rappresenta il modo in cui vogliamo formattare la stringa da scrivere sul file. 
dopo format vengono passate tutte le variabili che verranno usate per comporre la stringa risultante
la funzione restituisce un intero che contiene il numero di caratteri scritti sul file, oppure un valore negativo se si è verificato un errore

dentro la stringa format andremo a mettere delle sequenze speciali di caratteri (che iniziano col carattere '%') che ci permettono di scegliere la rappresentazione della stringa risultante (slide **Il parametro format della fprintf()**)
esempio:
```
int x = 97;
fprintf(stdout, "La variabile vale %d\n", x);
```
scrive in output "La variabile vale 97"
dentro il format possiamo anche mettere dei modificatori, ovvero length, precision e width (guarda sulle slide)

un'altra funzione fondamentale è **fscanf()**, ovvero il corrispondente in lettura di fprintf():
```
int fscanf(FILE *stream, const char *format, ...);
```
dove tuttavia il format funziona in modo diverso rispetto alla fprintf().
alla fscanf innanzitutto passiamo dei puntatori, non delle variabili, e il suo valore di ritorno è un intero che rappresenta il numero di parametri letti correttamente, oppure EOF se la lettura fallisce prima di leggere il primo parametro
leggi il funzionamento nelle slide sono bollito