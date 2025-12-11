#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// fare una struct può essere comodo per funzioni dove devo ritornare più cose
struct matrix{
    size_t rows, cols;
    double *data;
};

// posso fare la macro per scrivere di meno ogni volta che devo tirare fuori l'elemento
#define E(m, r, c) (m)->data[(r)*(m)->cols+(c)];

// funzione che printa la matrice
void mat_print(struct matrix *m){
    for (size_t r = 0; r < m->rows; ++r){
        for (size_t c = 0; c < m->cols; ++c){
            printf("% .1f ", m->data[r*m->cols+c]);
        }
        printf("\n");
    }
}

// funzione che mi permette di arrotondare ogni elemento all'estremo superiore
void mat_ceil(size_t rows, size_t cols, double *data){
    for (size_t r = 0; r < rows; ++r){
        for (size_t c = 0; c < cols; ++c){
            size_t i = r*cols+c;
            data[i]=ceil(data[i]);
        }
    }
}

// versione inplace di mat_ceil, che cioè restituisce una nuova matrice
double* mat_ceil_inplace(size_t rows, size_t cols, const double *data){
    // non possiamo dare ad un array dimensione non costante
    // quindi non possiamo scrivere double ris[rows*cols];
    double *ris = malloc(rows*cols*sizeof(double));
    for (size_t r = 0; r < rows; ++r){
        for (size_t c = 0; c < cols; ++c){
            size_t i = r*cols+c;
            ris[i]=ceil(data[i]);
        }
    }

    return ris;
}

// versione inplace, con struct
struct matrix* mat_ceil_inplace_struct(struct matrix *m){
    struct matrix *ris = malloc(sizeof(struct matrix));
    ris->rows = m->rows;
    ris->cols = m->cols;
    ris->data = malloc(m->rows * m->cols * sizeof(double));
    // non posso fare sizeof(m->data), perchè m->data è un puntatore ad array, quindi la sua dimensione è sempre la stessa
    // non posso sapere quanti sono i dati a cui punta un puntatore
    for (size_t r = 0; r < ris->rows; ++r){
        for (size_t c = 0; c < ris->cols; ++c){
            size_t i = r*ris->cols+c;
            ris->data[i]=ceil(m->data[i]);
        }
    }

    return ris;
}

void mat_delete(struct matrix *m){
    if (m!=NULL){
        free(m->data);
        free(m);
    }
}

int main(void){

    // ci servono 12 double, che possiamo riservare in una variabile automatica o allocata
    // decidiamo di usare un array (memoria automatica)

    double data[3*4] = {
        5, 8,   9,  3.2,
        7, 1.1, 2, -4,
        1, 2,   3,  4
    };

    struct matrix M = {3, 4, data};

    mat_print(&M);

    struct matrix* A = mat_ceil_inplace_struct(&M);

    mat_print(A);

    mat_delete(A);

    // tutte le operazioni sulle matrici si faranno con questo doppio for
    // per avere tutti gli elementi con una sola cifra decimale potevo scrivere %f.1
    // se invece voglio tutti gli elementi allineati, posso scrivere
    // % .1f, in modo da tenere sempre gli stessi spazi

    return 0;
}