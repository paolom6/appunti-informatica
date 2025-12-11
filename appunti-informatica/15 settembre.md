le slide sono disponibili su moodle, dove c'è un sacco di altra roba tra cui videolezioni

# presentazione del corso

simbolo di sommatoria (la E strana con una i = x sotto) significa sommare i numeri che vanno da x a un altro numero (cercatela un attimo)

il corso è principalmente alcune cose di base di informatica e programmazione in C, usando Microsoft VisualStudio (non vs code), dato che ha un buon debugger ed essendo studente è gratuito andando su https://portal.azure.com

non iniziamo con input/output, al fine di capire veramente cosa stiamo scrivendo e cosa sta succedendo nel programma tramite un debugger

non esistono delle lezioni integrative, tutte le lezioni sono parti del corso (quindi il laboratorio non è semplicemente una pratica di ciò che viene spiegato in aula). l'opis sbaglia in questo

per superare l'esame bisogna per forza programmare, non basta studiare

### Libro di testo

va bene qualunque libro di testo, però è consigliato **Programmare in C** di Tullio Facchinetti di Maggioli Editore

vanno bene anche dei libri gratis su internet

lo stesso per il libro degli esercizi, ma è consigliato **Esercizi di Programmazione in linguaggio C: 80 problemi e soluzioni commentate** di Costantino Grana.

durante l'esame si può usare una reference alla libreria di C con tutte le funzioni principali

***

il materiale didattico sta su doodle, ma il vero sito fondamentale da usare è https://olj.ing.unimore.it, dove si vedono gli esami dati in precedenza che andrebbero risolti in 2 ore

### Orario delle lezioni

che non sono obbligatorie

lunedì: 10:00-12:00
mercoledì: 14:00-18:00
venerdì: 08:00-10:00

#### Variazioni orario

prime due settimane il lunedì
3-7 novembre: pausa delle lezioni per appelli intermedi di analisi e geometria
8 dicembre: no lezione

***

### Modalità d'esame

esame di "teoria" con test a crocette da 1 ora
prova di programmazione in laboratorio da 2 ore

la teoria deve essere superata per accedere alla prova di programmazione, ma il voto finale è la media delle due prove

nel caso di questo corso, se si rifiuta un voto si può poi decidere successivamente di verbalizzarlo entro settembre

***

## Contenuto del corso

### Linguaggio C

**perchè fa cagare**

non esiste un tipo di dato specifico per le stringhe in c
ogni operazione vuole che si usi una funzione
gli array devono avere una dimensione fissata al momento della compilazione, quindi fanno cagare
buffer overflow (cercalo)
gli interi sforano e non c'è modo di controllare se ciò è accaduto

**perchè lo studiamo**

serve a capire le basi di tutti i linguaggi moderni, capendo cosa accade veramente nel computer
i programmi scritti in c sono i più veloci in assoluto
pur essendo di basso livello, consente una programmazione strutturata
pur essendo di alto livello, richiede di capire alcuni concetti fondamentali, come memoria, indirizzo, allocazione e deallocazione, richiesta e rilascio di risorse

***

## Informazione

l'informazione ha una caratteristica: non possiamo prevederne il contenuto
gli uomini hanno sempre rappresentato l'informazione, il computer (calcolatore elettronico) è in grado di elaborare informazioni
il computer sa **solo** elaborare informazioni in forma numerica, a partire da numeri, parole, immagini e suoni; teoricamente si potrebbero rappresentare anche odori, sensazioni tattili e sapori

innanzitutto bisogna trovare un modo di rappresentare i numeri 
i romani hanno rappresentato i numeri con I, V, X, ecc, mentre noi usiamo un sistema posizionale, in cui i simboli (o cifre) cambiano valore in base alla posizione che assume nel numero.
è fondamentale la **base** a cui si fa riferimento: nel nostro sistema posizionale di tutti i giorni usiamo la base 10

consideriamo i numeri naturali, che chiamiamo **interi senza segno** (guarda la slide ***Sistema posizionale***). normalmente nel sistema posizionale moltiplichiamo la base 10 per la potenza di 10 della posizione della nostra cifra. la cifra che utilizziamo deve essere minore della base, il che significa che c'è un solo modo per scegliere un determinato numero. per esempio, se utilizzassi la base 4, potrei utilizzare solo le cifre 0, 1, 2, 3. 103 in base 4 è uguale a 19 in base 10. i numeri in altre basi le leggiamo leggendo le cifre (quindi 123 è uno due tre, non centoventitre)
il computer **non** fa i conti in base 10, ma bensì in **base 2**
la base più piccola che possiamo usare per un sistema posizionale è la base 2, dove usiamo solamente 0 e 1
quindi tutti i calcolatori moderni usano la base 2, dove ogni cifra binaria è detta **bit**, e un gruppo di 8 bit è detto **byte**
storicamente si è decisa la base 2 perchè è molto più semplice distinguere gli stati elettronici, che in questo modo sono solamente 0 o 1
per facilitare la lettura di bit, questi vengono raggruppati a 4 a 4, per sempio 1.0100.011
**Slide Sistema posizionale e successive molto importanti**

