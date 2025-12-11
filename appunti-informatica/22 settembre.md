### I numeri con la virgola

anche nel rappresentare i numeri con la virgola utilizziamo un sistema posizionale, nel quale ogni numero dopo la virgola è una potenza negativa della base
vedi la sommatoria sulla slide, ma è sempre uguale
è possibile che i numeri razionali siano rappresentabili con un numero finito di cifre cambiando base: 
1/3 in base 3 diventa 0,1; mentre 1/2 in base 3 diventa 0,11111...
invece, se volessimo rappresentare 1/6 in base 3, dovremmo mettere infinite cifre (quindi 0,011111...), che è anch'esso periodico.
in base 10, per ottenere una rappresentazione con la virgola con un numero limitato di cifre, bisogna che al denominatore ci siano solo potenze di 2 e 5 (quindi i fattori primi che compongono la base 10). se invece al denominatore abbiamo fattori che non compongono la base, abbiamo un numero illimitato di cifre
l'unico modo esatto di esprimere frazioni come 1/3 in base 10 è usare numeri periodici, quindi rappresentare infiniti numeri

dunque il sistema posizionale consente di rappresentare esattamente qualsiasi numero razionale, a patto che sia possibile utilizzare un numero infinito di cifre. ciò introduce alcuni problemi nel momento in cui limitiamo il numero di cifre.

come nei numeri interi, esiste un algoritmo anche per fare la conversione di base dei numeri con la virgola (slide **Conversione di base**)
la dimostrazione non va saputa 
la parte non intera dei numeri si chiama *mantissa*, cioè la parte del numero minore di 1 (si chiama decimale normalmente perchè siamo in base 10)
nella dimostrazione, la mantissa è la sommatoria con i=-1, mentre il primo termine è la parte intera (che sappiamo già convertire)
sostanzialmente, quello che si fa è moltiplicare la mantissa per la base per farla diventare un numero intero (quindi spostare le cifra a sinistra)
questa proprietà del sistema posizionale vale per ogni base

consideriamo 12,8125 volendolo rappresentare in base 4
partiamo dalla parte intera: 
12 in base 4 è 30
0,8125 * 4 = 3,25, quindi possiamo aggiungere un ,3 alla base 4
0,25 * 4 = 1, quindi possiamo aggiungere un 1 alle cifre decimali
quindi 12,8125 si rappresenta 30,31 in base 4

proviamo sempre 12,8125 in base 5
12 in base 5 è 22
0,8125 * 5 = 4,0625, quindi possiamo aggiungere un 4 alle cifre decimali
iniziamo già a notare però che in questo caso le cifre decimali non stanno diminuendo
0,0625 * 5 = 0,3125, quindi aggiungiamo uno 0 alle cifre decimali
0,3125 * 5 = 1,5625, quindi aggiungiamo un 1 alle cifre decimali
0,5625 * 5 = 2,8125, quindi aggiungiamo un 2 alle cifre decimali
0,8125 -> è lo stesso numero da cui siamo partiti, quindi da qui sappiamo che il numero diventa periodico
quindi la rappresentazione di 12,8125 in base 5 sarà 22,4012 con la matissa periodica.

qualsiasi numero non periodico in base 2 si può scrivere non periodico in base 10, perchè ovviamente ogni numero non periodico in base 2 può avere al denominatore solo delle potenze del 2, che quindi vanno bene anche in base 10. non vale il contrario, a causa del fattore primo 5 che va bene in base 10 ma non in base 2.

0,1 per esempio non si può rappresentare al computer esattamente, a meno che non approssimiamo la nostra rappresentazione, il che può portare a dei problemi con numeri molto grandi.

## Numeri con segno

in matematica la rappresentazione dei numeri negativi è molto semplice, basta mettere un meno davanti al numero
se volessimo usare la stessa logica "umana" nei computer, avremmo bisogno di spazio processuale identico per fare le operazioni di somma e differenza, separandole, ma ciò è molto poco efficiente.

in informatica ovviamente dobbiamo porre un limite ai numeri che il computer può memorizzare, quindi limitare il numero di cifre. in questo modo alcune operazioni restano possibili, altre non lo sono più (slide **Rappresentazione con un numero finito di cifre**)

