nella slide **Esempi di do...while** è mostrato il ragionamento dietro a un programma che calcoli la radice quadrata di un numero, utilizzando l'algoritmo di Newton per gli zero di una funzione, quindi trovano gli zeri di *f(x)=x^2 - a* tramite il metodo di bisezione
per fare ciò possiamo partire con l'approssimazione x0=a e avvicinarsi alla soluzione con la successine xn mostrata nella slide, facendo un ciclo che va avanti finchè l'approssimazione non diventa abbastanza precisa da produrre due valori uguali uno dopo l'altro.
dunque dobbiamo fare un ciclo che va avanti finchè il valore non diventa uguale al precedente, e dato che non esiste un valore precedente a x0, invece di dare un valore a caso a t è comodo utilizzare un do...while
il codice finale sarà questo:
```
double radq(double a)
{
	double t, x = a;
	if (x <= 0.) {
		return 0.;
	}
	do {
		t = x;
		x = 0.5 * (t + a / t);
	} while (x != t);
		return x;
}

int main(void)
{
	double d = radq(137.0);
	return 0;
}
```

facciamo un altro esempio: vogliamo calcolare la somma dei primi n numeri naturali. il programma è abbastanza semplice e si può fare così:
```
unsigned int somma_primi (unsigned int n)
{
	unsigned int s = 0;
	unsigned int i;
	i = 1;
	while (i <= n) {
		s = s + i;
		i = i + 1;
	}
	return s;
}
int main(void)
{
	unsigned int x;
	x = somma_primi(10);
	return 0;
}
```
qui sono evidenti le 4 fasi del ciclo while: 
- i=1 è l'init
- while (i<=n) è il check
- s=s+1 è il body
- i=i+1 è l'update

tuttavia, esiste un comando chiamato **for** che sostanzialmente è un while scritto diversamente, dove possiamo racchiudere dentro le parentesi tonde del comando le fasi init, check e update, in questo modo:
```
for (init; check; update)
{
	body
}
```
il while scritto sopra diventerà:
```
for (i=1; i<=n; i=i+1){
	s=s+i;
}
```
e fa la stessa identica cosa

non ci interessa il valore di i=1 (che vale semplicemente 1), ma ci interessa quello che fa
attenzione a differenziare il **valore** di un'espressione e **ciò che fa**.
allo stesso modo, è inutile anche il valore dell'espressione i=i+1
le espressioni di init e update servono a fare qualcosa, se non modificano il valore di una variabile sono assolutamente inutili
invece, il valore dell'espressione i<=n, cioè del check, serve al for per capire se continuare il ciclo oppure no.

mentre nel while se non mettiamo il check il compilatore da errore, se non metto niente nel check del for il body viene eseguito all'infinito senza dare errori (questa è l'unica vera differenza tra while e for)

la somma dei numeri naturali con il for diventa così:
```
unsigned int somma_primi (unsigned int n)
{
	unsigned int x = 0;
	unsigned int i;
	for (i = 1; i <= n; i = i + 1) {
		x = x + i;
	}
	return x;
}

int main(void)
{
	unsigned int x;
	x = somma_primi(10);
	return 0;
}
```

l'operazione di incremento ha un operatore apposito per fare il +=1 (il **++**).
il suo comportamento è descritto nella slide **Incremento e decremento**, che non è scontatissimo:
- i++ è il postincremento
- ++i è il preincremento
entrambi incrementano il valore di x (x+=1), ma l'espressione di postincremento vale x, mentre quella di preincremento vale x+1
cambia quindi il valore di x rispetto a prima di aver eseguito l'espressione

la stessa cosa accade con l'operatore di decremento (**--**)

generalmente non si usano mai il preincremento e il predecremento, dato che creano spesso dei problemi
ma anche il postincremento da problemi, guardiamo il codice:
```
i=2;
a=i++ * i++;
```
questo produce un **Undefined behavior**, dato che il compilatore non sa quando bisogna fare l'incremento 
perciò non bisogna **mai** modificare il valore di una variabile più volte nella stessa espressione, sia col pre che col post incremento

è valida invece la seguente espressione:
```
int y=4;
int z=5;
int x;
x = ++y * z++;
```
dove x varrà 25, dato che sto preincrementando y, che diventa 5 prima dell'esecuzione dell'espressione, mentre z diventa 6 solo dopo l'esecuzione dell'espressione.
espressioni di questo tipo non andrebbero comunque mai scritte

nei for, potremmo usare ++i o i++ indifferentemente, dato che il valore dell'espressione è inutile, e i due incrementi **fanno la stessa cosa**.

x+=i viene eseguito n volte
i<=n viene eseguito n+1 volte
i=n+1 alla fine del ciclo

dal c99 l'init non deve più essere un espressione all'interno di un for, ma può essere anche una definizione. quindi se la variabile i ci serve solamente per fare il for, possiamo scrivere questo:
```
for (unsigned int i = 1; i <= n; ++i) {
	x += i;
}
```
in modo che quella i esista solo all'interno del for. quindi i, fuori dal for, non esiste più e non può essere usato

esistono alcuni operatori particolari (utilizzati veramente poco) che servono più che altro a saper leggere un codice che li utilizza (quindi noi non li useremo mai). sono dalla slide **Ancora operatori** in poi, tra cui anche alcuni **operatori per lavorare con i bit** (importanti).
oltre a quelli classici (and, or, xor, not) ci sono anche gli shift, che servono a spostare tutti i bit dei tipi interi verso destra (>>) o verso sinistra (<<), con i corrispettivi assegnamenti composti <<= e >>= (in base due significa dividere o moltiplicare per 2)
quando non ho più posto per spostare le cifre, le elimino.

x: 0011.0000
y: 1111.1000

x >>= 1 : 0001.1000 (18h)
y <<= 2 : 1110.0000 (e0h)