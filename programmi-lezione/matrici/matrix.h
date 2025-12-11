#pragma once

#include <stdlib.h>

struct matrix{
    size_t rows, cols;
    double *data;
};

extern struct matrix *new_mat(size_t rows, size_t cols);
extern void mat_print(struct matrix *m);
extern struct matrix *mat_ceil_inplace_struct(struct matrix *m);
extern void mat_delete(struct matrix *m);