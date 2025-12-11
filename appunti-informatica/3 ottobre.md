### Da assembly a linguaggio macchina

quando scrivo LD A, A non sta facendo riferimento al contenuto della cella A, ma sta solo facendo riferimento alla cella 08h. quindi tutto ciò che ho fatto è stato associare il nome A alla cella 08h. lo stesso vale per B e C, e nella C, che mi serve solo per contenere il risultato dell'operazione, faccio riferimento alla cella 00h, dato che tanto non mi serve a niente fare riferimento a un'altra cella.

se vogliamo scrivere un numero in assembly, è fondamentale cominciare con uno zero, per far capire all'assemblatore che quello è un numero.

scrivi un programma che dato un numero in memoria (A) ne calcola il valore assoluto e lo mette all'indirizzo B.

LD A
CMPv 0
JLs Negativo (in questo caso al posto di JLs potremmo usare JN, dato che A-0 rimane sempre A)
JMP Positivo

Positivo:  LD A
        ST B
        JMP Fine
Negativo: LD A
		 NEG
		 ST B
		 JMP Fine
Fine: JMP Fine

A: -7
B: 0

possiamo fare alcune modifiche per rendere il programma più veloce: 
- alla fine, visto che c'è scritto JMP Fine due volte di seguito, possiamo togliere quello dentro a Negativo, visto che tanto il program counter va avanti da solo
- i due LD A all'inizio di entrambe le funzioni non servono a nulla, dato che comunque l'unico numero che rimane caricato sull'accumulatore è A
- possiamo togliere il JMP a Positivo, dato che comunque è l'istruzione successiva
- potremmo anche rendere lo store una funzione a parte, invece di ripeterla per entrambe le funzioni

in questo modo il programma migliorato diventerebbe così

LD A
CMPv 0
JLs Negativo

Positivo:
Store
JMP Fine

Negativo: 
NEG
Store

Fine: JMP Fine
Store: ST B

A: -7
B: 0


associando le celle di memoria a delle lettere o delle funzioni, abbiamo usato delle **variabili** 

volendo possiamo creare la moltiplicazione, utilizzando la definizione di moltiplicazione, e quindi sommando il primo fattore tante volte quanto indicato dall'altro fattore. sostanzialmente, a x b è la sommatoria per i=1 che arriva a b di a. per realizzarla, dobbiamo creare un ciclo

LD C

JMP Controllo
Ciclo:             LD C
			ADD A
			ST C
			LD i
			ADDv 1
			ST i
			JMP Controllo
Controllo:      LD i
			CMP B
			JE Fine
			JMP Ciclo
Fine:              JMP Fine

A: 5
B: 3
C: 0
i: 0

così è come l'avevo pensato io, mentre di seguito metto la versione fatta bene con le cose in ordine per massimizzare l'efficienza (è la stessa cosa)

Ciclo:
LD i
CMP B
JE Fine
LD C
ADD A
ST C
LD i
ADDv 1
ST i
JMP Ciclo

Fine: 
JMP Fine

A: 5
B: 3
C: 0
i: 1

sulle slide c'è una versione alternativa, dove invece di fare un contatore che aumenta, ne faccio uno che diminuisce

con questo esempio, abbiamo visto un esempio di iterazione in informatica, cioè la capacità di ripetere una cosa più volte (in questo caso, fare un jump all'indietro per rifare delle operazioni più volte) e avere anche un meccanismo per uscire dal ciclo.

per l'esame dobbiamo saper scrivere tutte ste istruzioni in linguaggio macchina
dobbiamo iniziare con l'associare le nostre variabili a delle celle di memoria, quindi scrivere esattamente a cosa corrispondono Inizio, Fine, A, B e C della slide **La moltiplicazione intera**.

Inizio: 00h
Fine: 14h
A: 16h
B: 17h
C: 18h

una volta che so questi, devo sostituire le etichette, sia delle variabili che delle operazioni:

00:(Inizio) LD 17
02: CMPv 0
04: JE 14
06: LD 18
08: ADD 16
0A: ST 18
0C: LD 17
0E: SUBv 1
10: ST 17
12: JMP 0
14:(Fine) JMP 14
16:(A) 3
17:(B) 5
18:(C) 0

prova a fare a casa questo:
Si calcoli la somma dei numeri da 1 a N (variabile in memoria), e si metta
il risultato in una variabile S. L’operazione si può fare con 8 bit solo se
𝑁 ≤ 22.

ci sono altri esercizi nella slide **Altri esercizi**
dopo prova a scriverli anche in linguaggio macchina

per fare il controllo di A se è pari, ricordati che i numeri sono in binario (quindi se l'ultima cifra è 1 sarà dispari) e delle istruzioni and, not, ecc