come rappresento 17 in base 5? 32 in base 5
come rappresento 53 in base 6? 125 in base 6
come rappresento 138 in base 7? 255 in base 7

visto che esiste una sola soluzione, deve esistere un modo deterministico per ottenerla, cioè un **algoritmo**

in questo la conversione da una base all'altra è simile alla divisione intera: nella divisione intera entrano due numeri e ne escono altri due, quindi ci sono due risultati. 
dati il numero x e il divisore d (quindi voglio dividere x per d), bisogna trovare il quoziente q e il resto r, tali che: x = q * d + r
quando scrivo la matematica in questo modo, quindi senza assegnare dei valori, le formule valgono indipendentemente dalla base: quindi qui x, d e q non hanno una base

nella slide ***Ottenere la rappresentazione in una base b*** c'è scritto l'algoritmo per ottenere la rappresentazione in una base b. l'ultimo passaggio della prima slide serve a riscrivere il numero diviso per 10 tra le parentesi, tenendo fuori le unità. quindi se prendo un numero e lo divido per la sua base, il resto sono le unità (quindi ciò che sta fuori da quella parentesi)
per capirci:
137 : 10 = 13 con resto di 7
13 : 10 = 1 con resto di 3
1 : 10 = 0 con resto di 1
quindi posso ripetere l'algoritmo che divide per la base per ottenere le cifre del numero nella base che voglio
tornando a uno degli esempi precedenti:
138 : 7 = 19 con resto di 5
19 : 7 = 2 con resto di 5
2 : 7 = 0 con resto di 2
quindi unendo i resti ottengo il numero che avevo già calcolato prima (255), quindi l'algoritmo funziona
se volessi usare quest'algoritmo in base 2, il procedimento sarebbe particolarmente semplice dato che se il numero è pari il resto è 0, mentre se è dispari è 1.
proviamo col 323
323: dispari quindi resto 1
161: 1
80: 0
40: 0
e così via fino a 
1 : 2 = 0 con resto 1
e qua ho finito. il risultati finale è 101000011 in base 2
11010 in base 2 vale 26 in base 10
per fare questi calcoli è utile ricordarsi le potenze di 2, sono particolarmente significative 2 alla 8, 2 alla 10 e 2 alla 16:
2 alla 8 perchè con un byte, che sono 8 bit, posso rappresentare 256 combinazioni diverse
2 alla 10 perchè 1024 è un kb, che è molto vicino al kilo normale che sarebbe 1000
2 alla 16 perchè sono le combinazioni ottenibili con 2 byte, che sono 65536

unità di misura utili:
kilo = 1000 (10^3), in binario possiamo dire 2^8, che sono 1024 quindi un Ki
mega = 1000 k (10^6), in binario 2^16 che sono un Mi
giga = 1000 m (10^9), in binario 2^24 che sono un Gi
tera = 1000 g (10^12) in binario 2^32 che sono un Ti

tuttavia i numeri binari da usare sono molto scomodi per rappresentare numeri grandi, per questo si usano la base 8 e 16, che sono facilmente riconducibili alla base 2

la base 8 non è più utilizzata in quasi nessun caso, che ad oggi ha più un'importanza storica
per ogni combinazione bit di 3 cifre, esiste una corrispettiva base 8
per esempio 101110 sono due terzine (che devo prendere partendo da destra), 101 e 110, dove posso usare la base 8 per scriverlo 56.

la base 8 non è comunque così comoda, perchè raggruppando a 3 alla volta non si arriva giusti al byte, quindi a 8 bit. quindi ad oggi la base per rappresentare i bit in maniera più compatta è la base 16, anche detta esadecimale. 
avendo bisogno in questo caso di 16 simboli, dopo il 9 inizio ad usare le lettere. quindi 10 si rappresenta come a, 11 è b, 12 è c, ecc.
16 in base 16 si scrive 10 (è così per tutte le basi)

esiste un modo veloce per scrivere i numeri binari a 4 bit fino a 16 (c'è una tabella da imparare a memoria, slide ***Le basi 8 e 16*** dove vediamo i numeri in base 10, 16 e 2)

tutta sta roba serve per l'esame, soprattutto fare le conversioni. posso guardare gli esempi di esami di teoria su olj

per esempio convertiamo 237
in binario diventa: 1110.1101 (11.101.101)
237: 1
118: 0
59: 1
29: 1
14: 0
7: 1
3: 1
1: 1

in base 16 è ed (calcolato dividendo il binario in quartine)
in base 8 è 355 (calcolato dividendo il binario in terzine)

per allenarmi a casa posso usare numeri a caso