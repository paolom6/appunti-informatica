# Il linguaggio C

## Concetti base

Il linguaggio è nato per programmare il sistema operativo Unix in un linguaggio diverso dall'assembly, in modo da non dover cambiare assembly per ogni processore. I software per la traduzione da linguaggio C a linguaggio macchina sono detti compilatori, e prima del 1983 con la nascita del C standard ogni processore ne aveva una varietà leggermente diversa, a discrezione dei produttori di cpu. ovviamente questo causò alcuni problemi dato che si doveva far fronte alle differenze sviluppate in 10 anni. ora siamo al C23, lo standard più recente.

C è di alto livello dato che comunque non si tratta di linguaggio macchina, ma è anche di basso livello perchè è possibile fare riferimento alle celle di memoria, come una specie di assembly leggermente più evoluto.

un programma C è formato da dichiarazioni e direttive per il preprocessore (per il momento ignoriamo le direttive per il preprocessore). esistono due tipi di dichiarazioni: le definizioni, che quindi oltre a dichiarare che qualcosa esiste la definisce, e ciò che invece dichiara l'esistenza di qualcosa ma non dice cosa. per ora guarderemo solo le definizioni.

una variabile sappiamo già che è una cella o più celle di memoria che contengono dati. in ade8 non definivamo le variabili, ma davamo solo un nome alle celle; in C definiamo il nome di una variabile, senza sapere la cella di memoria dove verrà memorizzata, e possiamo anche definire il **tipo** della variabile (quindi decidere se sarà con segno o senza segno, a 16 o a 32 bit, e altre cose)
i tipi di variabili possono essere:
- numeri interi (ce ne sono 8 tipi, scritti nella slide **I tipi di dati numerici interi**, che possono essere a 8, 16, 32 o 64 bit) dove posso specificare se ha segno o no (unsigned). possono avere nome diverso in base al nome: i char sono di 1 byte, gli short sono di 2 byte, gli int sono di 4 byte e i long long sono di 8 byte. **attenzione**: il char non è un carattere, infatti in C non esiste un tipo di dato specifico per il testo (come possono esistere in js o in python)
- numeri in virgola mobile (esistono i float, che hanno 4 byte e quindi sono a 32 bit, e i double, che hanno 8 byte e quindi sono a 64 bit). questi sono codificati secondo lo standard IEE 754, che andrà saputo all'esame

per definire una variabile la sintassi è:

```
<tipo> <nome variabile> ;
```

il punto e virgola serve a indicare la fine della cosa che stiamo scrivendo, in questo caso la fine della definizione. alcuni esempi possono essere: 

```
char c;
short s;
int i;
long long numero;
float f;
double radice;
```

i caratteri utilizzabili per dare un nome a una variabile sono: lettere maiuscole e minuscole, numeri, underscore ( _ )
l'unico vincolo è che non può iniziare con un numero, dato che le sequenze che iniziano con un numero sono costanti numeriche. esse possono essere:
- decimali: iniziano con una cifra d 1 a 9 e continuano con altre cifre da 0 a 9
- ottali: cominciano con 0 e proseguono con altre cifre da 0 a 7
- esadecimali: cominciano con 0x e proseguono con altre cifre da 0 a 9 e con le lettere (maiuscole o minuscole) da a ad f
- binario: cominciano con 0b e proseguono con 0 e 1

per esempio, 0x123 sarebbe 291 in base 10
oppure 0123 sarebbe 83 in base 10

dunque ogni espressione ha un tipo, di quelli che abbiamo visto prima:
- un numero intero è sempre di tipo **int**, che può essere signed o unsigned (diventa unsigned se metto una u dopo il numero, anche se non lo faremo mai)
- un numero con la virgola è sempre di tipo **double**, che in C andrà espresso con il punto decimale (per esempio non si scrive 3,14, ma 3.14) (se vogliamo fare un float, aggiungiamo una f dopo il numero, anche se non lo faremo mai)
è anche possibile usare la notazione scientifica, aggiungendo una e con l'esponente di 10 che vogliamo usare (per esempio, 123 possiamo scriverlo 1.23e2)

per scrivere caratteri ASCII possiamo fare come in ade8, ovvero usare gli apici ''. ovviamente tutte le espressioni tra singolo apice sono ancora di tipo int, non char. se volessi andare a capo, che ha codice 0x10, devo usare il backslash \ (che significa che sto per usare un codice speciale) e un determinato codice speciale, in questo caso n. guarda la slide **Sequenze di escape**

quando dichiaro una variabile senza inizializzarla (quindi definirne il contenuto), posso scrivere così:

```
<tipo> <nome-variabile> = <espressione> ;
```

altrimenti, se non inizializzo la variabile, nella cella a lei riservata viene messo un numero a caso. (guarda la slide **Inizializzazione di variabili**)

ci sono alcune regole sintattiche per le espressioni che possiamo associare a una variabile, definite nella slide **Espressioni nel linguaggio C**. per operatore binario intendiamo fondamentalmente cose come gli operatori matematici (tipo * o +), mentre con operatore unario prefissi intendiamo solo quelli che possiamo mettere prima di un'espressione (quindi - e +), e con quelli postfissi intendiamo quelli che mettiamo dopo; le parentesi hanno lo stesso significato matematico

in C le espressioni possono "valere qualcosa", ma possono anche "fare qualcosa". le espressioni matematiche valgono qualcosa e non fanno nulla, come le espressioni "21", "numero", o "3.7f". inoltre, le espressioni che valgono qualcosa hanno anche un tipo (int, double, ecc)
ecco alcune definizioni con inizializzazioni:
```
char c = 21;
short s = 0xffff;
int i = '7';
long long numero = 1234567890123;
float f = 3.141592f;
double radice = 1.4142135623730950488016887242097;
```
quindi posso decidere di che tipo rendere qualsiasi espressione:
char c = 21 mi permette di inserire quello che normalmente dovrebbe essere un int (a 32 bit) in un char (a 8 bit), inserendo nell'unico byte disponibile quello meno significativo disponibile (per esempio, se faccio char c = 256, c sarà 0).
short s = 0xffff significa che s vale -1, dato che è uno short signed.
int i = '7' significa che i vale il codice ascii di 7

è possibile definire una variabile di sola lettura mettendo const davanti alla dichiarazione:
```
const <tipo> <nome-variabile> = <espressione>;
```
in questo modo non posso mai modificare questa variabile (ma non è una costante)

posso anche definire più variabili in una stessa riga:
```
int i, j, k;
char a = 9, b = 23, c = 12;
short s1, s2 = 33, s3;
```

### Le funzioni

Un programma C è sempre un elenco di definizioni, racchiuse dentro sottoprogrammi detti *funzioni*. Le funzioni vengono definite con un tipo (ovvero il tipo che la funzione restituisce), il nome e delle parentesi tonde, che sono ciò che le distingue dalle variabili. dentro le parentesi tonde ci metto dei parametri, cioè dei valori che utilizzeremo dentro la funzione. finita la definizione dei parametri, posso mettere dei comandi in linguaggio C, all'interno di parentesi graffe. ecco un esempio:
```
<tipo-di-ritorno> <nome-funzione> ( <parameteri> ) {
	<comandi>
}
```
