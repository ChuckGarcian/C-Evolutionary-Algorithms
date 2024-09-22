#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_rng.h>

/* GSL Helper Funtions */
void print_vector (gsl_vector *vector);
void print_matrix (const gsl_matrix * m);
void write_matrix (const gsl_matrix * m, char *filename);

void arange_matrix (gsl_matrix *x, int start);
gsl_vector *linspace(double start, double stop, int num);
void meshgrid(gsl_vector *x, gsl_matrix *x1, gsl_matrix *x2);
void matrix_set_normal (gsl_matrix *mat, const gsl_rng * rng, gsl_vector *mu, gsl_vector *sigma);

/* BBOB Functions */
gsl_vector *rastrigin_fn (gsl_matrix *x);
gsl_vector *sphere_fn (gsl_matrix *x);

