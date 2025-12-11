slide **Compilazione condizionale** e successive in Preprocessore e compilazione (sono entrato in ritardo dioc)

negli header non è possibile dichiarare più volte una stessa variabile. per evitare questo problema possiamo dire al nostro programma di ignorare la seconda dichiarazione, tramite un *include guard*, che fondamentalmente fa sì che se esiste già una dichiarazione, non se ne faccia un'altra.
se vogliamo usare un header nella nostra libreria, dobbiamo sempre come prima cosa includere l'header corrispondente. 
la slide **L'include guard (5)** è assolutamente fondamentale.

se per esempio abbiamo un header radice.h, dovremo scrivere questo al suo interno:

```
if !defined RADICE_H
#define RADICE_H

extern double radq(double a);

endif /*RADICE_H*/
```

nel programma radice.c

```
#include "radice.h"

double radq(double a){
	...
}
```

e nel programma c

```
#include "radice.h"
```

invece di scrivere tutto, volendo potremmo scrivere solo \#pragma once, ma dobbamo sapere comunque cosa in realtà stiamo scrivendo (quindi dobbiamo scrivere tutto)

attenzione al tipo di dato che si usa nei for, che deve corrispondere al tipo di dato che dobbiamo confrontare.

per i prossimi esercizi, invece di scrivere tutto in un solo programma separa la funzione e il main attraverso un header.


simile a malloc() è la funzione **calloc()**:
essa azzera la memoria quando allochiamo la memoria, a differenza di malloc che riempie la memoria allocata di roba a caso, finchè non ci mettiamo quello che vogliamo noi. inoltre la sintassi è un pelo diversa, si scrive così:
```
void* calloc(size_t num, size_t size);
```
quindi fondamentalmente con una virgola invece della moltiplicazione
in genere calloc è meglio per questa sua funzione di azzeramento della memoria.


mettiamo caso di voler aumentare di 1 la dimensione di un vettore: dobbiamo eseguire le seguenti operazioni (**Cambiare la dimensione della memoria allocata**):
- faccio una nuova malloc di n+1 elementi
- copio i dati precedenti nella nuova memoria
- libero la memoria vecchia
- aggiungo il nuovo elemento alla memoria nuova
- cambio il puntatore, che dovrà puntare alla memoria nuova

questo metodo è tuttavia parecchio inefficiente, perchè ci obbliga a spostare tutti i dati da una memoria vecchia a una nuova solo per aggiungere un nuovo elemento

la funzione **realloc()** ci permette di ridimensionare una memoria, cioè cambiare la dimensione di una malloc che abbiamo fatto in precedenza. attenzione però: una realloc restituisce un puntatore alla nuova memoria che ha allocato, ed è indispensabile assegnare questo puntatore a qualcosa, dato che se non riesce a ridimensionare la memoria nello stesso posto di prima, potrebbe dover spostarsi in un altro indirizzo.
la sintassi è la seguente:
```
void *realloc(void *ptr, size_t new_size)
```
che potenzialmente potremmo voler anche usare per diminuire la dimensione di una memoria. come abbiamo detto, se ingrandendo va incontro a una cella di memoria già occupata da qualcos'altro, sposta tutti i dati in un altro indirizzo di memoria (quindi usando il meccanismo a cui avevamo già pensato noi). se non c'è assolutamente spazio per riallocare la memoria, restituisce NULL.

dunque, se volessimo incrementare di 1 la dimensione del vettore puntato da v, potrei scrivere questo:
```
size_t n = 1;
++n;
v = realloc(v, n * sizeof(int));
v[n - 1] = 123; //ho messo un numero nell'indirizzo appena aggiunto
```

scrivere un programma in questo modo teoricamente manderebbe tutto in vacca se finiamo la memoria, dato che v punterebbe a NULL se questo accadesse, perdendo l'indirizzo di memoria dove si trovavano i dati precedenti, ma nel nostro caso non diamo importanza a questa casistica.

ci sono altri esempi di utilizzo nelle slide dei **puntatori seconda parte**, ci potrebbe usare in molti modi la realloc.