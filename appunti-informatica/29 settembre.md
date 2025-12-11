### Caratteri alfabetici

ovviamente il computer capisce solo i numeri 0 e 1, quindi l'unico modo per utilizzare le lettere bisogna associare a ogni lettera un numero

il primo standard introdotto a questo scopo è il codice **ASCII**, dove fondamentalmente c'è una tabella a cui si associa un numero a ciascun simbolo necessario (lettere maiuscole e minuscole, punteggiatura e alcuni codici di controllo, che servivano nella preistoria)
nella tabella vediamo come sono associate lettere e simboli, ma notiamo come questo standard funziona solo per l'inglese
era scomodo anche il fatto che l'ASCII lavorasse con 7 bit, mentre il resto del mondo dell'informatica si è conformato al byte (8 bit)
alcuni codici di controllo importanti sono: il codice ASCII 0 (quindi non lo zero che scriviamo sulla tastiera) corrisponde al NUL, che indica il nulla (serviva all'inizio per mantenere le comunicazioni anche quando non c'era nulla da comunicare); il codice 9, che è praticamente il tasto tab; il 10 (0A) che serviva per andare a capo; il 13 (0D) che serve sempre per andare a capo. sotto unix si è poi deciso di limitare il tasto per andare a capo al carattere 10, solo windows ad oggi continua ad avere sia il 10 che il 13

passando poi a 8 bit, dato che gli americani non avevano più bisogno di lettere, si sono aggiunti alcuni caratteri e lettere nuove con i nuovi 128 codici disponibili. vediamo come mancano comunque molti caratteri di lingue come greco, cirillico o tutte le lingue asiatiche

non era possibile includere tutte le lingue, anche per esempio solo quelle in india, dove ci sono 9 diversi insiemi di caratteri usati da 1 milione di persone. la compagnia di stampanti Xerox propose un sistema a 16 bit per carattere, chiamato Unicode, ma presto lo spazio finì

nel 1996 si decise che con l'Unicode 2.0 si sarebbero potuti usare più di un milione di codici possibili per rappresentare caratteri di qualsiasi tipo, che ad oggi non sono ancora stati usati tutti e vengono ancora aggiornati (ora siamo all'Unicode 17.0, dove abbiamo 160 mila caratteri)

per avere 1.114.112 codici possibili dovremmo usare 21 bit, che però rappresenta un peso inutile per il computer, che invece con l'ASCII ne usava solo 8
per risolvere questo problema sono stati introdotti gli **Unicode Transformation Format** (UTF), che ci permettono di usare meno bit a seconda dei caratteri che dobbiamo utilizzare
normalmente in Occidente si usa l'UTF-8, dove si usano 8 bit alla volta, mentre in Asia a volte è più conveniente l'UTF-16 (anche se normalmente si tende a utilizzare sempre l'UTF-8)

ci sono due idee alla base dell'UTF-8: 
- bisogna codificare i numeri a blocchi di 8 bit alla volta, i numeri piccoli possono usare meno byte, i numeri grandi ne usano di più
- bisogna che tutti i codici ASCII vengano codificati mettendo il bit più significativo uguale a zero, e poi fare il numero con gli spazi rimanenti; se il codice richiede un numero più grande di quelli consentiti a 7 bit, possiamo già capire che stiamo utilizzando 2 byte se il codice parte con 110, stessa cosa se uso 3 byte partirà da 1110. poi i bit che mi servono per fare il numero li scrivo dopo lo zero dell'110, mentre il byte dopo comincia sempre con 10. si è deciso di utilizzare i primi 2 bit di tutti gli altri byte in modo da riconoscere se ci si trova all'inizio di un code point o in mezzo (quindi se un byte non inizia con 11, so che non è all'inizio del mio numero) slide **Unicode Transformation Format (UTF)**

un file txt con scritto "ciao" è grande 4 byte, quindi per ogni carattere il computer ha usato 8 bit
mentre "cioè" sono 5 byte, perchè la e accentata mi servono più di 7 bit

sul sito compart.com possiamo vedere i bit in esadecimale usati da ogni carattere, quindi vederne il codice ASCII 
la è ha codice (U+00E8), dove 00E8 in binario è 0000.0000.1110.1000, dove quindi i bit minimi sono 8 (l'1 più significativo si trova in posizione 8).
visto che non siamo entro i 7 bit, ci tocca passare agli 11 bit, con cui invece possiamo rappresentarlo

è: U+00E8
binario: 0000.0000.**1**110.1000
bit minimi: 8
categoria UTF-8: 11 bit = 2 byte
scritto a 11 bit: 00011101000
UTF-8:  110xxxxx 10xxxxxx diventa **110**00011 **10**101000
UTF-8 in base 16: C3 A8

E8 in base 16 -> 232

U+AC10 (questo mi richiede 16 bit)
binario: 1010.1100.0001.0000
bit minimi: 16
categoria UTF-8: 16 bit = 3 byte
UTF-8: 1110 xxxx 10xx xxxx 10xx xxxx diventa 1110 1010 1011 0000 1001 0000
in base 16: EA B0 90

fai la codifica di 😍 sapendo che è U+1F60D
binario: 0001.1111.0110.0000.1101
bit minimi: 17
categoria: UTF-8: 21 bit = 4 byte
scritto a 21 bit: 0.0001.1111.0110.0000.1101
UTF-8: 1111 0xxx 10xx xxxx 10xx xxxx 10xx xxxx diventa 1111 0000 1001 1111 1001 1000 1000 1101

in base 16: F0 9F 98 8D

### Endianness

tutto l'hardware di memorizzazione funziona a byte, non a bit, che quindi andrebbero raggruppati sempre a gruppi di 8 bit
prendiamo un numero a 16 bit AC10: per memorizzarlo useremo 2 byte
immaginiamo che la memoria del computer sia organizzata a celle che contengono 8 bit, quindi un byte (guarda il disegno nella slide **Endianness**)
immaginiamo di avere le due celle | AC | | 10 |. notiamo che il byte più significativo è AC, mentre 10 è il meno significativo. in base a come numeriamo le cellule, possiamo associare all'indirizzo più basso il byte più significativo, oppure associarlo al byte meno significativo. in pratica, possiamo partire o dal più significativo o dal meno significativo. 
se associo all'indirizzo più basso il byte più significativo, questo ordinamento prende il nome di **big-endian**, mentre se metto il byte meno significativo (quindi in ordine crescente) lo chiamo **little-endian**. 
questi due nomi nascono da una guerra tra Motorola, che lavorava in big-endian, e Intel, che usava il little-endian. oggi si usa prevalentemente il little-endian, a parte per i sistemi di telecomunicazioni, che preferiscono il big-endian, anche detto **network order**.

little-endian e big-endian fanno riferimento solo al byte, non all'organizzazione dei bit all'interno del byte

in UTF-16 esiste un carattere detto **Byte Order Mark** (BOM, di codice FEFF) che stabilisce la endianness del file. prendiamo sempre AC10, se non so se è in little o big endian, esso potrebbe essere sia AC10 che 10AC. se so che è in little-endian è 10AC, mentre se è in big-endian è AC10. per saperlo, uso il BOM: se all'inizio del file leggo FEFF so che ci troviamo in big-endian, mentre se leggo FFFE ci troviamo in little-endian