#include <stdlib.h>
#include <string.h>

int arr_minval(int *x, size_t n){
    int min=x[0];
    for (size_t i = 1; i<n; ++i){
        if(x[i]<min){
            min=x[i];
        }
    }
    return min;
}

/* vogliamo riscrivere arr_minval in modo che vada bene sia 
per i double che per gli int
un modo potrebbe essere usare una macro */

#define MAKE_ARR_MIN_VAL(T)             \
T arr_minval_##T(T *x, size_t n){        \
    T min=x[0];                         \
    for (size_t i = 1; i<n; ++i){       \
        if(x[i]<min){                   \
            min=x[i];                   \
        }                               \
    }                                   \   
    return min;                         \
}                                       \

MAKE_ARR_MIN_VAL(int)
MAKE_ARR_MIN_VAL(double)

/* se vogliamo usare delle struct, questo metodo non funziona, 
dato che staremmo facendo dei confronti tra stringhe */

/* ci può venire in aiuto un void pointer, con una funzione
che invece di ritornare il minimo valore, ritorna la posizione 
ma ci serve uno strumento per cambiare il comportamento delle
funzioni in base ai tipi di dato */

/* introduciamo il concetto di puntatore a funzione, dichiarata
in questo modo:
int (*f)(char);*/

/* per riuscire a usare il void pointer, mi serve sapere di quanti
spazi il for deve andare avanti quando sta scorrendo l'array
per fare questo mi serve accettare un altro parametro*/
/* la compare è un puntatore a funzione: sto passando una funzione
alla funzione arr_minpos. devo usarla perchè non posso usare 
il maggiore tra due elementi di un null pointer */
/* trasformo i null pointer in puntatori a char perchè non posso
neanche fare addizione con un null pointer */

size_t arr_minpos(void *x, size_t n, 
    size_t elemsize, int compare(void*,void*)){
    size_t min;
    for (size_t i = 1; i<n; ++i){
        if(compare((char*)x + min*elemsize, 
        (char*)x + i*elemsize)>0){
            min=i;
        }
    }
    return min;
}

typedef struct persona{
    char nome[200];
    int eta;
} persona;

// qua definisco la compare, ne dovrò fare una per ogni tipo

int intcmp(void *vpa, void *vpb){
    int *pa = vpa;
    int *pb = vpb;
    int a = *pa;
    int b = *pb;

    if(a==b){
        return 0;
    }
    if (a>b){
        return 1;
    }
    return -1;

}

int doublecmp(const void *vpa, const void *vpb){
    const double *pa = vpa;
    const double *pb = vpb;
    const double a = *pa;
    const double b = *pb;

    if(a==b){
        return 0;
    }
    if (a>b){
        return 1;
    }
    return -1;

}

int etacmp(void *vpa, void *vpb){
    persona *pa = vpa;
    persona *pb = vpb;
    return intcmp(&pa->eta, &pb->eta);

}

int nomecmp(void *vpa, void *vpb){
    persona *pa = vpa;
    persona *pb = vpb;
    return strcmp(pa->nome, pb->nome);

}

/* esistono funzioni nella libreria standard che fanno queste cose */

int main(void){
    
    int a[]={6,-5,1,9,21,-3,7};
    int m = arr_minval(a, 7);

    double a2[]={6,-5,1,9,21,-3,7};
    double m2 = arr_minval_double(a2, 7);

    size_t m = arr_minpos(a, 7, sizeof(int), intcmp);

    // funzione già fatta nella libreria standard
    // c'è comunque bisogno di una funzione di compare corretta
    qsort(a, 7, sizeof(int), intcmp);

    /* esiste una funzione per cercare un numero all'interno di un
    array */
    int key = 21;
    int *p;

    p = bsearch(&key, a, 7, sizeof(int), intcmp);

    return 0;
}

// il codice intero è su moodle