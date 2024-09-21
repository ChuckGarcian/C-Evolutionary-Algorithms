#include <stdio.h>
#include <assert.h>
#include <tensor/tensor.h>

#define PI 3.14

void print_vector (gsl_vector *vector);
void print_matrix (const gsl_matrix * m);
void arange_matrix (gsl_matrix *x, int start);

tensor * t_asy (tensor *t, float beta);
tensor * t_osz (tensor *t);

gsl_vector *compute_z (gsl_vector *x1, gsl_vector *x2);
gsl_vector *rastrigin_fn (gsl_matrix *x);

int main (void)
{  
  int size1, size2;
  gsl_matrix *mat;
  gsl_vector *result;

  size1 = 3;
  size2 = 2;

  mat = gsl_matrix_alloc (size1, size2);
  arange_matrix (mat, 1);
  
  print_matrix (mat);  
  result = rastrigin_fn (mat);
  print_vector (result);
  
  return  0;
}

/**
 * Implementation of rastrigin as described here: https://www.sfu.ca/~ssurjano/rastr.html
 */
gsl_vector *rastrigin_fn (gsl_matrix *x)
{
  if (x == NULL)
    return NULL;

  int len = x->size1;
  int num_cols = x->size2;
  gsl_vector *xcpy = gsl_vector_calloc (len); // TMP vector
  gsl_vector *sum  = gsl_vector_calloc (len); // Vector returned

  // Allocation Failure
  if (xcpy == NULL || sum == NULL)
    return NULL;

  gsl_vector_view xi;

  for (int i = 0; i < num_cols; i++)
  { 
    xi = gsl_matrix_subcolumn (x, i, 0, len); // Get column vector 
    gsl_vector_memcpy (xcpy, &xi.vector);     // Copy into over
    
    // x1^2 - 10cos(2pix1)
    gsl_vector_mul (xcpy, &xi.vector);   
    gsl_vector_scale (&xi.vector, 2*PI);
    tensor_cos (tensor_view_vector (&xi.vector));
    gsl_vector_axpby (1, xcpy, -10, &xi.vector);
    gsl_vector_axpby (1, &xi.vector, 1, sum);
  }  
  
  double cnst = 10 * num_cols;
  gsl_vector_add_constant(sum, cnst);
  
  gsl_vector_free (xcpy);
  
  return sum;
}

void print_vector (gsl_vector *vector)
{
  printf ("[\n");
  for (int i=0; i < vector->size; i++)
    printf ("%g \n", gsl_vector_get (vector, i));
  
  printf ("]\n");
}
void print_matrix (const gsl_matrix *m)
{
  for (size_t i = 0; i < m->size1; ++i)
    {
      for (size_t j = 0; j < m->size2; ++j)
	    printf ("%g ", gsl_matrix_get (m, i, j));
      printf ("\n");
    }
}

void arange_vector (gsl_vector *vector, int start)
{
  
  for (int j = 0; j < vector->size; j++)
  {    
    gsl_vector_set (vector, j, start);
    start = start + 1;
  }

}

/*
  Set all elements in matrix 'x' to values from range(start, MSIZE). Simillar to 
  numpy.arange().
*/
void arange_matrix (gsl_matrix *x, int start)
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
    row_vector = gsl_matrix_subrow (x, i, 0, cols);    
    arange_vector (&row_vector.vector, iter);
    iter = iter + cols;
   }


}