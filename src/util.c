// Description: Utility functions

#include <gsl/gsl_math.h>
#include <tensor/tensor.h>
#include "util.h"

/**
 * Implementation of rastrigin as described here: https://www.sfu.ca/~ssurjano/rastr.html
 */
gsl_vector *rastrigin_fn(gsl_matrix *x)
{
  if (x == NULL)
    return NULL;
  
  int len = x->size1;
  int num_cols = x->size2;
  gsl_vector *xcpy = gsl_vector_calloc(len); // TMP vector
  gsl_vector *sum = gsl_vector_calloc(len);  // Vector returned

  // Allocation Failure
  if (xcpy == NULL || sum == NULL)
    return NULL;

  gsl_vector_view xi;

  for (int i = 0; i < num_cols; i++)
  {
    /* Implements: x^2 - 10cos(2pix) */
    xi = gsl_matrix_subcolumn(x, i, 0, len);    // Get column vector 'x'
    gsl_vector_memcpy(xcpy, &xi.vector);        // xp <- x (Copy column)

    gsl_vector_mul(xcpy, &xi.vector);           // xp <- xp*x
    gsl_vector_scale(&xi.vector, 2 * M_PI);     // x <- 2*pi*x 
    tensor_cos(tensor_view_vector(&xi.vector)); // x <- cos(x)
    
    gsl_vector_axpby(1, xcpy, -10, &xi.vector); // x <- xp - 10x
    gsl_vector_axpby(1, &xi.vector, 1, sum);    // sum <- sum + x
  }

  double cnst = 10 * num_cols;
  gsl_vector_add_constant(sum, cnst);
  
  gsl_vector_free(xcpy);

  return sum;
}

gsl_vector *sphere_fn (gsl_matrix *x)
{
  if (x == NULL)
    return NULL;
  
  int len = x->size1;
  int num_cols = x->size2;
  gsl_vector *xcpy = gsl_vector_calloc(len); // TMP vector
  gsl_vector *sum = gsl_vector_calloc(len);  // Vector returned

  // Allocation Failure
  if (xcpy == NULL || sum == NULL)
    return NULL;

  gsl_vector_view xi;

  for (int i = 0; i < num_cols; i++)
  {
    /* Implements: Sphere */
    xi = gsl_matrix_subcolumn(x, i, 0, len);    // Get column vector 'x'
    gsl_vector_memcpy(xcpy, &xi.vector);        // xp <- x (Copy column)
    gsl_vector_mul(xcpy, &xi.vector);           // xp <- X**2
    gsl_vector_axpby(1, xcpy, 1, sum);          // sum <- sum + xP
  }

  gsl_vector_free(xcpy);
  return sum;
}

void print_vector(gsl_vector *vector)
{
  printf("Vector: \n");
  printf("[");
  for (int i = 0; i < vector->size; i++)
    printf("%g ", gsl_vector_get(vector, i));

  printf("]\n");
}

void print_matrix(const gsl_matrix *m)
{
  printf ("Matrix: \n");
  printf ("[\n");
  for (size_t i = 0; i < m->size1; ++i)
  {
    for (size_t j = 0; j < m->size2; ++j)
      printf("%g ", gsl_matrix_get(m, i, j));
    printf("\n");
  }
  printf ("]\n");
}

void arange_vector(gsl_vector *vector, int start)
{

  for (int j = 0; j < vector->size; j++)
  {
    gsl_vector_set(vector, j, start);
    start = start + 1;
  }
}
 
/*
  Set all elements in matrix 'x' to values from range(start, MSIZE). Simillar to
  numpy.arange().
*/
void arange_matrix(gsl_matrix *x, int start)
{
  gsl_vector_view row_vector;
  size_t rows, cols, iter;

  rows = x->size1;
  cols = x->size2;
  iter = start;

  // Iterate through rows
  for (int i = 0; i < rows; i++)
  {
    // Get row vector
    row_vector = gsl_matrix_subrow(x, i, 0, cols);
    arange_vector(&row_vector.vector, iter);
    iter = iter + cols;
  }
}

/* Same as Numpy Linspace */
gsl_vector *linspace(double start, double stop, int num)
{
 gsl_vector *res = gsl_vector_alloc (num);
 double step = (stop - start) / (double)(num - 1);

 for (int i = 0; i < num; i++) 
     gsl_vector_set (res, i, start + ((double)i * step));
 
  return res;
}

void meshgrid(gsl_vector *x, gsl_matrix *x1, gsl_matrix *x2) 
{
    for (int i = 0; i < x->size; i++) {
        for (int j = 0; j < x->size; j++) {
            double val_j = gsl_vector_get(x, j);
            double val_i = gsl_vector_get(x, i);
            gsl_matrix_set(x1, i, j, val_j); 
            gsl_matrix_set(x2, i, j, val_i); 
        }
    }
}

/* Writes matrix to file in a format numpy can parse with np.genfromtxt ()*/
void write_matrix (const gsl_matrix * m, char *filename)
{
  FILE *file = fopen(filename, "w");  
  
  for (size_t i = 0; i < m->size1; ++i)
  {
    if (i) fprintf(file, "\n");
    
    for (size_t j = 0; j < m->size2; ++j)
      fprintf(file, "%g ", gsl_matrix_get(m, i, j));
    
  }
  
  fclose(file);
}