#include "matrix.h"
#include <stdio.h>
#include <math.h>

void mat_print(struct matrix *m){
    for (size_t r = 0; r < m->rows; ++r){
        for (size_t c = 0; c < m->cols; ++c){
            printf("% .1f ", m->data[r*m->cols+c]);
        }
        printf("\n");
    }
}

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

struct matrix *new_mat(size_t rows, size_t cols)
{
    struct matrix *ris = malloc(sizeof(struct matrix));
    ris->rows = rows;
    ris->cols = cols;
    ris->data = malloc(rows * cols * sizeof(double));

}
