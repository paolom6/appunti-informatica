## Puntatori

il concetto di puntatore è fondamentale non solo in assembly, ma in tutta l'informatica. in C inoltre, non basta introdurre il concetto di semplice puntatore, ma bisogna associargli anche un tipo di dato. ricordiamo che un puntatore è una variabile che contiene l'indirizzo di un'altra variabile. 
distinguere il tipo del puntatore è fondamentale perchè questo potrebbe puntare anche a delle variabili che occupano più di una cella di memoria (quindi a più di 8 bit).
non basta sapere che una variabile è un puntatore, ma dobbiamo sapere anche a quale tipo di variabile questa sta puntando

fino a qualche anno fa la maggior parte dei software erano a 32 bit, quindi erano in grado di utilizzare massimo 4 gb di ram. oggi invece siamo passati a 64 bit, quindi siamo in grado di utilizzare 16 miliardi di miliardi di byte.
visto che deve essere in grado di puntare a 2^64 celle di memoria diverse, i puntatori sono a 8 byte (64 bit)

l'indirizzo contenuto nel puntatore quindi sarà il primo indirizzo della nostra variabile, indifferentemente da quanto è grande il tipo di dato. sapendo quanto è grande il tipo di dato, il puntatore saprà quanti byte andare a prendere dopo l'indirizzo specificato.
essendo tutti i computer moderni in little endian, la cifra meno significativa andrà nell'indirizzo di memoria più basso.

il puntatore viene definito come qualsiasi variabile, in questo modo:
```
<tipo> *<nomevariabile>;
```
dove l'asterisco è un modificatore della variabile. attenzione, se definisco in questo modo:
```
char* p,q;
```
p è un puntatore a char, mentre q è un char normale. è buona norma mettere il modificatore attaccato alla variabile che vogliamo rendere un puntatore. 
nel caso di
```
int *a;
```
il puntatore è grande 8 byte (e sarà sempre grande uguale) mentre la variabile a cui punta è 4 byte

per utilizzare i puntatori, quindi per puntare a una variabile, si utilizza la seguente sintassi:
```
&<nome variabile>;
```
con cui associamo al puntatore l'indirizzo del primo byte della variabile da puntare. grazie al tipo di puntatore, questo saprà anche quanti byte successivi andare a considerare
in un programma vero:
```
int main(void)
{
	char x = 3;
	char *p;
	p = &x; //è sempre un expression statement
	return 0;
}
```
in questo modo p è un puntatore che contiene l'indirizzo di x. si dice che p punta a x.

per utilizzare un puntatore, cioè per leggere cosa contiene la variabile a cui il puntatore sta puntando, c'è la seguente sintassi:
```
*<variabile di tipo puntatore>
```
visto in un programma vero:
```
int main(void)
{
	char x = -27;
	char *p = &x; // p è di tipo "puntatore a char" (char*)
	int b;
	*p = -80;
	b = x;
	return 0;
}
```
quando arrivo al return, la b varrà -80, cioè il valore di x, che è stata modificata nella linea sopra dal puntatore. questo ci fa capire che una modifica alla zona di memoria a cui punta il puntatore, modifica proprio la variabile puntata.
p, in quanto puntatore a 64 bit, è sempre grande 8 byte, mentre x è 1 byte.
l'indirizzo di una variabile ha come tipo "puntatore a (tipo di variabile)". quindi &x, e quindi p, è di tipo puntatore a char.
\*p possiamo definirlo come "la cosa puntata da p", che in questo caso è la variabile x. \*p non è solo uguale a x, ma è proprio x.

scrivi -80 in complemento a 2 in 1 byte:

256-80 = 176 -> b0

considerando che b è un int, quindi occupa 4 byte, le sue celle di memoria saranno così:
|b0|, |ff|, |ff|, |ff|
dato che siamo in little-endian, dobbiamo convertire il -80 da 1 byte a 4 byte, e quindi devo mettere un ff in tutti i byte precedenti. il byte meno significativo (b0) viene messo all'indirizzo di memoria più piccolo, dato che il numero scritto "in ordine" sarebbe ffffffb0.

in visual studio per vedere gli indirizzi di memoria si può andare in debug -> windows -> memory (o fare alt+6)
per vedere l'indirizzo di una variabile, posso anche scrivere &\<nome variabile>.

ma realmente, a cosa possono servire i puntatori? 
per prima cosa, consentono di modificare le variabili passate tramite parametro. prendiamo come esempio questo programma sbagliato:
```
int y = 7;
void raddoppia (int x) {
	x = x * 2;
}
int main(void) {
	raddoppia(y);
	return 0;
}
```
in questo programma, alla fine y continua a rimanere 7, dato che y e l'x parametro della funzione sono due variabili diverse. per farlo funzionare, posso far sì che x sia un puntatore a x:
```
int y = 7;
void raddoppia (int *x) {
	*x = *x * 2;
}
int main(void) {
	raddoppia(&y);
	return 0;
}
```
qui sto passando come argomento della funzione l'indirizzo di y, e nella funzione stiamo modificando il parametro, che è un puntatore a int. in questo modo \*x sta puntando a y, e quindi la variabile viene effettivamente modificata.

possiamo anche usare i puntatori per far ritornare a una funzione più di un valore, oppure per usare più variabili che devono essere modificate per dei calcoli.
per fare un semplice scambio di variabili, possiamo fare in questo modo: 
```
void swap(unsigned int *a, unsigned int *b) {
	unsigned int tmp = *a;
	*a = *b;
	*b = tmp;
}
```
in modo da modificare effettivamente gli indirizzi di memoria che poi verranno passati come argomenti nella chiamata di funzione, che, se vogliamo scambiare i valori di due ipotetici int m e n fuori dalla funzione swap, dovrà essere swap(&m, &n)

quando si usano i puntatori, è fondamentale capire cosa sta succedendo a livello di memoria.
assegnare un valore a un puntatore (quindi senza asterisco) significa cambiare il posto dove sta puntando, non significa cambiare il valore contenuto in quel posto. 

attenzione ai tipi:
- se abbiamo la variabile x di tipo T, l’espressione &x è di tipo T* (puntatore a T);
- se abbiamo la variabile p di tipo T*, l’espressione \*p è di tipo T (la variabile puntata da p).
- se abbiamo la variabile p di tipo T*, l’espressione &p è di tipo T** (puntatore a puntatore a T… argh!).
- se abbiamo la variabile x di tipo T, l’espressione \*x non ha senso (errore)!

guarda le ultime slide dopo **Altre accortezze**