mettiamo conto di limitare le cifre in base 10 a una sola cifra: già un'addizione semplicissima come 8+3 farebbe 1, visto che non siamo in grado di usare 2 cifre
oppure, se limitassimo a 2 cifre, 68 + 37 diventerebbe 25.
questa si chiama *aritmetica modulare*, dove se superiamo il numero massimo consentito, si riparte da zero.
il fenomeno di superamento del massimo valore rappresentabile è detto *overflow*, che ci impone di ripartire da capo coi numeri.
un buon modo di vedere l'aritmetica modulare è dividere un cerchio in n parti, dove la somma ci fa spostare in senso orario e quindi se andiamo oltre il limite si riparte da zero. se volessimo fare la sottrazione, la questione è la stessa, ma ci spostiamo verso sinistra. quindi in modulo 10, 3-5=8

per sapere quante combinazioni possibili possiamo formare, si fa base elevato al numero di cifre che possiamo usare (per esempio, su un lucchetto a 4 cifre possiamo fare 10^4 combinazioni), e lo stesso vale per i numeri in base 2 (con 64 bit possiamo rappresentare 4 miliardi di combinazioni)

dall'aritmetica modulare nasce l'idea di usarla per rappresentare i numeri negativi (per esempio, in modulo 10 il 9 può valere anche -1), in modo da avere sia i negativi che i positivi nelle stesse combinazioni. per non avere sovrapposizioni, si è deciso di tenere metà dei valori associati ai numeri positivi, mentre l'altra metà ai numeri negativi (slide **Numeri negativi**)
tuttavia in questo modo, fare qualcosa come 4+2 diventa -4, quindi ho un altro overflow.
dunque non si è totalmente risolto il problema, ma almeno abbiamo introdotto i numeri negativi.

#### Rappresentazione in complemento alla base

nel caso del computer, in complemento a 2
consideriamo di lavorare in base b con n cifre, la relazione rappresentata nella slide ci da una regola che possiamo utilizzare
sostanzialmente, se i numeri sforano (quindi sono maggiori o uguali a (b^n)/2) il numero che vogliamo va sottratto a b^n (guarda la regola fatta bene, ma è abbastanza intuitiva)
tutto ciò perchè vogliamo fare le sottrazioni allo stesso modo con cui facciamo le somme, e possiamo fare ciò senza andare in senso antiorario, ma andando avanti in senso orario di (b^n - x), contando che vogliamo sottrarre di x.

mettiamo che voglio fare 130-97 in modulo 1000: si può riscrivere 130+(-97), che nella nostra aritmetica modulare diventa 130+(1000-97), che non farà 1033, ma solo 33. così questo meccanismo funziona.

tutti i microprocessori adesso utilizzano l'aritmetica in complemento a 2, che è l'unica base con cui dobbiamo saper fare queste operazioni (slide **Complemento a 2**)
per esempio, a 4 bit in complemento a 2 il numero 1010 è -6 invece di 10. così il massimo che posso rappresentare è 7, e il minimo è -8. 
in tutte le rappresentazioni in complemento alla base, c'è un numero in più tra i negativi rispetto ai positivi (perchè i positivi comprendono lo zero)
guardando la tabella nella slide, vediamo come tutti i numeri in base 2 che iniziano con 1 sono negativi. ciò è dimostrato nella slide **Peculiarità della base 2**, e possiamo fare la stessa osservazione anche con gli altri bit (per esempio se il terzo bit è 1, il numero è 4)
tutte le dimostrazioni non saranno da sapere, non sono veramente importanti
nel complemento a 2, la prima cifra fa tutta la differenza: se è 1 il numero è negativo, perchè, essendo una potenza negativa, la somma di tutte le altre cifre non arriverà mai al valore della prima cifra

prendiamo un numero a 8 bit: 1011.0001
senza contesto non possiamo sapere cosa rappresenta, ma diciamo in questo caso che stiamo rappresentando dei numeri interi a 8 bit. solo con questa informazione non possiamo ancora dire se il numero è positivo o negativo, in quanto abbiamo visto diverse rappresentazioni dei numeri interi a 8 bit. se infine diciamo che si tratta di un intero in complemento a 2, possiamo essere sicuri che questo numero sia negativo.

è fondamentale sapere di che rappresentazione si tratta, soprattutto nell'ottica di quando inizieremo a programmare.

1011.0001 in complemento a 2 fa: -128 + 32 + 16 + 1 = -79

come posso ottenere l'opposto di un numero rappresentato in complemento a 2? ci sono due algoritmi: invertire tutti i bit del numero e poi si somma 1 (quindi, usando l'esempio di prima con 1011.0001, diventa 0100.1111), oppure si copiano tutti i bit da destra a sinistra fino al primo 1 incluso, poi inverto gli altri.

