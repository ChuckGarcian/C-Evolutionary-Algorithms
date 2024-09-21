#include <stdio.h>
#include <assert.h>
#include <tensor/tensor.h>

#include "es.h"
#include "util.h"

void test_rastrigin (void);

int main(void)
{
  test_rastrigin ();
  return 0;
}

void test_rastrigin (void)
{
  int size1, size2;
  gsl_matrix *mat;
  gsl_vector *result;

  size1 = 3;
  size2 = 2;

  /* Allocate and Initialize a Matrix */
  mat = gsl_matrix_alloc (size1, size2);
  arange_matrix (mat, 1);
  printf ("Printing Matrix Prior: \n");
  print_matrix (mat);
  
  result = rastrigin_fn (mat);
  printf ("Printing 'rastrigin_fn' output On Input of Matrix: \n");
  print_vector (result);
}
