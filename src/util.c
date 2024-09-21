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