se considero un numero a 8 bit con segno 1000.0000, l'opposto sarà uguale (sempre 1000.0000) in quanto il numero più negativo possibile non ha un corrispettivo nei positivi, che arrivano allo stesso modulo -1, quindi c'è overflow. in questo caso infatti il numero vale -128, ma i positivi arrivano solo fino a 127.
quindi, se ho dei numeri in base b a n bit, in complemento a base b l'intervallo di numeri che posso rappresentare sarà [ -b^n, b^n-1 ].

se devo limitare il numero di cifre disponibili nel rappresentare numeri con la virgola cambia poco, devo solamente decidere quante cifre dedicare agli interi e quanti alla mantissa.
slide **Numeri in virgola fissa**
a 8 bit tuttavia possiamo rappresentare dei numeri con la virgola molto poco precisi, e anche se usassimo più bit (16 o 32) le cifre non diventano un numero enorme. per questo non è molto efficiente pretendere sempre una precisione esagerata, soprattutto se stiamo lavorando con numeri molto grandi.
è possibile approssimare usando la notazione scientifica, usando 4 cifre (1 intera e 3 di mantissa) e le potenze di 10 (**Numeri in virgola mobile**). il grande limite di questo metodo è che, per esempio, 10001 non lo posso rappresentare, dato che con 3 cifre decimali non riesco a rappresentare le unità se sto moltiplicando per 10^4. di conseguenza sto barattando la precisione per una migliore efficienza, e dunque non posso avere grandi numeri con una buona precisione.

lo **standard IEEE 754** è quello più diffuso nel mondo informatico, utilizzato per il calcolo scientifico in quanto è approssimato (mentre per i soldi non si usa questo), che definisce il formato per la rappresentazione dei numeri in virgola mobile. 
ci sono diversi formati in base alla precisione, di cui i più importanti sono la precisione singola (32 bit) e la precisione doppia (64 bit)
un numero in virgola mobile viene rappresentato in 3 parti: segno, esponente e mantissa. manca la parte intera, che viene omessa ed è sempre 1.

in un numero a 32 bit, questi vengono suddivisi così: 1 bit per il segno, 8 bit per l'esponente e 23 bit per la mantissa. il valore dei numeri normalizzati in questo modo si può calcolare con la formula: (-1)^s * 1.m * 2^(E-127)
dove E è il campo dell'esponente (ed E=e+127)

facciamo un esempio
abbiamo il numero 16.25, che dobbiamo scrivere in singola precisione secondo IEEE 754
innanzitutto lo scriviamo in binario
16 in base 2 diventa 10000
0,25 * 2 = 0,5 quindi aggiungo 0
0,5 = 1 quindi aggiungo 1
16.25 in binario è 10000,01, che in notazione scientifica diventa 1,000001 * 2^4 (perchè in un numero binario spostare la virgola verso sinistra è come dividere per 2)

quindi segno = + (non si usa il complemento a 2)
mantissa = 0000010000000000 fino ad arrivare a 23 bit
esponente = 4
E (campo esponente) = 4 + 127 = 3 + 128 = 1000.0011 (faccio + 128 invece di 127 perchè così devo solo aggiungere un numero a 1000.0000)

a 32 bit, il numero diventa 0 | 1000.0011 | 00000100000000000000000
che convertito in esadecimale è 41820000

posso anche esercitarmi a fare l'esercizio inverso

proviamo a rappresentare l'intero con segno a 16 bit 0010.1111.1001.1001 con le altre basi che conosciamo:
base 16: 2f99
base 8 (parto da destra): 27631

scriviamo -42 secondo IEEE 754:
binario: 101010
notazione: 1,01010 * 2^5 
quindi segno = -
mantissa = 01010000000000000000000
campo esponente (E) = 5 + 127 = 4 + 128 = 1000.0100
a 32 bit quindi è 1100.0010.0010.1000.0000.0000.0000.0000
esadecimale: c2280000

anche qua per esercitarmi posso scegliere numeri a caso e provare a convertire in IEEE 754

c1a80000 <- provalo a casa


### Numeri denormalizzati

Se abbiamo dei numeri molto piccoli (tra cui lo zero), quindi quando E=0, abbiamo dei numeri denormalizzati con una matissa molto piccola, calcolati con: (-1)^s * 0.m * 2^-126 
quando invece E=255 abbiamo tre casi possibili: possiamo avere degli infiniti se m=0, mentre se m non è zero il numero è NaN, ovvero Not a Number

nella slide **Numeri in singola precisione** possiamo vedere come il numero più grande rappresentabile non ha una buona precisione data la sua grandezza. in basso possiamo vedere come la precisione diminuisca man mano che aumentiamo le potenze del due, dato che possiamo sempre solo rappresentare 2^23 cifre per intervallo.