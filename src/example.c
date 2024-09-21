#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>

/* Function to print a gsl_matrix in a human-readable way */
void
print_gslmat (const gsl_matrix * m)
{
  for (uint i = 0; i < m->size1; ++i)
    {
      for (uint j = 0; j < m->size2; ++j)
	    printf ("%g ", gsl_matrix_get (m, i, j));
      printf ("\n");
    }
}

int example (void)
{
  /* Create a matrix with 3 rows and 4 columns */
  gsl_matrix * mat = gsl_matrix_alloc (3, 4);

  /* Fill it with random numbers between 0 and 1 */
  for (uint i = 0; i < mat->size1; ++i)
    for (uint j = 0; j < mat->size2; ++j)
      gsl_matrix_set (mat, i, j, (double)rand()/RAND_MAX);

  /* Display the matrix */
  printf ("Original matrix\n");
  print_gslmat (mat);

  for (uint j = 0; j < mat->size2; ++j)
    {
      /* Create a view of the j-th column of mat */
      gsl_vector_view col = gsl_matrix_column (mat, j);
      /* Compute the l1-norm of this column (sum of entries) */
      double d = gsl_blas_dasum (&col.vector);
      /* Divide all entries of this column by its norm */
      gsl_blas_dscal (1 / d, &col.vector);
    }

  /* Display the matrix */
  printf ("Normalized matrix\n");
  print_gslmat (mat);

  /* Exit */
  gsl_matrix_free (mat);
  return 0;
}