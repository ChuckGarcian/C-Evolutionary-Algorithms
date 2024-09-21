#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>


void print_vector (gsl_vector *vector);
void print_matrix (const gsl_matrix * m);
void arange_matrix (gsl_matrix *x, int start);

gsl_vector *rastrigin_fn (gsl_matrix *x);
