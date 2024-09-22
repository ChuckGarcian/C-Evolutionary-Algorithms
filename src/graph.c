#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <tensor/tensor.h>

#include "es.h"
#include "util.h"

int main (void)
{
  int x_min = -5;
  int x_max = 5;
  int num_points_per_dim = 100;
    
  /* Setup vector and matrix Objects */  
  gsl_vector *x  = linspace (x_min, x_max, num_points_per_dim);
  gsl_matrix *tmp = gsl_matrix_alloc (num_points_per_dim, 2);
  gsl_matrix *x1 = gsl_matrix_alloc (num_points_per_dim, num_points_per_dim);
  gsl_matrix *x2 = gsl_matrix_alloc (num_points_per_dim, num_points_per_dim);
  gsl_matrix *y_res = gsl_matrix_alloc (num_points_per_dim, num_points_per_dim);
  meshgrid (x, x1, x2);
  
  /* Compute Graphing Data */
  for (int i = 0; i < num_points_per_dim; i++)
  {    
    gsl_vector *res_row;
    
    gsl_vector_view x1_row = gsl_matrix_subrow(x1, i, 0, num_points_per_dim);
    gsl_vector_view x2_row = gsl_matrix_subrow(x2, i, 0, num_points_per_dim); 
        
    gsl_matrix_set_col (tmp, 0, &x2_row.vector);
    gsl_matrix_set_col (tmp, 1, &x1_row.vector);
    
    res_row = rastrigin_fn (tmp);
    gsl_matrix_set_row (y_res, i, res_row);
    gsl_vector_free (res_row);
    
  }
  
  /* Save Graphing Data */  
  write_matrix (x1, "src/x1.txt");
  write_matrix (x2, "src/x2.txt");  
  write_matrix (y_res, "src/y_res.txt");
  
  /* Plot the Graphed Data */
  int ret = system("python3 src/plot.py");
  if (ret == -1)
  {
    fprintf(stderr, "Error starting Python script\n");
    return 1;
  }

  printf ("Done -- Graph Saved\n");
  
  return 0;
}